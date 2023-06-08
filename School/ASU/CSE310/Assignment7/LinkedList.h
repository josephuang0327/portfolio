//********************************************************************
// ASU CSE310 Assignment #7
// Name: Wei Chieh Huang
// ASU ID: 1215427213
// Description: This is the linked list that will contain the list of
// city that the source city have a route to.
//********************************************************************

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//struct ArrCity represents an arrival city information with
//price info. from the departure city
struct ArrCity
{
    string arrCityName;
    int price;
    struct ArrCity* next;
};

//class LinkedList will contains a linked list of ArrCity
class LinkedList
{
    private:
        struct ArrCity* head;

    public:
        LinkedList();
        ~LinkedList();
        ArrCity* getHead();
        ArrCity* findArrCity(string aCity);
        bool addArrCity(string aCity, int price);
        void printArrCityList();
};

//Define all remaining functions according to above function declaration
//----
//----
LinkedList::LinkedList()
{
	head = NULL;
}

//destructor of the linked list
LinkedList::~LinkedList()
{
	ArrCity* node = NULL;
	while(head != NULL)
	{
	    node = head;
	    head = head->next;
	    delete(node);
	}
	head = NULL;
}

// get head
ArrCity* LinkedList::getHead()
{
	return head;
}

// find the city in the linked list
ArrCity* LinkedList::findArrCity(string aCity)
{
	ArrCity* current = head;

	//if list is empty
	if(head == NULL)
	{
		return NULL;
	}

	//loop through the linked list
	while(current->next != NULL)
	{
		//if matched return pointer
		if(current->arrCityName == aCity)
		{
			return current;
		}
		current = current->next;
	}
	return NULL;
}
//add the arrival city and price
bool LinkedList::addArrCity(string aCity, int price)
{
	ArrCity* current = head;
	ArrCity* cityInfo = new ArrCity;

	cityInfo-> arrCityName = aCity;
	cityInfo-> price = price;

	// if head is empty add it as head
	if(head == NULL)
	{
		head = cityInfo;
		return true;
	}

	//if head is not empty, set the new city as head and head->next = old food.
	else
	{
		while(current->next != NULL)
		{
			current = current->next;
		}
		current->next = cityInfo;
//		cityInfo-> next = head;
//		head = cityInfo;
		return true;
	}

	return false;

}



//Prints all the elements in the linked list starting from the head.
void LinkedList::printArrCityList()
{
    struct ArrCity *temp = head;

	if(head == NULL)
    {
		cout << "Arrival city list is empty\n";
		return;
	}
	while(temp!= NULL)
    {
		cout << temp->arrCityName << "(" << temp->price << "),";
		temp = temp->next;
	}
	cout <<"\n";
}
