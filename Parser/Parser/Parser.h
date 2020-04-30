#pragma once
#include<vector>
#include<string>
using namespace std;

class Statements
{
public:
	string statement;
	int code;
	Statements(string,int);
	Statements();
};
void ReadFile(vector<Statements> &text); //╤анд╪Ч


