/*
 * circuit.h
 *
 *  Created on: Nov 9, 2012
 *      Author: chjd
 */

#ifndef CIRCUIT_H_
#define CIRCUIT_H_

#include "std.hpp"

//class Elem;
#include "allElem.h"
class SubCkt;
class Task;
class Param;


/* --------------------------------------------- */
/*
 * params for sc circuit
 */
struct tScParam
{
	bool scflag;
	double clkfreq;
	int scinout;
};

typedef struct tScParam ScParam;

/* --------------------------------------------- */


class Circuit
{
public:
	void Init();
	void AddElem(ElemType tp,Elem* elem);
public:
	string filename;
	list<Elem*> elemList;	// keeps basic elems, R,C,L,E,F,G,H
	list<Elem*> sourceList; // keeps sources, voltage and current source
	list<Elem*> activeList;	// keep active devices, such as MOS
	list<Elem*> subcktList; // keep all subckts
	list<Task*> taskList;	// keep all tasks
	list<Param*> paramList;
	unordered_map<string,int> nodeMap={{"0",0}}; // map node name into index

	ScParam scparam;


public:
	// add a node, and return its index
	int AddNode(string& node){
		int N = nodeMap.size();
		auto tmp = nodeMap.insert(make_pair(node,N));
		return tmp.first.second;
	}

	double ParamValue(string& param)
	{
		double d = 1.0;
		char unit = param.back();
		if(isdigit(unit) || unit=='.')
			d = atof(param.c_str());
		else
		{
			double u = 1.0;
			switch(unit)
			{
			case 'f':
				u = 1.0e-15;break;
			case 'p':
				u = 1.0e-12;break;
			case 'n':
				u = 1.0e-09;break;
			case 'u':
				u = 1.0e-06;break;
			case 'm':
				u = 1.0e-03;break;
			case 'k':
				u = 1.0e+03;break;
			case 'x':
				u = 1.0e+06;break;
			case 'g':
				u = 1.0e+09;break;
			}
			d *= u;
		}
		return d;
	}
public:
// for parser
	// for R,C,L
	// did not have a good parser is the key problem
	// template for parse entry,
	ElemRes* AddRes(string& nm,string& sp,string& sn,string& dp)
	{
		int p = AddNode(sp);
		int n = AddNode(sn);
		double d = ParamValue(dp);
		ElemRes* elem = new ElemRes(nm,p,n,d);
		elemList.push_back(elem);
		return elem;
	}

	ElemSubckt* AddSubckt();
	void AddSubcktElem();
// subcktStack
// when meet subckt, push it to stack, then until ends subckt,  add elem to stack.top

};


#endif /* CIRCUIT_H_ */
