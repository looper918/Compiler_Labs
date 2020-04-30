#include"Parser.h"
#include<string>

using namespace std;

Statements::Statements(string str, int temp)
{
	this->statement = str;
	this->code = temp;
}
Statements::Statements()
{

}