//============================================================================
// Name        : Assignment6.cpp
// Author      : Matthew Noojin
// Class	   : CS219, Section 1001, Prof Andro-Vasko
// Date		   : 03/27/22
// Description : Read values and statements in a file,
// 				 we put our category name into a map,
//				 with a struct that holds the word count
//  			 and words needed to parse, as long as
//				 a vector of words to find in parsed hashmap,
//				 then we determine the amount of categories that
//				 have the amount of words that need to match with a statement.
//============================================================================

#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

// Our category stuct to be inserted into a map
struct category
{
	int wordCount = 0;
	int wordsNeeded = 0;
	std::vector<std::string> words;
};

std::string lowerCase(std::string);

int main() {

	// This is each word put into a vector, which
	// we will parse into a hashmap without duplicates
	std::vector<std::string> parseThis;

	// Our vector of names to output at the end of a test case
	std::vector<std::string> outputNames;

	// Condensed words
	std::unordered_map<std::string, bool> noDuplicates;

	// This hashmap has the category name and
	// the struct with parts of the category
	std::unordered_map<std::string, category> categoryMap;

	// String stream and string to pull things out
	// and our ifstream object
	std::stringstream ss;
	std::string str;
	std::ifstream inFile;

	// Open the file
	std::cout << "Enter filename: ";
	std::cin >> str;
	inFile.open(str);

	// Get total test cases
	getline(inFile, str);
	int testCases = std::stoi(str);

	/* Here our the steps of our algorithm.
	 * 1. We loop based on the number of read in test cases.
	 * 2. We clear most of our vectors and maps so they are empty.
	 * 3. Output test case #.
	 * 4. Loop based on number of categories we read in.
	 * 5. Set up the categoryMap with our read name, word count,
	 * 	  words needed to match in output, and a vector of words read to check for.
	 * 6. Afterwards, we read in our whole statement, line-by-line,
	 *    and we parse each word with a stringstream object to a vector of words.
	 * 7. After our vector of words in the statement is parsed and each word will be lowercase,
	 *    we have to eliminate duplicates using a hashmap, by
	 *    checking if a key has been inserted already, and then inserting it otherwise.
	 * 8. Reset values pertaining to an output vector, then we iterate through our map.
	 * 9. We iterate through categoryMap and use a .find() to check if
	 *    a key in noDuplicates is a word in categoryMap, if it is,
	 *    we increment foundWords.
	 * 10. If foundWords = .wordsNeeded in our current iterator object,
	 *     we need to push the key name of the current value onto a vector to output later.
	 * 11. Otherwise, we need to push SQF Problem onto the vector, but only once per test case
	 * 12. Then we output the pushed category names for the current test case
	 * 13. We do all of this again if there are more test cases
	 */

	// Loop through total amount of test cases
	for(int i = 0; i < testCases; i++)
	{
		// Clear our vectors and maps
		categoryMap.clear();
		noDuplicates.clear();
		parseThis.clear();
		// Our current test case
		std::cout << "Test case "
				<< (i + 1) << std::endl;

		// Get categories count
		getline(inFile, str);
		int categories = std::stoi(str);

		// Create our category map
		for(int j = 0; j < categories; j++)
		{
			// Name of category
			getline(inFile, str, ' ');
			std::string name = str;
			// Word count
			getline(inFile, str, ' ');
			categoryMap[name].wordCount = std::stoi(str);

			// Words needed to include the category
			getline(inFile, str, '\n');
			categoryMap[name].wordsNeeded = std::stoi(str);

			// Put the words into a vector in the struct
			for(int k = 0; k < categoryMap[name].wordCount; k++)
			{
				getline(inFile, str, '\n');
				str = lowerCase(str);
				categoryMap[name].words.push_back(str);
			}
		}

		// Take the words and put them in a vector to parse
		getline(inFile, str);
		ss << str;
		while(str != "")
		{
			// Get all the words in the paragraph
			std::string word;
			while(ss >> word)
			{
				word = lowerCase(word);
				parseThis.push_back(word);
			}
			// Clear and reassign string stream to parse words
			ss.clear();
			getline(inFile, str);
			ss << str;

		}

		// Parse duplicates in our statement into a hashmap
		for(unsigned long int j = 0; j < parseThis.size(); j++)
		{
			if(!noDuplicates[parseThis[j]])
				noDuplicates[parseThis[j]] = true;
		}

		// Reset specific values for outputting names
		bool checkSQF = false;
		outputNames.clear();

		// Iterate through map
		for(auto it = categoryMap.begin(); it != categoryMap.end(); it++)
		{

			// Words found
			int foundWords = 0;

			// Loop through word vector in categoryMap
			for(int j = 0; j < it->second.wordCount; j++)
			{
				// If we find the word and match it to duplicates map we increment found words
				if(noDuplicates.find(it->second.words[j]) != noDuplicates.end())
				{
					foundWords++;
				}
			}

			// If we have all the words needed
			if(it->second.wordsNeeded == foundWords)
			{
				outputNames.push_back(it->first);
			}
			// Otherwise we need to output sqf problem
			else if(checkSQF == false && it->second.wordsNeeded != foundWords)
			{
				outputNames.push_back("SQF Problem");
				checkSQF = true;
			}

		}

		// Output the names in our current test case
		for(int j = (outputNames.size() - 1); j >= 0; j--)
		{
			std::cout << outputNames[j] << std::endl;
		}

	}

	inFile.close();

	return 0;
}

// Turn and return the passed string to lowercase
std::string lowerCase(std::string word)
{
	// Iterate through word
	for(unsigned long int j = 0; j < word.length(); j++)
	{
		word[j] = tolower(word[j]);
	}

	// Return word
	return word;
}
