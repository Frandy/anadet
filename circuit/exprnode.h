/*
 * exprnode.h
 *
 *  Created on: Nov 16, 2012
 *      Author: chjd
 */

#ifndef EXPRNODE_H_
#define EXPRNODE_H_

#include "stdafx.hpp"

// for param node, using in .param,

enum class ExprNodeType
{
	// value
	VALUE,
	// param
	// PARAM,
	PARAMEXPR,
	PARAMDATA,
	PARAMFILE,
	// op
	OP,
	ADD,
	SUB,
	MUL,
	DIV,
	// func
	FUNC,		// this is ok, and enough, when this kind of node has a function member
	/*
	SIN,
	COS,
	EXP,
	ABS,
	GAUSS,		// gauss distribution
	AGAUSS,		// absolute gauss distribution
	UNIFORM, 	// uniform distribution
	*/
};

class ExprNode
{
public:
	ExprNode()=default;
	ExprNode(double v,ExprNodeType tp=ExprNodeType::VALUE):value(v),type(tp){}
	ExprNode(ExprNodeType tp):type(tp),value(){}
	virtual double Value() { return value;}
	virtual ~ExprNode(){}
protected:
	double value;
	ExprNodeType type;
};

/*
 * param node,
 * value cab define by expression, file, or data sequence
 */

class ParamNode:public ExprNode
{
public:
	ParamNode()=default;
	ParamNode(string nm,ExprNode* rt)
		:ExprNode(ExprNodeType::PARAMEXPR),index(0),name(nm){data.root = rt;}
	ParamNode(string nm,string tname,ExprNodeType tp=ExprNodeType::PARAMFILE)
		:ExprNode(tp),index(0),name(nm){
			data.seq.name = tname;
	}
// same as base class
/*	double Value(){
		return value;
	}
*/
	void Evaluate()
	{
		if(type==ExprNodeType::PARAMEXPR)
			value = data.root->Value();
		else
			value = data.seq.data[index++];
	}
	void Init(){
		switch(type)
		{
		case ExprNodeType::PARAMFILE:
			this->ReadFileData();
			break;
		case ExprNodeType::PARAMDATA:
			//this->InitSeqData();
			break;
		}
	}
	void Reset()
	{
		index = 0;
	}
	~ParamNode()
	{
		switch (type)
		{
		case ExprNodeType::PARAMEXPR:
			delete data.root;
			break;
		case ExprNodeType::PARAMFILE:
		{
			delete [] data.seq.data;
			data.seq.data = nullptr;
		}
			break;
		case ExprNodeType::PARAMDATA:
			data.seq.data = nullptr;
			break;
		}
	}
private:
	void ReadFileData(){
		assert(type==ExprNodeType::PARAMFILE);
		// data format, first row, size, and then the data,
		/*
		ifstream fp(data.seq.name.c_str());
		int size = 0;
		fp >> size; // >> endl;
		data.seq.data = new double[size];
		for(auto i=0;i<size;i++)
			fp >> data.seq.data[i];
		*/
		// maybe better to use C file read
		FILE* fp = fopen(data.seq.name.c_str(),"r");
		fscanf(fp,"%d\n",&(data.seq.size));
		data.seq.data = new double[data.seq.size];
		for(auto i=0;i<data.seq.size;i++)
			fscanf(fp,"%f\n",data.seq.data+i);

	}
	void InitSeqData(unordered_map<string,pair<int,double*> >& seqDataMap){
		assert(type==ExprNodeType::PARAMDATA);
		// seqDataMap, an hash_map in circuit, for keep seq data
		auto it = seqDataMap.find(data.seq.name);
		assert(it!=seqDataMap.end());
		data.seq.size = it->second.first;
		data.seq.data = it->second.second;
	}
private:
	int index;
	string name;

	// use union will save space, but not convenient, string can not be in union
	struct {
		ExprNode* root;
		struct {
			string name;
			int size;
			double* data; // or use vector
		}seq;
	}data;
};

/*
 * op node, +,-,*,/
 */

