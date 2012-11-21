/*
 * edge.h
 *
 *  Created on: Nov 21, 2012
 *      Author: chjd
 */

#ifndef EDGE_H_
#define EDGE_H_

class Edge
{
public:
	// default construct
	Edge()=default;
	// construct
	Edge(int id,int p,int n):index(id),nodep(p),noden(n){}
	// copy construct
	Edge(const Edge& e){
		index = e.Index();
		nodep = e.NodeP();
		noden = e.NodeN();
	}
	int Index() const { return index;}
	int NodeP() const { return nodep;}
	int NodeN() const { return noden;}

	// short large node to small node, if the node of this edge equal to large node
	// and re index node is done here
	// return true, if self-loop after short
	bool Short(int small,int large)
	{
		if(nodep==large)
			nodep = small;
		else if(nodep>large)
			nodep--;
		if(noden==large)
			noden = samll;
		else if(noden>large)
			noden--;
		return nodep==noden;
	}

private:
	int index;
	int nodep;
	int noden;
};


#endif /* EDGE_H_ */
