#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include<iomanip>
#include"auxiliary.h"

using namespace std;

int LINES = 1;
bool If_Error = false;
string File_Opened = "./.txt";
string File_Output = "./.dyd";
string Error_File_Name = "./.err";

int main(int argc,char *argv[])
{
	File_Opened.insert(2, argv[1]);
	File_Output.insert(2, argv[1]);
	Error_File_Name.insert(2, argv[1]);
	Analysis(Getprogram());
	system("pause");
	return 0;
}

bool IfCharacter(char chara)
{
	if ((chara >= 'a'&&chara <= 'z') || (chara >= 'A'&&chara <= 'Z'))
		return true;
	else
		return false;
}

bool IfNumber(char chara)
{
	if (chara >= '0'&&chara <= '9')
		return true;
	else
		return false;
}

bool IfCharacterEqual(char str1[], const char str2[], int num = 0)
{
	while (num >= 0)
	{
		if (str1[num] != str2[num])
			return false;
		else
			num--;
	}
	return true;
}

bool IsInvalid(char charc)
{
	if ((charc >= 'a'&&charc <= 'z') || (charc >= '0'&&charc <= 62))
		return false;
	else if (charc == '\n' || charc == '(' || charc == ')' || charc == '*')
		return false;
	else
		return true;
}

string Getprogram()
{
	string text, temp;
	ifstream File_out;

	File_out.open(File_Opened);
	if (!File_out)
	{
		cout << "File Open Failed" << endl;
		exit(0);
	}
	
	while (!File_out.eof())
	{
		//File_out >> temp;
		getline(File_out, temp);
		text = text + temp + "\n";
	}
	File_out.close();
	text += '\0';
	return text;
}

void FileStore(string temp, string code)
{
	if (If_Error)
	{
		If_Error = false;
		system("pause");
		return;   //文件打开失败
	};
	ofstream File_out;
	File_out.open(File_Output, ios_base::out | ios_base::app);//追加写
	File_out.fill(' ');
	cout <<left<<setw(16)<< temp << " " << code << endl;
	File_out << left<<setw(16)<<temp << " " << code << endl;
	File_out.close();
}

void ErrorHandling(int Error_Code)
{

	ofstream Error_File;
	Error_File.open(Error_File_Name, ios_base::out | ios_base::app);
	switch (Error_Code)
	{
	case 0:Error_File << "***LINE: " << LINES << "  Invalid Character" << endl; break; //非法字符
	case 1:Error_File << "***LINE: " << LINES << "  : does not match" << endl; break;   //：不匹配
	case 2:Error_File << "***LINE: " << LINES << "  identifier is too long" << endl; break;  //标识符溢出
	}
	Error_File.close();
}

void Analysis(string text)
{
	char Buffer[20];
	char *now_pointer = &text[0], *next_pointer = &text[1];
	int i = 0;
	while (*next_pointer != '\0')
	{

		if (*now_pointer == ' ')// 0->0
		{
			now_pointer++;
			next_pointer++;
			continue;
		}
		else if (IfCharacter(*now_pointer))// 0->1
		{
			while (IfCharacter(*next_pointer) || IfNumber(*next_pointer))
			{
				Buffer[i++] = *now_pointer;
				if (IsInvalid(*now_pointer))
				{
					If_Error = true;
					ErrorHandling(0);
				}
				now_pointer++;
				next_pointer++;
			}
			Buffer[i++] = *now_pointer;
			if (i > 16) ErrorHandling(2);

			if (IfCharacterEqual(Buffer, "begin", 4)) FileStore(Buffer, "01");
			else if (IfCharacterEqual(Buffer, "end", 2)) FileStore(Buffer, "02");
			else if (IfCharacterEqual(Buffer, "integer", 6)) FileStore(Buffer, "03");
			else if (IfCharacterEqual(Buffer, "if", 1)) FileStore(Buffer, "04");
			else if (IfCharacterEqual(Buffer, "then", 3)) FileStore(Buffer, "05");
			else if (IfCharacterEqual(Buffer, "else", 3)) FileStore(Buffer, "06");
			else if (IfCharacterEqual(Buffer, "function", 7)) FileStore(Buffer, "07");
			else if (IfCharacterEqual(Buffer, "read", 3)) FileStore(Buffer, "08");
			else if (IfCharacterEqual(Buffer, "write", 4)) FileStore(Buffer, "09");
			else FileStore(Buffer, "10");
			while (i-- != 0)
				Buffer[i] = NULL;
			i = 0;
		}
		else if (IfNumber(*now_pointer))//���� 0->3
		{
			while (IfNumber(*next_pointer)) //3->3
			{
				Buffer[i++] = *now_pointer;
				if (IsInvalid(*now_pointer))
				{
					ErrorHandling(0);
					If_Error = true;
				}
				now_pointer++;
				next_pointer++;
			}
			Buffer[i++] = *now_pointer;
			FileStore(Buffer, "11");
			while (i-- != 0)
				Buffer[i] = NULL;
			i = 0;
		}
		else if (*now_pointer == '=')
			FileStore("=", "12");
		else if (*now_pointer == '-')
			FileStore("-", "18");
		else if (*now_pointer == '*')
			FileStore("*", "19");
		else if (*now_pointer == '(')
			FileStore("(", "21");
		else if (*now_pointer == ')')
			FileStore(")", "22");
		else if (*now_pointer == '<')//0->10
		{
			if (*next_pointer == '=') //10->11
			{
				FileStore("<=", "14");
				now_pointer++;
				next_pointer++;
			}
			else if (*next_pointer == '>') //10->12
			{
				FileStore("<>", "13");
				now_pointer++;
				next_pointer++;
			}
			else  //10->13
			{
				FileStore("<", "15");
			}
		}
		else if (*now_pointer == '>')
		{
			if (*next_pointer == '=') //14->15
			{
				FileStore(">=", "16");
				now_pointer++;
				next_pointer++;
			}
			else  //14->16
				FileStore(">", "17");
		}
		else if (*now_pointer == ':')
		{
			if (*next_pointer == '=') //ƥ��ɹ�
			{
				FileStore(":=", "20");
				now_pointer++;
				next_pointer++;
			}
			else
			{
				ErrorHandling(1);
			}
		}
		else if (*now_pointer == ';')
		{
			FileStore(";", "23");
		}
		else   //0->21
		{
			while (i-- != 0)
				Buffer[i] = NULL;
			i = 0;
			if (*now_pointer == '\n')
			{
				FileStore("EOLN", "24");
				LINES++;
			}
			else
				ErrorHandling(0);
		}
		now_pointer++;
		next_pointer++;
	}
	FileStore("EOF", "25");
}
