/*
 * priorityQ.h
 *
 *  Created on: Apr 19, 2022
 *      Author: matt
 */

#ifndef PRIORITYQ_H_
#define PRIORITYQ_H_

#include <string>
#include <vector>

struct stockType
{
	std::string name;
	int timesPurchased;
	double dividend;
	double price;

	bool operator>(const stockType& rhs)
	{
        // Checking if the price is less than rhs
		if(this->price < rhs.price)
            return true;
        else if(this->price > rhs.price)
            return false;

        // Checking if times purchased is greater than rhs
        if (this->timesPurchased < rhs.timesPurchased)
            return false;
        else if(this->timesPurchased > rhs.timesPurchased)
            return true;

        // Checking if dividend is greater than rhs
        if(this->dividend < rhs.dividend)
            return false;
        else if(this->dividend > rhs.dividend)
            return true;

        // Checking if current value is higher in alphabet
        if(this->name < rhs.name)
            return true;
        else
            return false;
	}
};

template <class Type>
class priorityQ
{
public:
    priorityQ(int = 10);
	priorityQ(std::vector<Type>);
	priorityQ(const priorityQ<Type>&);
	~priorityQ();
	const priorityQ<Type>& operator=(const priorityQ<Type>&);
	void insert(Type);
	void deletePriority();
	Type getPriority() const;
	bool isEmpty() const;
	void bubbleUp(int);
	void bubbleDown(int);
	int getSize() const;

private:
	int capacity;
	int size;
	Type* heapArray;
};

#endif /* PRIORITYQ_H_ */
