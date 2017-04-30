#pragma once
#include <string>

using namespace std;

struct Node
{
	string name = "";
	int key = 0;			//the key is actually the row/column index for the adjArray
	int parent = 0;
	double weight = 0;
};

class Prim
{
public:
	Prim(int nodeCount);
	void runPrim(string* nameArray, double* adjArray);

private:
	int arrayDim;
	int heapSize;
	int pathSum = 0;
	int outputArrayIndex;
	Node* minHeap;
	string* outputArray;
//	string* nameArray;

	int findInHeap(int searchKey);
	void minHeapify(int startingPos);
	void startHeap(string* nameArray);
	Node extractMin();
	void addToOutputArray(string* nameArray, int heapIndex);
	void sortOutputArray();
};
