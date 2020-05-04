#pragma once
#include<vector>
#include<string>
#include<sstream>
#include<fstream>
#include<iostream>
#include<iomanip>
using namespace std;


#define BEGIN 1
#define END 2
#define INTEGER 3
#define IF 4
#define THEN 5
#define ELSE 6
#define FUNCTION 7
#define READ 8
#define WRITE 9
#define IDENTIFIER 10
#define CONSTANT 11
#define EOLN 24
#define EOF 25

//出错处理类型
#define LACK_OF " LACK OF "
#define VARIABLE_ALREADY_DEFINED " VARIABLE ALREADY DEFINED "
#define VARIABLE_NOT_DEFINED " VARIABLE NOT DEFINED "
#define DOES_NOT_MATCH " DOES NOT MATCH "
#define RELATION_TYPE_ERROR " RELATION TYPE ERROR "

class Statements
{
public:
	string statement;
	int code;
	static void ReadFile();
};


class Processes
{
	string pname;
	string ptype;
	int plev;
	int fadr;
	int ladr;
public:
	Processes(string, int, string,int,int);
	static void WriteFile();
	bool IfInTheTable();
};


class Variables
{
	string vname;  //变量名
	string vproc;  //所属过程
	bool vkind;  //分类
	string vtype; //变量类型
	int vlev;//变量层次
	int vadr;//变量位置
public:
	Variables(string, string, bool, int, int,string);//初始化类
	bool IfNotDefined();  //判断是否已定义
	bool IfParameter();
	static void WriteFile();
	friend void Processes::WriteFile();
};


class Error
{
	string ErrorType;
	int ErrorLine;
	string ErrorDisCription;
public:
	Error(int, string,string);
	static void WriteFile();


};


void Advance();
void ErrorHandling(string ErrorDiscription, string  ErrorCode);//出错处理

void  Program();   //程序
void  SubProgram();  //分程序
void  StatementList(); //说明语句表
void  StatementListA(); //说明语句表'
void  ExecutionStatementList();  //执行语句表
void  ExecutionStatementListA();  //执行语句表'
void  ExplanatoryStatement();  //说明语句
void  VariableDescription();   //变量说明
void  FunctionDescription();  //函数说明
void  Variable();  //变量
void  Identifier(); //标识符
//void  IdentifierA(); //标识符'
//void  Letter(); //字母
//void  Number(); //数字
void  Parameter(); //参数
void  FunctionBody(); //函数体
void  ExecuteStatement();//执行语句
void  ReadSentence(); //读语句
void  WriteSentence(); //写语句
void  AssignmentStatement(); //赋值语句
void  ConditionalStatement(); //条件语句
void  ArithmeticExpression(); //算术表达式
void  ArithmeticExpressionA(); //算术表达式'
void  Item();//项
void  ItemA();//项'
void  Factor();//因子
void  Constant();//常数
void  FunctionCall();//函数调用
//void  UnsignedInteger(); //无符号整数
//void  UnsignedIntegerA(); //无符号整数'
void  ConditionalExpression(); //条件表达式
void  RelationalOperator();  //关系运算符


