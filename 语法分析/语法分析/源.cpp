#include<iostream>
#include<fstream>
#include<string>
#include<cstdio>

using namespace std;

string Read_File()
{
	ifstream File_Input;
	string File_name = "./../../test.dyd";
	string text,temp;
	File_Input.open(File_name);
	while (!File_Input.eof())
	{
		getline(File_Input, temp);
		text = text + temp + "\n";
	}
	return text;
}

int main(void)
{
	string text = Read_File();
	cout << text;
	system("pause");
	return 0;
}