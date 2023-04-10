//============================================================================
// Name        : binTree.h
// Author      : Matthew Noojin
// Class	   : CS219, Section 1001, Prof Andro-Vasko
// Date		   : 03/01/22
// Program	   : Reads data on whether or not an apple is red, and
//				 then we build a binary tree and see how few jumps we need
//				 to find every red apple
//============================================================================

#ifndef BINTREE_H_
#define BINTREE_H_

#include <vector>

class binTree {
public:
	struct binTreeNode
	{
		bool apple;
		binTreeNode* left;
		binTreeNode* right;
	};

	binTree();
	binTree(std::vector<bool>);
	~binTree();
	int minTime();
private:
	void destroyTree(binTreeNode*);
	void buildTree(binTreeNode* r, std::vector<bool>, int);
	int minTime(binTreeNode* r, int);
	binTreeNode* root;
	// Added private member to have int size of vector
	int appleSize;
	// Added private member for keeping track of
	// needed minimum recursion calls without modifying time
	int inc;
};

#endif /* BINTREE_H_ */
