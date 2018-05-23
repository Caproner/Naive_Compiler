#include "Lexical/Lexical.h"
#include <iostream>

using namespace std;

int main()
{
	Lexical L;
	L.init();
	
	string s;
	while(cin>>s)
	{
		L.Input(s);
		if(L.Analysis())
		{
			Word_List ret=L.Output();
			for(int i=0;i<ret.List.size();i++)
			{
				cout<<"["<<ret.List[i].Number<<","<<ret.List[i].Value<<"]"<<endl;
			}
			cout<<"End"<<endl;
		}
		else
		{
			cout<<"Error!"<<endl;
		}
	}
}
