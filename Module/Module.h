#include <vector>

//�����࣬���ڴʷ������еĵ��ʻ��� 
class Word
{
	public:
		int Number;	//���ʵ������� 
		double Value;	//���ʵ�����ֵ 
		
		//���캯�� 
		Word(int nn=0,double vv=0):Number(nn),Value(vv){} 
};

//�����б��࣬������Ϊ�ʷ������Ľ�� 
class Word_List
{
	public:
		std::vector<Word> List;
};

//������࣬�����﷨������� 
class TreeNode
{
	public:
		Word Node_Word;	//�������Ӧ�ĵĵ��� 
		std::vector<TreeNode*> Next;	//���Ķ���ָ���б� 
		TreeNode *Parent;	//���ĸ���ָ�� 
};

//�﷨���࣬������Ϊ�﷨�����Ľ�� 
class Tree
{
	public:
		TreeNode *root;	//���ĸ���� 
};
