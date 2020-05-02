#pragma once
#include<vector>
#include<string>
#include<iostream>
using namespace std;

struct Statements
{
	string statement;
	int code;
};

extern vector<Statements>::iterator pointer;
extern int LINE;


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


#define LACK 1




void ReadFile(string Filename); //���ļ�
void Advance();
void ErrorHandling(string ErrorDiscription, int ErrorCode);//������

void  Program();   //����
void  SubProgram();  //�ֳ���
void  StatementList(); //˵������
void  StatementListA(); //˵������'
void  ExecutionStatementList();  //ִ������
void  ExecutionStatementListA();  //ִ������'
void  ExplanatoryStatement();  //˵�����
void  VariableDescription();   //����˵��
void  FunctionDescription();  //����˵��
void  Variable();  //����
void  Identifier(); //��ʶ��
//void  IdentifierA(); //��ʶ��'
//void  Letter(); //��ĸ
//void  Number(); //����
void  Parameter(); //����
void  FunctionBody(); //������
void  ExecuteStatement();//ִ�����
void  ReadSentence(); //�����
void  WriteSentence(); //д���
void  AssignmentStatement(); //��ֵ���
void  ConditionalStatement(); //�������
void  ArithmeticExpression(); //�������ʽ
void  ArithmeticExpressionA(); //�������ʽ'
void  Item();//��
void  ItemA();//��'
void  Factor();//����
void  Constant();//����
void  FunctionCall();//��������
void  UnsignedInteger(); //�޷�������
//void  UnsignedIntegerA(); //�޷�������'
void  ConditionalExpression(); //�������ʽ
void  RelationalOperator();  //��ϵ�����


