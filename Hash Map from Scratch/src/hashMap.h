/*
 * hashMap.h
 *
 *  Created on: Mar 29, 2022
 *      Author: matt
 */

#ifndef HASHMAP_H_
#define HASHMAP_H_

#include <string>

template <typename t1, typename t2>
class hashMap {
public:
	struct hashPair
	{
		t1 key;
		t2 value;
		hashPair* link;
	};
	struct iteratorPair
	{
		t1* key;
		t2* value;
		iteratorPair* link;
	};

	class iterator
	{
	public:
		friend class hashMap;
		iterator();
		const iterator& operator++(int);
		bool operator==(const iterator&) const;
		bool operator!=(const iterator&) const;
		t1 first();
		t2 second();
	private:
		iterator(iteratorPair*);
		iteratorPair* element;
	};

	hashMap();
	~hashMap();
	t2& operator[](t1);
	iterator begin() const;
	iterator end() const;
private:
	void resize();
	int h(std::string) const;
	int items;
	int size;
	hashPair** table;
	iteratorPair* head;
};

#endif /* HASHMAP_H_ */
