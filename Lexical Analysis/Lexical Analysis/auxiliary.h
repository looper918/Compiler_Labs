#ifndef AUXILIARY_H
#define AUXILIARY_H
#include<string>
using namespace std;

int LINES = 1;
bool If_Error = false;
string File_Opened = "./.txt";
string File_Output = "./.dyd";
string Error_File_Name = "./.err";

bool IfCharacter(char); //判断是否为小写字母
bool IfNumber(char);  //判断是否为数字
bool IfCharacter_Equal(char[], const char[], int);//判断两字符串是否相等
bool IsInvalid(char);//判断字符是否合法
void FileStore(string, string, int);//输出二元式文件
void ErrorHandling(int);//出错处理
void Analysis(string); //词法分析
string Getprogram(); //从文件中读取程序


#endif 

