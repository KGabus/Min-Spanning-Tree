// Minimum Spanning Tree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string filePath = "";		//todo: hardcode or get input?


int main()
{
	int tempInt;
	string currentInput;
	string filePath;

	cout << "Enter the input file:";	//todo: word better
	cin >> filePath;

	ifstream inFile(filePath, ios::binary);
	if (inFile.fail())
	{	//if the file is unable to be read, notify user and close the program
		cout << "Unable to open input file\n\n"
			<< "Program Exiting\n\nPress ENTER to exit\n";
		cin >> currentInput;
		exit(1);
	}

	inFile >> currentInput;		//todo: verify that it's an int?
	tempInt = atoi(currentInput.c_str());		

	//todo: refering to specific spots in adjArrays: location = (nValue * row) + col
	int nValue = tempInt;						//todo: is the matrix thing fixed??
	double* adjMatrix = new double[nValue * nValue];		//todo: fix the stupid matrix declaration thing
	string* nodeNamesMatrix = new string[nValue];

	for (int pos = 0; pos < nValue; pos++)			//todo: make sure this works
	{	//read in the names of the nodes and put them in the names array
		inFile >> nodeNamesMatrix[pos];
	}

	for (int row = 0; row <= (nValue * nValue); row++)
	{	//read in the adjancy matrix
			inFile >> adjMatrix[row];			//todo: breaks here
	}

	//todo: read in the file (can use <<)
	//todo: create adjancy matrix
	//todo: run through with kruskal 
	//todo: output kruskal
	//todo: run through with prim
	//todo: output prim
    return 0;
}

