#include "Grammer.h"
#include <iostream>

using namespace std;

int main()
{
	FILE *fp=fopen("Analysis_Table.txt","w+");
	Grammer G;
	G.init();
	string s;
	
	vector<string> Grammar_List;
	
	while(cin>>s)
	{
		G.Push_Back(s);
		Grammar_List.push_back(s);
	}
	fprintf(fp,"%d\n",Grammar_List.size());
	for(int i=0;i<Grammar_List.size();i++)
		fprintf(fp,"%s\n",Grammar_List[i].c_str());
	
	G.Create_FIRST();
	G.Create_FOLLOW();
	
	cout<<"�ַ������еı��Ϊ��"<<endl;
	
	for(int i=0;i<G.Char_to_Number.size();i++)
	{
		cout<<i<<" "<<G.Number_to_Char[i]<<endl;
	}

	cout<<"ÿ���ַ���FIRST��Ϊ��"<<endl;
	
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
	
	cout<<"ÿ���ַ���FOLLOW��Ϊ��"<<endl;
	
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
	
	cout<<"DFA�ıߵ���ϢΪ��"<<endl;
	
	G.DFA_init();
	G.DFA_Build(0);
	
	cout<<"DFAÿ�����ıհ�����ϢΪ��"<<endl;
	
	for(int i=0;i<G.DFA_Node_Cnt;i++)
	{
		G.print(i);
	}
	
	cout<<"�������ɵ�LR(1)���������ϢΪ��"<<endl;
	
	G.Table_init(fp);
	fclose(fp);
}
