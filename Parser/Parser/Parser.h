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
void ReadFile(vector<Statements> &text); //���ļ�
void Advancd();



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
void  IdentifierA(); //��ʶ��'
void  Letter(); //��ĸ
void  Number(); //����
void  Parameter(); //����
void  FunctionBody(); //������
void  Variable(); //����
void  ExecuteStatement();//ִ�����
void  ReadSentence(); //�����
void  WriteSentence(); //д���
void  AssignmentStatement(); //��ֵ���
void  ConditionalStatement(); //�������
void  ArithmeticExpression(); //�������ʽ
void  ArithmeticExpressionA(); //�������ʽ'
void  Item();//��
void  Factor();//����
void  Constant();//����
void  FunctionCall();//��������
void  UnsignedInteger(); //�޷�������
void  UnsignedIntegerA(); //�޷�������'
void  ConditionalExpression(); //�������ʽ
void  RelationalOperator();  //��ϵ�����


