/*
 * circuit.h
 *
 *  Created on: Nov 9, 2012
 *      Author: chjd
 */

#ifndef CIRCUIT_H_
#define CIRCUIT_H_

#include "std.hpp"

class Elem;
class SubCkt;
class Task;

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
public:
	string filename;
	list<Elem*> elemList;	// keeps basic elems, R,C,L,E,F,G,H
	list<Elem*> sourceList; // keeps sources, voltage and current source
	list<Elem*> activeList;	// keep active devices, such as MOS
	list<Elem*> subcktList; // keep all subckts
	list<Task*> taskList;	// keep all tasks
	unordered_map<string,int> nodeMap={{"0",0}}; // map node name into index

	ScParam scparam;

private:

	template<class Type>
	void ParseElem(vector<string>& line); // to avoid memory leak in parser
	void AddElem(ElemType tp,Elem* elem);
};

#endif /* CIRCUIT_H_ */
