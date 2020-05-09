#include<iostream>
#include<string>
#include<cstdlib>
#include"Parser.h"
using namespace std;

extern vector<Statements> text;

string Dyd = "./.dyd";
string Dys = "./.dys";
string Var = "./.var";
string Pro = "./.pro";
string Err = "./.err";

int main(int argc, char*argv[])
{
	Dyd.insert(2, argv[1]);
	Dys.insert(2, argv[1]);
	Pro.insert(2, argv[1]);
	Var.insert(2, argv[1]);
	Err.insert(2, argv[1]);

	Statements::ReadFile();
	Program();
	Variables::WriteFile();
	Processes::WriteFile();
	Error::WriteFile();
	system("pause");
	return 0;
}





