// Assignment: #1
// Your Name: Wei Chieh Huang
// ASU ID: 1215427213
// ASU Email Address: whuan110@asu.edu
// Description: All the method of adding, removing, changing, and searching for food name, price and id. The purpose
//				of the assignment is to review linked lists and get familiar with coding.

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//Food represents a food information
struct Food
{
    string foodName;
    int id;
    double price;
    struct Food* next;
};

//class LinkedList will contains a linked list of foods
class LinkedList
{
    private:
        struct Food* head;

    public:
        LinkedList();
        ~LinkedList();
        bool isFound(int foodId);
        bool add(string foodName, int foodId, double foodPrice);
        bool removeById(int foodId);
        bool removeByName(string foodName);
        bool changeFoodName(int foodId, string newFoodName);
        bool changeFoodPrice(int foodId, double newPrice);
        void printFoodList();
};

//Constructor to initialize an empty linked list
LinkedList::LinkedList()
{
    head = NULL;
}

//Destructor
//Before termination, the destructor is called to free the associated memory occupied by the existing linked list.
//It deletes all the nodes including the head and finally prints the number of nodes deleted by it.
//Return value: Prints the number of nodes deleted by it.
LinkedList::~LinkedList()
{
    int foodCount = 0;
    // code below to free up the memory of the food list and count how many item is being removed.
    Food *node = NULL;
    while(head != NULL)
    {
    	node = head;
    	head = head->next;
    	delete(node);
    	foodCount++;
    }
    head = NULL;

    cout << "The number of deleted food items is: " << foodCount <<"\n";
}

