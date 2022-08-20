//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** @file  HashedDictionary.cpp */

// Separate chaining resolves collisions

// PARTIALLY COMPLETE
#include <string>
#include "HashedEntry.h"

template<class KeyType, class ItemType>
class HashedDictionary
{
private:
	HashedEntry<KeyType, ItemType>** hashTable;
	static const int DEFAULT_SIZE = 1;
	HashedEntry<KeyType, ItemType>* nextPtr;
	int hashTableSize;

public:
	HashedDictionary();
	HashedDictionary(int size);
	void add(const KeyType& searchKey, const ItemType& newItem);
	bool remove(const KeyType& searchKey);
	HashedEntry<KeyType, ItemType>* getEntry(const KeyType& searchKey);
	void traverse(int itemHashIndex, void visit(HashedEntry<KeyType, ItemType>&)) const;
	void clear();
	bool isEmpty();
	int getTableSize();

protected:
	int getHashIndex(const KeyType& searchKey);
}; // end HashedDictionary

template <class KeyType, class ItemType>
HashedDictionary<KeyType, ItemType>::HashedDictionary()
{
	hashTableSize = DEFAULT_SIZE;
	hashTable = new HashedEntry<KeyType, ItemType> * [hashTableSize];

	for (int i = 0; i < hashTableSize; i++)
		hashTable[i] = nullptr;
}

template <class KeyType, class ItemType>
HashedDictionary<KeyType, ItemType>::HashedDictionary(int size)
{
	hashTableSize = size;
	hashTable = new HashedEntry<KeyType, ItemType> * [hashTableSize];

	for (int i = 0; i < hashTableSize; i++)
		hashTable[i] = nullptr;
}

template <class KeyType, class ItemType>
void HashedDictionary<KeyType, ItemType>::traverse(int itemHashIndex, void visit(HashedEntry<KeyType, ItemType>&)) const
{
	HashedEntry<KeyType, ItemType>* itemPtr = hashTable[itemHashIndex];

	while (itemPtr != nullptr) {
		visit(*itemPtr);
		itemPtr = itemPtr->getNext();
	}
}

template <class KeyType, class ItemType>
void HashedDictionary<KeyType, ItemType>::clear()
{
	HashedEntry<KeyType, ItemType>* nextPtr, * curPtr;

	for (int i = 0; i < hashTableSize; i++) {
		curPtr = hashTable[i];

		while (curPtr != nullptr) {
			nextPtr = curPtr->getNext();
			delete curPtr;
			curPtr = nextPtr;
		} // end while

		hashTable[i] = nullptr;
	} // end if
}

template <class KeyType, class ItemType>
int HashedDictionary<KeyType, ItemType>::getTableSize()
{
	return hashTableSize;
}

template <class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::isEmpty()
{
	for (int i = 0; i < hashTableSize; i++) {
		if (hashTable[i] != nullptr)
			return false;
	}

	return true;
}

template <class KeyType, class ItemType>
int HashedDictionary<KeyType, ItemType>::getHashIndex(const KeyType& searchKey)
{
	int strLen = searchKey.length();

	if (strLen == 0)
		return 0;

	return  ((unsigned char)searchKey[0]) % hashTableSize;
}


template <class KeyType, class ItemType>
void HashedDictionary<KeyType, ItemType>::add(const KeyType& searchKey, const ItemType& newItem)
{
	HashedEntry<string, string>* itemPtr = getEntry(searchKey);
	// Compute the hashed index into the array
	int itemHashIndex = getHashIndex(searchKey);
	// add your code here

	//æ²’æ??£word
	if (itemPtr == nullptr) {
		HashedEntry<string, string>* newptr = new HashedEntry<string, string>();
		newptr->setItem(newItem);
		newptr->setCount(1);

		HashedEntry<string, string>* temp = hashTable[itemHashIndex];
		if (temp == nullptr) {//?™bucket?¹æœ¬æ²’æ??©ä»¶
			hashTable[itemHashIndex] = newptr;
			return;
		}
		while (true)
		{
			if (temp->getNext() == nullptr) {
				temp->setNext(newptr);
				return;
			}
			temp = temp->getNext();
		}
	}
	else {
		HashedEntry<string, string>* temp = hashTable[itemHashIndex];
		while (true)
		{
			if (temp->getItem() == newItem) {
				temp->countUp();
				break;
			}
			temp = temp->getNext();
		}
	}

} // end add

template <class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::remove(const KeyType& searchKey)
{
	bool itemFound = false;
	HashedEntry<string, string>* itemPtr = getEntry(searchKey);
	// Compute the hashed index into the array
	int itemHashIndex = getHashIndex(searchKey);
	// add yor code here
	HashedEntry<string, string>* temp = hashTable[itemHashIndex];

	while (1) {
		//?¸å?
		if (temp->getItem() == searchKey) {
			//ä¸åªä¸€??
			if (temp->getCount() > 1) {
				temp->countDown();
				itemFound = true;
				return itemFound;
			}
			//?ªæ?ä¸€??
			else {
				HashedEntry<string, string>* preItemPtr = hashTable[itemHashIndex];
				if (preItemPtr == itemPtr) {//head
					hashTable[itemHashIndex] = nullptr;
					itemFound = true;
					return itemFound;
				}
				//?¾preitemptr
				while (true)
				{
					if (preItemPtr->getNext() == itemPtr)	break;
					preItemPtr = preItemPtr->getNext();
				}

				//body
				preItemPtr->setNext(itemPtr->getNext());
				itemFound = true;
				return itemFound;

			}
		}
		temp = temp->getNext();
	}

	return itemFound;
} // end remove

template <class KeyType, class ItemType>
HashedEntry<KeyType, ItemType>* HashedDictionary<KeyType, ItemType>::getEntry(const KeyType& searchKey)
{
	bool itemFound = false;

	// Compute the hashed index into the array
	int itemHashIndex = getHashIndex(searchKey);
	// add your code here
	HashedEntry<KeyType, ItemType>* cur = hashTable[itemHashIndex];

	while (cur)
	{
		if (cur->getItem() == searchKey) {
			itemFound = true;
			return cur;
		}
		cur = cur->getNext();
	}

	return nullptr;
}
