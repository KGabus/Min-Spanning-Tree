// Minimum Spanning Tree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include "Kruskal.h"
#include "Prim.h"

using namespace std;

string filePath = "C:\\Users\\Kaylee\\Desktop\\mst.txt";


int main()
{
	double inputDouble;
	string currentInput;

	ifstream inFile(filePath, ios::binary);
	if (inFile.fail())
	{	//if the file is unable to be read, notify user and close the program
		cout << "Unable to open input file\n\n"
			<< "Program Exiting\n\nPress ENTER to exit\n";
		cin >> currentInput;
		exit(1);
	}

	inFile >> currentInput;
	inputDouble = atoi(currentInput.c_str());		//convert the first thing in the file to a number

	//todo: refering to specific spots in adjArrays: location = (nValue * row) + col
	int nValue = inputDouble;
	double* adjMatrix = new double[nValue * nValue];		
	string* nodeNamesMatrix = new string[nValue];

	Kruskal KrsukalAlgorithm(nValue);
	Prim PrimAlgorithm(nValue);

	for (int pos = 0; pos < nValue; pos++)
	{	//read in the names of the nodes and put them in the names array
		inFile >> nodeNamesMatrix[pos];
	}

	for (int pos = 0; pos < (nValue * nValue); pos++)
	{	//read in the adjancy matrix
		inFile >> currentInput;
		inputDouble = atof(currentInput.c_str());		//convert text to double
		adjMatrix[pos] = inputDouble;
	}

	KrsukalAlgorithm.runKruskal(nodeNamesMatrix, adjMatrix);
	PrimAlgorithm.runPrim(nodeNamesMatrix, adjMatrix);

	//todo: run through with prim
	//todo: output prim
    return 0;
}

