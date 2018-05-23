#include <string>
#include <vector>
#include <map>
#include <cctype>

#include "../Module/Module.h"

class Lexical
{
	private:
		
		std::string Source;	//用于存储读入的源代码 
		Word_List Target;	//用于存储转换后的单词列表
		
		std::map<std::string,int> Symbol_Table;	//用于存储变量名符号表 
		
		int Get_Var_Number(std::string);	//返回变量名的对应编号 
		
		Word Get_Keyword(int&);	//判断从pos开始的第一个单词是否为关键字，并返回该单词并更新pos 
	
		Word Get_Var(int&);	//判断从pos开始的第一个单词是否为变量名，并返回该单词并更新pos 
	
		Word Get_Number(int&);	//判断从pos开始的第一个单词是否为常数，并返回该单词并更新pos
	
		Word Get_Symbol(int&);	//判断从pos开始的第一个单词是否为符号，并返回该单词并更新pos

		Word Get_Next_Word(int&);	//从源代码中第pos个字符开始提取第一个单词并返回，并更新pos 
		
	public:
		
		void init();	//初始化函数 
		void Input(std::string);	//读入函数，用于读入源代码并初始化 
		bool Analysis();	//对源代码进行词法分析 
		Word_List Output();	//返回单词列表 
};
