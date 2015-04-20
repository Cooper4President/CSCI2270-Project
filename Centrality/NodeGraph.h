#ifndef NODEGRAPH_H
#define NODEGRAPH_H

#include <iostream>
#include <vector>
#include <string>

struct Node{
	std::string name;
	int score = 0;
	std::vector<Node*> adj;
};

class NodeGraph{
public:
	NodeGraph();
	~NodeGraph();
	void AddNode(std::string name, int score);
	void AddEdge(std::string start, std::string end);
private:
	std::vector<Node> nodes;
};

#endif