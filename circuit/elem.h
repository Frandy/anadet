/*
 * elem.h
 *
 *  Created on: Nov 13, 2012
 *      Author: chjd
 */

#ifndef ELEM_H_
#define ELEM_H_

// for all may used headers
#include "stdafx.hpp"

#include "elemType.h"

class Elem
{
public:
	Elem()=default;
	// R,C,L,E,F,G,H, if OPAMP, d = 0
	Elem(string& nm,ElemType tp,double d=0,FaultType faulttp=FaultType::NONE):name(name),type(tp),value(d),fault(faulttp){}
	virtual ~Elem(){}

	string Name() 	  {	return name;}
	ElemType Type()   { 	return type;}

	void Name(string& nm) 	{	name = nm;}
	void Type(ElemType tp)	{	type = tp;}

	// for symbol
	// common
	int Index() const		{	return index;}
	void Index(int& k)		{	index = k++;}
	double Value()			{	return value;}  // calc coef
	void Value(double d)	{	value = d;}
	Cplx AcValue()			{	return acValue;} // calc gpdd
	// virtual
	// edge index, not needed independent, do when create LR graph
	// value, both dc value and ac value needed
	virtual void AcValueAtFreq(Cplx& s)	{}

	// for fault
	FaultType Fault() const { return fault;}
	void Fault(FaultType tp) { fault = tp;}

	// print
	virtual void Print(ostream& out){}

	// virtual void CreateGraphPair(Graph* lgph,Graph* rgph);
	// virtual bool Include(Graph* lgph,Graph* rgph,int& sign);
	// virtual bool Exclude(Graph* lgph,Graph* rgph,int& sign);

protected:
	string name;
	ElemType type;

// for symbol
	int index;
	double value;		// admittance
	Cplx acValue;		// cplx admittance

// for mna stamp
	struct {
		vector<pair<int,int> > dc;
		vector<pair<int,int> > tran;
		vector<pair<int,int> > ac;
	}stamp;

// some flag
	FaultType fault;
	InftyType inf;
};

// for symbols, both symbol index and edge index are needed,
// but symbol index are needed by others, such gpddnode,
// while edge index are only needed by the symbol its self


#endif /* ELEM_H_ */
