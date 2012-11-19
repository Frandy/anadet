/*
 * test_circuit.cpp
 *
 *  Created on: Nov 9, 2012
 *      Author: chjd
 */
#include "stdafx.hpp"
#include "elem.h"

#include "exprnode.h"

int main()
{
/*	ElemTwoNode a;
	a[0] = 1;
	a[1] = 2;

	cout << a[0] << endl;
*/
	ExprNode* a1 = new ExprNode(3.0);
	ExprNode* a2 = new ExprNode(4.0);
	//(ExprOpNode<'+'>)
	ExprAddNode* a3 = new ExprOpNode<'+'>(ExprNodeType::OP,a1,a2);
	cout << (a3->Value()) << endl;

	return 0;
}


