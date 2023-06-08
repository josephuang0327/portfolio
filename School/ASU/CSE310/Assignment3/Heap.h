//********************************************************
// Assignment: ASU CSE310 HW#3
// Your Name: Wei Chieh Huang
// ASU ID: 1215427213
// ASU Email address: whuan110@asu.edu
// Description: This program contains all of the function to make a one dimension dynamic heap array.
//				It takes a key, name, and price and store it in the array. Performs sorting, inserting
//				and deleting elements/
//********************************************************
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//Food represents a food. Each food with a unique key
struct Food
{
	int key;
	string foodName;
	double price;
};

//class Heap represents a Max heap that contains Food objects. Underline data structure is
//a one dimensional array of Food objects.
class Heap
{
    private:
		struct Food* foodArr;	//an array of Food
		int capacity, size;

    public:
		Heap(int capacity);
		~Heap();
		Food* getFoodArr();
		int getSize();
		int getCapacity();
		int isFound(int foodKey);
		bool increaseKey(int index, Food oneFoodwithNewKey);
		bool insert(int key, string foodName, double foodPrice);
		void heapify(int index);
		Food getHeapMax();
		void extractHeapMax();
		int leftChild(int parentIndex);
		int rightChild(int parentIndex);
		int parent(int childIndex);
		void printHeap();
};

//Constructor to dynamically allocate memory for a heap with the specified capacity
Heap::Heap(int capacity)
{
 	//----
 	//----
	this->size = 0;
	this->capacity = capacity;
	foodArr = new Food[capacity];
}

//Destructor
//Before termination, the destructor is called to free the associated memory occupied by the heap.
//and prints the number of nodes deleted by it.
Heap::~Heap()
{
	int foodCount = size;
	delete[] foodArr;


	cout << "\nThe number of deleted food items is: " << foodCount << endl;
	capacity = 5;
	foodArr = new Food[capacity];
}

