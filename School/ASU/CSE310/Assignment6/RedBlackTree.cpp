//************************************************************************
// ASU CSE310 Assignment #6 Fall 2020
// Name of Author: Wei Chieh Huang
// ASU ID: 1215427213
// Description: Red black tree implementation. See RedBlackTree.h
//              for the tree definition. You need to add your own
//              code at //---- position
//************************************************************************

#include "RedBlackTree.h"

using namespace std;

//*******************************************************************
//constructor
RedBlackTree::RedBlackTree()
{
	root = NULL;
}

//*******************************************************************
//destructor
RedBlackTree::~RedBlackTree()
{
	int nodeSize = deleteNode(root);
	cout << "The number of nodes deleted: " << nodeSize << endl;
}

//**************************************************************
//This function return the root of the red-black tree
Node* RedBlackTree::getRoot()
{
	return this->root;
}

//*******************************************************************
//delete the sub-tree rooted at 'node' and return number of nodes deleted
//This can be defined as a recursive function
int RedBlackTree::deleteNode(Node *node)
{
    if(node == NULL)
    	return 0;
	else
	{
	    //add your codes here
	    //----
		int count = 0;
		Node* y = NULL;
		Node* x = NULL;
		//string currKey = curr->foodID + curr->name + curr->supplierID;

		// if there is only one node.
		if(node->leftChild == NULL || node->rightChild == NULL)
		{
			y = node;
		}
		else
		{
			//y = findSuccessorNode(node);
		}

		// if left child is empty
		if(y->leftChild = NULL)
		{
			x = y->leftChild;
		}
		else
		{
			x = y->rightChild;
		}

		x->parent = y->parent;
		//if parent is empty
		if(y->parent == NULL)
		{
			root = x;
		}
		else if(y = y->parent->leftChild)	// if y is left child
		{
			y->parent->leftChild = x;
		}
		else
		{
			y->parent->rightChild = x;
		}

		if(y != node)
		{
			node = y;
		}
		if(y->color.compare("BLACK") == 0)
		{
			fixUp(x);
		}
	}
}

//****************************************************************
//This is the general BST insertion operation.
//It does not care about the color of the newly added node.
void RedBlackTree::insertNode(Node *node)
{
	if(node == NULL)
		return;
	if(this->root == NULL) // if the tree is empty
    {
		//add your codes here
		//----
		root = node;
	}
	else
    {
		//add your codes here
		//----
		Node* newNode = new Node();
		newNode = node;
		Node* x = root;
		Node* y = NULL;


		// x is not empty
		while(x != NULL)
		{
			y = x;
			string xKey = x->foodID + x->name + x->supplierID;
			if(compareNodes(node,xKey) < 0)
			{
				x = x->leftChild;
			}
			else
			{
				x = x->rightChild;
			}

		}
		string yKey = y->foodID + y->name + y->supplierID;
		if(y == NULL)
		{
			y = newNode;
		}
		else if(compareNodes(node, yKey) < 0) // compare node to decide where the node goes
		{
			y->leftChild = newNode;
		}
		else
		{
			y->rightChild = newNode;
		}


	}

	//At the end, need to call fixup() in case the newly
	//added node's parent is also RED
	fixUp(node);
}

