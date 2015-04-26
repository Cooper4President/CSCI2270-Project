#include "MatrixFile.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


/*
Class constructor.
Currently empty.
*/
MatrixFile::MatrixFile()
{
}


/*
Class destructor.
Currently empty.
*/
MatrixFile::~MatrixFile()
{
}


/*
void ClearBufferedData(bool, bool, bool);

Clears stored input/output buffer data for the categories selected in arguments. All three arguments are booleans,
which if entered as true will erase the corresponding data buffer.
The arguments correspond to the Names, Scores, and Adjacency data buffers, respectively.

Example:
To erase the buffered node names, but leave all other buffers intact:
MatrixFile ioStuff;
ioStuff.ClearBufferedData(true, false, false);

Pre: Will work even if buffer(s) are already empty.
Post: Some or all of the Name, Score, and Adjacency data buffers will be erased, depending on which arguments are entered.
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
void MatrixFile::ClearBufferedDataAll();

Calls ClearBufferedData with all true arguments. This erases input/output data from all categories.
See description of ClearBufferedData() method for more information.

Example:
MatrixFile ioStuff;
ioStuff.ClearBufferedDataAll();

Pre/Post: same as ClearBufferedData() method, listed above.
*/
void MatrixFile::ClearBufferedDataAll(){
	ClearBufferedData(true, true, true);
}


//getter functions BEGIN
std::vector<std::string> MatrixFile::GetNames(){
	return names;
}

std::vector<double> MatrixFile::GetScores(){
	return scores;
}

std::vector<std::vector<int> > MatrixFile::GetAdjacency(){
	return adjacency;
}
//getter functions END


void MatrixFile::ReadFileAdjacency(std::string filename){
	ifstream inputFile;
	inputFile.open(filename.c_str());
	if (inputFile.is_open() == false){
		cout << "Error opening file: " << filename << endl;
		return;
	}

	stringstream lineStream;
	string line;
	//read in top row
	getline(inputFile, line);
	lineStream << line;
	//read in names
	vector<string> tempNames;
	while (lineStream.good()){
		string token1;
		getline(lineStream, token1, ',');
		tempNames.push_back(token1);
	}

	//store nodes in buffer with default score (1)
	for (int i = 1; i < tempNames.size(); i++){
		StoreNode(tempNames[i], 1);
	}

	//read in connections and store data in buffer
	int indexRow = 0;
	int indexColumn = 0;
	while (inputFile.good()){
		indexColumn = 0;
		lineStream.clear();
		line = "";
		getline(inputFile, line);
		lineStream << line;

		if (indexRow > names.size()){
			break;
		}

		while (lineStream.good()){
			if (indexColumn > names.size()){
				break;
			}
			string token2;
			getline(lineStream, token2, ',');
			if (indexColumn > 0){
				if (atoi(token2.c_str()) == 1){
					StoreConnection(names[indexRow], names[indexColumn - 1]);
				}
			}
			indexColumn++;
		}

		indexRow++;
	}

	inputFile.close();
}

void MatrixFile::ReadFileScores(std::string filename){
	ifstream inputFile;
	inputFile.open(filename.c_str());
	if (inputFile.is_open() == false){
		cout << "Error opening file: " << filename << endl;
		return;
	}

	vector<string> tempNames;
	vector<double> tempScores;
	stringstream lineStream;
	string line;
	//read in names
	getline(inputFile, line);
	lineStream << line;
	while (lineStream.good()){
		string token1;
		getline(lineStream, token1, ',');
		tempNames.push_back(token1);
	}

	lineStream.clear();

	//read in scores
	line = "";
	getline(inputFile, line);
	lineStream << line;
	while (lineStream.good()){
		string token2;
		getline(lineStream, token2, ',');
		double tokenScore = atof(token2.c_str());
		tempScores.push_back(tokenScore);
	}

	//store names and scores in buffer
	for (int i = 0; i < tempNames.size(); i++){
		StoreNode(tempNames[i], tempScores[i]);
	}

	inputFile.close();
}

void MatrixFile::StoreConnection(std::string nameFrom, std::string nameTo){
	//verify both nodes exist first
	bool fromExists = false;
	bool toExists = false;
	int fromIndex, toIndex;
	for (int i = 0; i < names.size(); i++){
		if (names[i] == nameFrom){
			fromExists = true;
			fromIndex = i;
		}
		if (names[i] == nameTo){
			toExists = true;
			toIndex = i;
		}
		if (fromExists && toExists){
			break;
		}
	}

	if (fromExists == false || toExists == false){
		cout << "Could not make connection. At least one node does not exist: " <<nameFrom<<" , "<<nameTo<< endl;
		return;
	}
	if (nameFrom == nameTo){
		cout << "Node cannot connect to itself: " << nameFrom << endl;
		return;
	}

	//add connection to adjacency matrix
	adjacency[fromIndex][toIndex] = 1;
}

void MatrixFile::StoreNode(std::string name, double score){
	/*for (int i = 0; i < names.size(); i++){
		if (names[i] == name){
			//node with same name already exists, so overwrite it
			names[i] = name;
			scores[i] = score;
			return;
		}
	}*/

	names.push_back(name);
	scores.push_back(score);

	//expand adjacency matrix to proper size and fill new slots with default value (0 : 'no connection')
	//add new column and fill with 0's
	for (int i = 0; i < adjacency.size(); i++){
		adjacency[i].push_back(0);
	}
	//add new row and fill with 0's
	vector<int> row;
	for (int n = 0; n < names.size(); n++){
		row.push_back(0);
	}
	adjacency.push_back(row);
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