//Finish all the remaining functions according to the project's description
//----
//----
Food* Heap::getFoodArr()	//function to get food array
{
	return foodArr;
}
int Heap::getSize()			// function to get size
{
	return size;
}
int Heap::getCapacity()		// function to get capacity
{
	return capacity;
}
int Heap::isFound(int foodKey)	//function to check if the key is found in the food array
{
	int i = 0;
	while(i < size)
	{
		if(foodKey == foodArr[i].key)	//check each element if matches the key
		{
			return i;
		}
		i++;
	}
	return -1;
}
bool Heap::increaseKey(int index, Food oneFoodwithNewKey)	// function to increase the key of the index to a greater key.
{
	cout << endl << "Before increase key operation:" << endl;
	printHeap();

	// change the key first to new key
	foodArr[index].key = oneFoodwithNewKey.key;
	int currIndex = index;

	// create the variable to store the info
	int tempIndex;
	string tempName;
	double tempPrice;

	// when index is not 0 and parent key is smaller than the current index key
	while(currIndex > 0 && foodArr[parent(currIndex)].key < foodArr[currIndex].key)
	{
		//store all the info in the parent to temporary variables
		tempIndex = foodArr[parent(currIndex)].key;
		tempName = foodArr[parent(currIndex)].foodName;
		tempPrice = foodArr[parent(currIndex)].price;

		// the parent copy info from child
		foodArr[parent(currIndex)].key = foodArr[currIndex].key;
		foodArr[parent(currIndex)].foodName = foodArr[currIndex].foodName;
		foodArr[parent(currIndex)].price = foodArr[currIndex].price;

		// child copy info from temporary variables(which is from parent)
		foodArr[currIndex].key = tempIndex;
		foodArr[currIndex].foodName = tempName;
		foodArr[currIndex].price = tempPrice;

		currIndex = parent(currIndex);
	}



//	foodArr[index] = oneFoodwithNewKey;
//	heapify(index);

//	cout << endl << "Food with old key: " << index << " is increased to new key: " << oneFoodwithNewKey.key << endl;
//	cout << "After increase key operation:" << endl;
//	printHeap();
	return true;
}
bool Heap::insert(int key, string foodName, double foodPrice)	// function to insert foods
{
	// initialize temporary variables
	int currIndex;
	int tempIndex;
	string tempName;
	double tempPrice;

	if(isFound(key) >= 0)	// if key is already found then cannot insert
	{
		cout << endl << "Duplicated food item. Not added" << endl;
		return false;
	}
	if(size == capacity) // if capacity is at limit then capacity time 2 and copy array
	{
//		cout << "00002" << endl;
		Food* tempArr = new Food[capacity * 2];

		for(int i = 0; i < size; i++) 	//copy food from food array to temp
		{
			tempArr[i].key = foodArr[i].key;
			tempArr[i].foodName = foodArr[i].foodName;
			tempArr[i].price = foodArr[i].price;
		}
		foodArr = tempArr;
		capacity = capacity * 2;

		cout << endl << "Reach the capacity limit. Double the capacity" << endl << endl;
		cout << "The new capacity now is " << capacity << endl;
	}

	foodArr[size].key = key;
	foodArr[size].foodName = foodName;
	foodArr[size].price = foodPrice;

	size = size + 1;

	currIndex = size - 1;

	while(currIndex > 0 && foodArr[parent(currIndex)].key < foodArr[currIndex].key) // then reorder the array
	{
		tempIndex = foodArr[parent(currIndex)].key;
		tempName = foodArr[parent(currIndex)].foodName;
		tempPrice = foodArr[parent(currIndex)].price;

		foodArr[parent(currIndex)].key = foodArr[currIndex].key;
		foodArr[parent(currIndex)].foodName = foodArr[currIndex].foodName;
		foodArr[parent(currIndex)].price = foodArr[currIndex].price;

		foodArr[currIndex].key = tempIndex;
		foodArr[currIndex].foodName = tempName;
		foodArr[currIndex].price = tempPrice;
		currIndex = parent(currIndex);
	}
	return true;

}
Food Heap::getHeapMax()	// function return largest element
{
	return foodArr[0];
}
void Heap::extractHeapMax()	// function extract largest element
{
	cout << endl << "Before extract heap max operation:" << endl;
	printHeap();

	// extract first element and heapify
	foodArr[0] = foodArr[size -1];
	size--;
	heapify(0);

	cout << endl << "After extract heap max operation:" << endl;
	printHeap();
}
int Heap::leftChild(int parentIndex)	// get the left child's index
{
	int lChild;
	lChild = ((2 * parentIndex) + 1); //leftchild is parent index times 2 plus 1
	return lChild;
}
int Heap::rightChild(int parentIndex)	// get the right child's index
{
	int rChild;
	rChild = ((2 * parentIndex) + 2); //rightchild is parent index times 2 plus 2
	return rChild;
}
int Heap::parent(int childIndex)	// get the parents's index
{
	int val;
	    if(childIndex % 2 == 0)// if the index is even
	    {
	        val = ((childIndex - 1) / 2);
	    }
	    else// if the index is odd
	    {
	        val = (childIndex / 2);
	    }
	    return val;
}
void Heap::heapify(int index)	// reorder the specific index value
{
	// initialize the temporary variables
	int tempKey;
	string tempName;
	double tempPrice;
	int left;
	int right;
	int heapifyDir;

	left = leftChild(index); 		// get left child
	right = rightChild(index); 		// get right child

    if((left <= size) && (foodArr[left].key > foodArr[index].key))	// if left child is larger then parent
    {
        heapifyDir = left;
    }
    else	// stays the same
    {
    	heapifyDir = index;
    }
    if((right <= size) && (foodArr[right].key > foodArr[heapifyDir].key))	// if right child is larger then parent
    {
        heapifyDir = right;
    }
    if(heapifyDir != index) // one of the two child is larger than foodArr[i], so interchange values
    {
        //swap parent with left child
        tempKey = foodArr[index].key;
        tempName = foodArr[index].foodName;
        tempPrice = foodArr[index].price;

        foodArr[index] = foodArr[heapifyDir];

        foodArr[heapifyDir].key = tempKey;
        foodArr[heapifyDir].foodName = tempName;
        foodArr[heapifyDir].price = tempPrice;

        heapify(heapifyDir);
    }
}
void Heap::printHeap()	// print elements in food array
{
	//----
	//----
	if(size == 0)	// if nothing in food array
	{
		cout << endl << "Empty heap, no elements" << endl;
	}
	else	// print
	{
		cout << endl << "Heap capacity = " << capacity << endl;
		cout << endl << "Heap size = " << size << endl << endl;

		for(int i = 0; i < size; i++)
		{
			cout << left;
			cout << setw(5) << foodArr[i].key
				 << setw(8) << foodArr[i].foodName
				 << setw(8) << fixed << setprecision(2) << foodArr[i].price << endl;
		}
	}

}
