/*
 * LL.cpp
 *
 *  Created on: Jan 22, 2022
 *      Author: Matthew Noojin
 */

#include "LL.h"
#include <iostream>

/*
 * Iterator class, the nested class in the linked list
 * Is friends with the linked list to access its private members
 */

// Default constructor
template <typename type>
LL<type>::iterator::iterator()
{
	current = nullptr;
}
// Constructor that assigns the passed pointer to current
template <typename type>
LL<type>::iterator::iterator(node *ptr)
{
	current = ptr;
}
// Overloads the pointer * operator
template <typename type>
type LL<type>::iterator::operator*() const
{
	return current->data;
}
// Moves the iterator to the next element in the list
template <typename type>
const typename LL<type>::iterator& LL<type>::iterator::operator++(int)
{
	current = current -> next;
	return *this;
}
// Moves the iterator to the previous element in the
template <typename type>
const typename LL<type>::iterator& LL<type>::iterator::operator--(int)
{
	current = current->prev;
	return *this;
}
// Overloads == operator so list components can be compared
template <typename type>
bool LL<type>::iterator::operator==(const iterator& rhs) const
{
	if(this->current == rhs.current)
		return true;
	else
		return false;
}
// Same as the last overload function
template <typename type>
bool LL<type>::iterator::operator!=(const iterator& rhs) const
{
	if(this->current != rhs.current)
		return true;
	else
		return false;
}

/*
 * Linked list class
 * To be sorted
 */

// Default constructor
template <typename type>
LL<type>::LL()
{
	// Sets both head and tail to null
	head = nullptr;
	tail = nullptr;

}

// Copy constructor (rule of 3)
template <typename type>
LL<type>::LL(const LL<type>& copy)
{
	node* tmp = *copy.head;

	// Iterates through the linked list, starting from the tail
	while(tmp != nullptr)
	{
		// Inserts data from rhs list into new list
		this->tailInsert(tmp->data);

		// If we are at the start, we set our first value the head
		if(tmp == copy.head)
			this->head = tmp;

		// Keep updating the tail pointer until we reach the end
		this->tail = tmp;

		// Iterates to next value in list
		tmp = tmp->next;
	}
}

// Deallocates list
template <typename type>
LL<type>::~LL()
{
	while(tail != nullptr)
	{
		// Create new temp node to point to previous pointer of new tail
		node* tmp;

		// Have tmp equal to the next node, then delete tail and update it
		tmp = tail->prev;
		delete tail;
		tail = tmp;

	}

	// Set tail and head back to null when their memory is freed
	tail = nullptr;
	head = nullptr;

}

// = overload operator, uses destructor and copy constructor
template <typename type>
const LL<type>& LL<type>::operator=(const LL<type>& rhs)
{
	// Deallocate current list
	this->deleteList();

	// Our temp node points to the rhs's head
	node* tmp = *rhs.head;

	// Iterates through the linked list, starting from the tail
	while(tmp != nullptr)
	{
		// Inserts data from rhs list into new list
		this->tailInsert(tmp->data);

		// Iterates to next value in list
		tmp = tmp->next;
	}

	// Return our copied list
	return *this;
}

template <typename type>
LL<type>& LL<type>::deleteList()
{
	while(tail != nullptr)
	{
		// Create new node to hold the prev pointer on new tail
		node* tmp;

		// Have tmp equal to the next node, then delete tail and update it
		tmp = tail->prev;
		delete tail;
		tail = tmp;

	}

	// Set tail and head back to null
	tail = nullptr;
	head = nullptr;

	// Return the deallocated list
	return *this;
}

// Inserts a node to the back of the list
template <typename type>
void LL<type>::tailInsert(const type& item)
{
	// Our new node to insert
	node* ins = new node;

	// Sets up the new node with next/prev pointers and data
	ins->next = nullptr;
	ins->prev = tail;
	ins->data = item;

	// If the tail is not null, then its next must be set to the new node
	if(tail != nullptr)
		tail->next = ins;

	// If we are at the start, then the head must be set
	else if(tail == nullptr)
		head = ins;

	// For every subsequent node, it will only update our tail
	tail = ins;

}

// Returns an iterator object pointing to head of LL
template <typename type>
typename LL<type>::iterator LL<type>::begin() const
{
	return iterator(head);
}

// Returns an iterator object pointing to tail of LL
template <typename type>
typename LL<type>::iterator LL<type>::end() const
{
	return iterator(tail);
}

// Swap two iterator objects, accounting for its place on the list
template <typename type>
void LL<type>::swapNodes(iterator& it1, iterator& it2)
{

	// Our temp nodes that hold addresses to our different nodes
	node* tmp1 = it1.current;
	node* tmp2 = it2.current;
	node* tmp3 = it1.current->next;
	node* tmp4 = it2.current->prev;

if(it1.current == head && it2.current == tail)
{
	// Assign the current value in the head to the tail
	it1.current->next = nullptr;
	it1.current->prev = tmp4;

	// Assign the current value in the tail to the head
	it2.current->next = tmp3;
	it2.current->prev = nullptr;

	// Assign the new tail and head in the list
	tail = it1.current;
	head = it2.current;

	// More pointer updates to our nodes surrounding the its
	tmp3->prev = it2.current;
	tmp4->next = it1.current;

}

else if(it1.current == head)
{
	// it1 is now pointing to a normal node
	it1.current->prev = tmp2;
	it1.current->next = tmp2->next;
	tmp2->next->prev = it1.current;

	// it2 is now pointing to the head
	it2.current->next = tmp1;
	it2.current->prev = nullptr;
	head = it2.current;

}
else if(it2.current == tail)
{
	// it2 is now pointing to a normal node
	it2.current->next = tmp1;
	it2.current->prev = tmp1->prev;
	tmp1->prev->next = it2.current;

	// it1 is pointing to the tail
	it1.current->prev = tmp2;
	it1.current->next = nullptr;
	tail = it1.current;

}

else
{
	// Updating the nodes it2 points to around it
	it2.current->prev = tmp1->prev;
	tmp1->prev->next = it2.current;

	// Updating the nodes it1 points to around it
	it1.current->next = tmp2->next;
	tmp2->next->prev = it1.current;
	// it1 and it2 pointing to each other now
	it2.current->next = it1.current;
	it1.current->prev = it2.current;
}

// Make sure our iterators are pointing to their original address in the new spot
it2 = tmp1;
it1 = tmp2;

}
