/*
 * binTree.cpp
 *
 *  Created on: Mar 1, 2022
 *      Author: Matthew Noojin
 *      Implementation file for binTree.h
 */

#include "binTree.h"

// Default constructor
binTree::binTree()
{
	root = nullptr;
	appleSize = 0;
	inc = 0;
}

// Constructor to help initialize our root of the tree
binTree::binTree(std::vector<bool> apples)
{
	// Allocate our root node
	root = new binTreeNode;
	root->apple = apples[0];
	root->left = root->right = nullptr;

	// Size of our apples vector
	appleSize = (apples.size() - 1);

	// Set the size of our inc counter (we need this for our algorithm)
	inc = 0;

	// Initiate recursion
	buildTree(root, apples, 0);
}

// A recursive preorder function that builds our binary tree.
// Sets two nodes at once based on our data in the vector.
//
// Uses the equation i = (2 * i) + 1 to know where we need
// to pull more data from the vector.
//
// i being greater than or equal to the size of our vector
// after the equation executes is our base case as to not exceed the vector
void binTree::buildTree(binTreeNode* r, std::vector<bool> apples, int i)
{
	// Our next i's to read from will always be times 2 plus one
	// our current i. Doing this here also helps our base case trigger
	i = (2 * i) + 1;

	// Our base case to make sure we do not exceed the vector
	if(i >= appleSize)
		return;

	// Allocate new node to our left and right pointer at current node
	r->left = new binTreeNode;
	r->right = new binTreeNode;

	// Set the new node's left and right pointer to null (IMPORTANT!)
	r->left->left = r->left->right = nullptr;
	r->right->left = r->right->right = nullptr;

	// Set our apple values for our new nodes (our right child is always i+1)
	r->left->apple = apples[i];
	r->right->apple = apples[i + 1];

	// Recursively build the right and left sides of the tree
	buildTree(r->left, apples, i);
	buildTree(r->right, apples, (i + 1));

	return;
}

// Deallocate the list
void binTree::destroyTree(binTreeNode* r)
{
	binTreeNode* tmp;
	tmp = r;

	// Base case to return up the tree when we reach the end
	if(r == nullptr)
		return;

	// Recursive postorder call (we need to delete root last)
	destroyTree(tmp->left);
	destroyTree(tmp->right);

	delete r;

	return;
}

// Our destructor to deallocate the tree when we are done
binTree::~binTree()
{
	destroyTree(root);
}

// Wrapper function for our recursive mintime
int binTree::minTime()
{
	return minTime(root, 0);
}

/* Our magic recursive minTime function
 * The algorithm is:
 *
 * 1. Check for our base case, which is r = NULL, return 0 if it is
 * 2. Assign our boolean based on if r->apple is currently true
 * 3. Make a recursive call down the left side of the tree
 * 4. inc equals whatever the current call returns
 * 5. if inc is not 0, set time = inc and foundTrue = true
 *    if it is 0, we just make the next recursive call
 * 6. Repeat 3, 4, 5, but for the right side of the tree
 * 7. We now check if foundTrue was ever set to true,
 *    and if it was, we return time + 1 (unless we are at the root)
 *    this will be returned into inc for setting our time
 * 8. In any other case, we just return 0
 */
int binTree::minTime(binTreeNode* r, int time)
{
	// Our base case
	if(r == nullptr)
		return 0;

	// Our boolean, which will keep track if
	// true is found in a branch. It can start out as false
	// in a specific recursive call, but can be turned to true later on
	bool foundTrue = ((r->apple == true) ? true : false);

	// Our inc value, which will take
	// the return value of our recursive call down the left
	inc = minTime(r->left, (time + 1));
	// If inc is not 0, set time to it and foundTrue to true
	if(inc != 0)
	{
		time = inc;
		foundTrue = true;
	}
	// Same as above, but recursively down the right
	inc = minTime(r->right, (time + 1));
	if(inc != 0)
	{
		time = inc;
		foundTrue = true;
	}

	// If we found true in a branch, we return our time+1
	if(foundTrue == true)
	{
		// If we are in the root, we do not need to increment 1 again
		if(r == root)
			return time;
		// Otherwise, return time + 1
		else
			return ++time;
	}

	// Otherwise 0 is returned
	else
		return 0;


}
