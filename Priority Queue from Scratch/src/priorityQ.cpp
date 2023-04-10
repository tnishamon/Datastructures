/*
 * priorityQ.cpp
 *
 *  Created on: Apr 19, 2022
 *      Author: matt
 */

#include "priorityQ.h"

template <class Type>
priorityQ<Type>::priorityQ(int cap)
{
    capacity = cap;
    heapArray = new Type[cap];
    size = 0;
}

template <class Type>
priorityQ<Type>::priorityQ(std::vector<Type> v)
{
    capacity = v.size() + 1;
    heapArray = new Type[capacity];
    size = capacity - 1;

    // Inserts each value in vector into the heap. Size is allocated based on the size
    for (int i = 1; i <= size; i++)
        heapArray[i] = v[i - 1];

    for(int i = (size - 1); i > 0; i--)
        bubbleDown(i);
}

// Copy constructor
template <class Type>
priorityQ<Type>::priorityQ(const priorityQ<Type>& copy)
{
    for(int i = 1; i < copy.getSize(); i++)
    {
        heapArray[i] = copy.heapArray[i];
    }
    capacity = copy.capacity;
    size = copy.getSize();
}

// Deallocate the heap
template <class Type>
priorityQ<Type>::~priorityQ()
{
    delete[] heapArray;
}

// Equal operator to set each value of left and right side equal
template <class Type>
const priorityQ<Type>& priorityQ<Type>::operator=(const priorityQ<Type>& rhs)
{
    for(int i = 1; i < rhs.getSize(); i++)
    {
        heapArray[i] = rhs.heapArray[i];
    }
    capacity = rhs.capacity;
    size = rhs.getSize();
}

template <class Type>
void priorityQ<Type>::insert(Type item)
{
    size++;

    if(size == capacity)
    {
        Type* oldHeap = heapArray;
        capacity *= 2;
        heapArray = new Type[capacity];

        for(int i = 1; i < size; i++)
            heapArray[i] = oldHeap[i];

        delete[] oldHeap;
    }
    heapArray[size] = item;
    bubbleUp(size);
}

template <class Type>
void priorityQ<Type>::deletePriority()
{
    heapArray[1] = heapArray[size];
    size--;
    bubbleDown(1);
}

template <class Type>
Type priorityQ<Type>::getPriority() const
{
    return heapArray[1];
}

template <class Type>
bool priorityQ<Type>::isEmpty() const
{
    if(size == 0)
        return true;
    else
        return false;
}

template <class Type>
void priorityQ<Type>::bubbleUp(int index)
{
    int parentIndex = index / 2;

    while(index > 0 && parentIndex > 0 && heapArray[index] > heapArray[parentIndex])
    {
        // Swap the two values
        auto temp = heapArray[index];
        heapArray[index] = heapArray[parentIndex];
        heapArray[parentIndex] = temp;

        // Set us to our next index to bubble up from
        index = parentIndex;
        parentIndex = index / 2;
    }
}

template <class Type>
void priorityQ<Type>::bubbleDown(int index)
{
    // Where our leftChild's index falls in the heap array
    int leftChild = 2 * index;
    int rightChild = (2 * index) + 1;

    // Ternary statement to choose the next best child to move to in the heap
    // I'm sorry it's so scary with nested ternaries in it.
    // Basic breakdown:
    // Depending on which child to the parent is "greater" in value, will determine what is swapped
    // If left is greater, right is our valid child (this is a maxheap), so
    // we check if right's size is valid, then if not choose left.
    // The same happens for right, if left is smaller (i.e. not greater), we choose left
    // as long as it is valid.
    int chosenChild = (heapArray[leftChild] > heapArray[rightChild]) ?
              (leftChild < size) ? leftChild:rightChild
            : (rightChild < size) ? rightChild:leftChild;

    // Our base case
    if(leftChild >= size && rightChild >= size)
        return;

    // Statement that determines whether or not we swap based on values in heap
    if(heapArray[chosenChild] > heapArray[index])
    {
        // Swap our values in the heap array
        auto temp = heapArray[index];
        heapArray[index] = heapArray[chosenChild];
        heapArray[chosenChild] = temp;

        // Our new index downward
        index = chosenChild;
        bubbleDown(index);
    }

    // Call bubble down again
    return;
}

template <class Type>
int priorityQ<Type>::getSize() const
{
    // Return size of heapArray
    return size;
}
