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


//读文件
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

//将当前输入指针切换到下一个
void Advance()
{
	pointer++;
	if ((*pointer).code == EOLN)
	{
		line++;
		Advance();
	}
}


//Variables的函数

Variables::Variables(string vname, string vproc, bool vkind, int vlev, int vadr, string vtype="integer")
{
	this->vname = vname;
	this->vproc = vproc;
	this->vkind = vkind;
	this->vlev = vlev;
	this->vtype = vtype;
	this->vadr = vadr;
}

//判断对象是否未定义
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

//判断类是否为形参
bool Variables::IfParameter()
{
	return this->vkind;
}

//写变量名表文件
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


//Processes的函数

Processes::Processes(string pname, int plev, string ptype= "integer")
{
	this->pname = pname;
	this->plev = plev;
	this->ptype = ptype;
}

//写过程名表文件
void Processes::WriteFile()
{
	//初始化fadr和ladr
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

//判断对象是否未在表里 
bool Processes::IfInTheTable()
{
	for (Processes i : processes)
	{
		if (this->pname == i.pname && this->plev == i.plev)
			return false;
	}
	return true;
}

//Error的函数

Error::Error(string ErrorDiscription, string ErrorType, int ErrorLine)
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
		File_Output << "***LINE:" << i.ErrorLine << i.ErrorType<<" "<<i.ErrorDisCription<<endl;
	}
	File_Output.close();
}


//出错处理
void ErrorHandling(string ErrorDiscription, int ErrorCode)
{

	
}

//程序
void  Program()
{
	pointer = text.begin();
	SubProgram();
}

//分程序
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
				ErrorHandling("end", LACK_OF);
		}
		else
			ErrorHandling(";", LACK_OF);
	}
	else 
		ErrorHandling("begin", LACK_OF);
}

//说明语句表
void  StatementList() 
{
		ExplanatoryStatement();
		StatementListA();
}

//说明语句表'
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

//执行语句表
void  ExecutionStatementList()  
{
	ExecuteStatement();
	ExecutionStatementListA();
}

//执行语句表'
void  ExecutionStatementListA()  
{
	if ((*pointer).code == 23)
	{
		Advance();
		ExecuteStatement();
		ExecutionStatementListA();
	}
	
}

//说明语句
void  ExplanatoryStatement()
{	auto next_pointer = pointer + 1;   //可能存在问题
	if ((*next_pointer).code == FUNCTION)
		FunctionDescription();
	else
		VariableDescription();
}

//变量说明
void  VariableDescription()   
{
	if ((*pointer).code == INTEGER)
	{
		Advance();
		Variable();
	}
	else
		ErrorHandling("integer", LACK_OF);
}

//函数说明
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
						ErrorHandling(";", LACK_OF);
				}
				else
					ErrorHandling(")", LACK_OF);
			}
			else
			ErrorHandling("(", LACK_OF);
		}
		else
			ErrorHandling("function", LACK_OF);
	}
	else
		ErrorHandling("integer", LACK_OF);
	nowprocess = TempToStoreLastProcess;
	nowlevel--;
}

//变量
void  Variable()  //变量重定义在此处判断
{
	//Variables(string vname, string vproc, bool vkind, int vlev, int vadr, string vtype="integer")
	Variables new_variable((*pointer).statement, nowprocess, ifparameter, nowlevel, location);
	if ((*pointer).statement != nowprocess)  //非返回值
	{
		if ((*(pointer - 1)).code == INTEGER)
		{
			if (new_variable.IfNotDefined() || variable.size() == 0)
			{
				variable.push_back(new_variable);
				location++;
			}

			else //重定义
				//出错处理-变量重定义
				cout << "Variable " << (*pointer).statement << " Defined Several Times" << endl;
		}
		else
		{
			if (new_variable.IfParameter() && new_variable.IfNotDefined())  //变量为参数
			{
				variable.push_back(new_variable);
				location++;
			}
			else if (new_variable.IfNotDefined())
				//出错处理-变量未定义
					//cout << "Variable " << (*pointer).statement << " Not Defined" << endl;
				cout << "pointer is " << (*pointer).statement << " in line " << line << endl;
		}
	}
	Identifier();
}


//标识符
void  Identifier() 
{
	Advance();
}
//由于标识符一次性读入，故不需要下列产生式起作用
/*
//标识符'
void  IdentifierA()  
{
	if ((*pointer).code == 11)// 可能存在问题
		Number();
	else
		Letter();
	IdentifierA();
}

//字母
void  Letter()  
{

}

//数字
void  Number()  
{

}
*/

//参数
void  Parameter() 
{
	Variable();
}

//函数体
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
				ErrorHandling("end", LACK_OF);
		}
		else
			ErrorHandling(";", LACK_OF);
	}
	else
		ErrorHandling("begin", LACK_OF);
	
}

//执行语句
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

//读语句
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
				ErrorHandling(")", LACK_OF);
			nowprocess = TempToStoreLastProcess;
		}
		else
			ErrorHandling("(", LACK_OF);
	}
	else
		ErrorHandling("read", LACK_OF);
}

//写语句
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
				ErrorHandling(")", LACK_OF);
			nowprocess = TempToStoreLastProcess;
		}
		else
			ErrorHandling("(", LACK_OF);
	}
	else
		ErrorHandling("write", LACK_OF);
}

//赋值语句
void  AssignmentStatement()  
{
	Variable();
	if ((*pointer).code == 20)
	{
		Advance();
		ArithmeticExpression();
	}
	else
		ErrorHandling(":=", LACK_OF);
}

//条件语句
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
				ErrorHandling("else", LACK_OF);
		}
		else
			ErrorHandling("then", LACK_OF);
	}
	else
		ErrorHandling("if", LACK_OF);
}

//算术表达式
void  ArithmeticExpression() 
{
	Item();
	ArithmeticExpressionA();
}

//算术表达式'
void  ArithmeticExpressionA() 
{
	if ((*pointer).code == 18)
	{
		Advance();
		Item();
		ArithmeticExpressionA();
	}
	
}

//项
void  Item()
{
	Factor();
	ItemA();
}

//项'
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

//因子
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

//常数
void  Constant() 
{
	//UnsignedInteger();
	Advance();
}

//函数调用
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
			ErrorHandling(")", LACK_OF);
		ifparameter = false;
		nowprocess = TempToStoreLastProcess;
	}
	else
		ErrorHandling("(", LACK_OF);
}

/*
//无符号整数
void  UnsignedInteger()  
{
	Number();
	UnsignedIntegerA();
}

//无符号整数'
void  UnsignedIntegerA()  
{
	Number();
	UnsignedIntegerA();
}
*/
//条件表达式
void  ConditionalExpression() 
{
	ArithmeticExpression();
	RelationalOperator();
	ArithmeticExpression();
}

//关系运算符
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
		//出错处理-关系运算符错误
		cout << "Error" << endl;
	}
}