//A function to identify whether the parameterized food is inside the LinkedList or not.
//Return true if it exists and false otherwise.
bool LinkedList::isFound(int foodId)
{
	//----
	//----
	struct Food *node = head;
	bool isFound = false;
	//if node is not equals to null than keep going until finding the correct food. If could not found than return false;
	while(node != NULL)
	{
		if(node->id == foodId)
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

//Creates a new node and inserts it into the list at the right place.
//It maintains an alphabetical ordering of foods by their names. Each
//food item has a unique id, if two food items have exactly the same name,
//then insert it into the list in the increasing order of their IDs.
//Return value: true if it is successfully inserted and false in case of failures.
bool LinkedList::add(string foodName, int foodId, double foodPrice)
{
	//instantiate pointer and variables
	Food *foodItem = new Food;
	foodItem-> foodName = foodName;
	foodItem-> id = foodId;
	foodItem-> price = foodPrice;
	foodItem-> next = NULL;

	if(head == NULL)
	{
		head = foodItem;
		return true;
	}
	else
	{
		// if head new food item has smaller value, let head be the new item.
		if(foodItem-> foodName.compare(head->foodName) < 0)
		{
			foodItem-> next = head;
			head = foodItem;
			return true;
		}

		else
		{
			Food *current = head;
			Food *previous = NULL;
			// when current is not null keep going through next node until a empty node and add there.
			while(current != NULL)
			{
				// if head not equal to null and new item is smaller than head
				if(foodItem-> foodName.compare(current->foodName) < 0)
				{
					foodItem-> next = current;
					previous-> next = foodItem;
					return true;
				}
				// if food item equals to the current food name
				else if(foodItem->foodName == current->foodName)
				{
					//if head has the same food name than compare id
					if(foodItem->foodName == head->foodName)
					{
						if(foodItem->id > head->id)
						{
							foodItem->next = current->next;
							current->next = foodItem;
							return true;
						}
						else if(foodItem->id == head->id)
						{
							cout << "Duplicated food item. Not added." << endl;
							return false;
						}
						previous = foodItem;
						previous->next = current;
						head = previous;
						return true;
					}

					// if other node has the same name compare id
					if(foodItem->id < current->id)
					{
						foodItem->next = current;
						previous->next = foodItem;
						return true;
					}
					else if(foodItem->id == current->id)
					{
						cout << "Duplicated food item. Not added." << endl;
						return false;
					}
				}
				previous = current;
				current = current-> next;

			}
			previous->next = foodItem;
			return true;
		}
		return false;
	}
     //----
     //----
}

//Removes the given food by Id from the list, releases the memory and updates pointers.
//Return true if it is successfully removed, false otherwise.
bool LinkedList::removeById(int foodId)
{
	//----
	//----
	// if head equals null which means the list is empty
	if(head == NULL)
	{
		return false;
	}
	else
	{
		// if head equals food id than head goes to next and delete the old head
		if(head->id == foodId)
		{
			Food *node = head;
			head = head->next;
			delete(node);
			return true;
		}
		else
		{
			Food *current = head;
			Food *previous = NULL;
			// if current is not null than keep searching until it finds the id, if not found return false
			while(current != NULL)
			{
				if(current->id == foodId)
				{
					previous->next = current->next;
					delete(current);
					return true;
				}
				previous = current;
				current = current->next;
			}
			return false;
		}
	}
}

//Removes the given food by name from the list, releases the memory and updates pointers.
//Return true if it is successfully removed, false otherwise. Note: all foods with
//the parameterized name should be removed from the list.
bool LinkedList::removeByName(string foodName)
{
	//----
	//----
	// if head equals null which means the list is empty
	if(head == NULL)
	{
		return false;
	}
	else
	{
		bool isFound = false;
		Food *current = head;
		Food *previous = NULL;
		Food *node = NULL;
		Food *newCurrent = NULL;
		// if current is not null than keep searching until it finds the id, if not found return false
		while(current != NULL)
		{
			// if the head is food name than move the head to next node and delete old head and keep searching.
			if(head->foodName == foodName)
			{
				node = head;
				head = head->next;
				current = head;
				delete(node);
				isFound = true;
			}
			else if(current->foodName == foodName)
			{
				while(current->foodName == foodName || current != NULL)
				{
					node = current;
					current = current->next;
					previous->next = current;
					delete(node);
					if(current == NULL || current->foodName != foodName)
					{
						break;
					}
				}
				return true;
			}
			previous = current;
			current = current->next;
		}

		// return true if found and delete the name
		if(isFound == true)
		{
			return true;
		}
		else
		{
			cout << "No such food name found." << endl;
			return false;
		}
	}
}

//Modifies the name of the given Food item. Return true if it modifies successfully and
//false otherwise. Note: after changing a food name, the linked list must still be
//in alphabetical order of foods name
bool LinkedList::changeFoodName(int oldFoodId, string newFoodName)
{
	//----
	//----
	// if head equals null which means the list is empty
	if(head == NULL)
	{
		return false;
	}
	else
	{
		Food *current = head;
		Food *previous = NULL;
		Food *preNode = NULL;
		Food *node = NULL;
		// while current is not empty than find the food name, if the name is found replace it.
		while(current != NULL)
		{
			// if head id equals to the change search id
			if(head->id == oldFoodId)
			{
				current->foodName = newFoodName;
				node = current;
				previous = current;
				current = current->next;
				while(current != NULL)
				{
					// if node is smaller than the current name
					if(node->foodName == current->foodName)
					{
						if(head->id < current->id)
						{
							head = head->next;
							node->next = current;
							previous->next = node;
							return true;
						}
					}
					if(node->foodName.compare(current->foodName) < 0)
					{
						// if the current is head stay where it is.
						if(current == head)
						{
							// compare the two ids
							if(node->id > head->id)
							{
								head = head->next;
								node->next = current->next;
								previous->next = node;
								return true;
							}
							return true;
						}

						head = head->next;
						node->next = current;
						previous->next = node;
						return true;
					}
					previous = current;
					current = current->next;
				}

				head = head->next;
				node->next = current;
				previous->next = node;
				return true;
			}
			//if node other than head id is the same
			else if(current->id == oldFoodId)
			{
				current->foodName = newFoodName;
				node = current;
				current = head;
					while(current !=  NULL)
					{
						// if the change node is smaller than the head
						if(node->foodName.compare(head->foodName) < 0)
						{
							if(node->id < head->id)
							{
								preNode->next = node->next;
								//current->next = node->next;
								node->next = current;
								head = node;
								return true;
							}
							preNode->next = node->next;
							node->next = current;
							head = node;
							return true;
						}
						// if the replace node is smaller than other node, replace it.
						else if(node->foodName.compare(current->foodName) < 0)
						{
							if(node->id < head->id)
							{
								preNode->next = node->next;
								node->next = head;
								head = node;
								return true;
							}
							if(node->id > current->id)
							{
								current = current->next;
								node->next = current->next;
								previous->next = node;
								return true;
							}
							preNode->next = node->next;
							node->next = current;
							previous->next = node;
							return true;
						}
						previous = current;
						current = current->next;
					}
					// otherwise put the node at the end of the list
					preNode->next = node->next;
					node->next = current;
					previous->next = node;
					return true;
			}
			preNode = current;
			current = current->next;
		}
		return false;
	}
}

//Modifies the price of the given food item. Return true if it modifies successfully and
//false otherwise.
bool LinkedList::changeFoodPrice(int foodId, double newPrice)
{
    //----
    //----
	// if head equals null which means the list is empty
		if(head == NULL)
		{
			return false;
		}
		else
		{
			Food *current = head;
			// while current is not empty than find the food id, if the id is found replace the price.
			while(current != NULL)
			{
				if(current->id == foodId)
				{
					current->price = newPrice;
					return true;
				}
				current = current->next;
			}
			return false;
		}
}

//Prints all the elements in the linked list starting from the head node.
void LinkedList::printFoodList()
{
    //----
    //----

	// if head is empty than the list is empty
	if(head == NULL)
	{
		cout << "The list is empty" << endl;
	}
	//list all the food in the list
	else
	{
		Food *current = head;
		while(current != NULL)
		{
			cout << current->foodName << "	" << current-> id<< "	" << "$" << current->price << fixed << setprecision(2) << endl;
			current = current->next;
		}
	}
}
