#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>

using namespace std;
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
	return text;
}

int main(void)
{
	string text = Get_program();
	
	system("pause");
	return 0;
}