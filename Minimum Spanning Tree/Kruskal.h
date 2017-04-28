#pragma once
#include <string>

using namespace std;

struct Edge
{
	double weight = -1;
	string vertex1 = "";
	string vertex2 = "";
};

class Kruskal
{
public:
	//sets are currently implemented as comma seperated strings
	Kruskal(int arrayDim);
	void runKruskal(string* nameArray, double* adjArray);

private:
	int arrayDim;
	int pathSum = 0;
	int outputArrayIndex = 0;
	int itemsInSetArray = -1;
	string* setArray;
	Edge* edgeArray;
	string* outputArray;

	void makeAndAddSet(string insertString);
	int searchSets(string searchString);
	void unionSets(int resultPos, int removePos);
	int createSortedEdgeArray(double* adjArray);
	void addToOutputArray(Edge node);
	void sortOutputArray();
};