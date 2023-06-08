// ASU CSE310 Assignment #5
// Name of Author: Wei Chieh Huang
// ASU ID: 1215427213
// Description: this is where you need to design functions on Hash hashTable,
// such as hashInsert, hashDelete, hashSearch and hashDisplay

#include "LinkedList.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <math.h>

using namespace std;

class Hash
{
    private:
		LinkedList* hashTable;     //hashTable is a one-dimensional array of LinkedList
		int m;                     //slots number of the hash table
	public:
      Hash(int size);
      ~Hash();
      bool hashInsert(string foodID, string name, string supplierID, double price);
      bool hashDelete(string foodID, string name, string supplierID);
      bool hashSearch(string foodID, string name, string supplierID);
      void hashDisplay();
      int hashFunction(string key);

      //add any other auxiliary functions here
      //----
};

//constructor
Hash::Hash(int size)
{
	hashTable = new LinkedList[size];
	m = size;
}

//Destructor
Hash::~Hash()
{
	//----
	delete[] hashTable;
}

//hashInsert inserts a Food with the relevant info. into the hashTable.
//it returns true if the data is inserted successfully and false otherwise
bool Hash::hashInsert(string foodID, string name, string supplierID, double price)
{
	//----
	string key = foodID + name + supplierID;
	int keyIndex = hashFunction(key);

	// insert the food to the linked list by the index using hash function
	hashTable[keyIndex].insertFood(foodID, name, supplierID, price);
	cout << "slot index = " << keyIndex << endl;

	return true;
}

//hashDelete deletes a Food with the relevant key from the hashTable.
//it returns true if it is deleted successfully and false otherwise
//Note: key is the combination of foodID, name and supplierID
bool Hash::hashDelete(string foodID, string name, string supplierID)
{
      //----
	  string key = foodID + name + supplierID;
	  int keyIndex = hashFunction(key);
	  bool found = hashSearch(foodID, name, supplierID);

	  //if the food is not in the hash table
	  if(found == false)
	  {
	      cout << "\n";
	      cout	<< setw(4) << foodID
	            << setw(30) << name
	            << setw(12) << supplierID
	            << " is NOT deleted from hash table.\n" << endl;
		  return false;
	  }

	  //otherwise delete the food and notice the user is deleted
	  hashTable[keyIndex].deleteFood(foodID);
      cout << "\n";
      cout	<< setw(4) << foodID
            << setw(30) << name
            << setw(12) << supplierID
            << " is deleted from hash table.\n" << endl;
      return true;
}

//This function searches for a key inside the hash table and
//return true if it is found and false otherwise
//Note: key is the combination of foodID, name and supplierID
bool Hash::hashSearch(string foodID, string name, string supplierID)
{
    //----
   bool found = false;
   string key = foodID + name + supplierID;
   int keyIndex = hashFunction(key);
   found = hashTable[keyIndex].searchFood(foodID);

   //if the food ID is found in the hash table
   if (found)
   {
     cout   << "\n" << left
            << setw(4) << foodID
            << setw(30) << name
            << setw(12) << supplierID
            << " is found inside the hash table." << endl;
   	   	    return true;
   }
   	//if the food ID is not found in the hash table
	if(!found)
	{
      cout	<< "\n" << left
            << setw(4) << foodID
            << setw(30) << name
            << setw(12) << supplierID
            << " is NOT found inside the hash table." << endl;
			return false;
	}
 }

//This function prints all the elements from the hash hashTable.
void Hash::hashDisplay()
{
	//----
	//----
	// print out the hash table
	for(int i = 0; i < m; i++)
	{
		cout << "\nHashTable[" << i << "], size = " << hashTable[i].getSize() << endl;
		hashTable[i].displayList();
	}

}

//This is the hash function you will need to design, test and refine
//Given a Food key, the function should return the slot index where it
//will be hashed to
int Hash::hashFunction(string key)
{
    //----
	int keyNum = 0;
	int keyIndex = 0;
	double numMult = 0.65;

	// add each ascii value of string to to keyNum
	for(int i = 0; i < key.length(); i++)
	{
		keyNum = keyNum + key[i];
	}

	// using hash by multiplication by multiply a constant between 0 ~ 1
	keyNum = floor(keyNum * numMult);
	keyIndex = keyNum % m;

	return keyIndex;

}
