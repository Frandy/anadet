/*
 * exprnode.h
 *
 *  Created on: Nov 16, 2012
 *      Author: chjd
 */

#ifndef EXPRNODE_H_
#define EXPRNODE_H_

#include "stdafx.hpp"

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
		:ExprNode(ExprNodeType::PARAMEXPR),valued(false),index(0),name(nm){data.root = rt;}
	ParamNode(string nm,string filename)
		:ExprNode(ExprNodeType::PARAMFILE),valued(false),index(0),name(nm){
		data.file.filename = filename;
		ReadData();
	}
	void Evaluete()
	{
		index++;
		switch(type)
		{

		}
	}
private:
	void ReadData(){
		assert(type==ExprNodeType::PARAMFILE);
		// data format, first row, size, and then the data,
		ifstream fp(data.file.filename.c_str());
		int size = 0;
		fp >> size >> endl;
		data.file.data = new double[size];
		for(auto i=0;i<size;i++)
			fp >> data.file.data[i];
	}
private:
	bool valued;
	int index;
	string name;

	union{
		ExprNode* root;
		struct {
			string name;
			int size;
			double* data; // or use vector
		}file,seq;
	}data;
};

/*
 * op node, +,-,*,/
 */

class ExprOpNode:public ExprNode
{
public:
	ExprOpNode()=default;
	ExprOpNode(ExprNodeType tp,const ExprNode* pl,const ExprNode* pr)
		:ExprNode(tp),left(pl),right(pr){}
	~ExprOpNode(){
		delete left;
		left = nullptr;
		delete right;
		right = nullptr;
	}
	double Value(){
			double vl = left->Value();
			double vr = right->Value();
			switch(type)
			{
				case ExprNodeType::ADD:
				value = vl + vr;break;
				case ExprNodeType::SUB:
				value = vl - vr;break;
				case ExprNodeType::MUL:
				value = vl * vr;break;
				case ExprNodeType::DIV:
				value = vl / vr;break;
				default:;break;
			}
		return value;
	}
private:
	ExprNode* left;
	ExprNode* right;
};

namespace ExprFunc
{
	class FuncSin
	{
	public:
		double operator()(vector<double>& argv)
		{
			assert(argv.size()==1);
			return sin(argv[0]);
		}
	};
	class FuncCos
	{
	public:
		double operator()(vector<double>& argv)
		{
			assert(argv.size()==1);
			return cos(argv[0]);
		}
	};
};

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
	function<double(array<double>&)> func;
	array<ExprNode*> children;
};

 */



#endif /* EXPRNODE_H_ */
