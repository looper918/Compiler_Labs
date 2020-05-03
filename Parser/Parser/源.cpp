#include<iostream>
#include<string>
#include<cstdlib>
#include"Parser.h"
using namespace std;



int main(int argc, char*argv[])
{

	ReadFile(argv[1]);
	Program();
	Variables print;
	print.WriteFile(argv[1]);
	system("pause");
	return 0;
}





