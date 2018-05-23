#include "Grammer.h"
#include <cstdio>

bool Grammer::Add_Set(set<int> &S,set<int> &s)
{
	bool ret=false;
	for(set<int>::iterator it=s.begin();it!=s.end();it++)
	{
		if(S.find(*it)!=S.end())continue;
		ret=true;
		S.insert(*it);
	}
	return ret;
}

int Grammer::Find(char c)
{
	if(this->Char_to_Number[c]==0)
	{
		int num=this->Char_to_Number.size();
		this->Char_to_Number[c]=num;
		this->Number_to_Char[num]=c;
	}
	return this->Char_to_Number[c];
}

void Grammer::init()
{
	this->Grammer_List.clear();
	this->Number_to_Char.clear();
	this->Char_to_Number.clear();
	this->Number_to_Char[-1]='#';
	this->Char_to_Number['#']=-1;
}

void Grammer::Push_Back(string s)
{
	Grammer_Unit GU;
	GU.U=this->Find(s[0]);
	for(int i=3;i<s.length();i++)
		GU.V.push_back(this->Find(s[i]));
	this->Grammer_List.push_back(GU);
}

void Grammer::Create_FIRST()
{
	this->FIRST.clear();
	for(int i=0;i<=this->Char_to_Number.size();i++)
	{
		set<int> st;
		if((i>0)&&(!isupper(this->Number_to_Char[i])))
		{
			st.insert(i);
		}
		this->FIRST.push_back(st);
	}
	
	bool flag=true;
	while(flag)
	{
		flag=false;
		for(int i=0;i<this->Grammer_List.size();i++)
		{
			int u=this->Grammer_List[i].U;
			int v=this->Grammer_List[i].V[0];
			if(!isupper(this->Number_to_Char[v]))
			{
				if(this->FIRST[u].find(v)!=this->FIRST[u].end())continue;
				flag=true;
				this->FIRST[u].insert(v);
			}
			else
			{
				if(u==v)continue;
				flag=flag|this->Add_Set(this->FIRST[u],this->FIRST[v]);
			}
		}
	}
}

void Grammer::Create_FOLLOW()
{
	this->FOLLOW.clear();
	for(int i=0;i<=this->Char_to_Number.size();i++)
	{
		set<int> st;
		this->FOLLOW.push_back(st);
	}
	
	FOLLOW[this->Char_to_Number['X']].insert(-1);
	
	bool flag=true;
	while(flag)
	{
		flag=false;
		for(int i=0;i<this->Grammer_List.size();i++)
		{
			int u=this->Grammer_List[i].U;
			for(int j=0;j<this->Grammer_List[i].V.size();j++)
			{
				int v=this->Grammer_List[i].V[j];
				if(!isupper(this->Number_to_Char[v]))continue;
				if(j==this->Grammer_List[i].V.size()-1)
				{
					if(u==v)continue;
					flag=flag|this->Add_Set(this->FOLLOW[v],this->FOLLOW[u]);
				}
				else
				{
					int vv=this->Grammer_List[i].V[j+1];
					flag=flag|this->Add_Set(this->FOLLOW[v],this->FIRST[vv]);
				}
			}
		}
	}
}
