#ifndef NODEGRAPH_H
#define NODEGRAPH_H

#include <iostream>
#include <vector>
#include <string>

//forward declaration
struct Node;

struct AdjNode
{
	double weight;
	Node* node;
};

struct Node{
	std::string name;
	double score;
	std::vector<AdjNode*> adj;
};

class NodeGraph{
public:
	NodeGraph();
	~NodeGraph();
	void AddNode(std::string name, double score);
	void AddEdge(std::string start, std::string end, double weight);
	void CentralityEigenvector();
	void PrintNodes();
private:
	std::vector<Node> nodes;
};

#endif