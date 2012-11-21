/*
 * circuit.h
 *
 *  Created on: Nov 9, 2012
 *      Author: chjd
 */

#ifndef CIRCUIT_H_
#define CIRCUIT_H_

#include "stdafx.hpp"

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
	// keep all elems, for subckt expand, sc two phase, and so on, but not include fault elems
	list<Elem*> allInstList;
	// keep special elems, such with fault short or open(no need to process open), or with infity value
	list<Elem*> shortInstList;
	list<Elem*> openInstList;
private:
	string filename;
	// keeps basic elems, R,C,L,E,F,G,H
	list<Elem*> elemList;
	// keeps sources, voltage and current source
	list<Elem*> sourceList;
	// keep active devices, such as MOS
	list<Elem*> activeList;
	// keep opamps
	list<Elem*> opampList;
	// keep switches
	list<Elem*> switchList;
	// keep all subckt instances
	list<Elem*> subcktList;
	// keep extra elem new in circuit, instead of from parser
	list<Elem*> extraList;
	// keep all tasks, ordered list, DC < TRAN < AC
	list<Task*> taskList;

	// map node name into index
	unordered_map<string,int> nodeMap={{"0",0}};
	// map elem name with its address, for look-up
	unordered_map<string,Elem*> elemMap;
	// keep subckt circuit
	unordered_map<string,Elem*> subcktMap;
	// keep models, model may be save together with subcktMap
	unordered_map<string,Elem*> modelMap;
	// for look-up param value, this also can be iterate, so no need for list
	unordered_map<string,ParamNode*> paramMap;


	ScParam scparam;


public:
	// add a node, and return its index
	int AddNode(string& node){
		int N = nodeMap.size();
		auto tmp = nodeMap.insert(make_pair(node,N));
		return tmp.first.second;
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
		// return or no return ?
	}

	ElemSubckt* AddSubckt();
	void AddSubcktElem();
// subcktStack
// when meet subckt, push it to stack, then until ends subckt,  add elem to stack.top

};


#endif /* CIRCUIT_H_ */
