//============================================================================
// Name        : Assignment01.cpp
// Author      : Matthew Noojin
// Data		   : 01/22/22
// Class	   : CS302
// Section	   : 1001
// Professor   : Andro Vasko
// Description : Bubble sort a linked list
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include "LL.cpp"

int main()
{
	// Our linked list
	LL<int> list;
	// Iterator objects to move around and modify the list
	LL<int>::iterator i;
	LL<int>::iterator j;
	// A null iterator object for comparisons
	LL<int>::iterator nil(nullptr);

	// Helps us know when we are done bubble sorting
	bool swapped = true;

	// String to hold the file name
	std::string string;

	// Temp int to hold values
	int temp = 0;

	// Our input ifstream variable
	std::ifstream inFile;

	// Open our file
	std::cout << "Enter file with list: ";
	std::cin >> string;
	inFile.open(string);

	// Read data until we reach the end of the file
	while(!inFile.eof())
	{
		getline(inFile, string, '\n');

		if(inFile.eof())
			break;
		else if(string != "")
		{
			temp = std::stoi(string);
			list.tailInsert(temp);
		}
	}
	// Close file
	inFile.close();

	// Output the original, unsorted list
	i = list.begin();
	std::cout << "Original List" << std::endl;
	while(i != nil)
	{
		std::cout << *i << " ";
		i++;

	}

	// Start at the first and second element on the list
	i = list.begin();
	j = list.begin();
	j++;



	// Loops until swapped is false
	while(swapped == true)
	{
		// If swapped is not set to true, we are done
		swapped = false;
		// Loops until the end of the list
		while(j != nil)
		{
			// Checks if we need to swap our nodes
			if(*i > *j)
			{
				list.swapNodes(i, j);
				swapped = true;
			}
			// Iterate
			i++;
			j++;

		}

		// Reset from first two elements in list
		i = list.begin();
		j = list.begin();
		j++;

	}

	// Output for our sorted list
	std::cout << "\n\nSorted List" << std::endl;
	i = list.begin();

	while(i != nil)
	{
		std::cout << *i << " ";
		i++;

	}

	return 0;
}
