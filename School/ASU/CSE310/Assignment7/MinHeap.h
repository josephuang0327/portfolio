//********************************************************
// Assignment: ASU CSE310 HW#7
// Your Name: Wei Chieh Huang
// ASU ID: 1215427213
// ASU Email address: whuan110@asu.edu
// Description: This stores the source city, it's arrival
// city, price in heap.
//********************************************************
#include "LinkedList.h"

using namespace std;

//represent each node of the graph which is a departure City
struct City
{
    string cityName;
    int d;
    struct City* pi;
    LinkedList* arrCityList;
};

//class Heap represents a Min-heap that contains City objects. Underline data structure is
//a one dimensional array of City objects.
class MinHeap
{
    private:
        struct City* cityArr;	//an array of City
        int capacity, size;

	public:
        MinHeap(int capacity);
        ~MinHeap();

        City* getCityArr();
        int getSize();
        int getCapacity();
        int isFound(string cityName);
        bool decreaseKey(int index, City oneCitywithNewD);
        bool insert(City oneCity);
        void heapify(int index);
        City getHeapMin();
        void extractHeapMin();
        int leftChild(int parentIndex);
        int rightChild(int parentIndex);
        int parent(int childIndex);
        void printHeap();

        void build_min_heap();      //***newly added function
 };

//Constructor to dynamically allocate memory for a heap with the specified capacity
MinHeap::MinHeap(int capacity)
{
 	cityArr = new City[capacity];
	this->capacity = capacity;
	size = 0;
}

//Define all remaining functions according to above function declaration
//----
//----
MinHeap::~MinHeap()
{
	int cityCount = size;
	delete[] cityArr;
	cout << "\nThe number of deleted food items is: " << cityCount << endl;
}

City* MinHeap::getCityArr()
{
	return cityArr;
}

int MinHeap::getSize()
{
	return size;
}

int MinHeap::getCapacity()
{
	return capacity;
}
//search for city name
int MinHeap::isFound(string cityName)
{
	int i = 0;
	while(i < size)	// if within size
	{
		if(cityName == cityArr[i].cityName)	//check each element if matches the key
		{
			return i;
		}
		i++;
	}
	return -1;
}

// reorganize a key
bool MinHeap::decreaseKey(int index, City oneCitywithNewD)
{
	if(index < size)
	{
		cityArr[index] = oneCitywithNewD;
		int i = index;

	while(leftChild(index) < size)
	{
		int min = leftChild(i);

		if(cityArr[rightChild(i)].d < cityArr[leftChild(i)].d) // compare two child
		{
			min = rightChild(i);
		}

		if(cityArr[i].d < cityArr[min].d)
		{
			City temp = cityArr[i];
			cityArr[parent(i)] = temp;
			i = parent(i);
			index = min;
		}
		else
		{
			return false;
		}
	}
}

}

//insert a city
bool MinHeap::insert(City oneCity)
{
	// initialize temporary variables
		int currIndex;
		LinkedList* tempList;
		City tempCity;
		string tempName;
		double tempPrice;

		tempCity = oneCity;
		cityArr[size] = tempCity;

		size = size + 1;

		currIndex = size - 1;

		while(currIndex > 0 && cityArr[parent(currIndex)].d > cityArr[currIndex].d) // then reorder the array
		{
			tempList = cityArr[parent(currIndex)].arrCityList;
			tempName = cityArr[parent(currIndex)].cityName;
			tempPrice = cityArr[parent(currIndex)].d;

			// the parent copy info from child
			cityArr[parent(currIndex)].arrCityList = cityArr[currIndex].arrCityList;
			cityArr[parent(currIndex)].cityName = cityArr[currIndex].cityName;
			cityArr[parent(currIndex)].d = cityArr[currIndex].d;

			// child copy info from temporary variables(which is from parent)
			cityArr[currIndex].arrCityList = tempList;
			cityArr[currIndex].cityName = tempName;
			cityArr[currIndex].d = tempPrice;

			currIndex = parent(currIndex);
		}
		return true;
}

// reorder the entire graph
void MinHeap::heapify(int index)
{
	int i = 0;;
	City tempCity;
	tempCity = cityArr[index];
	i = 2 * index;
	while(i <= size) //sort the heap in min-heap format
	{
		if (i < size && cityArr[i + 1].d < cityArr[i].d)
		{
			i = i + 1;
		}
		if (tempCity.d < cityArr[i].d)
		{
			break;
		}
		else if (tempCity.d >= cityArr[i].d)
		{
			cityArr[i / 2] = cityArr[i];
			i = 2 * i;
		}
	}
	cityArr[i / 2] = tempCity;

}

City MinHeap::getHeapMin()
{
	return cityArr[size];
}

void MinHeap::extractHeapMin()
{
	int tempIndex = 0;
	while(rightChild(tempIndex) != -1)	// if right child is not empty
	{
		tempIndex = rightChild(tempIndex);
	}
	while(leftChild(tempIndex) != -1 )	// if left child is not empty
	{
		cityArr[tempIndex] = cityArr[leftChild(tempIndex)];
		tempIndex = leftChild(tempIndex);
	}
	size--;
}

int MinHeap::leftChild(int parentIndex)
{
	int lChild;
	lChild = ((2 * parentIndex) + 1); //leftchild is parent index times 2 plus 1
	return lChild;
}

int MinHeap::rightChild(int parentIndex)
{
	int rChild;
	rChild = ((2 * parentIndex) + 2); //rightchild is parent index times 2 plus 2
	return rChild;
}

int MinHeap::parent(int childIndex)
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

void MinHeap::build_min_heap()
{

}

//****************************************************************
//**Changed a little bit. Once extractedHeapMin, the procedure will
//put the last element at index 0 and re-heapify the array. We will
//keep the extracted City object
//*********************************************************
void MinHeap::printHeap()
{
	if (cityArr == NULL || size == 0)
		cout << "\nEmpty heap, no elements" << endl;
	else
	{
		cout << "\nHeap size = " << getSize() << "\n" << endl;

		cout << left;
		cout << setw(15) << "City Name"
             << setw(12) << "d Value"
             << setw(15) << "PI"
             << "Arrival City List" << endl;

		for (int i = 0; i < getSize(); i++)
		{
		    cout << left;
			cout << setw(15) << cityArr[i].cityName
                 << setw(12) << cityArr[i].d;
            if(cityArr[i].pi != NULL)
                    cout << setw(15) << cityArr[i].pi->cityName;
            else
                    cout << setw(15) << "No Parent";
    		 cityArr[i].arrCityList->printArrCityList();
		}
	}
}
