/*
 * LL.h
 *
 *  Created on: Jan 22, 2022
 *      Author: Matthew Noojin
 */

#ifndef LL_H_
#define LL_H_

template <typename type>
class LL
{
	struct node
	{
		type data;
		node * prev;
		node * next;
	};
public:
	class iterator
	{
	public:

		// Iterator defintions
		friend class LL;
		iterator();
		iterator(node *);
		type operator*() const;
		const iterator& operator++(int);
		const iterator& operator--(int);
		bool operator==(const iterator&) const;
		bool operator!=(const iterator&) const;
	private:
		node * current;
	};

	// Linked list defintions
	LL();
	LL(const LL<type>&);
	const LL<type>& operator =(const LL<type>&);
	~LL();
	void tailInsert(const type&);
	iterator begin() const;
	iterator end() const;
	void swapNodes(iterator&, iterator&);
	private:
	node * head;
	node * tail;

	LL<type>& deleteList();
	};


#endif /* LL_H_ */
