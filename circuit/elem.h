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
	Elem(string& nm,ElemType tp,double d=0)
		:name(name),type(tp),admittance(d),infty(InftyType::NONE),fault(FaultType::NONE){}
	virtual ~Elem(){}

	string Name() 	  {	return name;}
	ElemType Type()   { 	return type;}

	void Name(string& nm) 	{	name = nm;}
	void Type(ElemType tp)	{	type = tp;}

	// value, the value in netlist, if to calc coef or stamp, use admittance
	virtual double Value()			{	return admittance;}
	virtual void Value(double d)	{	admittance = d;}



	// for symbol
	// common
	int Index() const		{	return index;}
	void Index(int& k)		{	index = k++;}
	double Admittance()		{	return admittance;}
	// virtual
	//@{
	// edge index, not needed independent, do when create LR graph
	virtual void CreateGraphPair(Graph* left,Graph* right);
	virtual bool Include(Graph* left,Graph* right,int& sign);
	virtual bool Exclude(Graph* left,Graph* right,int& sign);
	//@}
	// value, both dc value and ac value needed
	virtual void AcAdmittanceAtFreq(Cplx& s)	{}

	// for fault
	FaultType Fault() const { return fault;}
	void Fault(FaultType tp) {
		fault = tp;
		if(fault==FaultType::SHORT)
			infty = InftyType::INF;
		else if(fault==FaultType::OPEN)
			infty = InftyType::ZERO;
	}
	InftyType Infty() const { return infty;}
	// do this after parse the element, d < min or d>max ?
	virtual void Infty(double d){}

	// print
	virtual void Print(ostream& out){}

protected:
	string name;
	ElemType type;

// for symbol
	int index;
	double admittance;		// admittance
	Cplx cadmittance;		// cplx admittance

// for mna stamp
	struct {
		vector<pair<int,int> > dc;
		vector<pair<int,int> > tran;
		vector<pair<int,int> > ac;
	}stamp;

// some flag
	FaultType fault;
	InftyType infty;
};

// for symbols, both symbol index and edge index are needed,
// but symbol index are needed by others, such gpddnode,
// while edge index are only needed by the symbol its self


#endif /* ELEM_H_ */
