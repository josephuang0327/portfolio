// ASU CSE310 Assignment #5
// Name of Author: Wei Chieh Huang
// ASU ID: 1215427213
// Description: this is the main program that reads input from keyboard,
// it then call hash functions to execute hash commands given in the input.

/**************************************************************************
//(1)Describe here what is your hash function?
 * My hash function was a multiplication hash function. Which it multiplies
 * the ascii key value with a constant that is between 0 ~ 1 (0.65 in this
 * program). Then, modulo it by the size of the hash table. Which the result
 * was ranging between 8 ~ 14.
 *
//(2)What is the number of collisions you expected?
 * The ultimate number will be somewhere between 9 ~ 10 in each index. Since
 * there are 109 inputs and the size of the hash table is 11. The ideal
 * distribution will be equally spread. However, it is hard to achieve that.
 * My solution is 8 ~ 14 which is pretty close in my opinion.
 *
//(3)Did your hash function work well? Using the test cases, what's your hash
//   table's load factor?
 * I think my hash function worked pretty well since it is close to the ideal
 * distribution in my opinion. The load factor can be calculated using
 * (number of elements) / (number of index) which is (109/11) = 9.9 for test
 * case #4.
 *
//(4)If you had to change your hash function to reduce the number of collisions,
//   how will you change it?
 * If I have to reduce the number of collision I will probably tested more
 * constant values for my multiplication hash function. If all of them doesn't
 * work, then I'll probably test using hash by division as my new hash
 * function.
//----
***************************************************************************/

#include "Hash.h"
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>


using namespace std;

//This function extracts tokens from oneLine and get all info. of a Food
void getFoodInfo(string oneLine, string& FoodID, string& name, string& supplierID, double& price);

//This function extracts tokens from oneLine and get a Food key which is
//the combination of FoodID, name and supplierID
void getKey(string oneLine, string& FoodID, string& name, string& supplierID);

int main()
{
    //a variable represents the number of hash table slots
   int size;

    //a variable represents the number of commands
   int numOfCommand;

    //a variable represents the actual command name
   string command;

   string FoodID, name, supplierID;
   double price;
   string delimiter = ",";

	//declare any other necessary variables here
   //----

   string oneLine;

   cout << "Enter the size of the hash table: ";
   cin >> size;
   cin.ignore(20, '\n');

   //create the hash table with the relevant number of slots
   //----
   Hash* hashTable = new Hash(size);

 do {
		cout << "\nEnter food info.(enter InsertionEnd to terminate): " << endl;
		getline(cin, oneLine);
		if(oneLine.compare("InsertionEnd") == 0)
            break;

      //if command is not InsertionEnd
      //Get one line, call getFoodInfo(), then
      //insert the new Food inside the hash table
      //----

		getFoodInfo(oneLine, FoodID, name, supplierID, price);
		hashTable->hashInsert(FoodID, name, supplierID, price);

	} while(true);
 	cout << "\nEnter number of commands: " << endl;
    cin >> numOfCommand;
    cin.ignore(20, '\n');

	for(int i= 0; i < numOfCommand; i++)
   {
 		//get one line from the input file and extract the first token,
 		//if the token is hashDisplay, call the relevant function in Hash.h
 		//-----

		//ask for the command
		cout << "Enter command: " << endl;
		getline(cin,oneLine);

		//extract the first token
		command = oneLine.substr(0, oneLine.find(delimiter));
		getKey(oneLine, FoodID, name, supplierID);

		if(command.compare("hashDisplay") == 0)
		{
			hashTable->hashDisplay();
		}

 		//if the token is hashSearch, call the relevant function in Hash.h
 		//----

		else if(command.compare("hashSearch") == 0)
		{
			hashTable->hashSearch(FoodID, name, supplierID);
			cout << endl;
		}

 		//if the token is hashDelete, call the relevant function in Hash.h
 		//----

		else if(command.compare("hashDelete") == 0)
		{
			hashTable->hashDelete(FoodID, name, supplierID);
		}

      //for all other cases, show the following message
      //cout << "Invalid command" << endl;

		else
		{
			cout << "Invalid command" << endl;
		}

   } //end for loop

	return 0;
} //end main

//*******************************************************************
//This function extract the tokens from one line and
//get all Food info.
//*******************************************************************
void getFoodInfo(string oneLine, string& FoodID, string& name, string& supplierID, double& price)
{
   string delimiter = ",";

   //finish the remaining codes below
   //----
   //----

   // similar to the getKey() function that is given by the professor
   	int pos = oneLine.find(delimiter);
   	string token = oneLine.substr(0,pos);
   	FoodID = token;
   	oneLine.erase(0, pos+delimiter.length());

   	pos = oneLine.find(delimiter);
   	token = oneLine.substr(0,pos);
   	name = token;
   	oneLine.erase(0, pos+delimiter.length());

   	pos = oneLine.find(delimiter);
   	token = oneLine.substr(0,pos);
   	supplierID = token;
   	oneLine.erase(0, pos+delimiter.length());

   	pos=oneLine.find(delimiter);
   	token = oneLine.substr(0,pos);
   	price = std::stod(token);
   	oneLine.erase(0, pos+delimiter.length());


   //Note: you can use stod to convert a string into double
   //but you will need c++11 compiler to achieve this
   //for example: price = stod(token);
}

//********************************************************************
//This function extracts the FoodID, name, supplierID from a given line
//These info. forms the key of a Food.
//This function is given to you. Study it.
//********************************************************************
void getKey(string oneLine, string& FoodID, string& name, string& supplierID)
{
    string delimiter = ",";
    int pos=oneLine.find(delimiter);
	string token = oneLine.substr(0,pos);
	string command = token;
	oneLine.erase(0, pos+delimiter.length());

	pos=oneLine.find(delimiter);
	token = oneLine.substr(0,pos);
	FoodID = token;
	oneLine.erase(0, pos+delimiter.length());

	pos=oneLine.find(delimiter);
	token = oneLine.substr(0,pos);
	name = token;
	oneLine.erase(0, pos+delimiter.length());

	pos=oneLine.find(delimiter);
	token = oneLine.substr(0,pos);
	supplierID = token;
	oneLine.erase(0, pos+delimiter.length());
}
