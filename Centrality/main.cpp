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

	bool menuLoop = true;
	while (menuLoop){
		cout << "---------------------------\n---CENTRALITY: Main Menu---\n---------------------------" << endl;
		cout << "1. Quit\n2. Add Node\n3. Add Edge\n4. Print all nodes in network\n5. Compute Eigenvector Centrality" << endl;
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

		switch (choice){
		default:
			cout << "Invalid choice. Enter only the number." << endl;
			break;
		case 1:
			//quit
			cout << "Quitting..." << endl;
			menuLoop = false;
			break;
		case 2:
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
		case 3:
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
		case 4:
			//print nodes
			graph.PrintNodes();
			break;
		case 5:
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
		}
	}

	return 0;
}