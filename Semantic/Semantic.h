#include "../Module/Module.h"

class Semantic
{
	private:
		
		std::map<int,double> Var_Space;	//变量空间，用于存储当前有哪些变量，以及他们的值 
		
		bool DFS(TreeNode*,double&);	//对以TreeNode为根的语法树进行DFS 
		
	public:
		
		void init();	//初始化 
		
		bool Analysis(Forest);	//对该语法森林进行语义分析和生成结果，返回语义分析是否成功 
};
