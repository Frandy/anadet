/*
 * elem.h
 *
 *  Created on: Nov 13, 2012
 *      Author: chjd
 */

#ifndef ELEM_H_
#define ELEM_H_

// for all may used headers
#include "std.hpp"

#include "elemType.h"

class Elem
{
public:
// basic function, construction & member visit function
	Elem()=default;
	Elem(string& nm,ElemType tp):name(name),type(tp){}						// for OPAMP
	Elem(string& nm,ElemType tp,double d):name(name),type(tp),value(d){}	// for R,C,L,E,F,G,H
	virtual ~Elem(){}

	string& Name() const 	{	return name;}
	ElemType& Type() const { 	return type;}

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
	// value, both dc value and ac value needed
	virtual void AcValueAtFreq(Cplx& s)	{}

	// for fault
	FaultType Fault() const { return fault;}
	void Fault(FaultType tp) { fault = tp;}

// end of basic function

// basic virtual function

	// print
	virtual void Print(ostream& out){}

// public interface,  virtual function


// end public interface

protected:
	string name;
	ElemType type;

// for symbol
	int index;
	double value;		// admittance
	Cplx acValue;		// cplx admittance

// some flag
	FaultType fault;
};

// for symbols, both symbol index and edge index are needed,
// but symbol index are needed by others, such gpddnode,
// while edge index are only needed by the symbol its self


#endif /* ELEM_H_ */
