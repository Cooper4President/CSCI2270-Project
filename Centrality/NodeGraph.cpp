#include "NodeGraph.h"
#include <iostream>

using namespace std;


NodeGraph::NodeGraph(){

}

NodeGraph::~NodeGraph(){

}

void NodeGraph::AddNode(string name, int score){
	//check to make sure node with same name doesn't already exist
	for (int i = 0; i < nodes.size(); i++){
		if (nodes[i].name == name){
			return;
		}
	}
	//add node to graph
	Node tempNode;
	tempNode.name = name;
	tempNode.score = score;
	nodes.push_back(tempNode);
}

void NodeGraph::AddEdge(string start, string end){
	Node* startNode = nullptr;
	Node* endNode = nullptr;

	bool startFound = false;
	bool endFound = false;
	for (int i = 0; i < nodes.size(); i++){
		if (nodes[i].name == start){
			startNode = &nodes[i];
			startFound = true;
		}
		if (nodes[i].name == end){
			endNode = &nodes[i];
			endFound = true;
		}
		if (startFound == true && endFound == true){
			break;
		}
	}

	if (startFound == false){
		cout << "Node named: " << start << " not found!" << endl;
		return;
	}
	if (endFound == false){
		cout << "Node named: " << end << " not found!" << endl;
		return;
	}

	//add end node to adjacency vector of start node
	startNode->adj.push_back(endNode);
}
