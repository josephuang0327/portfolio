//********************************************************************
// ASU CSE310 Assignment #8 Fall 2020
// Name of Author:
// ASU ID:
// Description: This is the header file that defines an undirected graph
//              with an array of vertices and edges
//********************************************************************

#include "Edge.h"

using namespace std;

class Graph
{
   private:
      int V, E;         //number of vertices and edges in the graph
      City* cityArr;    //an array of City objects
      Edge* edgeArr;    //an array of Edge objects

   public:
      Graph(int numOfCities, int numOfEdges, City* cityArray, Edge* edgeArray);
      void destructor();
      void make_set(City* aCity);
      City* find_set(City* aCity);
      void link(City* aCity, City* bCity);
      void Union(City* aCity, City* bCity);
      void printEdgeArray();
      void MergeSortEdges();
      void mergeSort(Edge* edgeArray, int start, int end);
      void merge(Edge* edgeArray, int start, int mid, int end);

      void MST_Kruskal();
};

//*******************************************************************
//Constructor
Graph::Graph(int numOfCities, int numOfEdges, City* cityArray, Edge* edgeArray)
{
	//----
	//----
}

//*******************************************************************
//Destructor
void Graph::destructor()
{
	//----
	//----
}

//*******************************************************************
//Given a City, this function creates a new set whose only member is
//the City.
void Graph::make_set(City* aCity)
{
	//----
	//----
}

//*******************************************************************
//Given a City, this function returns a pointer to the representative
//of the (unique) set containing 'aCity'
City* Graph::find_set(City* aCity)
{
	//----
	//----
}

//*******************************************************************
//Given two cities, this function checks the dynamic sets that contain
//'aCity' and 'bCity' and update their rank and parent info. accordingly
void Graph::link(City* aCity, City* bCity)
{
	//----
	//----
}

//*******************************************************************
//Given two cities, this function unites the dynamic sets that contain
//'aCity' and 'bCity' into a new set that is the union of the two sets.
void Graph::Union(City* aCity, City* bCity)
{
	//----
	//----
}

//*******************************************************************
//This function print each of the edges of edge array. It can be
//used as an auxillary function to check the MergeSort result
void Graph::printEdgeArray()
{
	//----
	//----
}

//*******************************************************************
//This function performs the Merge Sort on the graph edges according
//to the weight. Sort all edges in non-decreasing order
void Graph::MergeSortEdges()
{
	//----
	//----
}

//*******************************************************************
//This function performs the Merge Sort on a sub edgeArray.
void Graph::mergeSort(Edge* edgeArray, int start, int end)
{
	//----
	//----
}

//*******************************************************************
//This function merges the two sorted sub edgeArray.
void Graph::merge(Edge* edgeArray, int start, int mid, int end)
{
 int n1 = mid-start+1;  //get the length of the first half subarray
  int n2 = end-mid;      //get the length of the second half subarray

     //Dynamically create two new arrays each stored the sorted half
	     Edge* left = (Edge*)malloc(sizeof(Edge) * n1);
	     Edge* right = (Edge*)malloc(sizeof(Edge) * n2);

	     //----
	     //----

	   //at the end, release the memory left and right occupied
      delete left;
      delete right;
}


//*******************************************************************
//This function performs the Kruskal algorithm on the graph.
void Graph::MST_Kruskal()
{
   cout << "MST Kruskal Algorithm Result\n" << endl;
   double totalWeight = 0.0;

   //----
   //----
   //----

   cout << "=================================================" << endl;
   cout << "Total Price: " << totalWeight << endl;
}
