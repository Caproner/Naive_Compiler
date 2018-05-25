#include "Grammar.h"

#define TEST

void Grammar::Delete(TreeNode *p)
{
	for(int i=0;i<p->Next.size();i++)
	{
		this->Delete(p->Next[i]);
	}
	delete p;
} 

//对第pos个语句进行语法分析，并生成语法树加入森林 
bool Grammar::Handle_Analysis(int pos)
{
	while(!(this->Status_Stack.empty()))
		this->Status_Stack.pop();
	while(!(this->Symbol_Stack.empty()))
	{
		TreeNode *p=this->Symbol_Stack.top();
		this->Symbol_Stack.pop();
		this->Delete(p);
	}
	
	Word_List &WL=this->Handle_List[pos];
	WL.List.push_back(Word(14,0));
	this->Status_Stack.push(0);
	
	int cur=0;
	
	bool ret=true;
	
	#ifdef TEST
	int Count=1;
	#endif
	
	while(true)
	{
		#ifdef TEST
		printf("%d: ",Count++);
		#endif
		if(cur==WL.List.size())
		{
			ret=false;
			break;
		}
		char &C=this->Number_to_Symbol[WL.List[cur].Number];
		int &S=this->Status_Stack.top();
		if(this->ACTION.find(std::make_pair(C,S))==this->ACTION.end())
		{
			ret=false;
			break;
		}
		int Status_Code=this->ACTION[std::make_pair(C,S)];
		#ifdef TEST
		printf("Find ACTION[%c,%d] = %d, ",C,S,Status_Code);
		#endif
		if(Status_Code==0)
		{
			#ifdef TEST
			printf("Accept!\n");
			#endif
			break;
		}
		else if(Status_Code>0)
		{
			#ifdef TEST
			printf("Push_Back %d\n",Status_Code);
			#endif
			this->Status_Stack.push(Status_Code);
			TreeNode *p=new TreeNode;
			p->Next.clear();
			p->Parent=NULL;
			p->Node_Word=WL.List[cur];
			this->Symbol_Stack.push(p);
			cur++;
		}
		else
		{
			Status_Code=-Status_Code;
			char U_Symbol=this->Grammars[Status_Code][0];
			#ifdef TEST
			printf("Reduce: %s, ",this->Grammars[Status_Code].c_str());
			#endif
			int len=this->Grammars[Status_Code].length();
			TreeNode *p=new TreeNode;
			p->Next.clear();
			p->Parent=NULL;
			p->Node_Word=Word(13,0);
			for(int i=0;i<len-2;i++)
			{
				if(this->Symbol_Stack.empty())
				{
					ret=false;
					break;
				}
				TreeNode *q=this->Symbol_Stack.top();
				this->Symbol_Stack.pop();
				p->Next.push_back(q);
				q->Parent=p;
				this->Status_Stack.pop();
			}
			if(!ret)break;
			std::reverse(p->Next.begin(),p->Next.end());
			if(this->GOTO.find(std::make_pair(U_Symbol,this->Status_Stack.top()))==this->GOTO.end())
			{
				ret=false;
				break;
			}
			#ifdef TEST
			printf("Push_Back GOTO[%c,%d]=%d\n",U_Symbol,this->Status_Stack.top(),this->GOTO[std::make_pair(U_Symbol,this->Status_Stack.top())]);
			#endif
			this->Status_Stack.push(this->GOTO[std::make_pair(U_Symbol,this->Status_Stack.top())]);
			this->Symbol_Stack.push(p);
		}
	}
	if(ret)
	{
		this->Grammar_Forest.forest.push_back(this->Symbol_Stack.top());
		this->Symbol_Stack.pop();
	}
	else
	{
		while(!(this->Symbol_Stack.empty()))
		{
			TreeNode *p=this->Symbol_Stack.top();
			this->Symbol_Stack.pop();
			this->Delete(p);
		}
	}
	return ret;
}	
		 
//初始化函数 
void Grammar::init()
{
	this->ACTION.clear();
	this->GOTO.clear();
	this->Grammars.clear();
	
	this->Number_to_Symbol.clear();
	this->Number_to_Symbol[1]='v';
	this->Number_to_Symbol[2]='p';
	this->Number_to_Symbol[3]='x';
	this->Number_to_Symbol[4]='c';
	this->Number_to_Symbol[5]='+';
	this->Number_to_Symbol[6]='-';
	this->Number_to_Symbol[7]='*';
	this->Number_to_Symbol[8]='/';
	this->Number_to_Symbol[9]='=';
	this->Number_to_Symbol[10]='(';
	this->Number_to_Symbol[11]=')'; 
	this->Number_to_Symbol[14]='#';
	
	FILE *fp=fopen("Analysis_Table.txt","r");
	char Grammar_String[105];
	int Cnt;
	fscanf(fp,"%d",&Cnt);
	while(Cnt--)
	{
		fscanf(fp,"%s",Grammar_String);
		std::string s=Grammar_String;
		this->Grammars.push_back(s);
	}
	char Tag[3],Symbol[3];
	int Status,Target;
	while(~fscanf(fp,"%s",Tag))
	{
		fscanf(fp,"%s",Symbol);
		fscanf(fp,"%d",&Status);
		fscanf(fp,"%d",&Target);
		if(Tag[0]=='G')this->GOTO[std::make_pair(Symbol[0],Status)]=Target;
		else this->ACTION[std::make_pair(Symbol[0],Status)]=Target;
	}
}
		
//用于输入词法分析的结果，并将其按分号分句
void Grammar::Input(Word_List WL)
{
	this->Handle_List.clear();
	Word_List PWL;
	
	for(int pos=0;pos<WL.List.size();pos++)
	{
		Word &W=WL.List[pos];
		if(W.Number==12)
		{
			this->Handle_List.push_back(PWL);
			PWL.List.clear();
		}
		else
		{
			PWL.List.push_back(W);
		}
	}
}
		
//对单词列表进行语法分析
bool Grammar::Analysis()
{
	this->Grammar_Forest.forest.clear();
	for(int i=0;i<this->Handle_List.size();i++)
	{
		if(this->Handle_Analysis(i))continue;
		return false;
	}
	return true;
}	
		
//返回语法森林 
Forest Grammar::Output()
{
	return this->Grammar_Forest;
}	
