/*
 * graph.h
 *
 *  Created on: Nov 21, 2012
 *      Author: chjd
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include "stdafx.h"

#include "edge.h"

class Graph
{
public:
	// default construct
	Graph()=default;
	// copy construct
	Graph(Graph& gph)
	{
		edgenum = gph.EdgeNum();
		nodenum = gph.NodeNum();
		edgeArray = list<Edge>(gph.EdgeArray());
	}

	// nodenum and edge num initialize when construct, then decrease by self
	int NodeNum() { return nodenum;}
	int EdgeNum() {	return edgenum;}
	// return reference of edgeArray, then you can change edgeArray
	list<Edge>& EdgeArray() {	return edgeArray;}

	// for construct GPDD, collapse & removal
	int Collapse(int edgeindex,int& sign);
	int Removal(int edgeindex);

	// for pre-process, short two node, do not care about sign
	void Collapse(int edgeindex);

	// for hash, graph share
	size_t Hash() const
	{
		// 4 8-bit
		int seed_a = nodenum * 7 + edgenum;
		int prime = 37;
		int seed_b=0, seed_c=0,seed_d=0;
		for(auto it=edgeArray.begin(),et=edgeArray.end();it!=et;it++)
		{
			seed_b ^= it->Index() * (seed_c%prime);
			seed_c |= it->NodeP() * (seed_d%prime);
			seed_d &= it->NodeN() * (seed_b%prime);
		}
		size_t seed = (seed_d<<24) & (0xFF000000);
		seed = seed |((seed_c<<16) & (0x00FF0000));
		seed = seed | ((seed_b<<8) & (0x0000FF00));
		seed = seed | (seed_a & 0x000000FF);
		return seed;
	}

	// another hash policy, each edge to a char, then hash string
	// use char16_t and u16string, or just char, string
	// char16_t, 65536
	// char, 256
	size_t HashByString() const
	{
		u16string seed_t(min(edgenum+1,16),char(0));
		seed_t[0] = char(nodenum + edgenum * 7);
		int i=1;
		for(auto it=edgeArray.begin(),et=edgeArray.end();it!=et;it++)
		{
			int t = it->Index() * 11 + it->NodeP() * 5 + it->NodeN();
			seed_t[i++] = char(t);
			if(i>16)
				break;
		}
		std::hash<std::string> hash_fn;
		return hash_fn(str);
	}

	friend bool operator!=(Graph& g1,Graph& g2)
	{
		if(g1.NodeNum()!=g2.NodeNum())
			return true;
		if(g1.EdgeNum()!=g2.EdgeNum())
			return true;
		auto it_g1 = g1.EdgeArray().begin(),et_g1 = g1.EdgeArray().end();
		auto it_g2 = g2.EdgeArray().begin();
		for(;it_g1!=et_g1;it_g1++,it_g2++)
		{
			if(*(it_g1)!=*(it_g2))
				return true;
		}
		return false;
	}
	friend bool operator==(const Graph& g1,const Graph& g2)
	{
		return !(g1!=g2);
	}

private:
	int nodenum;
	int edgenum; // instead of list.size
	list<Edge> edgeArray;

};

class GraphHash
{
public:
	size_t operator () (const Graph* graph) const
	{
		return graph->Hash();
	}
};

class GraphCompare
{
	public:
		bool operator () (const Graph* g1,const Graph* g2) const
		{
			return (g1==g2 || (*g1==*g2));
		}
};

typedef unordered_map<Graph*,Graph*,GraphHash,GraphCompare> GraphMapMap;

class GraphMap
{
	public:
		GraphMap()	{	}
		~GraphMap()
		{
			unordered_map<Graph*,Graph*,GraphHash,GraphCompare>::iterator it = graphMap.begin();
			for(;it!=graphMap.end();it++)
			{
				delete (Graph*) (it->first);
			}
		}

		void Add(Graph* graph)
		{
			graphMap.insert(make_pair(graph,graph));
		}

		Graph* GraphShare(Graph* graph)
		{
			//unordered_map<Graph*,Graph*,GraphHash,GraphCompare>::iterator it = graphMap.find(graph);
			pair<GraphMapMap::iterator,bool> itf = graphMap.insert(make_pair(graph,graph));
			if(!itf.second)
			{
			//	Graph::graphSharedCnt++;
				delete (Graph*) graph;
			}
			return itf.first->second;
		}

		void Clear()
		{
			unordered_map<Graph*,Graph*,GraphHash,GraphCompare>::iterator it = graphMap.begin();
			for(;it!=graphMap.end();it++)
			{
				delete (Graph*) (*it).second;
			}
			graphMap.clear();
		}

	private:
		unordered_map<Graph*,Graph*,GraphHash,GraphCompare> graphMap;
};


#endif /* GRAPH_H_ */
