#include <string>
#include <vector>
#include <map>
#include <cctype>

#include "../Module/Module.h"

class Lexical
{
	private:
		
		std::string Source;	//���ڴ洢�����Դ���� 
		Word_List Target;	//���ڴ洢ת����ĵ����б�
		
		std::map<std::string,int> Symbol_Table;	//���ڴ洢���������ű� 
		
		int Get_Var_Number(std::string);	//���ر������Ķ�Ӧ��� 
		
		Word Get_Keyword(int&);	//�жϴ�pos��ʼ�ĵ�һ�������Ƿ�Ϊ�ؼ��֣������ظõ��ʲ�����pos 
	
		Word Get_Var(int&);	//�жϴ�pos��ʼ�ĵ�һ�������Ƿ�Ϊ�������������ظõ��ʲ�����pos 
	
		Word Get_Number(int&);	//�жϴ�pos��ʼ�ĵ�һ�������Ƿ�Ϊ�����������ظõ��ʲ�����pos
	
		Word Get_Symbol(int&);	//�жϴ�pos��ʼ�ĵ�һ�������Ƿ�Ϊ���ţ������ظõ��ʲ�����pos

		Word Get_Next_Word(int&);	//��Դ�����е�pos���ַ���ʼ��ȡ��һ�����ʲ����أ�������pos 
		
	public:
		
		void init();	//��ʼ������ 
		void Input(std::string);	//���뺯�������ڶ���Դ���벢��ʼ�� 
		bool Analysis();	//��Դ������дʷ����� 
		Word_List Output();	//���ص����б� 
};
