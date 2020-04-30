#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<vector>
#include<sstream>
#include"Parser.h"
using namespace std;

int main(void)
{
	vector<Statements> text;
	ReadFile(text);
	for (Statements i : text)
	{
		cout << i .statement<< endl;
		cout << i.code << endl;
	}
	system("pause");
	return 0;
}

void ReadFile(vector<Statements> &text)
{
	ifstream File_Input;
	string File_name = "./test.dyd";
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
}