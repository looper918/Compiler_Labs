#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include<array>

using namespace std;

int LINES=1;
bool If_Error = false;

//�ж��Ƿ�ΪСд��ĸ
bool If_Character(char chara)
{
	if ((chara >= 'a'&&chara <= 'z')|| (chara >= 'A'&&chara <= 'Z'))
		return true;
	else
		return false;
}

//�ж��Ƿ�Ϊ����
bool If_Number(char chara)
{
	if (chara >= '0'&&chara <= '9')
		return true;
	else
		return false;
}

//�ж����ַ����Ƿ����
bool If_Character_Equal(char str1[], const char str2[],int num=0)
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

//���ļ��ж�ȡ����
string Get_program()
{
	string File_Name = "./../../test_error.txt";
	string text, temp;
	ifstream File_out;
	File_out.open(File_Name);
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

//�����Ԫʽ�ļ�
void File_Store(string temp, string code,int num = 1)
{
	if (If_Error)
	{
		cout << "Error" << endl;
		return;   //����ʱ����ӡ����
	}
	temp.resize(num);
	ofstream File_out;
	string File_Name = "./../../test.dyd";
	File_out.open(File_Name, ios_base::out | ios_base::app);//��׷��дģʽ���ĵ�
	while (temp.size() < 16)
		temp = " " + temp;
	cout << temp << " " << code << endl;
	File_out << temp << " " << code << endl;
	File_out.close();
	If_Error = false;
}

void Error_Handling(int Error_Code)
{
	string Error_File_Name = "./../../test.err";
	ofstream Error_File;
	Error_File.open(Error_File_Name, ios_base::out | ios_base::app);
	switch (Error_Code)
	{
	case 0:Error_File << "LINE: " << LINES << "  Invalid Character" << endl; break; //�Ƿ��ַ�
	case 1:Error_File << "LINE: " << LINES << "  : does not match" << endl; break;   //����ƥ��
	case 2:Error_File << "LINE: " << LINES << "  identifier is too long" << endl; break;  //�������
	}
	Error_File.close();
}
//�ʷ�����
void Analysis(string text)
{
	char Buffer[20];
	char *now_pointer = &text[0], *next_pointer = &text[1];
	int i = 0;
	while (*next_pointer != '\0')
	{
		
		if (*now_pointer == ' ')//�ո� 0->0
		{
			now_pointer++;
			next_pointer++;
			continue;
		}
		else if (If_Character(*now_pointer))//��ĸ 0->1
		{
			while (If_Character(*next_pointer) || If_Number(*next_pointer))
			{
				Buffer[i++] = *now_pointer;
				if (*now_pointer >= 'A'&&*now_pointer <= 'Z')
				{
					If_Error = true;
					Error_Handling(0);
				}
				now_pointer++;
				next_pointer++;
			}
			Buffer[i++] = *now_pointer;
			if (i > 16) Error_Handling(2);
			
			if (If_Character_Equal(Buffer,"begin",4)) File_Store(Buffer,"01",i);
			else if (If_Character_Equal(Buffer, "end", 2)) File_Store(Buffer, "02", i);
			else if (If_Character_Equal(Buffer, "integer", 6)) File_Store(Buffer, "03", i);
			else if (If_Character_Equal(Buffer, "if", 1)) File_Store(Buffer, "04", i);
			else if (If_Character_Equal(Buffer, "then", 3)) File_Store(Buffer, "05", i);
			else if (If_Character_Equal(Buffer, "else", 3)) File_Store(Buffer, "06", i);
			else if (If_Character_Equal(Buffer, "function", 7)) File_Store(Buffer, "07", i);
			else if (If_Character_Equal(Buffer, "read", 3)) File_Store(Buffer, "08", i);
			else if (If_Character_Equal(Buffer, "write", 3)) File_Store(Buffer, "09", i);
			else File_Store(Buffer, "10",i);
			while (i-- != 0)
				Buffer[i] = NULL;
			i = 0;
			If_Error = false;
		}
		else if (If_Number(*now_pointer))//���� 0->3
		{
			while (If_Number(*next_pointer)) //3->3
			{
				Buffer[i++] = *now_pointer;
				if (*now_pointer >= 'A'&&*now_pointer <= 'Z') Error_Handling(0);
				now_pointer++;
				next_pointer++;
			}
			Buffer[i++] = *now_pointer;
			File_Store(Buffer, "11");
			while (i-- != 0)
				Buffer[i] = NULL;
			i = 0;
		
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
			if (*next_pointer == '=') //ƥ��ɹ�
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
		}
		now_pointer++;
		next_pointer++;
	}
	File_Store("EOF", "25", 3);
}


int main(void)
{
	/*
	string text = Get_program();
	cout << text<<endl;
	cout<<text.size();
	*/
	Analysis(Get_program());
	system("pause");
	return 0;
}