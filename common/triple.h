/*
 * triple.h
 *
 *  Created on: Nov 22, 2012
 *      Author: chjd
 */

#ifndef TRIPLE_H_
#define TRIPLE_H_

template<typename _T1, typename _T2, typename _T3>
class triple
{
public:
	// construct from default
	triple() :
		first(_T1()), second(_T2()), third(_T3())
	{
	}
	// construct from specified values
	triple(const _T1& _v1, const _T2& _v2, const _T3& _v3) :
		first(_v1), second(_v2), third(_v3)
	{
	}
	// copy-like construct
	template<typename T1, typename T2, typename T3>
	triple(const triple<T1, T2, T3>& other) :
		first(other.first), second(other.second), third(other.third)
	{
	}
/*	template<typename T1, typename T2, typename T3>
	friend bool operator==(const triple<T1,T2,T3>& left,const triple<T1,T2,T3>& right)
	{
		return (left.first==right.first) && (left.second==right.second) && (left.third==right.third);
	}
*/
public:
	typedef triple<_T1, _T2, _T3> triple_type;
	typedef _T1 first_type;
	typedef _T2 second_type;
	typedef _T3 third_type;
	_T1 first;
	_T2 second;
	_T3 third;
};

#endif /* TRIPLE_H_ */
