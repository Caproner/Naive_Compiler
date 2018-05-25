#include <vector>
#include <stack>
#include <string>
#include <map>
#include <cstdio>
#include <algorithm>

#include "../Module/Module.h"

class Grammar
{
	private:
		
		std::vector<Word_List> Handle_List;	//���ڴ洢�����б�ÿ������Ϊһ�������б� 
		
		Forest Grammar_Forest;	//���ڴ洢�������ɵ��﷨ɭ��
		
		std::vector<std::string> Grammars;	//�洢�ķ� 
		
		std::map<std::pair<char,int>,int> ACTION;	//LR(1)�������е�ACTION�� 
		
		std::map<std::pair<char,int>,int> GOTO;	//LR(1)�������е�GOTO�� 
		
		std::stack<int> Status_Stack;	//״̬ջ
		
		std::stack<TreeNode*> Symbol_Stack;	//����ջ
		
		std::map<int,char> Number_to_Symbol;	//���ֱ����ӳ�䵽���ս��ַ���ӳ�� 
		
		void Delete(TreeNode*);	//�ݹ�ɾ���� 
		
		bool Handle_Analysis(int);	//�Ե�pos���������﷨�������������﷨������ɭ�� 
		 
	public:
		
		void init();	//��ʼ������ 
		
		void Input(Word_List);	//��������ʷ������Ľ���������䰴�ֺŷ־� 
		
		bool Analysis();	//�Ե����б�����﷨����
		
		Forest Output();	//�����﷨ɭ�� 
};
