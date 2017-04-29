#pragma once
#include <string>

using namespace std;

struct Node
{
	string key = "";
	double weight = 0;
	int parent = 0;
};

class Prim
{
public:
	Prim(int nodeCount);
	void runPrim(string* nameArray, double* adjArray);

private:
	int arrayDim;
	int heapSize;
	Node* minHeap;
	string* outputArray;
	string* nameArray;

	int findInHeap(string searchKey);
	void minHeapify(int startingPos);
	void startHeap(string* nameArray);
	Node extractMin();
};
