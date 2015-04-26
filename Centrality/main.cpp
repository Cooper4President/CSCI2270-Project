/*
Cooper Matous
Final Project
CSCI 2270 - Hoenigman
*/

#include "NodeGraph.h"
#include "MatrixFile.h"
#include <iostream>
#include <stdlib.h>

using namespace std;


int main(int argc, char* argv[]){

	NodeGraph graph;
	MatrixFile fileIO;

	bool menuLoop = true;
	while (menuLoop){
		cout << "---------------------------\n---CENTRALITY: Main Menu---\n---------------------------" << endl;
		cout << "1. Load network from file\n2. Export network to file\n3. Add node manually\n4. Add edge manually" << endl;
		cout << "5. Print all nodes in network\n6. Compute Eigenvector Centrality\n7. placeholder\n 8. Quit" << endl;
		cout << "---------------------------\nSelect choice: " << endl;

		string choiceInput = "";
		cin >> ws;
		getline(cin, choiceInput);
		int choice = atoi(choiceInput.c_str());

		//these variables are used for getting user input in multiple
		//parts of the switch statement
		string name1 = "";
		string name2 = "";
		double number = 0;
		string numberStr = "";
		//variables used in loading from file
		vector<string> nodeNames;
		vector<vector<int> > adjacency;
		//variable used in writing to file
		vector<Node> nodeList;

		switch (choice){
		default:
			cout << "Invalid choice. Enter only the number." << endl;
			break;
		case 1:
			//load network from file
			cout << "Enter filename of matrix to load: " << endl;
			name1 = "";
			cin >> ws;
			getline(cin, name1);
			//get data from file
			fileIO.ClearBufferedDataAll();
			fileIO.ReadFileAdjacency(name1);
			nodeNames = fileIO.GetNames();
			adjacency = fileIO.GetAdjacency();
			//build nodegraph from data
			for (int i = 0; i < nodeNames.size(); i++){
				graph.AddNode(nodeNames[i], 1);
			}
			for (int j = 0; j < adjacency.size(); j++){
				for (int k = 0; k < adjacency[j].size(); k++){
					if (adjacency[j][k] = 1){
						graph.AddEdge(nodeNames[j], nodeNames[k], 1);
					}
				}
			}
			break;
		case 2:
			//store network in file
			cout << "Enter name for new file:" << endl;
			name1 = "";
			cin >> ws;
			getline(cin, name1);
			//get data from nodegraph
			nodeList = graph.GetNodes();
			//output data to file
			fileIO.ClearBufferedDataAll();
			for (int i = 0; i < nodeList.size(); i++){
				fileIO.StoreNode(nodeList[i].name, nodeList[i].score);
				for (int k = 0; k < nodeList[i].adj.size(); k++){
					fileIO.StoreConnection(nodeList[i].name, nodeList[i].adj[k]->node->name);
				}
			}
			fileIO.WriteFileAdjacency(name1);
			break;
		case 3:
			//add node
			name1 = "";
			numberStr = "";
			cout << "Enter node name: " << endl;
			cin >> ws;
			getline(cin, name1);
			cout << "Enter node score:" << endl;
			cin >> ws;
			getline(cin, numberStr);
			number = atof(numberStr.c_str());

			graph.AddNode(name1, number);
			break;
		case 4:
			//add edge
			name1 = "";
			name2 = "";
			numberStr = "";
			cout << "Enter name of starting node: " << endl;
			cin >> ws;
			getline(cin, name1);
			cout << "Enter name of ending node: " << endl;
			cin >> ws;
			getline(cin, name2);
			cout << "Enter edge weight: " << endl;
			cin >> ws;
			getline(cin, numberStr);
			number = atof(numberStr.c_str());

			graph.AddEdge(name1, name2, number);
			break;
		case 5:
			//print nodes
			graph.PrintNodes();
			break;
		case 6:
			//compute eigenvector centrality
			cout << "Number of iterations to run: " << endl;
			numberStr = "";
			cin >> ws;
			getline(cin, numberStr);
			number = atof(numberStr.c_str());
			cout << "Running..." << endl;

			for (int i = 0; i < number; i++){
				graph.CentralityEigenvector();
			}

			cout << "Ran " << number << " iterations." << endl;
			cout << "Print nodes to view new scores." << endl;
			break;
		case 7:
			break;
		case 8:
			//quit
			cout << "Quitting..." << endl;
			menuLoop = false;
			break;
		}
	}

	return 0;
}