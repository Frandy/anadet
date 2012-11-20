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
