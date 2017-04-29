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
	int nodeIndex;
	int weightFound;
	
	Node node1;
	Node node2;

	
	while (heapSize != 0)
	{
		node1 = extractMin();
		for (int col = 0; col < arrayDim; col++)
		{	//finds all adj nodes
			weightFound = adjArray[node1.key * arrayDim + col];
			if (weightFound > 0)
			{	//if there is a weight in adjArray
				nodeIndex = findInHeap(col);		//find the other node of the edge
				if (nodeIndex != -1 && weightFound < minHeap[nodeIndex].weight)
				{	//if the node was found and the new weight is less than its old weight, adjust the node in the heap
					minHeap[nodeIndex].weight = weightFound;
					minHeap[nodeIndex].parent = node1.key;
					
					//todo: figure out how to deal with heapify-ing the heap

				}
			}
		}
	}

	//somehow use what remains after that^ to get and output the edges used
	//don't forget the weights
	//and sorting the outputs
}

int Prim::findInHeap(int searchKey)
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
		minHeap[pos].name = nameArray[pos - 1];
		minHeap[pos].key = pos - 1;
		minHeap[pos].weight = DBL_MAX;
		minHeap[pos].parent = -1;

		heapSize++;
	}

	minHeap[1].weight = 0;		//set the first item's weight to 0 as a starting point for finding graph edges
}

Node Prim::extractMin()
{	//todo: this needs tested
	Node extractedNode = minHeap[1]; 
	minHeap[1] = minHeap[heapSize];
	heapSize--;		//todo: make sure the first node doesn't need to be moved too
	minHeapify(1);

	return extractedNode;
}
