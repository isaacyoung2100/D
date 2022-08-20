
#include "BagInterface.h"
#include "Node.h"
#include <cstddef>
#include <string>

template<class ItemType>
class LinkedBag : public BagInterface<ItemType>
{
public:
	Node<ItemType>* headPtr; // Pointer to first node
	int itemCount;           // Current count of bag items

public:
	LinkedBag();
	LinkedBag(const LinkedBag<ItemType>& aBag); // Copy constructor
	virtual ~LinkedBag();                       // Destructor should be virtual
	int getCurrentSize() const;
	bool isEmpty() const;
	bool add(const ItemType& newEntry);
	void copy(const LinkedBag<ItemType>* anotherBag);
	void compact();
	void clear();
	bool contains(const ItemType& anEntry) const;
	int getFrequencyOf(const ItemType& anEntry) const;
	vector<ItemType> toVector() const;
}; // end LinkedBag

template<class ItemType>
LinkedBag<ItemType>::LinkedBag() : headPtr(nullptr), itemCount(0)
{
}  // end default constructor

template<class ItemType>
LinkedBag<ItemType>::~LinkedBag()
{
	clear();
}  // end destructor

template<class ItemType>
bool LinkedBag<ItemType>::isEmpty() const
{
	return itemCount == 0;
}  // end isEmpty

template<class ItemType>
int LinkedBag<ItemType>::getCurrentSize() const
{
	return itemCount;
}  // end getCurrentSize

template<class ItemType>
void LinkedBag<ItemType>::clear()
{
	Node<ItemType>* nodeToDeletePtr = headPtr;

	while (headPtr != nullptr)
	{
		headPtr = headPtr->getNext();

		// Return node to the system
		nodeToDeletePtr->setNext(nullptr);
		delete nodeToDeletePtr;

		nodeToDeletePtr = headPtr;
	}  // end while
	// headPtr is nullptr; nodeToDeletePtr is nullptr

	itemCount = 0;
}  // end clear

template<class ItemType>
bool LinkedBag<ItemType>::add(const ItemType& newEntry)
{
	Node<ItemType>* nextNodePtr = new Node<ItemType>();
	nextNodePtr->setItem(newEntry);
	nextNodePtr->setNext(headPtr);

	headPtr = nextNodePtr;
	itemCount++;

	return true;
}

template<class ItemType>
int LinkedBag<ItemType>::getFrequencyOf(const ItemType& anEntry) const
{
	int frequency = 0;
	int counter = 0;
	Node<ItemType>* curPtr = headPtr;
	while ((curPtr != nullptr) && (counter < itemCount))
	{
		if (anEntry == curPtr->getItem())
		{
			frequency++;
		} // end if

		counter++;
		curPtr = curPtr->getNext();
	} // end while

	return frequency;
}  // end getFrequencyOf


template<class ItemType>
vector<ItemType> LinkedBag<ItemType>::toVector() const
{
	vector<ItemType> bagContents;
	Node<ItemType>* curPtr = headPtr;
	int counter = 0;
	while ((curPtr != nullptr) && (counter < itemCount))
	{
		bagContents.push_back(curPtr->getItem());
		curPtr = curPtr->getNext();
		counter++;
	}  // end while

	return bagContents;
}  // end

//3-d #��C�ƻs
template<class ItemType>
void LinkedBag<ItemType>::copy(const LinkedBag<ItemType>* anotherBag)
{// add your code here

	Node<ItemType> *anocurPtr = anotherBag->headPtr;
	//#copy a linklist
	Node<ItemType>* fheadPtr = new Node<ItemType>(anocurPtr->getItem(), nullptr);//#���Y #�ƻs�Y
	itemCount++;
	
	Node<ItemType>* fcurPtr = fheadPtr;
	anocurPtr = anocurPtr->getNext();

	while (anocurPtr)//#�ƻs����
	{
		Node<ItemType>* newPtr = new Node<ItemType>();
		newPtr->setItem(anocurPtr->getItem());
		newPtr->setNext(nullptr);

		fcurPtr->setNext(newPtr);
		itemCount++;

		fcurPtr = fcurPtr->getNext();
		anocurPtr = anocurPtr->getNext();

		//Isaac_display(fheadPtr); cout << endl;
	}

	headPtr = fheadPtr;
	
	return;
}  // end remove

//3-b #�ƧǦ�C
template<class ItemType>
void LinkedBag<ItemType>::compact()
{
// add your code here
	Node<ItemType>* checkthis, * pre;//#check one by one
	checkthis = headPtr->getNext();	pre = headPtr;//#�q�ĤG�Ӷ}�l�ˬd�P�e�����O�_����

	Node<ItemType>* run;
	while(1){
		if (checkthis == nullptr) {
			break;
		}
	
		run = headPtr;

		while(1)
		{	
			if (run == checkthis) 
					break;

			if (checkthis->getItem() == run->getItem()  ) {//#�p�G�����ػP�e��run�����̼�
				pre->setNext(checkthis->getNext());

				break;
			}
			//#�L���ƦV�U�]
			run = run->getNext();
		}
		
		checkthis = checkthis->getNext();
		while (1) {//#��pre #pre���U
			if (pre->getNext() == checkthis)	break;
			pre = pre->getNext();
		}

	}

	return;
}  // end