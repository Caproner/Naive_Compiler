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
		
		std::vector<Word_List> Handle_List;	//用于存储语句的列表，每个语句均为一个单词列表 
		
		Forest Grammar_Forest;	//用于存储最终生成的语法森林
		
		std::vector<std::string> Grammars;	//存储文法 
		
		std::map<std::pair<char,int>,int> ACTION;	//LR(1)分析表中的ACTION表 
		
		std::map<std::pair<char,int>,int> GOTO;	//LR(1)分析表中的GOTO表 
		
		std::stack<int> Status_Stack;	//状态栈
		
		std::stack<TreeNode*> Symbol_Stack;	//符号栈
		
		std::map<int,char> Number_to_Symbol;	//从种别编码映射到非终结字符的映射 
		
		void Delete(TreeNode*);	//递归删除树 
		
		bool Handle_Analysis(int);	//对第pos个语句进行语法分析，并生成语法树加入森林 
		 
	public:
		
		void init();	//初始化函数 
		
		void Input(Word_List);	//用于输入词法分析的结果，并将其按分号分句 
		
		bool Analysis();	//对单词列表进行语法分析
		
		Forest Output();	//返回语法森林 
};