//*******************************************************************
//At beginning, each newly added node will always be RED,
//this may violate the red-black tree property #4. fixUp()
//function will restore the property.
void RedBlackTree::fixUp(Node *z)
{
    if(z == root)
    {
		z->color = "BLACK";
		return;
	}

	 //if z's color is 'RED' and its parent's color is also 'RED'
    while(z->color.compare("RED") == 0 &&
          z->parent != NULL &&
          z->parent->color.compare("RED") == 0)
    {
       //add your codes here
       //----
       //----
    	Node* y = new Node;
    	if(z->parent == z->parent->parent->leftChild)	//if z parent = uncle node
    	{
    		y = z->parent->parent->rightChild;
    		if(y->color.compare("RED") == 0)
    		{
    			z->parent->color = "BLACK";
    			y->color = "BLACK";
    			z->parent->parent->color = "RED";
    			z = z->parent->parent;
    		}
    		else if(z == z->parent->rightChild)	// if z is a right child
    		{
    			z = z->parent;
    			leftRotate(z);
    		}
    		z->parent->color = "BLACK";
    		z->parent->parent->color = "RED";
    		rightRotate(z->parent->parent);
    	}
    	else
    	{
    		y = z->parent->parent->rightChild;
    		if(y->color.compare("RED") == 0)	// if y is RED
    		{
    		   z->parent->color = "BLACK";
    		   y->color = "BLACK";
    		   z->parent->parent->color = "RED";
    		   z = z->parent->parent;
    		}
    		else if(z == z->parent->rightChild)	// if z = right child
    		{
    		   z = z->parent;
    		   leftRotate(z);
    		}
    		z->parent->color = "BLACK";
    		z->parent->parent->color = "RED";
    		rightRotate(z->parent->parent);
    	}

    }//end while

    //make sure the root is always 'BLACK'
    this->root->color = "BLACK";
}

//*****************************************************
//This function print the pre-order traversal of the
//subtree rooted at 'node'.It's a recursive function
void RedBlackTree::preOrderTraversal(Node *node)
{
	if(node == NULL)
   {
		return;
	}
	else
   {
       //add your codes here
       //----
	   //----
		print(node);
		preOrderTraversal(node->leftChild);
		preOrderTraversal(node->rightChild);
	}
}

//**************************************************
//This function print the in-order traversal of the
//subtree rooted at 'node'.It's a recursive function
void RedBlackTree::inorderTraversal(Node *node)
{
   if(node == NULL)
   {
		return;
   }
	else
    {
       //add your codes here
       //----
	   //----
		if(node->leftChild != NULL)
		{
			inorderTraversal(node->leftChild);
		}

		print(node);

		if(node->rightChild != NULL)
		{
			inorderTraversal(node->rightChild);
		}
	}
}

//**************************************************
//This function print the post-order traversal of the
//subtree rooted at 'node'.It's a recursive function
void RedBlackTree::postOrderTraversal(Node *node)
{
   if(node == NULL)
   {
		return;
	}
	else
   {
       //add your codes here
       //----
	   //----

		if(node->leftChild != NULL)
		{
			postOrderTraversal(node->leftChild);
		}

		if(node->rightChild != NULL)
		{
			postOrderTraversal(node->rightChild);
		}
		print(node);
	}
}

//**************************************************************
//This function returns a pointer points to the minimum node from
//the current sub-tree rooted at 'node'. It's a recursive function
Node* RedBlackTree::findMinimumNode(Node *node)
{
	if (node == NULL)
   {
		cout << "Tree is empty, no MINIMUM." << endl;
		return node;
	}
    else
    {
       //add your codes here
       //----
	   //----
    	while(node->leftChild != NULL)
    	{
    		node = node->leftChild;
    	}
    	return node;
	}
}

//**************************************************************
//This function returns a pointer points to the maximum node from
//the current sub-tree rooted at 'node'. It's a recursive function
Node* RedBlackTree::findMaximumNode(Node *node)
{
	if (node == NULL)
   {
		cout << "Tree is empty, no MAXIMUM." << endl;
		return node;
	}
   else
   {
       //add your codes here
       //----
	   //----
	   while(node->rightChild != NULL)
	   {
		   node = node->rightChild;
	   }
	   return node;
	}
}

//**************************************************************
//This function search the tree for a given key of a Food
//Note: key is the combination of foodID, name, supplierID
//It returns a pointer points to the node if founded, otherwise return NULL
Node* RedBlackTree::treeSearch(string foodID, string name, string supplierID)
{
   string key1 = foodID + name + supplierID;
	Node *node = root;
	bool isFound = false;
	while(node != NULL)
    {
		//----
		//-----
		if(compareNodes(node, key1) == 0)	// if node is found
		{
			isFound = true;
		}
		else if(compareNodes(node, key1) < 0) // move to right
		{
			node = node->rightChild;
		}
		else								// move to left
		{
			node = node->leftChild;
		}
    }
	if(isFound == true)
	{
		 cout << left;
		 cout << setw(5) << foodID
	          << setw(35) << name
	          << setw(15) << supplierID
	          << " is FOUND." << endl;
	            return node;
	}
	else
	{
	    cout << left;
	    cout << setw(5) << foodID
	         << setw(35) << name
	         << setw(15) << supplierID
	         << " is NOT FOUND." << endl;
	         return NULL;
	}
}

