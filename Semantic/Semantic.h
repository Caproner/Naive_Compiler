#include <map>
#include <cstdio>

#include "../Module/Module.h"

class Semantic
{
	private:
		
		std::map<double,double> Var_Space;	//�����ռ䣬���ڴ洢��ǰ����Щ�������Լ����ǵ�ֵ 
		
		bool DFS(TreeNode*);	//����TreeNodeΪ�����﷨������DFS 
		
	public:
		
		void init();	//��ʼ�� 
		
		bool Analysis(Forest&);	//�Ը��﷨ɭ�ֽ���������������ɽ����������������Ƿ�ɹ� 
};
