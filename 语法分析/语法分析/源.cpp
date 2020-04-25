#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include<array>

using namespace std;

//判断是否为小写字母
bool If_Character(char chara)
{
	if (chara >= 'a'&&chara <= 'z')
		return true;
	else
		return false;
}

//判断是否为数字
bool If_Number(char chara)
{
	if (chara >= '0'&&chara <= '9')
		return true;
	else
		return false;
}

//从文件中读取程序
string Get_program()
{
	string File_Name = "./../../test.txt";
	string text,temp;
	ifstream File_out;
	File_out.open(File_Name);
	while(!File_out.eof())
	{ 
		//File_out >> temp;
		getline(File_out,temp);
		text = text + temp+"\n";
	}
	File_out.close();
	text += '\0';
	return text;
}

//输出二元式文件
void File_Store(string temp,string code)
{
	ofstream File_out;
	string File_Name = "./../../test.dyd";
	File_out.open(File_Name, ios_base::out | ios_base::app);//以追加写模式打开文档
	while(temp.size() <= 16)
		temp = " " + temp;
	File_out << temp << " " << code<< endl;
	File_out.close();

}

//词法分析
void Analysis(string text)
{
	string temp[16];
	char *now_pointer = &text[0], *next_pointer = &text[1];
	int i = 0;
	while ( *next_pointer!= '\0')
	{
		
		if (*now_pointer == ' ')//空格 0->0
		{
			now_pointer++;
			next_pointer++;
		}
		else if (If_Character(*now_pointer))//字母 0->1
		{
			temp[i++] = *now_pointer;
			now_pointer++;
			next_pointer++;
         //TODO 1->2
			
		}
		else if (If_Number(*now_pointer))//数字 0->3
		{
			while (If_Number(*next_pointer)) //3->3
			{
				temp[i++] = *now_pointer;
				now_pointer++;
				next_pointer++;
			}
			//TODO 3->4
		}
		else if (*now_pointer == '=')
		{
			//TODO  print and store messsage
		}
		else if (*now_pointer == '*')
		{
			//TODO  print and store messsage
		}
		else if (*now_pointer == '(')
		{
			//TODO  print and store messsage
		}
		else if (*now_pointer == ')')
		{
			//TODO  print and store messsage
		}
		else if (*now_pointer == '<')
		{
			//TODO  print and store messsage
		}
		else if (*now_pointer == '>')
		{
			//TODO  print and store messsage
		}
		else if (*now_pointer == ':')
		{
			//TODO  print and store messsage
		}
		else if (*now_pointer == ';')
		{
			//TODO  print and store messsage
		}
		else if (*now_pointer == '\n')
		{
			*now_pointer++;
			*next_pointer++;

			while (i-- != 0)
				temp[i] = ' ';
			i = 0;
			File_Store("EOLN","24");
		}
		else   //0->21
		{
			*now_pointer++;
			*next_pointer++;
			while (i-- != 0)
				temp[i] = ' ';
			i = 0;
		}
 	}
	File_Store("EOF", "25");
}


int main(void)
{
	/*
	string text = Get_program();
	cout << text<<endl;
	cout<<text.size();
	*/
	Analysis( Get_program());
	system("pause");
	return 0;
}