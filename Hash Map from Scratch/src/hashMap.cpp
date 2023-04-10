/*
 * hashMap.cpp
 *
 *  Created on: Mar 29, 2022
 *      Author: matt
 */

#include "hashMap.h"

template <typename t1, typename t2>
hashMap<t1, t2>::hashMap()
{
	// Initialize all hashMap values
	size = 5;
	items = 0;
	head = new iteratorPair;
	head = nullptr;
	table = new hashPair*[size];

	for(int i = 0; i < size; i++)
	{
		table[i] = nullptr;
	}
}

template <typename t1, typename t2>
hashMap<t1, t2>::~hashMap()
{

	// Delete head
	while(head != nullptr)
	{
		iteratorPair* temp;
		temp = head->link;
		delete head;
		head = temp;
	}

	// Go through our hashtable and delete everything
	for(int i = 0; i < size; i++)
	{
		if(table[i] != nullptr)
		{
			hashPair* temp = table[i];
			while(temp != nullptr)
			{
				temp = table[i]->link;
				delete table[i];
				table[i] = temp;
			}
		}
	}

	table = nullptr;
	delete[] table;

}

template <typename t1, typename t2>
t2& hashMap<t1, t2>::operator[](t1 key)
{
	// table[x]
	hashPair* i;
	// Starts at head
	iteratorPair* j;

	// Resize if our load factor is >= 50%
	if((static_cast<float>(items)/size) >= 0.5)
		resize();

	// Store return value of hash function
	int x = h(key);

	// Will repeat if we hit a collision
	do
	{
		// Set i and j
		i = table[x];
		j = head;
		// If first elements in the index for the hashtable
		// is null, we create a new node.
		if(i == nullptr)
		{
			// Allocate table node
			i = new hashPair;
			table[x] = i;
			i->key = key;
			i->value = t2();
			i->link = nullptr;

			// If head is empty, allocate it
			if(head == nullptr)
			{
				j = new iteratorPair;
				head = j;
			}
			// Otherwise, we insert into head table
			else
			{
				while(j->link != nullptr)
					j = j->link;

				j->link = new iteratorPair;
				j = j->link;
			}
			j->key = &(i->key);
			j->value = &(i->value);
			j->link = nullptr;

			// New item
			items++;

			// Return the value pertaining to our key
			return i->value;
		}
		// Otherwise, we return the key if it exists already
		if(i->key == key)
			return i->value;

		// Then, we move i to the next linked value
		i = i->link;
		// If the next linked value is null, create a new node
		if(i == nullptr)
		{
			// Allocate new node
			i = new hashPair;
			table[x]->link = i;
			i->key = key;
			i->value = t2();


			// Set up the head linked list
			if(head == nullptr)
			{
				j = new iteratorPair;
				head = j;
			}
			// If head is not empty
			else
			{
				while(j->link != nullptr)
					j = j->link;

				j->link = new iteratorPair;
				j = j->link;
			}
			j->key = &(i->key);
			j->value = &(i->value);
			j->link = nullptr;

			// New item
			items++;

			// Return key's value
			return i->value;
		}
		// Otherwise, we check if the key exists
		if(i->key == key)
			return i->value;

		// If the key does not exist in the list,
		// and the list is full, we resize the x int
		x = (x + 1) % size;
		// If we get to this point, we need to try again
	}while(true);
}

template <typename t1, typename t2>
typename hashMap<t1, t2>::iterator hashMap<t1, t2>::begin() const
{
	return head;
}

template <typename t1, typename t2>
typename hashMap<t1, t2>::iterator hashMap<t1, t2>::end() const
{
	// We "iterate" to the end of our head list
	iteratorPair* temp;
	temp = head;
	while(temp->link != nullptr)
		temp = temp->link;

	// Return the end
	return temp;
}

template <typename t1, typename t2>
void hashMap<t1, t2>::resize()
{
	// Set new size, but keep the old size
	int oldSize = size;
	size *= 2;
	// Keep the old table
	hashPair** oldTable = table;

	// Delete our head list completely
	while(head != nullptr)
	{
		iteratorPair* temp;
		temp = head->link;
		delete head;
		head = temp;
	}

	// Table will be completely new
	table = new hashPair*[size];
	// Set all new values to null
	for(int i = 0; i < size; i++)
		table[i] = nullptr;

	// Items is reset as well
	items = 0;

	// Rehashes the table based on the old size
	for(int hash = 0; hash < oldSize; hash++)
	{
		if(oldTable[hash] != nullptr)
		{
			hashPair* newNode = oldTable[hash];
			while(newNode != nullptr)
			{
				(*this)[newNode->key] = newNode->value;
				newNode = newNode->link;
			}
		}
	}

	// Delete the old table
	delete[] oldTable;

}

template <typename t1, typename t2>
int hashMap<t1, t2>::h(std::string key) const
{
	// Hashes the key based on its ASCII values
	int modKey = 0;
	for(unsigned long int i = 0; i < key.size(); i++)
	{
		modKey += key[i];
	}

	return (modKey % size);
}

/*
 * Iterator class
 */

template <typename t1, typename t2>
hashMap<t1, t2>::iterator::iterator()
{
	element = nullptr;
}

template <typename t1, typename t2>
hashMap<t1, t2>::iterator::iterator(iteratorPair* p)
{
	element = p;
}

template <typename t1, typename t2>
const typename hashMap<t1, t2>::iterator& hashMap<t1, t2>::iterator::operator++(int)
{
	// Iterate value
	*this = element->link;

	return *this;
}


template <typename t1, typename t2>
bool hashMap<t1, t2>::iterator::operator==(const hashMap<t1, t2>::iterator& rhs) const
{
	// Checks if value is ==
	if(this->element == rhs.element)
		return true;

	// Else it is false
	return false;
}

template <typename t1, typename t2>
bool hashMap<t1, t2>::iterator::operator!=(const hashMap<t1, t2>::iterator& rhs) const
{
	// Checks if value is !=
	if(this->element == rhs.element)
		return false;

	//Else it is false
	return true;
}

template <typename t1, typename t2>
t1 hashMap<t1, t2>::iterator::first()
{
	// Key to the iterator variable
	return *(element->key);
}

template <typename t1, typename t2>
t2 hashMap<t1, t2>::iterator::second()
{
	// Value to the iterator variable
	return *(element->value);
}


