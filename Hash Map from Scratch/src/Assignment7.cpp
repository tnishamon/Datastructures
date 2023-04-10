//============================================================================
// Name        : Assignment7.cpp
// Author      : Matthew Noojin
// Class	   : CS302, Section 1001, Prof Andro-Vasko
// Date		   : 04/12/22
// Description : Read candidates and parties in a file,
// 				 we put them into a hash table, and then
// 		         check for the amount of votes a candidate gets.
// 	             Based on the amount of votes, we determine if there is a
//				 winner or if there is a tie.
//============================================================================
#include "hashMap.h"
#include "hashMap.cpp"
#include <iostream>
#include <fstream>

int main() {

	std::ifstream inFile;
	std::string string1;
	std::string string2;

	hashMap<std::string, std::string> candidateMap;
	hashMap<std::string, int> voteMap;

	// Open the file
	std::cout << "Enter filename: ";
	std::cin >> string1;
	inFile.open(string1);

	// Gets total cases count
	getline(inFile, string1);

	int cases = stoi(string1);

	for(int i = 0; i < cases; i++)
	{

		// Get total amount of candidates
		getline(inFile, string1);
		int candidates = stoi(string1);

		// Set up our candidate map with
		// key = candidate, value = party
		for(int j = 0; j < candidates; j++)
		{
			getline(inFile, string1);
			getline(inFile, string2);
			candidateMap[string1] = string2;
		}

		// In case of a tie
		candidateMap["null"] = "Tie";

		// Get the total votes
		getline(inFile, string1);
		int votesTotal = stoi(string1);

		// Increment for total amount of votes
		for(int k = 0; k < votesTotal; k++)
		{
			getline(inFile, string1);
			voteMap[string1]++;
		}

		// Output
		std::cout << "Case " << (i + 1) << " results: ";

		// Check for the winner
		std::string winner = voteMap.end().first();

		// Go from start to end of map checking for most amount of votes
		for(auto it = voteMap.begin(); it != voteMap.end(); it++)
		{
			if(it.second() > voteMap[winner])
				winner = it.first();
		}

		// Output winner
		std::cout << candidateMap[winner] << std::endl;

	}

	return 0;
}
