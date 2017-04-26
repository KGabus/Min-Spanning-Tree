#include "stdafx.h"
#include "Kruskal.h"

Kruskal::Kruskal(int size)
{
	arrayDim = size;
}

void Kruskal::makeSet(string insertString)
{
	insertString += ",";
	makeAndAddSet(insertString);
}

int Kruskal::findSet(string searchString)
{
	searchString += ",";
	searchSets(searchString);
}

void Kruskal::unionSets(int resultPos, int removePos)
{
	combineSets(resultPos, removePos);
}

void Kruskal::makeEdgeArray(int * adjArray)
{
	createAndSortEdgeArray(adjArray);
}

void Kruskal::makeAndAddSet(string insertString)
{
	setArray[itemsInSetArray] = insertString;
	itemsInSetArray++;
}

int Kruskal::searchSets(string searchString)
{
	for (int pos = arrayDim; pos >= 0; pos--)
	{
		if (setArray[pos].find(searchString) != std::string::npos)
			return pos;		//if the string is found in the set, return the location of the set
	}

	return -1;			//if the string was not found, return -1
}

void Kruskal::combineSets(int resultPos, int removePos)
{	//takes the union of two sets and places it in the resultPos spot in the set array
	//resultPos must be the lower value of the two
	//everything beneath removePos is moved up on spot and decrements count of array items
	setArray[resultPos] += setArray[removePos];

	for (int pos = removePos; pos <= itemsInSetArray; pos++)
		setArray[pos] = setArray[pos + 1];

	itemsInSetArray--;
}

void Kruskal::createAndSortEdgeArray(int * adjArray)
{	//todo: figure out if this needs to be edge pointer and resolve that fiasco if necessary

	int edgesInArray = 0;

	for (int row = 0; row <= arrayDim; row++)
		for (int col = 0; col <= arrayDim; col++)
		{	//for every item in adjArray, create an edge and store it in edgeArray
			Edge newEdge;// = new Edge;
			newEdge.vertex1 = setArray[row];				//todo: i think this is right??
			newEdge.vertex2 = setArray[col];
			newEdge.weight = adjArray[(arrayDim * row) + col];
			edgeArray[(arrayDim * row) + col] = newEdge;

			if (newEdge.weight > 0)
				edgesInArray++;

		}

	for (int pos = (arrayDim * arrayDim); pos > 0; pos--)
	{	//sort the edges in ascending order
		if (edgeArray[pos].weight > 0)
		{	//if the weight isn't 0
			if (edgeArray[pos].weight < edgeArray[pos + 1].weight)
			{	//swap the two edges
				Edge temp;
				temp.vertex1 = edgeArray[pos + 1].vertex1;
				temp.vertex2 = edgeArray[pos + 1].vertex2;
				temp.weight = edgeArray[pos + 1].weight;

				edgeArray[pos + 1].vertex1 = edgeArray[pos].vertex1;
				edgeArray[pos + 1].vertex2 = edgeArray[pos].vertex2;
				edgeArray[pos + 1].weight = edgeArray[pos].weight;

				edgeArray[pos].vertex1 = temp.vertex1;
				edgeArray[pos].vertex2 = temp.vertex2;
				edgeArray[pos].weight = temp.weight;
			}
		}
	}//todo: this is where I left off on tuesday. I am far too tired to be productive right now.
}
