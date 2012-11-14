/*
 * elemType.h
 *
 *  Created on: Nov 13, 2012
 *      Author: chjd
 */

#ifndef ELEMTYPE_H_
#define ELEMTYPE_H_

// elem type,
enum class ElemType
{
	RES,
	CAP,
	IND,
	VSRC,
	ISRC,
	VCVS,
	CCCS,
	VCCS,
	CCVS,
	MOS,
	OPAMP,
	SWITCH,
	SUBCKT,
};

// flag, fault, short or open
enum class FaultType
{
	NONE,
	SHORT,
	OPEN
};


// flag, extreme value, being infinity or zero
enum class InftyType
{
	NONE,
	INF,
	ZERO
};

#endif /* ELEMTYPE_H_ */
