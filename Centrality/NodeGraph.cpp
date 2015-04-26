#include "NodeGraph.h"
#include <iostream>
#include <math.h>

using namespace std;


NodeGraph::NodeGraph(){

}

NodeGraph::~NodeGraph(){

}

void NodeGraph::AddNode(string name, double score){
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

void NodeGraph::AddEdge(string start, string end, double weight){
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
	AdjNode* addAdj = new AdjNode();
	addAdj->node = endNode;
	startNode->adj.push_back(addAdj);
}

void NodeGraph::CentralityEigenvector(){
	//THIS FUNCTION IS CURRENTLY BUGGED AND MAY RETURN IMPROPER SCORE VALUES
	//calculates centrality scores for all nodes by the eigenvector centrality method
	//this method is intended to be used in multiple iterations
	//the more iterations, the more accurate the estimation of the dominant eigenvector of the adjacency matrix

	vector<double> productVect;
	for (int i = 0; i < nodes.size(); i++){
		productVect.push_back(0);
		for (int j = 0; j < nodes[i].adj.size(); j++){
			//compute matrix dot product of row and column vectors and store them in product vector
			productVect[i] += (nodes[i].score) * (nodes[i].adj[j]->node->score);
		}
	}

	//normalized magnitude of product vector
	double norm = 0;
	for (int i = 0; i < productVect.size(); i++){
		norm += productVect[i] * productVect[i];
	}
	norm = sqrt(norm);

	/*
	Use magnitude to normalize product vector to unit length.
	This becomes the eigenvector.
	*/
	vector<double> eigenVect;
	for (int n = 0; n < productVect.size(); n++){
		eigenVect.push_back(0);
		eigenVect[n] = (productVect[n]) / norm;
	}

	//assigned new scores to nodes based on corresponding values in eigenvector
	for (int k = 0; k < nodes.size(); k++){
		nodes[k].score = eigenVect[k];
	}
}

vector<Node> NodeGraph::GetNodes(){
	return nodes;
}

void NodeGraph::PrintNodes(){
	//print names of all nodes and their score
	if (nodes.size() == 0){
		cout << "Nodegraph is empty." << endl;
		return;
	}

	for (int i = 0; i < nodes.size(); i++){
		cout << nodes[i].name << ":" << nodes[i].score << endl;
	}
}
