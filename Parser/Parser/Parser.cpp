#include"Parser.h"


vector<Statements> text;

vector<Variables> variable;

vector<Statements>::iterator pointer;



int line = 1;
bool ifparameter = false;
string nowprocess = "main";
int nowlevel = 0;
int location=0;

//���ļ�
void ReadFile(string FileName)
{
	ifstream File_Input;
	string File_name = "./.dyd";
	File_name.insert(2, FileName);
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
	pointer = text.begin();
}

//����ǰ����ָ���л�����һ��
void Advance()
{
	pointer++;
	if ((*pointer).code == EOLN)
	{
		line++;
		Advance();
	}
}


//Variables�ĺ���
Variables::Variables()
{

}

Variables::Variables(string vname, string vproc, bool vkind, int vlev, int vadr, string vtype="integer")
{
	this->vname = vname;
	this->vproc = vproc;
	this->vkind = vkind;
	this->vlev = vlev;
	this->vtype = vtype;
	this->vadr = vadr;
}

//�ж����Ƿ�δ����
bool Variables::IfNotDefined()
{
	bool notdefined=true;
	for (Variables i : variable)
	{
		if (this->vname == i.vname && this->vproc == i.vproc &&this->vkind==i.vkind && this->vlev == i.vlev )
		{
			notdefined = false;
			break;
		}
	}
	return notdefined;
}

//�ж����Ƿ�Ϊ�β�
bool Variables::IfParameter()
{
	return this->vkind;
}

//д���������ļ�
void Variables::WriteFile(string filename)
{
	ofstream File_Output;
	string File_Name = "./.var";
	File_Name.insert(2, filename);
	File_Output.open(File_Name, ios_base::out | ios_base::app);
	if (!File_Output)
	{
		cout << "File Open Failed" << endl;
		exit(0);
	}
	File_Output.fill(' ');
	File_Output <<left<< setw(16) << "vname";
	File_Output <<left<< setw(16) << "vproc";
	File_Output << left<<setw(16) << "vkind";
	File_Output <<left<< setw(16) << "vlev";
	File_Output <<left<< setw(16) << "vtype";
	File_Output <<left<< setw(16) << "vadr" << endl;
	for (Variables i : variable)
	{
		File_Output << left<<setw(16) << i.vname;
		File_Output <<left<< setw(16) << i.vproc;
		File_Output <<left<< setw(16) << i.vkind;
		File_Output <<left<< setw(16) << i.vlev;
		File_Output << left<<setw(16) << i.vtype;
		File_Output<<left<<setw(16)<<i.vadr<< endl;
	}
	File_Output.close();
}




//������
void ErrorHandling(string ErrorDiscription, int ErrorCode)
{
	switch (ErrorCode)
	{
	case LACK:
	{
		cout << "***LINE " << line << " " << " LACK " << ErrorDiscription<<endl;
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
{	auto next_pointer = pointer + 1;   //���ܴ�������
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
	nowlevel++;
	string TempToStoreLastProcess = nowprocess;
	nowprocess = (*(pointer +2)).statement;
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
				ifparameter = true;
				Parameter();
				ifparameter = false;
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
	nowprocess = TempToStoreLastProcess;
	nowlevel--;
}

//����
void  Variable()  //�����ض����ڴ˴��ж�
{
	//Variables(string vname, string vproc, bool vkind, int vlev, int vadr, string vtype="integer")
	Variables new_variable((*pointer).statement, nowprocess, ifparameter, nowlevel, location);

	if ((*(pointer - 1)).code == INTEGER)
	{
		if (new_variable.IfNotDefined() || variable.size() == 0)
		{
			variable.push_back(new_variable);
			location++;
		}

		else //�ض���
			//������-�����ض���
			cout << "Variable " << (*pointer).statement << " Defined Several Times" << endl;
	}
	else
	{
		if (new_variable.IfParameter() && new_variable.IfNotDefined())  //����Ϊ����
		{
			variable.push_back(new_variable);
			location++;
		}
		else if (new_variable.IfNotDefined())
			//������-����δ����
				//cout << "Variable " << (*pointer).statement << " Not Defined" << endl;
			cout << "pointer is " << (*pointer).statement << " in line " << line << endl;
	}
	Identifier();
}


//��ʶ��
void  Identifier() 
{
	Advance();
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
			string TempToStoreLastProcess = nowprocess;
			nowprocess = (*(pointer - 2)).statement;
			ifparameter = true;
			Variable();
			ifparameter = false;
			if ((*pointer).code == 22)
				Advance();
			else
				ErrorHandling(")", LACK);
			nowprocess = TempToStoreLastProcess;
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
			string TempToStoreLastProcess = nowprocess;
			nowprocess = (*(pointer -2)).statement;
			ifparameter = true;
			Variable();
			ifparameter = false;
			if ((*pointer).code == 22)
				Advance();
			else
				ErrorHandling(")", LACK);
			nowprocess = TempToStoreLastProcess;
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
		string TempToStoreLastProcess = nowprocess;
		nowprocess = (*(pointer - 2)).statement;
		ifparameter = true;
		ArithmeticExpression();
		if ((*pointer).code == 22)
			Advance();
		else
			ErrorHandling(")", LACK);
		ifparameter = false;
		nowprocess = TempToStoreLastProcess;
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

