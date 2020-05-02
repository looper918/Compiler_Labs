#include"Parser.h"
#include<string>

using namespace std;

//����ǰ����ָ���л�����һ��
void Advance()
{
	pointer++;
	if ((*pointer).code==24)
	{
		LINE++;
		Advance();
	}
}

//������
void ErrorHandling(string ErrorDiscription, int ErrorCode)
{
	switch (ErrorCode)
	{
	case LACK:
	{
		cout << "***LINE " << LINE << " " << " LACK " << ErrorDiscription<<endl;
	}
	}
}

//����
void  Program()
{
	SubProgram();
}

//�ֳ���
void  SubProgram() 
{
	if ((*pointer).code == BEGIN)
	{
		Advance();
		StatementList();
		if ((*pointer).code == 23)
		{
			Advance();
			ExecutionStatementList();
			if ((*pointer).code == END)
				Advance();
			else
				ErrorHandling("end", LACK);
		}
		else
			ErrorHandling(";", LACK);
	}
	else 
		ErrorHandling("begin", LACK);
}

//˵������
void  StatementList() 
{
		ExplanatoryStatement();
		StatementListA();
}

//˵������'
void  StatementListA()
{
	auto next_pointer = pointer + 1;
	if ((*next_pointer).code == EOLN) next_pointer++;
	if ((*pointer).code == 23 && (*next_pointer).code == INTEGER)
	{
		Advance();
		ExplanatoryStatement();
		StatementListA();
	}
	
}

//ִ������
void  ExecutionStatementList()  
{
	ExecuteStatement();
	ExecutionStatementListA();
}

//ִ������'
void  ExecutionStatementListA()  
{
	if ((*pointer).code == 23)
	{
		Advance();
		ExecuteStatement();
		ExecutionStatementListA();
	}
	
}

//˵�����
void  ExplanatoryStatement()
{
	auto next_pointer = pointer + 1;   //���ܴ�������
	if ((*next_pointer).code == FUNCTION)
		FunctionDescription();
	else
		VariableDescription();
}

//����˵��
void  VariableDescription()   
{
	if ((*pointer).code == INTEGER)
	{
		Advance();
		Variable();
	}
	else
		ErrorHandling("integer", LACK);
}

//����˵��
void  FunctionDescription()
{
	if ((*pointer).code == INTEGER)
	{
		Advance();
		if ((*pointer).code == FUNCTION)
		{
			Advance();
			Identifier();
			if ((*pointer).code == 21)
			{
				Advance();
				Parameter();
				if ((*pointer).code == 22)
				{
					Advance();
					if ((*pointer).code == 23)
					{
						Advance();
						FunctionBody();
					}
					else
						ErrorHandling(";", LACK);
				}
				else
					ErrorHandling(")", LACK);
			}
			else
			ErrorHandling("(", LACK);
		}
		else
			ErrorHandling("function", LACK);
	}
	else
		ErrorHandling("integer", LACK);
}

//����
void  Variable()  
{
	Identifier();
}

//��ʶ��
void  Identifier() //�����ض����ڴ˴��ж�
{
	Advance();
	//Letter();
	//IdentifierA();

}
//���ڱ�ʶ��һ���Զ��룬�ʲ���Ҫ���в���ʽ������
/*
//��ʶ��'
void  IdentifierA()  
{
	if ((*pointer).code == 11)// ���ܴ�������
		Number();
	else
		Letter();
	IdentifierA();
}

//��ĸ
void  Letter()  
{

}

//����
void  Number()  
{

}
*/

//����
void  Parameter() 
{
	Variable();
}

//������
void  FunctionBody()
{
	if ((*pointer).code == BEGIN)
	{
		Advance();
		StatementList();
		if ((*pointer).code == 23)
		{
			Advance();
			ExecutionStatementList();
			if ((*pointer).code == END)
				Advance();
			else 
				ErrorHandling("end", LACK);
		}
		else
			ErrorHandling(";", LACK);
	}
	else
		ErrorHandling("begin", LACK);
}

//ִ�����
void  ExecuteStatement()  
{
	//auto next_pointer = pointer + 1;
	if ((*pointer).code == READ)
		ReadSentence();
	else if ((*pointer).code == WRITE)
		WriteSentence();
	else if ((*pointer).code == IF)
		ConditionalStatement();
	else
		AssignmentStatement();
}

//�����
void  ReadSentence() 
{
	if ((*pointer).code == READ)
	{
		Advance();
		if ((*pointer).code == 21)
		{
			Advance();
			Variable();
			if ((*pointer).code == 22)
				Advance();
			else
				ErrorHandling(")", LACK);
		}
		else
			ErrorHandling("(", LACK);
	}
	else
		ErrorHandling("read", LACK);
}

//д���
void  WriteSentence() 
{
	if ((*pointer).code == WRITE)
	{
		Advance();
		if ((*pointer).code == 21)
		{
			Advance();
			Variable();
			if ((*pointer).code == 22)
				Advance();
			else
				ErrorHandling(")", LACK);
		}
		else
			ErrorHandling("(", LACK);
	}
	else
		ErrorHandling("write", LACK);
}

//��ֵ���
void  AssignmentStatement()  
{
	Variable();
	if ((*pointer).code == 20)
	{
		Advance();
		ArithmeticExpression();
	}
	else
		ErrorHandling(":=", LACK);
}

//�������
void  ConditionalStatement() 
{
	if ((*pointer).code == IF)
	{
		Advance();
		ConditionalExpression();
		if ((*pointer).code == THEN)
		{
			Advance();
			ExecuteStatement();
			if ((*pointer).code == ELSE)
			{
				Advance();
				ExecuteStatement();
			}
			else
				ErrorHandling("else", LACK);
		}
		else
			ErrorHandling("then", LACK);
	}
	else
		ErrorHandling("if", LACK);
}

//�������ʽ
void  ArithmeticExpression() 
{
	Item();
	ArithmeticExpressionA();
}

//�������ʽ'
void  ArithmeticExpressionA() 
{
	if ((*pointer).code == 18)
	{
		Advance();
		Item();
		ArithmeticExpressionA();
	}
	
}

//��
void  Item()
{
	Factor();
	ItemA();
}

//��'
void  ItemA()
{
	if ((*pointer).code == 19)
	{
		Advance();
		Factor();
		ItemA();
	}
	else
		return;
}

//����
void  Factor() 
{
	auto next_pointer = pointer + 1;
	if ((*pointer).code == CONSTANT)
		Constant();
	else if ((*next_pointer).code==21)
		FunctionCall();
	else
		Variable();
}

//����
void  Constant() 
{
	//UnsignedInteger();
	Advance();
}

//��������
void  FunctionCall()   
{
	Identifier();
	if ((*pointer).code == 21)
	{
		Advance();
		ArithmeticExpression();
		if ((*pointer).code == 22)
			Advance();
		else
			ErrorHandling(")", LACK);
	}
	else
		ErrorHandling("(", LACK);
}

/*
//�޷�������
void  UnsignedInteger()  
{
	Number();
	UnsignedIntegerA();
}

//�޷�������'
void  UnsignedIntegerA()  
{
	Number();
	UnsignedIntegerA();
}
*/
//�������ʽ
void  ConditionalExpression() 
{
	ArithmeticExpression();
	RelationalOperator();
	ArithmeticExpression();
}

//��ϵ�����
void  RelationalOperator()  
{
	int code = (*pointer).code;
	switch (code)
	{    
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
	 Advance();
	 break;
	default:
		//������-��ϵ���������
		cout << "Error" << endl;
		
	}
}

