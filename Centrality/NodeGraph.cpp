#include "NodeGraph.h"
#include <iostream>
#include <math.h>

using namespace std;


/*
NodeGraph class Constructor.
Currently empty.
*/
NodeGraph::NodeGraph(){

}


/*
NodeGraph class Destructor.
Currently empty.
*/
NodeGraph::~NodeGraph(){

}


/*
void NodeGraph::AddNode(string, double);

Adds a node to the nodegraph data structure. It will check if there is already a node in the graph with the same name, and will not add duplicates.
The first argument is the name for the node. The second argument is
its 'score' value. The 'score' values of the nodes are used by the algorithms for calculating centrality measures.
Typically, you would want to initialize all node scores to 1 before calculating centrality, but this method provide functionality
for setting any arbitrary initial score values, for maximum user customization.

Example:
NodeGraph graph;
graph.AddNode("ThisISaNode", 1);

No preconditions are required before calling this method.
After the method is called, the new node is added to the nodegraph data structure.
*/
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


/*
void NodeGraph::AddEdge(string, string, double);

Adds an edge/connection to the nodegraph. The first argument is the name of the node to start at. The second
argument is the name of the node to end at. The third argument is the weight value of the edge/connection.
The method stores this (directed) edge, and its weight, in the nodegraph data structure.

Note that edge weight referred to here is different from the 'score' values of the individual nodes; the two should not be confused.
None of the algorithms currently in the library utilize the edge weight property. It is simply included here to allow
for future extensibility should an algorithm require it.

Example:
NodeGraph graph;
graph.AddEdge("node1", "node2", 123.45);

There should already be at least two nodes stored in the nodegraph before calling this method. A connection/edge can not be created
between nonexistant nodes! Additionally, a node can not be connected to itself.
After being called, this method will add the necessary edge/connection data to the nodegraph data structure.
*/
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


/*
void NodeGraph::CentralityDegree();

Calculates centrality scores by the 'Degree' method. It is intended to be run for multiple iterations.
The more iterations are run, the more precise the results become.
This technique for quantifying centrality is not quite as advanced as the Eigenvector technique.
It is intended to provide a comparison, and this method will not necessarily rank the nodes in the same order.
There is no 'correct' way to measure centrality. The different mathematical techniques each have pros and cons depending on the situation.

Example:
NodeGraph graph;
graph.CentralityDegree();

The network needs to be populated with nodes, and all edges/connections should be in place, before running this method.
After an iteration is run, the method stores the new scores in each of the nodes.
*/
void NodeGraph::CentralityDegree(){
	for (int i = 0; i < nodes.size(); i++){
		for (int k = 0; k < nodes[i].adj.size(); k++){
			nodes[i].score += nodes[i].adj[k]->node->score;
		}
	}

	//find highest score and use this to normalize
	double maxScore = 0;
	for (int i = 0; i < nodes.size(); i++){
		if (nodes[i].score > maxScore){
			maxScore = nodes[i].score;
		}
	}

	//normalize all scores
	for (int x = 0; x < nodes.size(); x++){
		nodes[x].score = nodes[x].score / maxScore;
	}
}


/*
void NodeGraph::CentralityEigenvector();

Calculates centrality scores for all nodes by the eigenvector centrality method.
This method is intended to be used in multiple iterations.
The more iterations, the more accurate the estimation of the dominant eigenvector of the adjacency matrix.

Example:
NodeGraph graph;
graph.CentralityEigenvector();

The network needs to be populated with nodes, and all edges/connections should be in place, before running this method.
After an iteration is run, the method stores the new scores in each of the nodes.
*/
void NodeGraph::CentralityEigenvector(){
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


//simple getter method
vector<Node> NodeGraph::GetNodes(){
	return nodes;
}


/*
void NodeGraph::PrintNodes();

Prints the names of all nodes in network, and their score values.

Example:
NodeGraph graph;
graph.PrintNodes();

Does not alter any data.
*/
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
