//********************************************************************
// ASU CSE310 Assignment #7
// Name of Author: Wei Chieh Huang
// ASU ID: 1215427213
// Description: This is the header file that defines a directed graph
//********************************************************************

#include "MinHeap.h"

using namespace std;

class Graph
{
   private:
   int numOfNode;        //number of nodes in the graph
   MinHeap* cityHeap;    //a min-heap of departure City objects

   //feel free to add other necessary functions
   public:
   Graph(int numOfNode, MinHeap* cityHeap);
   void destructor();
   void printGraph();
   void initialize_single_source(string sourceCityName);
   void relax(City u, City v);
   int findOneCity(string aCityName);

   void dijkstra(string sourceCityName);
   void printDijkstraPath(string sourceCityName);
};

//*******************************************************************
//Constructor
Graph::Graph(int numOfNode, MinHeap* cityHeap)
{
   this->numOfNode = numOfNode;
   this->cityHeap = cityHeap;
}

//*******************************************************************
//Destructor Graph::~Graph()
void Graph::destructor()
{
   delete [] cityHeap;
   cityHeap = NULL;
   numOfNode = 0;
}

//Define all remaining functions according to above function declaration
//----
//----

void Graph::printGraph()
{
	cout << left;
	cout << setw(15) << "City Name"
	     << setw(12) << "d Value"
	     << setw(15) << "PI"
	     << "Arrival City List" << endl;
}

// Set the price and pi to default value
void Graph::initialize_single_source(string sourceCityName)
{
	//seting all value
	for(int i = 0; i < numOfNode; i++)
	{
		cityHeap->getCityArr()[i].d = 99999;
		cityHeap->getCityArr()[i].pi = NULL;
	}

	int index = findOneCity(sourceCityName);
	cityHeap->getCityArr()[index].d = 0;

	/*
	 * for each vertex v in G.V
	 * {
	 * 	v.d = inf
	 * 	v.pi = null
	 * 	}
	 * s.d = 0
	 */
}

// updating the cost of all vertices
void Graph::relax(City u, City v)
{
	if(u.cityName.empty())	// if u city is empty
	{
		return;
	}
	int weight = u.arrCityList->findArrCity(v.cityName)->price;

	if(v.d > u.d + weight) // find the best route
	{
		v.d = u.d + weight;
		v.pi = &u;
		cityHeap->decreaseKey(cityHeap->isFound(v.cityName), v);
	}
}

// find the city
int Graph::findOneCity(string aCityName)
{
	for(int i = 0; i < numOfNode; i++)
	{
		if(cityHeap[i].isFound(aCityName) != -1) // if is found
		{
			int pos = cityHeap[i].isFound(aCityName);
			return pos;
		}
	}
	return -1;
}

//*******************************************************************
//This function performs the dijkstra's shortest path algorithm
void Graph::dijkstra(string sourceCityName)
{
   //----
	initialize_single_source(sourceCityName);
	MinHeap* S = new MinHeap(cityHeap->getCapacity());
	MinHeap* Q = new MinHeap(cityHeap->getCapacity());

	for(size_t i = 0; i < cityHeap->getSize(); i++)
	{
		Q->insert(cityHeap->getCityArr()[i]);
	}

	while(Q->getSize() > 0)	//when it is not empty
	{
		City u  = Q->getHeapMin();
		Q->extractHeapMin();
		S->insert(u);
		City v;
		ArrCity* adjacent = u.arrCityList->getHead();

		while(adjacent != NULL)	// while there is adjacent city
		{
			v = S->getCityArr()[S->isFound(adjacent->arrCityName)];
			relax((S->getCityArr()[S->isFound(u.cityName)]),v);
			adjacent = adjacent->next;
		}
	}

	/*
	 * Q = G.V
	 * while(Q != NULL)
	 * {
	 * U = extractMin(Q)
	 * S = S{u}
	 * for vertex v in G.adj[u]
	 * {
	 * relax(u.v.w)
	 * }
	 * }
	 */

}

//*********************************************************************************
//This function prints the cheapest price and path after the Dijkstra's algorithm
void Graph::printDijkstraPath(string sourceCityName)
{
   cout << "\nSource City: " << sourceCityName << endl;
   cout << left;
   cout << setw(15) << "\nArrival City" << setw(15) << "Lowest Price"   << setw(15) << "Shortest Path" << endl;
   //----
   //----

   int index = findOneCity(sourceCityName);

   cout << setw(15) << cityHeap->getCityArr()[index].cityName << setw(15) << cityHeap->getCityArr()[index].d << cityHeap->getCityArr()[index].arrCityList << endl;

   City* pos = &(cityHeap->getCityArr()[index]);
   while(pos->pi != NULL)
   {
	   City tempPath = cityHeap->getCityArr()[index];
	   string path;
	   while(tempPath.cityName != pos->cityName)
	   {
		   int i = 0;
		   if(i > 0)
		   {
			   path = path + "->";
		   }
		   i++;
	   }
	   cout << setw(15) << cityHeap->getCityArr()[index].cityName << setw(15) << cityHeap->getCityArr()[index].d << path << endl;;
	   pos = pos->pi;
   }



}
