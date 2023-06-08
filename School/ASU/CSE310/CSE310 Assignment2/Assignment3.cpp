//********************************************************************************
// Assignment: ASU CSE310 HW#3
// Name: Wei Chieh Huang
// ASU ID: 1215427213
// ASU Email Address: whuan110@asu.edu
// Description: This program displays a menu of choices to a user
//              and performs the chosen task. It will keep asking a user to
//              enter the next choice until the choice of 'Q' (Quit) is entered.
//             	//---- is where you should add your own code
//********************************************************************************

#include <iostream>
#include <string>
//include the header file here
//----
#include "Heap.h"

using namespace std;

void printMenu();

int main()
{
	char input1 = 'Z';
	string foodName;
	int key, newKey;
	int capacity, index = -1;   //1D array capacity and index
	double price;
	bool success = false;

    Food oneFood, maxFood;

	//a variable used to represent a Heap object
	Heap* heap1 = nullptr;
	printMenu();

	do {
		cout << "\nWhat action would you like to perform?" << endl;
		cin.get(input1);
		input1 = toupper(input1);
		cin.ignore(20, '\n');	//flush the buffer

		// matches one of the cases
		switch (input1)
		{
			case 'C':	//create empty Heap with the relevant capacity
				cout << "\nPlease enter the heap capacity: ";
				//----
				//----
				cin >> capacity;
				cin.ignore(20, '\n');	//flush the buffer
				heap1 = new Heap(capacity);
				break;

			//delete the heap, call the destructor explicitly. Re-initialize heap1
			//with capacity 5
			case 'D':
				cout << "\nDelete the heap" << endl;
				//----
				//----
				heap1->~Heap();
				heap1 = new Heap(5);
				break;

			case 'E':	//Extract the maximum node
                //----
				//----
				if(heap1 == NULL)	// if heap is empty
				{
					cout << endl << "Empty heap, can NOT extract max" << endl;
				}
				else
				{
//					cout << endl << "Before extract heap max operation" << endl;
					heap1->extractHeapMax();
//					cout << endl << "After extract heap max operation" << endl;
				}
				break;

			case 'F':	//Find a food
				cout << "\nEnter the food key you want to search: ";
				cin >> key;
				cin.ignore(20, '\n');	//flush the buffer

				//----
				//----
				if(heap1->isFound(key) == -1)	// if the key is not found
				{
					cout << endl << "Food with key: " << key << " is NOT found" << endl;
				}
				else	// if the key is found
				{
					cout << endl << "Food with key: " << key << " is found" << endl;
				}

				break;

			case 'I':	//Insert a Food
				cout << "\nEnter the food name: ";
				getline(cin, foodName);
				cout << "\nEnter food key: ";
				cin >> key;
				cout << "\nEnter the food price: ";
				cin >> price;
				cin.ignore(20, '\n');	//flush the buffer

				//----
				//----
				success = heap1->insert(key, foodName, price);
				//cout << "success" << success << endl;
				if(success == true)	// if insert is success
				{
					cout << endl << "The food \"" << foodName << "\" is added" << endl;
				}
				else	// if insert fail
				{
					cout << endl << "The food \"" << foodName << "\" is NOT added" << endl;
				}
				break;

			case 'K':	//increase the key
				cout << "\nEnter the old food key you want to increase: ";
				cin >> key;
				cout << "\nEnter the new key value: ";
				cin >> newKey;
				cin.ignore(20, '\n');	//flush the buffer

				//----
				//----
				oneFood.key = newKey;
				if(newKey < key)	// check if new key is less than old key.
				{
					cout << endl << "Increase key error: new key is smaller than current key" << endl;
					break;
				}

				index = heap1->isFound(newKey);
				if(index != -1)	// check if new key exist already
				{
					cout << endl << "The new key you entered already exist, increase key operation failed" << endl;
					break;
				}

				index = heap1->isFound(key);
				if(index == -1) // check if the old key exist
				{
					cout << endl << "The old key you try to increase does not exist" << endl;
					break;
				}
				else // no error then increase key
				{
					heap1->increaseKey(index,oneFood);
				}
				cout << endl << "Food with old key: " << key << " is increased to new key: " << newKey << endl;
				cout << endl << "After increase key operation:" << endl;
				heap1->printHeap();
				break;
			case 'M':	//get the maximum node
			    //----
				//----
				maxFood = heap1->getHeapMax();
				if(heap1->getSize() == 0)	// if heap is empty
				{
					cout << "Empty heap, cannot get max node" << endl;
				}
				else	// print
				{
					cout << endl << "The maximum heap node is:" << endl;
					cout << setw(5) << maxFood.key
						 << setw(8) << maxFood.foodName
						 << setw(8) << fixed << setprecision(2) << maxFood.price << endl;
				}
				break;

			case 'P':	//Print heap contents
			    //----
				//----
				heap1->printHeap();

				break;

			case 'Q':	//Quit
				delete heap1;
				break;

			case '?':	//Display Menu
				printMenu();
				break;

			default:
				cout << "Unknown action\n";
				break;
		}
	} while (input1 != 'Q');
	return 0;
}

/**The function displays the menu to a user**/
void printMenu()
{
	cout << "Choice\t\tAction\n";
	cout << "------\t\t------\n";
	cout << "C\t\tCreate a heap\n";
	cout << "D\t\tDelete the heap\n";
	cout << "E\t\tExtract max node\n";
	cout << "F\t\tFind a food by key\n";
	cout << "I\t\tInsert a food\n";
	cout << "K\t\tIncrease the key\n";
	cout << "M\t\tGet the max node\n";
	cout << "P\t\tPrint the heap\n";
	cout << "Q\t\tQuit\n";
	cout << "?\t\tDisplay Help\n\n";
}
