#ifndef AUXILIARY_H
#define AUXILIARY_H
#include<string>
using namespace std;

int LINES = 1;
bool If_Error = false;
string File_Opened = "./.txt";
string File_Output = "./.dyd";
string Error_File_Name = "./.err";

bool If_Character(char); //�ж��Ƿ�ΪСд��ĸ
bool If_Number(char);  //�ж��Ƿ�Ϊ����
bool If_Character_Equal(char[], const char[], int);//�ж����ַ����Ƿ����
bool Is_Invaild(char);//�ж��ַ��Ƿ�Ϸ�
void File_Store(string, string, int);//�����Ԫʽ�ļ�
void Error_Handling(int);//������
void Analysis(string); //�ʷ�����
string Get_program(); //���ļ��ж�ȡ����


#endif 

