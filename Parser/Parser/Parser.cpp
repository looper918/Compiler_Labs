#include"Parser.h"

vector<Statements> text;
vector<Variables> variable;
vector<Processes> processes;
vector<Error> errors;
vector<Statements>::iterator pointer;

extern string Dys;
extern string Dyd;
extern string Pro;
extern string Var;
extern string Err;

bool ifparameter = false;
string nowprocess = "main";
int nowlevel = 0;
int location=0;
int line = 1;


//���ļ�
void Statements::ReadFile()
{
	ifstream File_Input;
	string temp;
	File_Input.open(Dyd);
	if (!File_Input)
	{
		cout << "File Open Failed" << endl;
		exit(0);
	}

	ofstream File_Output;
	File_Output.open(Dys);
	if (!File_Output)
	{
		cout << "File Open Failed" << endl;
		exit(0);
	}

	while (!File_Input.eof())
	{
		getline(File_Input, temp);
		File_Output << temp << endl;
		stringstream input(temp);
		Statements new_statement;
		input >> new_statement.statement >> new_statement.code;
		text.push_back(new_statement);
	}
	File_Input.close();
	File_Output.close();
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

Variables::Variables(string vname, string vproc, bool vkind, int vlev, int vadr, string vtype="integer")
{
	this->vname = vname;
	this->vproc = vproc;
	this->vkind = vkind;
	this->vlev = vlev;
	this->vtype = vtype;
	this->vadr = vadr;
}

//�ж϶����Ƿ�δ����
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
void Variables::WriteFile()
{
	ofstream File_Output;
	File_Output.open(Var);
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


//Processes�ĺ���

Processes::Processes(string pname, int plev, string ptype= "integer",int fadr=0,int ladr=0)
{
	this->pname = pname;
	this->plev = plev;
	this->ptype = ptype;
	this->ladr = fadr;
	this->ladr = ladr;
}

//д���������ļ�
void Processes::WriteFile()
{
	//��ʼ��fadr��ladr
   bool flag = true;
   for (Processes & i : processes)
   {
	   for (Variables j : variable)
	   {
		   if (i.pname == j.vproc)
		   {
			   if (flag)
			   {
				   i.fadr = j.vadr;
				   i.ladr = j.vadr;
				   flag = false;
			   }
			   else
				   i.ladr = j.vadr;
			   //break;
		   }
	   }
	   flag = true;
   }
	ofstream File_Output;
	File_Output.open(Pro);
	if (!File_Output)
	{
		cout << "File Open Failed" << endl;
		exit(0);
	}
	File_Output.fill(' ');
	File_Output << left << setw(16) << "pname";
	File_Output << left << setw(16) << "ptype";
	File_Output << left << setw(16) << "plev";
	File_Output << left << setw(16) << "fadr";
	File_Output << left << setw(16) << "ladr" << endl;

	for (Processes i : processes)
	{
		File_Output << left << setw(16) << i.pname;
		File_Output << left << setw(16) << i.ptype;
		File_Output << left << setw(16) << i.plev;
		File_Output << left << setw(16) << i.fadr;
		File_Output << left << setw(16) << i.ladr<<endl;
	}
	File_Output.close();
}

//�ж϶����Ƿ�δ�ڱ��� 
bool Processes::IfInTheTable()
{
	for (Processes i : processes)
	{
		if (this->pname == i.pname && this->plev == i.plev)
			return false;
	}
	return true;
}

//Error�ĺ���

Error::Error(int ErrorLine, string ErrorType, string ErrorDiscription=" ")
{
	this->ErrorDisCription = ErrorDiscription;
	this->ErrorType = ErrorType;
	this->ErrorLine = ErrorLine;
}

void Error::WriteFile()
{
	ofstream File_Output;
	File_Output.open(Err);
	if (!File_Output)
	{
		cout << "File Open Failed" << endl;
		exit(0);
	}
	for (Error i:errors)
	{
		File_Output << "***LINE: " << i.ErrorLine << " "<<i.ErrorType<<" "<<i.ErrorDisCription<<endl;
	}
	File_Output.close();
}


//����
void  Program()
{
	pointer = text.begin();
	SubProgram();
}

//�ֳ���
void  SubProgram() 
{
	Processes main("main", 0);
	processes.push_back(main);
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
			{
				Error new_error(line, LACK_OF,"end");
				errors.push_back(new_error);
			}
		}
		else
		{
			Error new_error(line, LACK_OF,";");
			errors.push_back(new_error);
		}
	}
	else 
	{
		Error new_error(line, LACK_OF,"begin");
		errors.push_back(new_error);
	}
}

//˵������
void  StatementList() 
{
		ExplanatoryStatement();
		StatementListA();
}

