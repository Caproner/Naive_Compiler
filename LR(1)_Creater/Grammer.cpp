#include "Grammer.h"
#include <cstdio>
#include <conio.h>

bool Closure_Unit::operator ==(const Closure_Unit &p)const
{
	if(p.follow!=follow)return false;
	if(p.num!=num)return false;
	if(p.pos!=pos)return false;
	return true;
}

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

bool Closure::operator ==(const Closure &p)const
{
	set<Closure_Unit>::iterator it=Closure_Set.begin();
	set<Closure_Unit>::iterator jt=p.Closure_Set.begin();
	while(it!=Closure_Set.end())
	{
		if(jt==p.Closure_Set.end())return false;
		if(!((*it)==(*jt)))return false;
		it++;
		jt++;
	}
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
	
	this->FIRST[0].insert(0);
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

void Grammer::Closure_Build(int pos)
{
	bool flag=true;
	Closure &C=this->DFA_Node[pos];
	
	while(flag)
	{
		flag=false;
		vector<Closure_Unit> v;
		for(set<Closure_Unit>::iterator it=C.Closure_Set.begin();it!=C.Closure_Set.end();it++)
		{
			Closure_Unit U=*it;
			if(U.pos==U.G.V.size())continue;
			int First_num;
			if(U.pos==U.G.V.size()-1)First_num=U.follow;
			else First_num=U.G.V[U.pos+1];
			set<int> &st=this->FIRST[First_num];
			for(int i=0;i<this->Grammer_List.size();i++)
			{
				Grammer_Unit GU=this->Grammer_List[i];
				if(GU.U!=U.G.V[U.pos])continue;
				for(set<int>::iterator jt=st.begin();jt!=st.end();jt++)
				{
					Closure_Unit CU;
					CU.init(GU,*jt);
					CU.num=i;
					v.push_back(CU);
				}
			}
		}
		
		for(int i=0;i<v.size();i++)
		{
			int sz=C.Closure_Set.size();
			C.Closure_Set.insert(v[i]);
			if(sz!=C.Closure_Set.size())flag=true;
		}
	}
}

void Grammer::DFA_init()
{
	for(int i=0;i<1005;i++)
	{
		this->DFA_Node[i].init();
		this->DFA_Edge_W[i].clear();
		this->DFA_Edge_Next[i].clear();
	}
	
	Closure C;
	C.init();
	
	Closure_Unit CU;
	CU.init(this->Grammer_List[0],0);
	CU.num=0;
	C.Insert(CU);
	
	this->DFA_Node[0]=C;
	this->Closure_Build(0);
	this->DFA_Node_Cnt=1;
}

void Grammer::DFA_Build(int pos)
{
	Closure C=this->DFA_Node[pos];
	for(int i=1;i<this->FIRST.size();i++)
	{
		Closure PC=C.Update(i);
		if(PC.Closure_Set.size()==0)continue;
		this->DFA_Node[this->DFA_Node_Cnt++]=PC;
		int DFA_pos=this->DFA_Node_Cnt-1;
		this->Closure_Build(DFA_pos);
		
		
		bool flag=true;
		for(int j=0;j<this->DFA_Node_Cnt-1;j++)
		{
			if(this->DFA_Node[j]==this->DFA_Node[DFA_pos])
			{
				DFA_pos=j;
				this->DFA_Node_Cnt--;
				flag=false;
				break;
			}
		}
		printf("%d--%c-->%d\n",pos,this->Number_to_Char[i],DFA_pos);
		this->DFA_Edge_Next[pos].push_back(DFA_pos);
		this->DFA_Edge_W[pos].push_back(i);
		if(flag)
			this->DFA_Build(DFA_pos);
	}
}

void Grammer::print(int i)
{
	printf("Closure #%d\n",i);
	Closure C=this->DFA_Node[i];
	for(set<Closure_Unit>::iterator it=C.Closure_Set.begin();it!=C.Closure_Set.end();it++)
	{
		Closure_Unit CU=*it;
		printf("%c-",this->Number_to_Char[CU.G.U]);
		for(int j=0;j<CU.G.V.size();j++)
		{
			if(j==CU.pos)printf("¡¤");
			printf("%c",this->Number_to_Char[CU.G.V[j]]);
		}
		if(CU.pos==CU.G.V.size())printf("¡¤");
		printf(", %c\n",this->Number_to_Char[CU.follow]);
	}
	printf("\n");
}
