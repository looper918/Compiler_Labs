#ifndef AUXILIARY_H
#define AUXILIARY_H
#include<string>
using namespace std;



bool IfCharacter(char); //�ж��Ƿ�ΪСд��ĸ
bool IfNumber(char);  //�ж��Ƿ�Ϊ����
bool IfCharacterEqual(char[], const char[], int);//�ж����ַ����Ƿ����
bool IsInvalid(char);//�ж��ַ��Ƿ�Ϸ�
void FileStore(string, string,int);//�����Ԫʽ�ļ�
void ErrorHandling(int);//������
void Analysis(string); //�ʷ�����
string Getprogram(); //���ļ��ж�ȡ����


#endif 

