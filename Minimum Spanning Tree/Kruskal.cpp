#include "stdafx.h"
#include "Kruskal.h"
#include <iostream>

using namespace std;

Kruskal::Kruskal(int size)
{
	arrayDim = size;

	setArray = new string[arrayDim];
	edgeArray = new Edge[arrayDim * arrayDim];
	outputArray = new string[arrayDim];
}

void Kruskal::makeSet(string insertString)
{
	insertString += ",";
	makeAndAddSet(insertString);
}

int Kruskal::findSet(string searchString)
{
	searchString += ",";
	return searchSets(searchString);
}

void Kruskal::unionSets(int resultPos, int removePos)
{
	combineSets(resultPos, removePos);
}

void Kruskal::runKruskal(string* nameArray, double* adjArray)
{
	string vertex1 = "";
	string vertex2 = "";

	int v1Set;
	int v2Set;

	for (int pos = 0; pos < arrayDim; pos++)
		makeAndAddSet(nameArray[pos] + ",");		//the comma seperates values in the string so they can be uniquely identified

	int numberOfEdges = createSortedEdgeArray(adjArray);
	for (int pos = 0; pos < numberOfEdges; pos++)
	{
		vertex1 = edgeArray[pos].vertex1;
		vertex2 = edgeArray[pos].vertex2;

		v1Set = searchSets(vertex1);
		v2Set = searchSets(vertex2);

		if (v1Set != v2Set)
		{
			combineSets(v1Set, v2Set);
			addToOutputArray(edgeArray[pos]);
		}
	}	//todo: i think after this point it just needs to print

	sortOutputArray();

	for (int pos = 0; pos <= outputArrayIndex; pos++)
		cout << outputArray[pos] << endl;


	cout << "it didn't crash so there's that.";
}

void Kruskal::makeAndAddSet(string insertString)
{
	setArray[itemsInSetArray + 1] = insertString;
	itemsInSetArray++;
}

int Kruskal::searchSets(string searchString)
{
	size_t location;
	for (int pos = itemsInSetArray; pos >= 0; pos--)
	{
		location = setArray[pos].find(searchString);
		if (location != std::string::npos)				//if the string is found in the set, return the location of the set
			return pos;	
	}

	return -1;			//if the string was not found, return -1
}

void Kruskal::combineSets(int set1, int set2)		//todo: this is untested
{	//takes the union of two sets and places it in the lower indexed spot in the set array
	//everything beneath the higher set index is moved up on spot and decrements count of array items
	if (set1 < set2)
	{
		setArray[set1] += setArray[set2];

		for (int pos = set2; pos < itemsInSetArray; pos++)
			setArray[pos] = setArray[pos + 1];
	}
	else
	{
		setArray[set2] += setArray[set1];

		for (int pos = set1; pos <= itemsInSetArray; pos++)
			setArray[pos] = setArray[pos + 1];
	}
	
	itemsInSetArray--;
}

int Kruskal::createSortedEdgeArray(double * adjArray)
{	//generates the array of edges for the adjacancy array
	//only has non 0 edges
	//sorted in ascending order
	int edgesInArray = 0;

	for (int row = 0; row < arrayDim; row++)
		for (int col = 0; col < arrayDim; col++)
		{	//for every non zero item in adjArray, create an edge and store it in edgeArray
			Edge newEdge;// = new Edge;
			newEdge.vertex1 = setArray[row];				//todo: i think this is right??
			newEdge.vertex2 = setArray[col];
			newEdge.weight = adjArray[(arrayDim * row) + col];
			

			if (newEdge.weight > 0)
			{	//only write the edges that are non-zero
				edgeArray[edgesInArray] = newEdge;
				edgesInArray++;
			}
		}

	for (int loop = 0; loop < edgesInArray - 1; loop++)
	{	//bubble sort the edges to get them in ascending order according to weight
		for (int pos = 0; pos < edgesInArray - 1; pos++)
		{	//sort the edges in ascending order
			if (edgeArray[pos].weight > 0)
			{	//if the weight isn't 0
				if (edgeArray[pos].weight > edgeArray[pos + 1].weight)
				{	//swap the two edges
					Edge temp = edgeArray[pos];

					edgeArray[pos].vertex1 = edgeArray[pos + 1].vertex1;
					edgeArray[pos].vertex2 = edgeArray[pos + 1].vertex2;
					edgeArray[pos].weight = edgeArray[pos + 1].weight;

					edgeArray[pos + 1] = temp;
				}
			}
		}
	}
	
	return edgesInArray;
}

void Kruskal::addToOutputArray(Edge node)
{
	outputArray[outputArrayIndex] = node.vertex1.substr(0, node.vertex1.length() - 1) + "-" + node.vertex2.substr(0, node.vertex2.length() - 1) + ":\t" + to_string(node.weight);
	outputArrayIndex++;
}

void Kruskal::sortOutputArray()
{	//uses bubble sort to alphabetaticly sort the output edges
	//string currentFirstVertex = "";

	//for (int loop = 0; loop < outputArrayIndex - 1; loop++)
	//	for (int pos = 0; pos < outputArrayIndex - 1; pos++)
	//		if (edgesInTree[pos].vertex1 > edgesInTree[pos + 1].vertex1)
	//		{	//sort the first vertex
	//			Edge temp = edgesInTree[pos];

	//			edgesInTree[pos].vertex1 = edgesInTree[pos + 1].vertex1;
	//			edgesInTree[pos].vertex2 = edgesInTree[pos + 1].vertex2;
	//			edgesInTree[pos].weight = edgesInTree[pos + 1].weight;

	//			edgesInTree[pos + 1] = temp;
	//		}
		
	string temp;
	for (int loop = 0; loop < outputArrayIndex - 1; loop++)
		for (int pos = 0; pos < outputArrayIndex - 1; pos++)
			if (outputArray[pos] > outputArray[pos + 1])
			{	//sort the second vertex
				temp = outputArray[pos];
				outputArray[pos] = outputArray[pos + 1];
				outputArray[pos + 1] = temp;
			}
}
