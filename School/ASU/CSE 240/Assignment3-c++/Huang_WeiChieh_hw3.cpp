/*
Author: Wei Chieh Huang
Date:	28/Feb/2020
Description: Create three kind of arrays, one dimensional integer array, one dimensional char array, two dimensional string array
			 Use random generator to fill integer and char array. Making function for calculating median, average, duplicate, and
			 uniques. Sort integer and char array, using quick sort, merger sort, or shell sort.
*/

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

void OneD();
void SingleDimension();
void TwoD();
void FillCharArray(char*, int);
void CharSort(char*, int, int);
void SortArray(int*, int, int);

float CalcAverage(int*, int);
float CalcMedian(int*, int);

int CalcDuplicate(int*, int);
int CountFrequency(char*, int, char);
int RemoveChar(char*, int, char);

char RandomChar();


// initialization all function above

int main (int argc, char *argv[])
{
	int option;
	bool checkQuit = false;

	// initialization above

	cout << "Welcome to Assignment 3!" << endl;


	while(checkQuit == false)										// Menu
	{
		cout << "Menu:" << endl;
		cout << "1 - 1D Math" << endl;
		cout << "2 - Single Dimension Character Processing" << endl;
		cout << "3 - Two-D Character Processing" << endl;
		cout << "4 - Exit" << endl;
		cout << "Choose an option:" << endl;
		cin >> option;												// ask for options

		if(option == 1)												// option1 1D math
		{
			OneD();
			cout << endl;
		}
		else if(option == 2)										// option2 single dimension (char array)
		{
			SingleDimension();
			cout << endl;
		}
		else if(option == 3)										// option3 two dimension (stirng array)
		{
			TwoD();
			cout << endl;
		}
		else if(option == 4)										// check if exit
		{
			checkQuit = true;
		}
		else														// if enter not 1 through 4 than go back to menu
		{
			cout << "\nPlease enter a valid input option!" << endl;
		}
	}
}
void OneD()																			// part 1
{
	int arraySize;
	int minValue;
	int maxValue;
	int* OneDArray;
	int randNum;
	int i;
	int duplicate;

	float arrayAverage;
	float median;

	// initialization above

	cout << "Enter array size (positive number only): " << endl;					// ask for array size
	cin >> arraySize;
	while(arraySize <= 0)															// if not positive or less than 1
	{
		cout << "Please enter valid array size (positive number only): " << endl;
		cin >> arraySize;
	}

	cout << "Enter the minimum value: " << endl;									// ask for minimum value
	cin >> minValue;
	cout << "Enter the maximum value: " << endl;									// ask for maximum value that is greater than minimum
	cin >> maxValue;
	while(maxValue <= minValue)														// if less than minimum ask for input
		{
			cout << "Please enter valid maximum value that is greater than minimum value: " << endl;
			cin >> maxValue;
		}
	OneDArray = new int [arraySize];
	//OneDArray = (int*) malloc(arraySize * sizeof(int));								// memory allocate the array using malloc()
	srand(time(NULL));																// set the random to be random

	for(i = 0; i < arraySize; i++)													// generate random number in the array
	{
		randNum = rand() % (maxValue - minValue) + minValue;
		OneDArray[i] = randNum;
	}
	cout << endl;

	SortArray(OneDArray, 0, arraySize - 1);							// call the QuickSort function to sort the array
	cout << "[ ";
	for(int i = 0; i < arraySize; i++)								// print out the array values
	{
		cout << OneDArray[i];
		if(i < arraySize -1)										// dash between each number in element
		{
			cout << " - ";
		}

	}
	cout << " ]" << endl;

	arrayAverage = CalcAverage(OneDArray, arraySize);				// store return value in CalcAverage function
	cout << "The average is: " << arrayAverage << endl;

	median = CalcMedian(OneDArray, arraySize);						// store return value in CalcMedian function
	cout << "The median is: " << median << endl;

	duplicate = CalcDuplicate(OneDArray, arraySize);				// store return value in CalcDuplicate function
	cout << "Duplicate: " << duplicate << endl;
	cout << "Uniques: " << arraySize - duplicate << endl;			// find the uniques simply subtract the duplicates
}

int CalcDuplicate(int* numberList, int size)
{
	int i, j;
	int duplicate = 0;

	for(i = 0; i < size; i++)
	{
		if(numberList[i] == numberList[i+1])							// check if current number is equal to next element
		{
			duplicate += 1;												// if same duplicate + 1;
		}
	}
	return duplicate;
}

