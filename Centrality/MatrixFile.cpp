#include "MatrixFile.h"
#include <iostream>
#include <fstream>

using namespace std;


MatrixFile::MatrixFile()
{
}


MatrixFile::~MatrixFile()
{
}

/*
void ClearBufferedData(bool, bool, bool);
Clears stored input/output buffer data for the categories selected in arguments.

Example:
To erase the buffered node names, but leave all other buffers intact:
ClearBufferedData(true, false, false);

Will work even if buffer(s) are already empty.
*/
void MatrixFile::ClearBufferedData(bool nameData, bool scoreData, bool adjData){
	if (nameData){
		names.clear();
	}
	if (scoreData){
		scores.clear();
	}
	if (adjData){
		for (int i = 0; i < adjacency.size(); i++){
			adjacency[i].clear();
		}
	}
}

/*
Calls ClearBufferedData with all true arguments. This erases input/output data from all categories.
*/
void MatrixFile::ClearBufferedDataAll(){
	ClearBufferedData(true, true, true);
}

void MatrixFile::StoreConnection(std::string nameFrom, std::string nameTo){

}

void MatrixFile::StoreNode(std::string name, double score){

}

/*
void MatrixFile::WriteFileAdjacency(string);
Creates a file with the specified filename. Writes all node names and connections from buffer to the file.
Data is stored in the form of an adjacency matrix, where a value of 0 means 'no connection', 1 means 'connected'.

Example:
WriteFileAdjacency("MyAdjacencyMatrix.txt");

Adjacency matrix buffer must be populated for this work correctly.
*/
void MatrixFile::WriteFileAdjacency(std::string filename){
	ofstream outputFile;
	outputFile.open(filename.c_str());
	if (outputFile.is_open() == false){
		cout << "Error creating file: " << filename << endl;
		return;
	}

	outputFile << "UNUSED";
	for (int i = 0; i < names.size(); i++){
		outputFile << "," << names[i];
	}

	for (int j = 0; j < names.size(); j++){
		outputFile << "\n" << names[j];
		for (int k = 0; k < names.size(); k++){
			outputFile << "," << adjacency[j][k];
		}
	}

	outputFile.close();
}

/*
void MatrixFile::WriteFileScores(string);
Creates a file with the specified filename. Writes all node names and scores from the buffer to the file.

Example:
WriteFileScores("MyNodeScores.txt");
*/
void MatrixFile::WriteFileScores(std::string filename){
	ofstream outputFile;
	outputFile.open(filename.c_str());
	if (outputFile.is_open() == false){
		cout << "Error creating file: " << filename << endl;
		return;
	}

	if (names.size() > 0){
		outputFile << names[0];
	}
	for (int i = 1; i < names.size(); i++){
		outputFile <<","<< names[i];
	}

	outputFile << "\n";

	if (scores.size() > 0){
		outputFile << scores[0];
	}
	for (int j = 0; j < scores.size(); j++){
		outputFile << "," << scores[j];
	}

	outputFile.close();
}