#include "../Module/Module.h"

class Semantic
{
	private:
		
		std::map<int,double> Var_Space;	//�����ռ䣬���ڴ洢��ǰ����Щ�������Լ����ǵ�ֵ 
		
		bool DFS(TreeNode*,double&);	//����TreeNodeΪ�����﷨������DFS 
		
	public:
		
		void init();	//��ʼ�� 
		
		bool Analysis(Forest);	//�Ը��﷨ɭ�ֽ���������������ɽ����������������Ƿ�ɹ� 
};