float CalcAverage(int* numberList, int size)							// Calculate average
{
	int i;
	float sum = 0;

	for(i = 0; i < size; i++)											// add up every number in array
	{
		sum += numberList[i];
	}
	return sum/size;													// return a float value
}
void CharSort(char* numberList, int start, int end)						// performing quicksort
{
	   int i = start;
	   int j = end;
	   int pivot = numberList[(start + end) / 2];
	   char temp;

	      // partition

	   while (i <= j)													// sorting the array
	   {
	         while (numberList[i] < pivot)
	         {
	               i++;
	         }
	         while (numberList[j] > pivot)
	         {
	               j--;
	         }
	         if (i <= j)
	         {
	               temp = numberList[i];
	               numberList[i] = numberList[j];
	               numberList[j] = temp;
	               i++;
	               j--;
	         }
	   }
	      	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	 // recursion
	      if (start < j)
	      {
	    	  CharSort(numberList, start, j);
	      }
	      if (i < end)
	      {
	          CharSort(numberList, i, end);
	      }
}
void SortArray(int* numberList, int start, int end)						// performing quicksort
{
	   int i = start;
	   int j = end;
	   int temp;
	   int pivot = numberList[(start + end) / 2];
	      // partition

	   while (i <= j)													// sorting the array
	   {
	         while (numberList[i] < pivot)
	         {
	               i++;
	         }
	         while (numberList[j] > pivot)
	         {
	               j--;
	         }
	         if (i <= j)
	         {
	               temp = numberList[i];
	               numberList[i] = numberList[j];
	               numberList[j] = temp;
	               i++;
	               j--;
	         }
	   }
	      	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	 // recursion
	      if (start < j)
	      {
	    	  SortArray(numberList, start, j);
	      }
	      if (i < end)
	      {
	          SortArray(numberList, i, end);
	      }
}

float CalcMedian(int* numberList, int size)								// calculate the median
{
	int midPoint = size/2;												// set midpoint to size / 2

	if(size % 2 == 1)													// if is odd number size simply find the middle one
	{
		return numberList[midPoint];
	}
	else																// if is even find the average of middle two values
	{
		return (float)(numberList[midPoint - 1] + numberList[midPoint])/2;
	}
}

void SingleDimension()													// part 2
{
	int arraySize;
	int countFrequency;
	int option;
	int i;

	bool checkExit = false;

	char* singleArray;
	char letterCheck;
	char removeChar;

	// initialization above

	cout << "Enter array size (positive number only): " << endl;
	cin >> arraySize;
	while(arraySize <= 0)															// if not positive or less than 1
	{
		cout << "Please enter valid array size (positive number only): " << endl;
		cin >> arraySize;
	}
	singleArray = new char[arraySize];
	//singleArray = (char*) malloc(arraySize * sizeof(char));

	srand(time(NULL));
	FillCharArray(singleArray, arraySize);				// call to fill the array with random char
	cout << "\nFilling the array!" << endl;
	cout << "[ ";
	for(i = 0; i < arraySize; i++)
	{
		cout << singleArray[i] << " ";
	}
	cout << "]\n" << endl;

	while(checkExit == false)							// check if the user wnat exit
	{
		cout << "What would you like to do?" << endl;
		cout << "1 - Check frequency of a letter" << endl;
		cout << "2 - Remove a letter" << endl;
		cout << "3 - Sort" << endl;
		cout << "4 - Return to menu" << endl;
		cin >> option;
		if(option == 1)									//check frequency of letter
		{
			cout << "What letter do you want to check?" << endl;
			cin >> letterCheck;
			while(!islower(letterCheck))
			{
				cout << "Please enter a lower case letter!" << endl;
				cin >> letterCheck;
			}
			countFrequency = CountFrequency(singleArray, arraySize, letterCheck);
			cout << "The frequency of the letter is: " << countFrequency << endl;
		}
		else if(option == 2)							// remove a letter
		{
			cout << "What letter do you want to remove?" << endl;
			cin >> removeChar;
			while(!islower(removeChar))					// check if lower case
			{
				cout << "Please enter a lower case letter!" << endl;
				cin >> removeChar;
			}

			arraySize = RemoveChar(singleArray, arraySize, removeChar);		// get new size
			cout << "Your new array: " << endl;
			cout << "[ ";
			for(i = 0; i < arraySize; i++)
			{
				cout << singleArray[i] << " ";
			}
			cout << "]\n" << endl;
		}
		else if(option == 3)							// sort the array
		{
			CharSort(singleArray, 0, arraySize - 1);	// call the QuickSort(char) function to sort the array
			cout << "[ ";
			for(i = 0; i < arraySize; i++)
			{
				cout << singleArray[i] << " ";
			}
			cout << "]\n" << endl;
		}
		else if(option == 4)							// exit to main menu
		{
			checkExit = true;
		}
		else											// if user input invalid number, ask to input again.
		{
			cout << "Please enter a valid number!" << endl;
		}
	}

}
int RemoveChar(char* charArray, int size, char letter)					// remove a char and return a new size
{
	int i;
	int j = 0;
	int newSize = 0;

	char* tempArray = new char [size];

	for(i = 0; i < size; i++)
	{
		if(charArray[i] != letter)										// loop and check if the array has a remove char
		{
			tempArray[j] = charArray[i];
			j++;
			newSize++;
		}
	}
	size = newSize;
	for(i = 0; i < size; i++)											// copy back the value from temp array
	{
		charArray[i] = tempArray[i];
	}
	return size;
}

