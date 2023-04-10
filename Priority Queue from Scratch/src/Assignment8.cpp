//============================================================================
// Name        : Assignment8.cpp
// Author      : Matthew Noojin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "priorityQ.h"
#include "priorityQ.cpp"
#include <unordered_map>
#include <fstream>

int main()
{
    int days = 0;
    double accountBalance = 0.0;
    double profit = 0.0;
    std::string someString;

    std::ifstream stockFile;
    std::ifstream simFile;

    priorityQ<stockType> PQ;

    std::cout << "Stock file: ";
    std::cin >> someString;
    std::cout << std::endl;

    stockFile.open(someString);

    std::cout << "Sim file: ";
    std::cin >> someString;
    std::cout << std::endl;

    simFile.open(someString);

    std::cout << "Amount of days to simulate: ";
    std::cin >> days;
    std::cout << std::endl;

    std::cout << "Amount you wish to transfer into brokerage account: ";
    std::cin >> accountBalance;
    std::cout << std::endl;

    while(!stockFile.eof())
    {
        getline(simFile, someString, '\n');
    }


    for(int i = 1; i <= days; i++)
    {
        std::cout << "Day " << i << " Current balance $ " << accountBalance << std::endl;


    }


	return 0;
}
