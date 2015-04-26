#ifndef MATRIXFILE_H
#define MATRIXFILE_H

#include <string>
#include <vector>
#include <stdlib.h>

class MatrixFile
{
public:
	MatrixFile();
	~MatrixFile();
	void ClearBufferedData(bool nameData, bool scoreData, bool adjData);
	void ClearBufferedDataAll();
	std::vector<std::string> GetNames();
	std::vector<double> GetScores();
	std::vector<std::vector<int> > GetAdjacency();
	void ReadFileAdjacency(std::string filename);
	void ReadFileScores(std::string filename);
	void StoreConnection(std::string nameFrom, std::string nameTo);
	void StoreNode(std::string name, double score);
	void WriteFileAdjacency(std::string filename);
	void WriteFileScores(std::string filename);
private:
	/*
	These variables are a buffer for input/output data, used to store information read in
	from a file, or information waiting to be written to a file.
	*/
	//names of all nodes
	std::vector<std::string> names;
	//score values for all nodes, at corresponding indices with the 'names' vector
	std::vector<double> scores;
	//matrix that stores adjacency status for all possible pairs of nodes
	//stores 0 for 'not connected'(default) and 1 for 'connected'
	std::vector<std::vector<int> > adjacency;
};


#endif
