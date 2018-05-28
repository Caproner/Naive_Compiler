#include "Lexical/Lexical.h"
#include "Grammar/Grammar.h"
#include "Semantic/Semantic.h"

#include <iostream>

//#define TEST

using namespace std;


void print(TreeNode *p)
{
	cout<<"Current Address: "<<p<<endl;
	cout<<"Word: ("<<p->Node_Word.Number<<","<<p->Node_Word.Value<<")"<<endl;
	cout<<"Son_Count: "<<p->Next.size()<<endl;
	for(int i=0;i<p->Next.size();i++)
	{
		cout<<"\tAddress: "<<p->Next[i]<<endl;
	}
	cout<<"Parent: "<<p->Parent<<endl;
	cout<<endl;
	for(int i=0;i<p->Next.size();i++)
	{
		print(p->Next[i]);
	}
}

char Read[100005];

int main(int argc,char *argv[])
{
	Lexical L;
	L.init();
	
	Grammar G;
	G.init();
	
	Semantic S;
	S.init();
	
	FILE *Input;
	if(argc!=1)Input=fopen(argv[1],"r");
	
	string s;
	while(true)
	{
		if(argc==1)
		{
			if(!getline(cin,s))break;
		}
		else
		{
			if(fgets(Read,100000,Input)==NULL)break;
			s=Read;
		}
		L.Input(s);
		if(!L.Analysis())
		{
			cout<<"Error���ʷ���������"<<endl;
			continue;
		}
		
		Word_List WL=L.Output();
		#ifdef TEST
		for(int i=0;i<WL.List.size();i++)
		{
			cout<<"["<<WL.List[i].Number<<","<<WL.List[i].Value<<"]"<<endl;
		}
		cout<<"�ʷ���������"<<endl;
		#endif
		
		G.Input(WL);
		if(!G.Analysis())
		{
			cout<<"Error���﷨��������"<<endl;
			continue;
		}
		
		Forest F=G.Output();
		#ifdef TEST
		for(int i=0;i<F.forest.size();i++)
		{
			cout<<"�����"<<i+1<<"���﷨��"<<endl;
			print(F.forest[i]);
		}
		cout<<"�﷨��������"<<endl;
		#endif
		
		if(!S.Analysis(F))
		{
			cout<<"Error�������������"<<endl;
			continue; 
		}
		
		#ifdef TEST
		for(int i=0;i<F.forest.size();i++)
		{
			cout<<"�����"<<i+1<<"���﷨��"<<endl;
			print(F.forest[i]);
		}
		cout<<"�����������"<<endl;
		#endif
	}
	
}
