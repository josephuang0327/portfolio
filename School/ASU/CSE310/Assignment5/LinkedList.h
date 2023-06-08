// ASU CSE310 Assignment #5
// Name of Author: Wei Chieh Huang
// ASU ID: 1215427213
// Description: A simple linked list that implements a list of Food objects. A user can
//              perform searching, insertion or deletion on the linked list.

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

struct Food
{
	string foodID, name, supplierID;
	double price;
	struct Food* next;
};

class LinkedList
{
	private:
		struct Food* head;
		int size;
    public:
       	LinkedList();
       	~LinkedList();
       	Food* getHead();
       	int getSize();
       	bool insertFood(string foodID, string name, string supplierID, double price);
       	bool deleteFood(string foodID);
       	bool searchFood(string foodID);
       	void displayList();
};

//Constructor
LinkedList::LinkedList()
{
    head = NULL;
    size = 0;
}

//Destructor
LinkedList::~LinkedList()
{
	//----
	Food *node = NULL;
	while(head != NULL)
	{
	    node = head;
	    head = head->next;
	    delete(node);
	}
	head = NULL;
}

//Accessor for the head
Food* LinkedList::getHead()
{
    return head;
}

//Return number of foods inside the Linked list
int LinkedList::getSize()
{
	return size;
}

//Insert the parameter food at the head of the linked list.
//return true if it is inserted successfully and false otherwise
bool LinkedList::insertFood(string foodID, string name, string supplierID, double price)
{
    //----
	//instantiate pointer and variables
	Food *foodItem = new Food;
	foodItem-> foodID = foodID;
	foodItem-> name = name;
	foodItem-> supplierID = supplierID;
	foodItem-> price = price;
	foodItem-> next = NULL;

	// if head is empty add it as head
	if(head == NULL)
	{
		head = foodItem;
		size++;
		return true;
	}

	//if head is not empty, set the new food as head and head->next = old food.
	else
	{

		foodItem-> next = head;
		head = foodItem;
		size++;
		return true;
	}

	return false;

 }

//Delete the food with the given foodID from the linked list.
//Return true if it is deleted successfully and false otherwise
bool LinkedList::deleteFood(string foodID)
{
	//----
	// if head equals null which means the list is empty
	if(head == NULL)
	{
		return false;
	}
	else
	{
		// if head equals food id than head goes to next and delete the old head
		if(head->foodID == foodID)
		{
			Food *node = head;
			head = head->next;
			delete(node);
			size--;
			return true;
		}
		else
		{
			Food *current = head;
			Food *previous = NULL;

			// if current is not null than keep searching until it finds the id, if not found return false
			while(current != NULL)
			{
				if(current->foodID == foodID)
				{
					previous->next = current->next;
					delete(current);
					size--;
					return true;
				}
				previous = current;
				current = current->next;
			}
			return false;
		}
	}
}

//This function searches the food list with the given foodID
//returns true if it is found, otherwise return false.
bool LinkedList::searchFood(string foodID)
{
	//----
	struct Food *node = head;
	bool isFound = false;
	//if node is not equals to null than keep going until finding the correct food. If could not found than return false;
	while(node != NULL)
	{
		if(node->foodID == foodID)
		{
			isFound = true;
			break;
		}
		else
		{
			node = node->next;
		}
	}
	return isFound;
}

//This function displays the content of the linked list.
void LinkedList::displayList()
{
   struct Food *temp = head;

	if(head == NULL)
    {
		return;
	}
	while(temp != NULL)
    {
      cout << left;
      cout << setw(4) << temp->foodID
           << setw(30) << temp->name
           << setw(12) << temp->supplierID
           << setw(8) << temp->price << endl;
      temp = temp->next;
	}
}
