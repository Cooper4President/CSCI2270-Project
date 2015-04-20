/*
Cooper Matous
Final Project
CSCI 2270 - Hoenigman
*/

#include "NodeGraph.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[]){

	NodeGraph graph;

	bool menuLoop = true;
	while (menuLoop){
		cout << "---------------------------\n---CENTRALITY: Main Menu---\n---------------------------" << endl;
		cout << "1. Quit\n2. test\n3. test" << endl;
		cout << "---------------------------\nSelect choice: " << endl;

		string choiceInput = "";
		cin >> ws;
		getline(cin, choiceInput);
		int choice = atoi(choiceInput.c_str());

		switch (choice){
		default:
			cout << "Invalid choice. Enter only the number." << endl;
			break;
		case 1:
			cout << "Quitting..." << endl;
			menuLoop = false;
			break;
		case 2:
			break;
		case 3:
			break;
		}
	}

	return 0;
}