template<char op>
class ExprOpNode:public ExprNode
{
public:
	ExprOpNode()=default;
	ExprOpNode(ExprNodeType tp,ExprNode* pl,ExprNode* pr)
		:ExprNode(tp),left(pl),right(pr){}
	~ExprOpNode(){
		delete left;
		left = nullptr;
		delete right;
		right = nullptr;
	}
	double Value()
	{
		double vl = left->Value();
		double vr = right->Value();
		return OpFunc(vl, vr);
	}
private:
	double OpFunc(double& a,double& b);
private:
	ExprNode* left;
	ExprNode* right;
};


template<>
inline double ExprOpNode<'+'>::OpFunc(double& a,double& b)
{
	return a+b;
}

template<>
inline double ExprOpNode<'-'>::OpFunc(double& a,double& b)
{
	return a-b;
}

template<>
inline double ExprOpNode<'*'>::OpFunc(double& a,double& b)
{
	return a*b;
}

template<>
inline double ExprOpNode<'/'>::OpFunc(double& a,double& b)
{
	assert(b!=0); // double != ?
	return a/b;
}

template<>
class ExprOpNode<'m'>:public ExprNode
{
public:
	ExprOpNode()=default;
	ExprOpNode(ExprNodeType tp,ExprNode* pl,ExprNode* pr)
		:ExprNode(tp),right(pr){}
	~ExprOpNode(){
		delete right;
		right = nullptr;
	}
	double Value()
	{
		double vr = right->Value();
		return -vr;
	}
private:
	ExprNode* right;
};

typedef ExprOpNode<'+'> ExprAddNode;
typedef ExprOpNode<'-'> ExprSubNode;
typedef ExprOpNode<'*'> ExprMulNode;
typedef ExprOpNode<'/'> ExprDivNode;
typedef ExprOpNode<'m'> ExprNegNode;


namespace ExprFunc
{
class FuncSin
{
public:
	double operator()(vector<double>& argv)
	{
		assert(argv.size() == 1);
		return sin(argv[0]);
	}
};
class FuncCos
{
public:
	double operator()(vector<double>& argv)
	{
		assert(argv.size() == 1);
		return cos(argv[0]);
	}
};
}
;

// both ok to use template or function object

class ExprFuncNode:public ExprNode
{
public:
	ExprFuncNode()=default;
	// if function without param
	ExprFuncNode(function<double(vector<double>&)> exprFunc)
		:ExprNode(ExprNodeType::FUNC),func(exprFunc){}
	// if function with one param
	ExprFuncNode(function<double(vector<double>&)> exprFunc,ExprNode* p0)
		:ExprNode(ExprNodeType::FUNC),func(exprFunc){children.push_back(p0);}
	// function with two param
	// function with three param
	// or, use variable length param list
	ExprFuncNode(function<double(vector<double>&)> exprFunc,int argc,...)
		:ExprNode(ExprNodeType::FUNC),func(exprFunc)
	{
		va_list arg_ptr;
		ExprNode* argv = nullptr;
		int nArg=0;     //可变参数的数目
		va_start(arg_ptr,argc); //以固定参数的地址为起点确定变参的内存起始地址。
		do
		{
		    ++nArg;
		    argv = va_arg(arg_ptr,ExprNode*); //得到下一个可变参数的值
		    children.push_back(argv);
		} while(nArg<argc);
	}

	// or use add child
	void AddChild(ExprNode* child)
	{
		children.push_back(child);
	}
	~ExprFuncNode(){
		for(auto it=children.begin(),et=children.end();it!=et;it++)
		{
			delete (*it);
			*it = nullptr;
			// though they are in list, they may be shared, use shared_ptr?
		}
	}
	double Value(){
		vector<double> params(children.size());
		int i = 0;
		for(auto it=children.begin(),et=children.end();it!=et;it++)
		{
			params[i++] = (*it)->Value();
		}
		value = func(params);
		return value;
	}
private:
	function<double(vector<double>&)> func;
	list<ExprNode*> children;
};

// if want to avoid using list, we can use template, maybe
/*

template<class tExprFunc,int argc>
class ExprFuncNode : public ExprNode
{
public:

private:
	tExprFunc func;
	array<ExprNode*> children[argc];
};

 */



#endif /* EXPRNODE_H_ */
