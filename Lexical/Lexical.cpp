#include "Lexical.h"

#include <cstdio>
#include <conio.h>

//返回变量名的对应编号
int Lexical::Get_Var_Number(std::string s)
{
	if(this->Symbol_Table[s]==0)
	{
		int num=this->Symbol_Table.size();
		this->Symbol_Table[s]=num;
	}
	return this->Symbol_Table[s];
}

//判断从pos开始的第一个单词是否为关键字，并返回该单词并更新pos 
Word Lexical::Get_Keyword(int &pos)
{
	if(pos+2<this->Source.length())
	{
		std::string check;
		check+=this->Source[pos];
		check+=this->Source[pos+1];
		check+=this->Source[pos+2];
		if(check=="var")
		{
			pos+=3;
			return Word(1,0);
		}
	}
	
	if(pos+4<this->Source.length())
	{
		std::string check;
		check+=this->Source[pos];
		check+=this->Source[pos+1];
		check+=this->Source[pos+2];
		check+=this->Source[pos+3];
		check+=this->Source[pos+4];
		if(check=="print")
		{
			pos+=5;
			return Word(2,0);
		}
	}
	
	return Word(-1,0);
} 
	
//判断从pos开始的第一个单词是否为变量名，并返回该单词并更新pos
Word Lexical::Get_Var(int &pos)
{
	if(!isalpha(this->Source[pos]))return Word(-1,0);
	
	std::string s;

	while((pos<this->Source.length())&&(isalpha(this->Source[pos]))||(isdigit(this->Source[pos])))
	{
		s+=this->Source[pos];
		pos++;
	}
	
	return Word(3,this->Get_Var_Number(s));
}

//判断从pos开始的第一个单词是否为常数，并返回该单词并更新pos
Word Lexical::Get_Number(int &pos)
{	
	if(!isdigit(this->Source[pos]))return Word(-1,0);
	
	double ret=0;
	
	while((pos<this->Source.length())&&(isdigit(this->Source[pos])))
	{
		ret=ret*10+(this->Source[pos]-'0');
		pos++;
	}
	
	if(this->Source[pos]=='.')
	{
		double k=0.1;
		pos++;
		while((pos<this->Source.length())&&(isdigit(this->Source[pos])))
		{
			ret=ret+(this->Source[pos]-'0')*k;
			pos++;
			k/=10;
		}
	}
	
	return Word(4,ret);
}
	
//判断从pos开始的第一个单词是否为符号，并返回该单词并更新pos
Word Lexical::Get_Symbol(int &pos)
{
	switch(this->Source[pos])
	{
		case '+':pos++;return Word(5,0);break;
		case '-':pos++;return Word(6,0);break;
		case '*':pos++;return Word(7,0);break;
		case '/':pos++;return Word(8,0);break;
		case '=':pos++;return Word(9,0);break;
		case '(':pos++;return Word(10,0);break;
		case ')':pos++;return Word(11,0);break;
		case ';':pos++;return Word(12,0);break;
		default:return Word(-1,0);
	}
}


//从源代码中第pos个字符开始提取第一个单词并返回，并更新pos 
//若提取出错返回Error 
Word Lexical::Get_Next_Word(int &pos)
{
	Word ret;
	
	ret=this->Get_Keyword(pos);
	if(ret.Number!=-1)return ret;
	
	ret=this->Get_Var(pos);
	if(ret.Number!=-1)return ret;
	
	ret=this->Get_Number(pos);
	if(ret.Number!=-1)return ret;
	
	ret=this->Get_Symbol(pos);
	if(ret.Number!=-1)return ret;
	
	return Word(-1,0);
} 

//初始化函数
void Lexical::init()
{
	this->Symbol_Table.clear();
} 

//读入函数，用于读入源代码并初始化
void Lexical::Input(std::string S) 
{
	this->Source=S;
	this->Target.List.clear();
}

//对源代码进行词法分析 
//若词法分析出错则返回false 
bool Lexical::Analysis()
{
	int pos=0;
	while(pos<this->Source.length())
	{
		if(!isgraph(this->Source[pos]))
		{
			pos++;
			continue;
		}
		Word w=this->Get_Next_Word(pos);
		if(w.Number==-1)
		{
			this->Target.List.clear();
			return false;
		} 
		this->Target.List.push_back(w);
	}
	return true;
}

//返回单词列表
Word_List Lexical::Output()
{
	return this->Target;
}
