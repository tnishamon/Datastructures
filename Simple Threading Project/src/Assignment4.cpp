//============================================================================
// Name        : Assignment4.cpp
// Author      : Matthew Noojin
// Class	   : CS219, Section 1001, Prof Andro-Vasko
// Date		   : 02/20/22
// Program	   : Reads in two matrices from a file and
//				 performs matrix multiplication in parallel
//============================================================================

#include <iostream>
#include <thread>
#include <vector>
#include <fstream>

// Our two matrixes to multiply, and the result
std::vector<std::vector<int>> matrixOne;
std::vector<std::vector<int>> matrixTwo;
std::vector<std::vector<int>> matrixThree;

void matrixMult(const int, const int);

int main()
{
	// Our max amount of threads
	int maxThreads = std::thread::hardware_concurrency();

	// Vector of threads where we loop and spawn threads to calculate matrix
	std::vector<std::thread> threadPool;

	// File input
	std::ifstream inFile;
	std::string fileName;

	// Open given file
	std::cout << "Enter filename: ";
	std::cin >> fileName;
	inFile.open(fileName);

	// Get the size of the matrix
	getline(inFile, fileName, ' ');
	int n1 = std::stoi(fileName);
	getline(inFile, fileName, '\n');
	int m1 = std::stoi(fileName);

	// Read the first matrix in
	for(int i = 0; i < n1; i++)
	{
		std::vector<int> temp;
		for(int j = 0; j < m1; j++)
		{
			// If we are at the end of the line
			if(j == (m1 - 1))
			{
				getline(inFile, fileName, '\n');
				temp.push_back(std::stoi(fileName));
			}

			// Otherwise we get each number
			else
			{
				// Get each number
				getline(inFile, fileName, ' ');

				// If the number isn't read correctly we grab it again
				while(fileName == "")
					getline(inFile, fileName, ' ');

				temp.push_back(std::stoi(fileName));
			}
		}
		// Push back the temp matrix onto the vector
		matrixOne.push_back(temp);
	}

	// Get the sizes of the second matrix
	getline(inFile, fileName, ' ');
	int n2 = std::stoi(fileName);
	getline(inFile, fileName, '\n');
	int m2 = std::stoi(fileName);
	// Read the first matrix in
	for(int i = 0; i < n2; i++)
	{
		std::vector<int> temp;
		for(int j = 0; j < m2; j++)
		{
			// If we are at the end of the line
			if(j == (m2 - 1))
			{
				getline(inFile, fileName, '\n');
				temp.push_back(std::stoi(fileName));
			}
			// Otherwise we get each number
			else
			{
				// Get each number
				getline(inFile, fileName, ' ');

				// If the number isn't read correctly we grab another
				// part of the string
				while(fileName == "")
					getline(inFile, fileName, ' ');

				temp.push_back(std::stoi(fileName));
			}
		}
		// Push back the temp matrix onto the 2D vector
		matrixTwo.push_back(temp);
	}

	// Close da file
	inFile.close();

	// Allocate space for matrix three
	// In matrix mult, the product of the
	// two matrices is an (n1xm2) matrix
	// as long as m1=n2, which we are assuming
	for(int i = 0; i < n1; i++)
	{
		std::vector<int> temp;
		for(int j = 0; j < m2; j++)
		{
			temp.push_back(0);
		}
		matrixThree.push_back(temp);
	}

	/*
	 * Basic Algorithm:
	 * 1. Spawn a thread that calls the function
	 * 2. The function receives our i and j in our for loop
	 * 3. The matrix multiplication happens only at matrixThree[i][j]
	 * 4. If our threadPool's size exceeds the hardware concurrency, we reset the thread pool
	 * 5. We keep going until matrixThree is built (we loop n1xm2 times)
	 */

	// Loops through matrix to assemble matrixThree with matrix multiplication
	for(unsigned long int i = 0; i < matrixOne.size(); i++)
	{
		for(unsigned long int j = 0; j < matrixTwo[0].size(); j++)
		{
			threadPool.push_back(std::thread(matrixMult, i, j));

			// If we reach our max threadPool limit, we clear the threads to spawn more
			if(threadPool.size() % maxThreads == 0)
			{
				// Let all the threads join
				for(unsigned long int j = 0; j < threadPool.size(); j++)
					threadPool[j].join();

				// Clear the threadPool
				threadPool.clear();
			}
		}
	}

	// Clear the threadPool
	for(unsigned long int i = 0; i < threadPool.size(); i++)
	{
		threadPool[i].join();
	}

	threadPool.clear();
	// Output the third matrix
	for(unsigned long int i = 0; i < matrixThree.size(); i++)
	{
		for(unsigned long int j = 0; j < matrixThree[i].size(); j++)
		{
			std::cout << matrixThree[i][j] << " ";
		}
		std::cout << std::endl;
	}

	return 0;
}
	/* Need to linearly calculate the multiplication between
	 * our current row in matrix one, and current column in
	 * matrix two. This is because the multiplication of
	 * each column and row add into our current i, j in
	 * matrix three. Stores the result in the global matrix three.
	 */
void matrixMult(const int threadRow, const int threadCol)
{

	for(unsigned long int i = 0; i < matrixOne[0].size(); i++)
	{
		matrixThree[threadRow][threadCol] += matrixOne[threadRow][i] * matrixTwo[i][threadCol];
	}


}
