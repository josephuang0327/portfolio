//************************************************************************
// ASU CSE310 Assignment #8 Fall 2020
// ASU ID:
// Name:
// Description: this is the main program that reads input from keyboard,
// it then use disjoint set data structure to perform Kruskal MST algorithm
// on the graph.
// //---- is where you need to add your own codes
//**************************************************************************

#include "Graph.h"

using namespace std;

void getArrCityInfo(string oneArrCityInfo, string& arrCityName, double& price);
int searchCity(City* oneCityArray,int size, string oneCityName);

int main()
{
   int V, E;        //number of vertices and edges

   //cout << "Enter number of vertices and edges: " << endl;
   cin >> V >> E;
   cin.ignore(20, '\n');

   //a City array used to store all vertices (Cities) of the graph
   City* cityArray[V];

   //an array used to store all edges of the graph
   Edge* edgeArray[E];
   //----
   //----

   int i = 0, j = 0; //index for cityArray and edgeArray

   //local variables
   City* city1 = NULL;
   City* city2 = NULL;
   Edge* aNewEdge;

   string oneLine;

   //cout << "Enter one departure and its arrival city info." << endl;
   getline(cin, oneLine);

   while(oneLine.compare("End") != 0)
   {
      //get one line of the input, extract the first token
      //create a City if it doesn't exist in cityArray,
      //insert it inside the cityArray. This will be first point
      //for aNewEdge
      //----
      //----
	   double price;
	   string cityName;
	   string arrivalName;

	   //extract first token
	   string delimiter1 = ",";
	   int pos = oneLine.find(delimiter1);
	   string token = oneLine.substr(0,pos);
	   cityName = token;

	   oneLine.erase(0, pos+delimiter1.length());

	   int found = searchCity(cityArray[0], V, cityName);

	   if(found == -1)
	   {
		   cityArray[i]->cityName = cityName;
		   cout << cityArray[i]->cityName << endl;
		   i++;
	   }




      //extract the arrival city info. check whether it exists in
      //cityArray or not, if not, create a new City, add it inside.
      //This city will be the second point for aNewEdge
      //----
      //----

	   pos = oneLine.find(delimiter1);
	   while(pos != -1)
	   {
//		   cout << "pos: " << pos << endl;

		   getArrCityInfo(oneLine, arrivalName, price);
		   cout << "arrival: " << arrivalName << endl;
		   cout << "price: " << price << endl;

		   found = searchCity(cityArray[0], V, arrivalName);
		   cout << "found: " << found << endl;
		   cout << "here 2" << endl;

		   if(found == -1)
		   {
//			   cityArray[i]->cityName = arrivalName;
//			   cout << cityArray[i]->cityName << endl;
			   i++;
		   }

		   oneLine.erase(0, pos+delimiter1.length());
		   cout << oneLine << endl;
		   pos = oneLine.find(delimiter1);


	   }
      //by using the two cities we got above, create a new edge, add
      //it inside edgeArray
      //----
      //----

      //get next line
      //cout << "Enter one departure and its arrival city info." << endl;
      getline(cin, oneLine);
   } //repeat until the 'End'

   //Create a Graph object by using cityArray and edgeArray
   //----

   //Run Kruskal MST algorithm on above graph
   //----
}

//****************************************************************
//By giving a string, for example 'Dallas(456.5)', this function
//extract the arrival city name 'Dallas' and air ticket price '456.5'
//Note: the delimeter is left or right parenthesis
//****************************************************************
void getArrCityInfo(string oneArrCityInfo, string& arrCityName, double& price)
{
   string delimiter1 = "(", delimiter2 = ")";
   int pos=oneArrCityInfo.find(delimiter1);
   string token = oneArrCityInfo.substr(0,pos);
   arrCityName = token;

   oneArrCityInfo.erase(0, pos+delimiter1.length());

   pos = oneArrCityInfo.find(delimiter2);
   token = oneArrCityInfo.substr(0,pos);
   price = stod(token);
   oneArrCityInfo.erase(0, pos+delimiter2.length());
}

//*********************************************************************
//Given a city name, this function searches cityArray and it return the
//index of the City if it already exists, otherwise it returns -1
//****************************************************************
int searchCity(City* oneCityArray, int arraySize, string oneCityName)
{
   //----Los Angeles,Honolulu(710.5),Santa Fe(450.0),San Diego(200.0),

   //----
	int index = 0;
	while(index < arraySize)
	{
		cout << "index: " << index << endl;
		if(oneCityArray[index].cityName == oneCityName)
		{
			return index;
		}
		index++;
	}

	return -1;
}
