#include <vector>

//�����࣬���ڴʷ������еĵ��ʻ��� 
class Word
{
	public:
		int Number;	//���ʵ������� 
		int Value;	//���ʵ�����ֵ 
};

//�����б��࣬������Ϊ�ʷ������Ľ�� 
class Word_List
{
	public:
		vector<Word> v;
};

//������࣬�����﷨������� 
class TreeNode
{
	public:
		Word Node_Word;	//�������Ӧ�ĵĵ��� 
		vector<TreeNode*> Next;	//���Ķ���ָ���б� 
		TreeNode *Parent;	//���ĸ���ָ�� 
};

//�﷨���࣬������Ϊ�﷨�����Ľ�� 
class Tree
{
	public:
		TreeNode *root;	//���ĸ���� 
};