int CountFrequency(char* charArray, int size, char letter)				// count the frequency of a letter
{
	int i;
	int count = 0;
	for(i = 0; i < size; i++)											// loop through each row to find the array
	{
		if(charArray[i] == letter)
		{
			count += 1;
		}
	}
	return count;
}

char RandomChar()														// generate a random char
{
	char randomChar = 'a' + rand() % 26;
	return randomChar;
}

void FillCharArray(char* charArray, int size)							// fill array with random char, which call RandomChar()
{
	int i;

	for(i = 0; i < size; i++)
	{
		charArray[i] = RandomChar();
	}
}

void TwoD()
{
	int option;
	int row;
	int column;
	int i, j;
	int frequencyCount = 0;

	char** twoDArray;
	char letter;
	char removeChar;

	bool checkExit = false;

	// inistialization above

	//string inputString;
	//twoDArray = (char**) malloc(raw * sizeof(char));
	cout << "How many strings do you want to enter?" << endl;
	cin >> row;
	while(row <= 0)													// ask for valid input
	{
		cout << "Please enter number greater than zero!" <<endl;
		cin >> row;
	}
	cout << "What is the max size of the string?" << endl;
	cin >> column;
	while(column <= 0)												// ask for valid input
	{
		cout << "Please enter number greater than zero!" <<endl;
		cin >> column;
	}

	twoDArray = new char* [row];									// make the first array

	for(i = 0; i < row; i++)										// make the second array
	{
		twoDArray[i] = new char [column];
	}

	for(i = 0; i < row; i++)
	{
		cout << "Enter string "<< i + 1 << ": ";
		cin >> twoDArray[i];

	}
	cout << endl;

	for(i = 0; i < row; i++)
	{
		cout << twoDArray[i] << endl;;
	}
	cout << "\n" << endl;

	while(checkExit == false)													// check if user want exit
	{
		cout << "1. Check frequency of a letter" << endl;
		cout << "2. Remove a letter" << endl;
		cout << "3. Return to main menu" << endl;
		cin >> option;

		if(option == 1)															// check frequency
		{
			cout << "What letter would you like to check?" << endl;
			cin >> letter;
			while(!islower(letter))
			{
				cout << "Please enter a letter that is in lower case!" << endl;
				cin >> letter;
			}
			for(i = 0; i < row; i++)
			{
				frequencyCount = CountFrequency(twoDArray[i], column, letter);
				cout << twoDArray[i] << " - " << frequencyCount << endl;
//				frequencyCount = 0;
			}
		}
		else if(option == 2)													// remove letter
		{
			cout << "What letter would you like to remove?" << endl;
			cin >> removeChar;
			while(!islower(removeChar))											// check if lower
			{
				cout << "Please enter a letter that is in lower case!" << endl;
				cin >> removeChar;
			}
			for(i = 0; i < row; i++)											// remove letter from every row
			{
				RemoveChar(twoDArray[i], column, removeChar);
				cout << twoDArray[i] << endl;
			}

		}
		else if(option == 3)													// exit
		{
			checkExit = true;
		}
		else																	// invalid input
		{
			cout << "Please enter a valid number!" << endl;
			cin >> option;
		}
	}
	//	string* twoDArray;
	//	twoDArray = new string[stringAmount];

	//	for(stringCount = 1; stringCount <= stringAmount; stringCount++)
	//	{
	//		cout << "Enter string "<< stringCount << ": ";
	//		cin >> inputString;
	//		twoDArray[i] = inputString;
	//		cout << endl;
	//		i++;
	//	}
}

