/*
 * res.h
 *
 *  Created on: Nov 13, 2012
 *      Author: chjd
 */

#ifndef RES_H_
#define RES_H_

#include "elem.h"

// no more than three levels inheritance

class ElemRes : public Elem
{
public:
// basic function, construction & member visit function
	ElemRes()=default;
	ElemRes(string& nm,int p,int n,double d):Elem(nm,ElemType::RES,1.0/d),nodep(p),noden(n){}

	// basic virtual function inherited from base class Elem
	// print
	virtual void Print(ostream& out){
		out << setw(16) << name << " ";
		out << setw(4) << nodep << " " << setw(4) << noden;
		out << "\t" << value << endl;
	}

// end basic function
private:
	int nodep;
	int noden;
};


#endif /* RES_H_ */
