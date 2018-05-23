#include <vector>
#include <set>
#include <map>
#include <string>
#include <cctype>

using namespace std;

class Grammer_Unit
{
	public:
		int U;
		vector<int> V;
};

class Grammer
{
	public:
		vector<Grammer_Unit> Grammer_List;
		
		map<char,int> Char_to_Number;
		map<int,char> Number_to_Char;
		
		vector< set<int> > FIRST;
		vector< set<int> > FOLLOW;
		
		int Find(char);
		bool Add_Set(set<int>&,set<int>&);
		
		void init();
		void Push_Back(string);
		void Create_FIRST();
		void Create_FOLLOW();
};