//****************************************************
//This function left-rotate the BST at 'node'
void RedBlackTree::leftRotate(Node *node)
{
	if(node == NULL)
		return;

	//add your codes here
    //----
	//----
	Node* y = new Node;
	y = node->rightChild;
	node->rightChild = y->leftChild;

	if(y->leftChild != NULL)
	{
		y->leftChild->parent = node;
	}
	y->parent = node->parent;

	if(node->parent == NULL)
	{
		root = y;
	}
	else if(node == node->parent->leftChild)
	{
		node->parent->leftChild = y;
	}
	else
	{
		node->parent->rightChild = y;
		y->leftChild = node;
		node->parent = y;
	}
}

//***************************************************
//This function right-rotate the BST at 'node'
//**************************************************************
//This function finds the predecessor of the given 'node'
//it prints the relevant predecessor info. on screen.
void RedBlackTree::rightRotate(Node *node)
{
	if(node == NULL)
		return;

	//add your codes here
    //----
	//----
	Node* y = new Node;
		y = node->leftChild;
		node->rightChild = y->leftChild;

		if(y->leftChild != NULL)
		{
			y->leftChild->parent = node;
		}
		y->parent = node->parent;

		if(node->parent == NULL)
		{
			root = y;
		}
		else if(node == node->parent->leftChild)
		{
			node->parent->leftChild = y;
		}
		else
		{
			node->parent->rightChild = y;
			y->leftChild = node;
			node->parent = y;
		}
}


Node* RedBlackTree::findPredecessorNode(Node *node)
{
   Node* predn;
   bool found = false;

   if(root == NULL)	// if root is empty
   {
	   predn = NULL;
   }
   string rootKey = root->foodID + root->name + root->supplierID;
   if(compareNodes(node, rootKey) == 0)	// if node = root
   {
	   if(root->leftChild != NULL)		// if left child is not empty
	   {
		   predn = findMaximumNode(root->leftChild);
		   found = true;
	   }
   }

   else if(compareNodes(node, rootKey) < 0)	// find predecessor on left child
   {
	   findPredecessorNode(root->leftChild);
   }
   else										// find predecessor on right child
   {
	   predn = root;
	   findPredecessorNode(root->rightChild);
   }

   if(found == true) // is found
   {
      //add your codes here
      //----
	  cout << left;
      cout << "Its Predecessor is: " << endl;
	  print(predn);
	  return predn;
	}
	else  //not found
	{
	   //add your codes here
      //----
      cout << left;
      cout << "Its Predecessor does NOT EXIST"	<< endl;
      return predn;
	}
}

//**************************************************************
//This function finds the successor of the given 'node'
//it prints the relevant successor info. on screen.
Node* RedBlackTree::findSuccessorNode(Node *node)
{
   Node* sn;
   bool found = false;

   if(root == NULL)		// if root is not empty
   {
   	   sn = NULL;
   }
   string rootKey = root->foodID + root->name + root->supplierID;
   if(compareNodes(node, rootKey) == 0)	// if node == root
   {
   	   if(root->rightChild != NULL)	// if left child is not empty
   	   {
   		   sn = findMinimumNode(root->rightChild);
   		   found = true;
   	   }
   }

      else if(compareNodes(node, rootKey) < 0)	// find successor of left child
      {
    	  sn = root;
    	  findSuccessorNode(root->leftChild);
      }
      else										// find successor of right child
      {
    	  findSuccessorNode(root->rightChild);
      }

   if(true) // is found
   {
      //add your codes here
      //----
      cout << left;
      cout << "Its Successor is: " << endl;
		print(sn);
		return sn;
	}
	else  //not found
   {
      cout << left;
      cout << "Its Successor does NOT EXIST"	<< endl;
      return sn;
	}
}

