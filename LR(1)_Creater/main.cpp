#include "Grammer.h"
#include <iostream>

using namespace std;

int main()
{
	Grammer G;
	G.init();
	string s;
	
	while(cin>>s)
	{
		G.Push_Back(s);
	}
	
	G.Create_FIRST();
	G.Create_FOLLOW();
	
	for(int i=0;i<G.Char_to_Number.size();i++)
		cout<<i<<" "<<G.Number_to_Char[i]<<endl;

	for(int i=1;i<G.FIRST.size();i++)
	{
		cout<<"FIRST("<<G.Number_to_Char[i]<<")={";
		for(set<int>::iterator it=G.FIRST[i].begin();it!=G.FIRST[i].end();it++)
		{
			if(it!=G.FIRST[i].begin())cout<<",";
			cout<<G.Number_to_Char[*it];
		}
		cout<<"}"<<endl;
	}
	
	for(int i=1;i<G.FOLLOW.size();i++)
	{
		cout<<"FOLLOW("<<G.Number_to_Char[i]<<")={";
		for(set<int>::iterator it=G.FOLLOW[i].begin();it!=G.FOLLOW[i].end();it++)
		{
			if(it!=G.FOLLOW[i].begin())cout<<",";
			cout<<G.Number_to_Char[*it];
		}
		cout<<"}"<<endl;
	}
}
