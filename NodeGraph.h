#ifndef NODEGRAPH_H
#define NODEGRAPH_H

#include <iostream>

struct Node{
	int score = 0;
	std::vector<Node*> adj;
};

#endif