#include "stdafx.h"
#include "Prim.h"
#include <iostream>

Prim::Prim(int nodeCount)
{
	arrayDim = nodeCount;
	minHeap = new Node[arrayDim + 1];
	outputArray = new string[arrayDim];
	heapSize = 0;
}

void Prim::runPrim(string * nameArray, double * adjArray)
{	//runs the Prim algorithm and outputs results to the console
	int nodeIndex;
	int weightFound;
	int arrayIndex;
	
	Node node1;
	Node node2;

	startHeap(nameArray);

	while (heapSize > 0)
	{	//while the heap isn't empty, extract the vertex assoc. with the lowest weight
		//find all the nodes adj to it
		//if the weight between the two nodes is less than the weight currently assoc. with the adj. node
		//adjust the adj node's weight and parent and heapify the heap
		node1 = extractMin();
		for (int col = 0; col <= arrayDim; col++)
		{	//finds all adj nodes
			arrayIndex = node1.key;
			weightFound = adjArray[arrayIndex * arrayDim + col];
			if (weightFound > 0)
			{	//if there is a weight in adjArray
				nodeIndex = findInHeap(col);		//find the other node of the edge
				if (nodeIndex != -1 && weightFound < minHeap[nodeIndex].weight)
				{	//if the node was found and the new weight is less than its old weight, adjust the node in the heap
					minHeap[nodeIndex].weight = weightFound;
					minHeap[nodeIndex].parent = node1.key;
					
					for (nodeIndex; nodeIndex > 0; nodeIndex--)
					minHeapify(nodeIndex);

				}
			}
		}
	}

	//sum the weight and prep for output
	for (int pos = 1; pos < arrayDim; pos++)
	{
		addToOutputArray(nameArray, pos);
		pathSum += minHeap[pos].weight;
	}

	sortOutputArray();
	cout << "Total Path Weights' Sum: " << pathSum << endl; 
	for (int pos = 0; pos < outputArrayIndex; pos++)		//print the output
		cout << outputArray[pos] << endl;
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
{	//recurisvely restores the min heap property of the heap 
	int leftChildPos = 2 * startingPos;
	int rightChildPos = 2 * startingPos + 1;
	int currentMinPos;

	//determine the lowest weight of the three nodes
	if (leftChildPos < heapSize && minHeap[leftChildPos].weight < minHeap[startingPos].weight)
		currentMinPos = leftChildPos;
	else if (rightChildPos < heapSize && minHeap[rightChildPos].weight < minHeap[startingPos].weight)
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
{	//fills the heap with nodes and sets the heap size
	for (int pos = 1; pos <= arrayDim; pos++)
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
{	//extracts the lowest weight item (always first spot in array)
	//swaps the first and last items in the heap
	//reduces the heap size and calls minHeapify
	Node extractedNode = minHeap[1]; 
	minHeap[1] = minHeap[heapSize];
	minHeap[heapSize] = extractedNode;
	heapSize--;
	
	minHeapify(1);

	return extractedNode;
}

void Prim::addToOutputArray(string* nameArray, int heapIndex)
{	//formats the output for the algorithm
	string node1 = nameArray[minHeap[heapIndex].parent];
	string node2 = minHeap[heapIndex].name;
	string outputString;

	if (node1 < node2)
		outputString = node1 + "-" + node2 + "\t";
	else outputString = node2 + "-" + node1 + "\t";

	outputArray[outputArrayIndex] = outputString + to_string(minHeap[heapIndex].weight);
	outputArrayIndex++;
}

void Prim::sortOutputArray()
{	//uses bubble sort to alphabeticaly sort the output edges		
	string swapString;
	for (int loop = 0; loop < outputArrayIndex - 1; loop++)
		for (int pos = 0; pos < outputArrayIndex - 1; pos++)
			if (outputArray[pos] > outputArray[pos + 1])
			{
				swapString = outputArray[pos];
				outputArray[pos] = outputArray[pos + 1];
				outputArray[pos + 1] = swapString;
			}
}
