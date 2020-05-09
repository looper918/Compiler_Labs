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

//错误类型
#define LACK_OF " LACK OF "
#define VARIABLE_ALREADY_DEFINED " VARIABLE ALREADY DEFINED "
#define VARIABLE_NOT_DEFINED " VARIABLE NOT DEFINED "
#define DOES_NOT_MATCH " DOES NOT MATCH "

class Statements
{
public:
	string statement;  //语句
	int code;   //语句代码
	static void ReadFile();  //读文件
};


class Processes
{
	string pname;  //过程名
	string ptype;   //过程类型，默认integer
	int plev;    //过程层次
	int fadr;    //第一个变量在变量名表中的位置
	int ladr;   //最后一个变量在变量名表中的位置
public:
	Processes(string, int, string,int,int);
	static void WriteFile();    //写文件
	bool IfInTheTable();   //过程是否已经在表里了
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
	bool IfParameter();    //判断是否是参数
	static void WriteFile();   //写文件
	friend void Processes::WriteFile();
};


class Error
{
	string ErrorType;   //错误的类型
	int ErrorLine;     //错误所在行数
	string ErrorDisCription;  //错误描述//
public:
	Error(int, string,string);   
	static void WriteFile();   //写文件
};


void Advance();


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


