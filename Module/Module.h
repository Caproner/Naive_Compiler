#include <vector>

#ifndef MODULE
#define MODULE

//单词类，用于词法分析中的单词划分 
class Word
{
	public:
		int Number;	//单词的种类编号 
		double Value;	//单词的内码值 
		
		//构造函数 
		Word(int nn=0,double vv=0):Number(nn),Value(vv){} 
};

//单词列表类，用于作为词法分析的结果 
class Word_List
{
	public:
		std::vector<Word> List;
};

//树结点类，用于语法树的组成 
class TreeNode
{
	public:
		Word Node_Word;	//结点所对应的的单词 
		std::vector<TreeNode*> Next;	//结点的儿子指针列表 
		TreeNode *Parent;	//结点的父亲指针 
};

//语法森林类，用于存储多个语法树，用于作为语法分析的结果 
class Forest
{
	public:
		std::vector<TreeNode*> forest;
};

#endif
