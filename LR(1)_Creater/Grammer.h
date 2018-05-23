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

class Closure_Unit
{
	public:
		int num;
		Grammer_Unit G;
		int pos;
		int follow;
		
		bool operator <(const Closure_Unit &)const;
		
		void init(Grammer_Unit,int);
		bool Update(int);
};

class Closure
{
	public:
		set<Closure_Unit> Closure_Set;
		int number;
		
		void init();
		void Insert(Closure_Unit);
		Closure Update(int);
};

class Grammer
{
	public:
		
		//输入和预处理部分 
		
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
		
		//DFA部分
		
		vector<Closure> DFA_Node;
		vector<int> DFA_Edge_Next;
		vector<int> DFA_Edge_W; 
		
		void Closure_Build(int);
		void DFA_init();
		void DFA_Build(int);
		
		//表部分
		
		vector< vector<int> > ACTION;	//正数表示移进，负数表示归约，零表示acc 
		vector< vector<int> > GOTO; 
		
		void Table_init();
};
