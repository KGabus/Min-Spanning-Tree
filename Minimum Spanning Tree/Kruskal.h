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
	//Kruskal();
	Kruskal(int arrayDim);

	void makeSet(string insertString);	//todo: figure out how I'm planning on doing sets
	int findSet(string searchString);	//todo: find the set a parameter belongs in and put it there? If the item is in the set, it returns it's position in the set array. Else returns -1
	void unionSets(int resultPos, int removePos);//todo: take the union of the two sets?
	void makeEdgeArray(int* adjArray);
	void runKruskal(string* nameArray, double* adjArray);

private:
	int arrayDim;
	int pathSum = 0;
	int outputArrayIndex = 0;
	int itemsInSetArray = -1;
	string* setArray;// = new string[arrayDim];
	Edge* edgeArray;// = new Edge[arrayDim * arrayDim];
	string* outputArray;


	void makeAndAddSet(string insertString);
	int searchSets(string searchString);
	void combineSets(int resultPos, int removePos);
	int createSortedEdgeArray(double* adjArray);
	void addToOutputArray(Edge node);
	void sortOutputArray();
};