//**************************************************************
//This function find the minimum node of the entire red-black tree
//It print out the minimum node info. on screen if tree is not empty
//or print 'Tree is empty' message on screen.
void RedBlackTree::treeMinimum()
{
	if (root == NULL)
    {
		cout << "Tree is empty. No Minimum." << endl;
		return;
	}

	//add your codes here
	//----
	//----
	Node* node = new Node;
	Node* min = new Node;
	min = findMinimumNode(node);

}

//**************************************************************
//This function find the maximum node of the entire red-black tree
//It print out the maximum node info. on screen if tree is not empty
//or print 'Tree is empty' message on screen.
void RedBlackTree::treeMaximum()
{
	if (root == NULL)
    {
		cout << "Tree is empty. No Maximum." << endl;
		return;
	}

	//add your codes here
	//----
	//----
	Node* node = new Node;
	Node* max = new Node;
	max = findMaximumNode(node);
}

//******************************************************************
//This function print out the pre-order traversal of the entire tree
void RedBlackTree::treePreorder()
{
	//add your codes here
	//----
	//----
	preOrderTraversal(root);
}

//******************************************************************
//This function print out the in-order traversal of the entire tree
void RedBlackTree::treeInorder()
{
	//add your codes here
	//----
	//----
	inorderTraversal(root);

}

//******************************************************************
//This function print out the post-order traversal of the entire tree
void RedBlackTree::treePostorder()
{
	//add your codes here
	//----
	//----
	postOrderTraversal(root);
}

//******************************************************************
//Given a Food's key, this function first check whether the
//food is inside the tree or not, if it is inside, it will print
//its predecessor info. on screen, if not, it print an error message
void RedBlackTree::treePredecessor(string foodID, string name, string supplierID)
{
	if (root == NULL)
		cout << "Tree is empty. No Predecessor." << endl;
	else
   {
      //add your codes here
      //----
      //----
		Node* foodItem = new Node;
		foodItem->foodID = foodID;
		foodItem->name = name;
		foodItem->supplierID = supplierID;
		findPredecessorNode(foodItem);
	}
}

//******************************************************************
//Given a food's key, this function first check whether the
//food is inside the tree or not, if it is inside, it will print
//its successor info. on screen, if not, it print an error message
void RedBlackTree::treeSucessor(string foodID, string name, string supplierID)
{
	if (root == NULL)
		cout << "Tree is empty. No Successor." << endl;
	else
   {
      //add your codes here
      //----
      //----
		Node* foodItem = new Node;
		foodItem->foodID = foodID;
		foodItem->name = name;
		foodItem->supplierID = supplierID;
		findSuccessorNode(foodItem);
	}
}

//**************************************************************
//This function create a node from the given info., then insert
//the node inside the red-black tree. Note: at beginning, the newly
//added node should always be 'RED'
void RedBlackTree::treeInsert(string foodID, string name, string supplierID, double price)
{
	//add your codes here
	//----
	//----
	Node* foodItem = new Node;
	foodItem->foodID = foodID;
	foodItem->name = name;
	foodItem->supplierID = supplierID;
	foodItem->price = price;
	foodItem->color = "RED";

	insertNode(foodItem);

}

//******************************************************************
//Given a 'node', this function prints all its information on screen
void RedBlackTree::print(Node *node)
{
        cout << left;
		cout << setw(5) << node->foodID
             << setw(35) << node->name
             << setw(15) << node->supplierID
            << setw(7) << fixed << setprecision(2) << node->price
            << setw(7) << node->color << endl;
}

//**************************************************************
//Given a Node 'node1', this function compares it with another
//node's key.
//key is a string combination of foodID + name + supplierID
//It returns a negative number if in alphabetical order, key2 is
//in front of 'node1'; otherwise it returns a positive number
int RedBlackTree::compareNodes(Node *node1, string key2)
{
	//add your codes here
	//----
	//----
	string key1 = node1->foodID + node1->name + node1->supplierID;
	return key1.compare(key2);
}
