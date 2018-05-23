#include "Grammer.h"
#include <cstdio>

bool Closure_Unit::operator <(const Closure_Unit &p)const
{
	if(num!=p.num)return num<p.num;
	if(pos!=p.pos)return pos<p.pos;
	return follow<p.follow;
}

void Closure_Unit::init(Grammer_Unit g,int f)
{
	this->G=g;
	this->pos=0;
	this->follow=f;
}

bool Closure_Unit::Update(int C)
{
	if(pos==G.V.size())return false;
	if(G.V[pos]!=C)return false;
	pos++;
	return true;
}


void Closure::init()
{
	this->Closure_Set.clear();
}

void Closure::Insert(Closure_Unit U)
{
	this->Closure_Set.insert(U);
}

Closure Closure::Update(int C)
{
	Closure ret;
	ret.init();
	for(set<Closure_Unit>::iterator it=this->Closure_Set.begin();it!=this->Closure_Set.end();it++)
	{
		Closure_Unit CU=*it;
		if(CU.Update(C))
			ret.Insert(CU);
	}
	return ret;
}

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
		int num=this->Char_to_Number.size()-1;
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
	this->Number_to_Char[0]='#';
	this->Char_to_Number['#']=0;
}

void Grammer::Push_Back(string s)
{
	Grammer_Unit GU;
	GU.U=this->Find(s[0]);
	for(int i=2;i<s.length();i++)
		GU.V.push_back(this->Find(s[i]));
	this->Grammer_List.push_back(GU);
}

void Grammer::Create_FIRST()
{
	this->FIRST.clear();
	for(int i=0;i<this->Char_to_Number.size();i++)
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
	for(int i=0;i<this->Char_to_Number.size();i++)
	{
		set<int> st;
		this->FOLLOW.push_back(st);
	}
	
	FOLLOW[this->Char_to_Number['X']].insert(0);
	
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




