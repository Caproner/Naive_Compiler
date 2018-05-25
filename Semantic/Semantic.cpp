#include "Semantic.h"

//对以TreeNode为根的语法树进行DFS 
//若出现语义错误则返回false 
bool Semantic::DFS(TreeNode *p)
{
	if(p->Next.size()==0)return true;
	
	for(int i=0;i<p->Next.size();i++)
	{
		if(!(this->DFS(p->Next[i])))return false;
	}
	
	if(p->Next.size()==1)
	{
		TreeNode *q=p->Next[0];
		p->Node_Word.Number=q->Node_Word.Number;
		p->Node_Word.Value=q->Node_Word.Value;
		return true;
	}
	
	if(p->Next.size()==2)
	{
		TreeNode *a=p->Next[0];
		TreeNode *b=p->Next[1];
		if(a->Node_Word.Number==1)
		{
			if(this->Var_Space.find(b->Node_Word.Value)!=this->Var_Space.end())
				return false;
			this->Var_Space[b->Node_Word.Value]=0;
			return true;
		}
		else
		{
			if(this->Var_Space.find(b->Node_Word.Value)==this->Var_Space.end())
				return false;
			printf("%lf\n",this->Var_Space[b->Node_Word.Value]);
			return true;
		}
	}
	
	if(p->Next.size()==3)
	{
		TreeNode *a=p->Next[0];
		TreeNode *b=p->Next[1];
		TreeNode *c=p->Next[2];
		if(a->Node_Word.Number==10)
		{
			p->Node_Word.Number=b->Node_Word.Number;
			p->Node_Word.Value=b->Node_Word.Value;
			return true;
		}
		if(b->Node_Word.Number==9)
		{
			if(this->Var_Space.find(a->Node_Word.Value)==this->Var_Space.end())
				return false;
			this->Var_Space[a->Node_Word.Value]=c->Node_Word.Value;
			return true;
		}
		if(a->Node_Word.Number==3)
		{
			if(this->Var_Space.find(a->Node_Word.Value)==this->Var_Space.end())
				return false;
			a->Node_Word.Number=4;
			a->Node_Word.Value=this->Var_Space[a->Node_Word.Value];
		}
		if(c->Node_Word.Number==3)
		{
			if(this->Var_Space.find(c->Node_Word.Value)==this->Var_Space.end())
				return false;
			c->Node_Word.Number=4;
			c->Node_Word.Value=this->Var_Space[c->Node_Word.Value];
		}
		if((b.Node_Word.Number==8)&&(c->Node_Word.Value==0))return false;
		p->Node_Word.Number=4;
		if(b.Node_Word.Number==5)
			p->Node_Word.Value=a.Node_Word.Value+c.Node_Word.Value;
		if(b.Node_Word.Number==6)
			p->Node_Word.Value=a.Node_Word.Value-c.Node_Word.Value;
		if(b.Node_Word.Number==7)
			p->Node_Word.Value=a.Node_Word.Value*c.Node_Word.Value;
		if(b.Node_Word.Number==8)
			p->Node_Word.Value=a.Node_Word.Value/c.Node_Word.Value;
		return true;
	}
	
	if(p->Next.size()==4)
	{
		TreeNode *a=p->Next[0];
		TreeNode *b=p->Next[1];
		TreeNode *c=p->Next[2];
		TreeNode *d=p->Next[3];
		if(this->Var_Space.find(b->Node_Word.Value)!=this->Var_Space.end())
			return false;
		this->Var_Space[b->Node_Word.Value]=d->Node_Word.Value;
		return true;
	}
}

//初始化 
void Semantic::init()
{
	this->Var_Space.clear();
}

//对该语法森林进行语义分析和生成结果，返回语义分析是否成功
bool Semantic::Analysis(Forest &F)
{
	for(int i=0;i<F.forest.size();i++)
	{
		TreeNode *p=F.forest[i];
		if(this->DFS(p))continue;
		return false;
	}
	return true;
}
