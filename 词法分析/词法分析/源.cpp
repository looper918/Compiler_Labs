#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include"auxiliary.h"

using namespace std;

int main(void)
{
	string temp;
	cout << "Input File name:" << endl;
	cin >> temp;
	File_Opened.insert(8, temp);
	File_Output.insert(8, temp);
	Error_File_Name.insert(8, temp);
	Analysis(Get_program());
	system("pause");
	return 0;
}

bool If_Character(char chara)
{
	if ((chara >= 'a'&&chara <= 'z') || (chara >= 'A'&&chara <= 'Z'))
		return true;
	else
		return false;
}

bool If_Number(char chara)
{
	if (chara >= '0'&&chara <= '9')
		return true;
	else
		return false;
}

bool If_Character_Equal(char str1[], const char str2[], int num = 0)
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

bool Is_Invalied(char charc)
{
	if ((charc >= 'a'&&charc <= 'z') || (charc >= '0'&&charc <= 62))
		return false;
	else if (charc == '\n' || charc == '(' || charc == ')' || charc == '*')
		return false;
	else
		return true;
}

string Get_program()
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

void File_Store(string temp, string code, int num = 1)
{
	if (If_Error)
	{
		cout << "Error" << endl;
		return;   //出错时不打印该行
	}
	temp.resize(num);
	ofstream File_out;
	File_out.open(File_Output, ios_base::out | ios_base::app);//以追加写模式打开文档
	while (temp.size() < 16)
		temp = " " + temp;
	cout << temp << " " << code << endl;
	File_out << temp << " " << code << endl;
	File_out.close();
	If_Error = false;
}

void Error_Handling(int Error_Code)
{

	ofstream Error_File;
	Error_File.open(Error_File_Name, ios_base::out | ios_base::app);
	switch (Error_Code)
	{
	case 0:Error_File << "LINE: " << LINES << "  Invalid Character" << endl; break; //非法字符
	case 1:Error_File << "LINE: " << LINES << "  : does not match" << endl; break;   //：不匹配
	case 2:Error_File << "LINE: " << LINES << "  identifier is too long" << endl; break;  //长度溢出
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

		if (*now_pointer == ' ')//空格 0->0
		{
			now_pointer++;
			next_pointer++;
			continue;
		}
		else if (If_Character(*now_pointer))//字母 0->1
		{
			while (If_Character(*next_pointer) || If_Number(*next_pointer))
			{
				Buffer[i++] = *now_pointer;
				if (Is_Invalied(*now_pointer))
				{
					If_Error = true;
					Error_Handling(0);
				}
				now_pointer++;
				next_pointer++;
			}
			Buffer[i++] = *now_pointer;
			if (i > 16) Error_Handling(2);

			if (If_Character_Equal(Buffer, "begin", 4)) File_Store(Buffer, "01", i);
			else if (If_Character_Equal(Buffer, "end", 2)) File_Store(Buffer, "02", i);
			else if (If_Character_Equal(Buffer, "integer", 6)) File_Store(Buffer, "03", i);
			else if (If_Character_Equal(Buffer, "if", 1)) File_Store(Buffer, "04", i);
			else if (If_Character_Equal(Buffer, "then", 3)) File_Store(Buffer, "05", i);
			else if (If_Character_Equal(Buffer, "else", 3)) File_Store(Buffer, "06", i);
			else if (If_Character_Equal(Buffer, "function", 7)) File_Store(Buffer, "07", i);
			else if (If_Character_Equal(Buffer, "read", 3)) File_Store(Buffer, "08", i);
			else if (If_Character_Equal(Buffer, "write", 3)) File_Store(Buffer, "09", i);
			else File_Store(Buffer, "10", i);
			while (i-- != 0)
				Buffer[i] = NULL;
			i = 0;
			If_Error = false;
		}
		else if (If_Number(*now_pointer))//数字 0->3
		{
			while (If_Number(*next_pointer)) //3->3
			{
				Buffer[i++] = *now_pointer;
				if (Is_Invalied(*now_pointer))
				{
					Error_Handling(0);
					If_Error = true;
				}
				now_pointer++;
				next_pointer++;
			}
			Buffer[i++] = *now_pointer;
			File_Store(Buffer, "11");
			while (i-- != 0)
				Buffer[i] = NULL;
			i = 0;
			If_Error = false;
		}
		else if (*now_pointer == '=')
			File_Store("=", "12");
		else if (*now_pointer == '-')
			File_Store("-", "18");
		else if (*now_pointer == '*')
			File_Store("*", "19");
		else if (*now_pointer == '(')
			File_Store("(", "21");
		else if (*now_pointer == ')')
			File_Store(")", "22");
		else if (*now_pointer == '<')//0->10
		{
			if (*next_pointer == '=') //10->11
			{
				File_Store("<=", "14", 2);
				now_pointer++;
				next_pointer++;
			}
			else if (*next_pointer == '>') //10->12
			{
				File_Store("<>", "13", 2);
				now_pointer++;
				next_pointer++;
			}
			else  //10->13
			{
				File_Store("<", "15");
			}
		}
		else if (*now_pointer == '>')
		{
			if (*next_pointer == '=') //14->15
			{
				File_Store(">=", "16", 2);
				now_pointer++;
				next_pointer++;
			}
			else  //14->16
				File_Store(">", "17");
		}
		else if (*now_pointer == ':')
		{
			if (*next_pointer == '=') //匹配成功
			{
				File_Store(":=", "20", 2);
				now_pointer++;
				next_pointer++;
			}
			else
			{
				Error_Handling(1);
			}
		}
		else if (*now_pointer == ';')
		{
			File_Store(";", "23");
		}
		else   //0->21
		{
			while (i-- != 0)
				Buffer[i] = NULL;
			i = 0;
			if (*now_pointer == '\n')
			{
				File_Store("EOLN", "24", 4);
				LINES++;
			}
			else
				Error_Handling(0);
		}
		now_pointer++;
		next_pointer++;
	}
	File_Store("EOF", "25", 3);
}
