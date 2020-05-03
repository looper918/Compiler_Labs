#include"Parser.h"


vector<Statements> text;

vector<Variables> variable;

vector<Statements>::iterator pointer;



int line = 1;
bool ifparameter = false;
string nowprocess = "main";
int nowlevel = 0;
int location=0;

//读文件
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

//判断类是否未定义
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




//出错处理
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

//程序
void  Program()
{
	SubProgram();
}

//分程序
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
		ErrorHandling("integer", LACK);
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

//变量
void  Variable()  //变量重定义在此处判断
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

//写语句
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
		ErrorHandling(":=", LACK);
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
				ErrorHandling("else", LACK);
		}
		else
			ErrorHandling("then", LACK);
	}
	else
		ErrorHandling("if", LACK);
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
			ErrorHandling(")", LACK);
		ifparameter = false;
		nowprocess = TempToStoreLastProcess;
	}
	else
		ErrorHandling("(", LACK);
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

