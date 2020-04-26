#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include<array>

using namespace std;

//�ж��Ƿ�ΪСд��ĸ
bool If_Character(char chara)
{
	if (chara >= 'a'&&chara <= 'z')
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

//���ļ��ж�ȡ����
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

//�����Ԫʽ�ļ�
void File_Store(string temp,string code,int num = 1)
{
	temp.resize(num);
	ofstream File_out;
	string File_Name = "./../../test.dyd";
	File_out.open(File_Name, ios_base::out | ios_base::app);//��׷��дģʽ���ĵ�
	while(temp.size() < 16)
		temp = " " + temp;
	cout << temp << " " << code << endl;
	File_out << temp << " " << code<< endl;
	File_out.close();

}

//�ʷ�����
void Analysis(string text)
{
    char temp[16];
	char *now_pointer = &text[0], *next_pointer = &text[1];
	int i = 0;
	while ( *next_pointer!= '\0')
	{
		
		if (*now_pointer == ' ')//�ո� 0->0
		{
			now_pointer++;
			next_pointer++;
			continue;
		}
		else if (If_Character(*now_pointer))//��ĸ 0->1
		{
		  while (If_Character(*next_pointer)||If_Number(*next_pointer))
		  {
			temp[i++] = *now_pointer;
			now_pointer++;
			next_pointer++;
		  }
		  temp[i++] = *now_pointer;
		  if (strcmp(temp,"begin")==0) File_Store(temp,"01",i);
		  else if (strcmp(temp, "end")==0) File_Store(temp, "02", i);
		  else if (strcmp(temp, "integer")==0) File_Store(temp, "03", i);
		  else if (strcmp(temp, "if")==0) File_Store(temp, "04", i);
		  else if (strcmp(temp, "then")==0) File_Store(temp, "05", i);
		  else if (strcmp(temp, "else")==0) File_Store(temp, "06", i);
		  else if (strcmp(temp, "function")==0) File_Store(temp, "07", i);
		  else if (strcmp(temp, "read")==0) File_Store(temp, "08", i);
		  else if (strcmp(temp, "write")==0) File_Store(temp, "09", i);
		  else File_Store(temp, "10",i);

		  while (i-- != 0)
			  temp[i] = ' ';
		  i = 0;
		}
		else if (If_Number(*now_pointer))//���� 0->3
		{
			while (If_Number(*next_pointer)) //3->3
			{
				temp[i++] = *now_pointer;
				now_pointer++;
				next_pointer++;
			}
			temp[i++] = *now_pointer;
			File_Store(temp, "11");
			while (i-- != 0)
				temp[i] = ' ';
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
				File_Store("<=", "14",2);
				now_pointer++;
				next_pointer++;
			}
			else if (*next_pointer == '>') //10->12
			{
				File_Store("<>", "13",2);
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
				File_Store(":=", "20",2);
				now_pointer++;
				next_pointer++;
			}
			else
			{
				//TODO ƥ�����
				cout << "Error" << endl;
			}	
		}
		else if (*now_pointer == ';')
		{
			File_Store(";","23");
		}
		else   //0->21
		{
			while (i-- != 0)
				temp[i] = ' ';
			i = 0;
			if(*now_pointer == '\n')
				File_Store("EOLN", "24",4);
		}
		now_pointer++;
		next_pointer++;
 	}
	File_Store("EOF", "25",3);
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