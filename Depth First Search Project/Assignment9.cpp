//==============================================================================
// Name        : Assignment9.cpp
// Author      : Matthew Noojin
// Class	   : CS302, Section 1001, Prof Andro-Vasko
// Date		   : 05/05/22
// Description : We will parse a file to construct a basic graph
//               using an adjacency list format in an unordered map.
//               we also construct the same list, but backwards for parsing.
//               With the backward list, we can determine which nodes have
//               no neighbors, which will be our starting point. We also parse
//               a vector full of each unique node to iterate through.
//               After sorting our vectors, we start looping through them
//               and we perform a DFS traversal to determine which of
//               the nodes are the ancestors of our given node at the time.
//               Then we clear everything and loop until the end of the vectors.
//==============================================================================
#include <iostream>
#include <unordered_map>
#include <list>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>


// Prototype for our DFS function
bool ancestors(std::string, std::string,
               std::unordered_map<std::string, std::list<std::string>>,
               std::unordered_map<std::string, bool>&,
               std::unordered_map<std::string, bool>&);

int main() {
    // Our main map with the graph of adjacent nodes
    std::unordered_map<std::string, std::list<std::string>> adjList;
    std::unordered_map<std::string, std::list<std::string>> backwardsList;
    // Our visited map to help with DFS traversal
    std::unordered_map<std::string, bool> visited;
    // Our map to see if a value really is an ancestor of our value
    std::unordered_map<std::string, bool> ancestorMap;
    // String parsing stuff
    std::stringstream ss;
    std::ifstream inFile;
    std::string line, partOfLine;
    std::vector<std::string> names;

    // Our sorted lists of all nodes and nodes with no neighbors
    std::vector<std::string> noNeighbors;
    std::vector<std::string> sortedFullList;

    // Input
    std::cout << "Enter file: ";
    std::cin >> line;

    // Open the file
    inFile.open(line);

    // Parse the file
    while (getline(inFile, line, '\n'))
    {
        // Insert into string stream
        ss << line;

        // Get the first from part until ->
        getline(ss, partOfLine, '-');
        // Parse out ->
        getline(ss, line, ' ');
        // Get the to part
        getline(ss, line);

        // Pop that pesky extra space character in the back >:(
        partOfLine.pop_back();

        // Push it onto our map
        adjList[partOfLine].push_back(line);
        backwardsList[line].push_back(partOfLine);

        // Keep a map of all the names
        ancestorMap[line] = true;
        ancestorMap[partOfLine] = true;

        // Clear the string stream for next pass
        ss.clear();
    }
    // Close file
    inFile.close();

    // Iterate through our two lists to check for nodes with no neighbors
    for(auto it = backwardsList.begin(); it != backwardsList.end();it++)
    {
        // Iterates through our descendants in our current parent
        for(auto descendants = it->second.begin(); descendants != it->second.end();descendants++)
        {
            // We only have a node that has no neighbors if it does exist in our
            // adjacency list as a key, but not in our backwards list as a key
            // Basically, if a key points to something in the main list, but
            // doesn't in the backwards list, it has no neighbors
            if(adjList.find(*descendants) != adjList.end() &&
            backwardsList.find(*descendants) == backwardsList.end() && !visited[*descendants])
            {
                // Just using visited to make this code a lil smaller
                visited[*descendants] = true;
                // This is our list of nodes with no neighbors
                noNeighbors.push_back(*descendants);
            }
        }

    }

    // This will sort every named node we see
    for(auto it = ancestorMap.begin(); it != ancestorMap.end();it++)
    {
        if (it->second)
        {
            it->second = false;
            sortedFullList.push_back(it->first);
        }
    }

    // Clear the maps we used temporarily
    visited.clear();
    ancestorMap.clear();

    // Sort our vectors alphabetically
    std::sort(noNeighbors.begin(), noNeighbors.end());
    std::sort(sortedFullList.begin(), sortedFullList.end());

    // Our big boy algorithm. Top for loop goes through our sorted full array
    for(int i = 0; i < sortedFullList.size();i++)
    {
        // Output
        std::cout << "Relative name: " << sortedFullList[i] << std::endl;

        // This will loop through our list of roots
        for (int j = 0; j < noNeighbors.size(); j++) {
            // Initiate recursive call
            ancestors(noNeighbors[j], sortedFullList[i],
                      adjList, visited, ancestorMap);
            // Clear visited map for future recursion purposes
            visited.clear();
        }

        // Set up our vector of names from the ancestorMap built in ancestors
        for (auto it = ancestorMap.begin(); it != ancestorMap.end(); it++)
        {
            if (it->second)
                names.push_back(it->first);
        }

        // If we have no ancestors, output None
        if(names.empty())
            names.push_back("None");

        // Sort
        std::sort(names.begin(), names.end());

        // Output ancestors
        std::cout << "List of ancestors " << std::endl;
        for(int k = 0; k < names.size();k++)
            std::cout << names[k] << std::endl;

        // Clear names and the ancestorMap to prepare for next pass
        names.clear();
        ancestorMap.clear();

        std::cout << std::endl;

    }

    return 0;
}

/*
 * Our recursive DFS function. Returns a boolean, which helps the recursion along.
 * We pass the current node we are on, the node we are looking for the ancestors of,
 * our adjacency list, the visited list (to check if we have been to a node), and
 * another bool map, but for confirming if a node is an ancestor.
 *
 * Algorithm:
 * 1. Check our base case, which
 *    is if current is equal to the number we are searching for.
 * 2. We mark it true that we have visited the current node.
 * 3. Then, starting from our current node, we loop through its
 *    descendants, and if we have not visited the descendant's node,
 *    we make a recursive call, depending on what the recursive function
 *    returns, we set the ancestor map for current to true.
 * 4. Outside the loop, visited is reset, and if our ancestorMap
 *    is true, we return true up to the other ancestors, and otherwise
 *    false.
 *
 *    To break it down a little more, we basically traverse the graph
 *    keeping track of what we visit, until we hit what we are looking for,
 *    and we return up the tree. We do this with other starting points
 *    and making sure to clear visited as to hit every ancestor of a node.
 */
bool ancestors(std::string current, std::string searchName,
               std::unordered_map<std::string, std::list<std::string>> famTree,
               std::unordered_map<std::string, bool>& visited,
               std::unordered_map<std::string, bool>& ancestorMap)
{
    // Base case
    if(current == searchName)
        return true;

    // Mark our node as visited
    visited[current] = true;

    // Loop through current's descendants
    for(auto descendants = famTree[current].begin(); descendants != famTree[current].end(); descendants++)
    {
        // If we have not visited
        if(!visited[*descendants])
        {
            // We set ancestorMap to true depending on the return value of our recursive call
            if(ancestors(*descendants, searchName, famTree, visited, ancestorMap))
                ancestorMap[current] = true;
        }
    }

    // Clear visited
    visited.clear();

    // Either return true or false depending on what we find
    if(ancestorMap[current])
        return true;
    else
        return false;
}
