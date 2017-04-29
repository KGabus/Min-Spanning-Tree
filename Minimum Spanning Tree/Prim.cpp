#include "stdafx.h"
#include "Prim.h"

Prim::Prim(int nodeCount)
{
	arrayDim = nodeCount;
	minHeap = new Node[arrayDim + 1];
	outputArray = new string[arrayDim];
	heapSize = 0;
}

void Prim::runPrim(string * nameArray, double * adjArray)
{	//todo: nothing in runPrim is actually written yet
	while (heapSize != 0)
	{
		//get the smallest weight
		//for each adj node
			//if the weight is non zero and we've just found a lower weight to get to the second node
				//adjust the second node's parent and weight values
				//run heapify (recursive, will involve math to figure out)
	}
}

int Prim::findInHeap(string searchKey)
{	//returns the index of the key in the heap
	//if it isn't in the heap, returns -1
	for (int pos = 1; pos <= heapSize; pos++)
	{
		if (minHeap[pos].key == searchKey)
			return pos;
	}
	return -1;
}

void Prim::minHeapify(int startingPos)
{	//todo: this needs tested
	int leftChildPos = 2 * startingPos;
	int rightChildPos = 2 * startingPos + 1;
	int currentMinPos;

	//determine the lowest weight of the three nodes
	if (leftChildPos < startingPos && minHeap[leftChildPos].weight < minHeap[startingPos].weight)
		currentMinPos = leftChildPos;
	else if (rightChildPos < startingPos && minHeap[rightChildPos].weight < minHeap[startingPos].weight)
		currentMinPos = rightChildPos;
	else currentMinPos = startingPos;

	if (currentMinPos != startingPos)
	{	//if either of the children had lower weights, swap them and call minHeapify
		Node node;
		node = minHeap[startingPos];
		minHeap[startingPos] = minHeap[currentMinPos];
		minHeap[currentMinPos] = node;
		minHeapify(currentMinPos + 1);
	}

}

void Prim::startHeap(string* nameArray)
{
	for (int pos = 1; pos < arrayDim; pos++)
	{
		minHeap[pos].key = nameArray[pos - 1];
		minHeap[pos].weight = DBL_MAX;
		minHeap[pos].parent = -1;

		heapSize++;
	}
}

Node Prim::extractMin()
{	//todo: this needs tested
	Node extractedNode = minHeap[1]; 
	minHeap[1] = minHeap[heapSize];
	heapSize--;		//todo: make sure the first node doesn't need to be moved too
	minHeapify(1);

	return extractedNode;
}
