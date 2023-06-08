//********************************************************************
// ASU CSE310 Assignment #7
// Name of Author: Wei Chieh Huang
// ASU ID: 1215427213
// Description: This is the driver program which add city and
//				arrival city to the heap and linked list.
//********************************************************************

#include "Graph.h"

using namespace std;

void getCityInfo(string oneLine, string& depCityName, LinkedList* arrCityList);
void getArrCityInfo(string oneArrCityInfo, string& arrCityName, int& distance);

int main()
{
   int count;       //a variable for number of nodes
   string oneLine, sourceCityName;
   cout << "Enter num of cities: ";
   cin >> count;
   cin.ignore(20, '\n');       //will be used in Linux testing

   //For each line, we will create a LinkedList for a specific departure city
   //it represents all its reachable arrival cities.
   //Here we use an array of City to store them
   City* cityArr = new City[count];
   LinkedList* ll = new LinkedList();

   //Initialize cityArr. set each node's d value to be very large 20000
   //initialize each arrival city list
   for(int i = 0; i< count; i++)
   {
      cityArr[i].d = 20000;
      //----
      //----
      cityArr[i].cityName = "";
      cityArr[i].pi = NULL;
      cityArr[i].arrCityList = NULL;
   }

   //get input line by line
   for(int i = 0; i< count; i++)
   {
      cout << "\nEnter one City info.: " << endl;
      getline(cin, oneLine);
      //----
      string dCityName;
      LinkedList* arrCityList = new LinkedList();

      getCityInfo(oneLine, dCityName, arrCityList);

      cityArr[i].cityName = dCityName;
      cityArr[i].arrCityList = arrCityList;

   }

   cout << "Enter source city name: " << endl;
   getline(cin, sourceCityName);

   //create a MinHeap which capacity is double the size
   MinHeap* cityHeap = new MinHeap(count*2);

   //insert each City objects one by one inside cityHeap
   //----
   for(int i = 0; i < count; i++)
   {
	   cityHeap->insert(cityArr[i]);
   }


   //create a Graph object by using its constructor
   //----
   Graph* graph = new Graph(count, cityHeap);


   //print the graph adjacency list before running Dijkstra algorithm
   cout << "\nPrint the graph before Dijkstra algorithm" << endl;
   //----;
   cityHeap->printHeap();

   //Do depth first search on the graph
   //----
   graph->dijkstra(sourceCityName);

   //print the Dijkstra shortest path result
   cout << "\nPrint the Dijkstra algorithm running result" << endl;
   //----
   graph->printDijkstraPath(sourceCityName);
}

//**************************************************************
//This function from one line, get all city info.
void getCityInfo(string oneLine, string& depCityName, LinkedList* arrCityList)
{
   //----
	LinkedList* ll = new LinkedList();
	string token;
	string delimiter = ",";
	string arrCity = "";
	int price = 0;
    int pos = 0;

    pos = oneLine.find(delimiter);
    token = oneLine.substr(0, pos);
    depCityName = token;
    oneLine.erase(0, pos + delimiter.length());

    pos = oneLine.find(delimiter);
    while(pos != -1)	// keep extracting until there is no more city
    {
		token = oneLine.substr(0, pos);
		getArrCityInfo(token, arrCity, price);
		arrCityList->addArrCity(arrCity, price);
		oneLine.erase(0, pos + delimiter.length());
		pos = oneLine.find(delimiter);
    }

}

//****************************************************************************
//
void getArrCityInfo(string oneArrCityInfo, string& arrCityName, int& distance)
{
   string delimiter1 = "(", delimiter2 = ")";
   int pos = oneArrCityInfo.find(delimiter1);
   string token = oneArrCityInfo.substr(0,pos);
   arrCityName = token;

   oneArrCityInfo.erase(0, pos+delimiter1.length());

   pos = oneArrCityInfo.find(delimiter2);
   token = oneArrCityInfo.substr(0,pos);
   distance = stoi(token);
   oneArrCityInfo.erase(0, pos+delimiter2.length());
}
