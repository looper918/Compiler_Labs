#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<vector>
#include<sstream>
#include"Parser.h"
using namespace std;

vector<Statements> text;

vector<Statements>::iterator pointer;
int LINE = 1;

int main(int argc, char*argv[])
{

	ReadFile(argv[1]);
	Program();
	system("pause");
	return 0;
}

void ReadFile(string FileName)
{
	ifstream File_Input;
	string File_name = "./.dyd";
	File_name.insert(2, FileName);
	string temp;
	File_Input.open(File_name);
	if (!File_Input)
	{
		cout << "File Open Failed" << endl;
		exit(0);
	}
	while (!File_Input.eof())
	{
		getline(File_Input, temp);
		stringstream input(temp);
		Statements new_statement;
		input >> new_statement.statement >> new_statement.code;
		text.push_back(new_statement);
	}
	pointer = text.begin();
}



