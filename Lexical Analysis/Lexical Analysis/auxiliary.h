#ifndef AUXILIARY_H
#define AUXILIARY_H
#include<string>
using namespace std;

int LINES = 1;
bool If_Error = false;
string File_Opened = "./.txt";
string File_Output = "./.dyd";
string Error_File_Name = "./.err";

bool IfCharacter(char); //�ж��Ƿ�ΪСд��ĸ
bool IfNumber(char);  //�ж��Ƿ�Ϊ����
bool IfCharacter_Equal(char[], const char[], int);//�ж����ַ����Ƿ����
bool IsInvalid(char);//�ж��ַ��Ƿ�Ϸ�
void FileStore(string, string, int);//�����Ԫʽ�ļ�
void ErrorHandling(int);//������
void Analysis(string); //�ʷ�����
string Getprogram(); //���ļ��ж�ȡ����


#endif 

