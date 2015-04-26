#ifndef NODEGRAPH_H
#define NODEGRAPH_H

#include <iostream>
#include <vector>
#include <string>


//forward declaration
struct Node;


/*
AdjNodes store the directed edges and weights for the graph data structure.
*/
struct AdjNode
{
	/*weight property is not currently used by any algorithms in library but is 
	included in case a new algorithm needs to make use of it*/
	double weight;
	Node* node;
};


/*
Represents individual nodes in the network. These make up the graph data structure.
*/
struct Node{
	std::string name;
	double score;
	std::vector<AdjNode*> adj;
};


//the 'nodegraph' stores all nodes and connections of the network. It uses a graph data structure.
class NodeGraph{
public:
	//Description comments for these methods are in the .cpp file.
	NodeGraph();
	~NodeGraph();
	void AddNode(std::string name, double score);
	void AddEdge(std::string start, std::string end, double weight);
	void CentralityDegree();
	void CentralityEigenvector();
	std::vector<Node> GetNodes();
	void PrintNodes();
private:
	//stores all nodes of the network.
	std::vector<Node> nodes;
};

#endif