//˵������'
void  StatementListA()//�˴������ȱ�٣���
{
	auto next_pointer = pointer + 1;
	if ((*next_pointer).code == EOLN) next_pointer++;
	
	if ((*pointer).code == 23 && (*next_pointer).code == INTEGER)
	{
		Advance();
		ExplanatoryStatement();
		StatementListA();
	}
	else if ((*pointer).code ==INTEGER)
	{
		Error new_error(line-1, LACK_OF, ";");
		errors.push_back(new_error);
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
	auto next_pointer = pointer + 1;
	if ((*next_pointer).code == EOLN) next_pointer++;
	if ((*pointer).code == 23)
	{
		Advance();
		ExecuteStatement();
		ExecutionStatementListA();
	}
	else if ((*pointer).code != END && (*next_pointer).code != END && (*pointer).code != 23)  //δƥ�䵽�� ���·�����ִ�����
	{
		Error new_error(line-1, LACK_OF, ";");
		errors.push_back(new_error);
		ExecuteStatement();
		ExecutionStatementListA();
	}
	else
		return;
}

//˵�����
void  ExplanatoryStatement()
{	
	auto next_pointer = pointer + 1;   
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
	{
		Error new_error(line, LACK_OF, "integer");
		errors.push_back(new_error);
	}
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
					{
						Error new_error(line, LACK_OF,";");
						errors.push_back(new_error);
					}
				}
				else
				{
					Error new_error(line, LACK_OF,")");
					errors.push_back(new_error);
				}
			}
			else
			{
				Error new_error(line, LACK_OF,"(");
				errors.push_back(new_error);
			}
		}
		else
		{
			Error new_error(line, LACK_OF,"function");
			errors.push_back(new_error);
		}
	}
	else
	{
		Error new_error(line, LACK_OF,"integer");
		errors.push_back(new_error);
	}
	nowprocess = TempToStoreLastProcess;
	nowlevel--;
}

//����
void  Variable()  //�����ض����ڴ˴��ж�
{
	//Variables(string vname, string vproc, bool vkind, int vlev, int vadr, string vtype="integer")
	Variables new_variable((*pointer).statement, nowprocess, ifparameter, nowlevel, location);
	if ((*pointer).statement != nowprocess)  //�Ƿ���ֵ
	{
		if ((*(pointer - 1)).code == INTEGER)
		{
			if (new_variable.IfNotDefined() || variable.size() == 0)
			{
				variable.push_back(new_variable);
				location++;
			}
			else //�ض���
			{
				Error new_error(line, VARIABLE_ALREADY_DEFINED);
				errors.push_back(new_error);
			}
		}
		else
		{
			if (new_variable.IfParameter() && new_variable.IfNotDefined())  //����Ϊ����
			{
				variable.push_back(new_variable);
				location++;
			}
			else if (new_variable.IfNotDefined())
			{
				Error new_error(line, VARIABLE_NOT_DEFINED);
				errors.push_back(new_error);
			 }
		}
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
	Processes new_process((*(pointer - 6)).statement, nowlevel);
	if(new_process.IfInTheTable())
	    processes.push_back(new_process);
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
			{
				Error new_error(line, LACK_OF,"end");
				errors.push_back(new_error);
			}
		}
		else
		{
			Error new_error(line, LACK_OF,";");
			errors.push_back(new_error);
		}
	}
	else
	{
		Error new_error(line, LACK_OF,"begin");
		errors.push_back(new_error);
	}
	
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
	else if((*pointer).code==IDENTIFIER)
		AssignmentStatement();
}

//�����
void  ReadSentence() 
{
	if ((*pointer).code == READ)
	{
		Processes new_process((*pointer).statement, nowlevel);
		if (new_process.IfInTheTable())
			processes.push_back(new_process);
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
			{
				Error new_error(line, LACK_OF,")");
				errors.push_back(new_error);
			}
			nowprocess = TempToStoreLastProcess;
		}
		
		else
		{
			Error new_error(line, LACK_OF,"(");
			errors.push_back(new_error);
		}

	}
	else
	{
		Error new_error(line, LACK_OF,"read");
		errors.push_back(new_error);
	}
}

//д���
void  WriteSentence() 
{
	if ((*pointer).code == WRITE)
	{
		Processes new_process((*pointer).statement, nowlevel);
		if (new_process.IfInTheTable())
			processes.push_back(new_process);
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
			{
				Error new_error(line, LACK_OF,")");
				errors.push_back(new_error);
			}
			nowprocess = TempToStoreLastProcess;
		}
		else
		{
			Error new_error(line, LACK_OF,"(");
			errors.push_back(new_error);
		}
	}
	else
	{
		Error new_error(line, LACK_OF,"write");
		errors.push_back(new_error);
	}
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
	{
		Error new_error(line, LACK_OF, ":=");
		errors.push_back(new_error);
	}
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
			{
				Error new_error(line, LACK_OF, "else");
				errors.push_back(new_error);
			}
		}
		else
		{
			Error new_error(line, LACK_OF, "then");
			errors.push_back(new_error);
		}
	}
	else
	{
		Error new_error(line, LACK_OF, "if");
		errors.push_back(new_error);
	}
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
	/*
	else if ((*pointer).code == IDENTIFIER)
	{
		Error new_error(line - 1, LACK_OF, "*");
		errors.push_back(new_error);
		Factor();
		ItemA();
	}
	*/
	else
		return;
}

//����
void  Factor() 
{
	auto next_pointer = pointer + 1;
	if ((*pointer).code == CONSTANT)
		Constant();
	else if ((*next_pointer).code==21)  //��Ӧ��������
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
		{
			Error new_error(line, LACK_OF,")");
			errors.push_back(new_error);
		}
		ifparameter = false;
		nowprocess = TempToStoreLastProcess;
	}
	else
	{
		Error new_error(line, LACK_OF, ")");
		errors.push_back(new_error);
	}
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
		return;
	}
}

