﻿// HW6.cpp : 定義主控台應用程式的進入點。
//
//嘿嘿
//#include "stdafx.h"
#include "BagInterface.h"
#include "ArrayBag.h"
#include "LinkedBag.h"
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

void displayBag(ArrayBag<string>& bag)
{	
	cout << endl << "bagdisplay1" << endl << "The bag contains " << bag.getCurrentSize()
		<< " items: ";
	vector<string> bagItems = bag.toVector();
	int numberOfEntries = (int)bagItems.size();
	for (int i = 0; i < numberOfEntries; i++)
	{
		cout << bagItems[i] << " ";
	}  // end for
	cout << endl;
}  // end displayBag

void bagTester(ArrayBag<string>& bag)
{
	cout << endl << "bagtester1" << endl << "isEmpty: returns " << bag.isEmpty() << endl;
	displayBag(bag);

	string items[] = { "1A", "2B", "3C", "4D", "5E", "6F" };
	cout << "Add 6 items to the bag: " << endl;

	for (int i = 0; i < 6; i++)
	{
		bag.add(items[i]);
	}  // end for

	cout << endl << "bagTester" << endl;
	cout << "isEmpty: returns " << bag.isEmpty() << endl;
	cout << "getCurrentSize: returns " << bag.getCurrentSize() << endl;
	cout << "add(\"extra\") returns " << bag.add("extra") << endl;
	cout << "addFirst(\"extra\") returns " << bag.addFirst("extra") << endl;
	cout << "insertFirst(\"extra\") returns " << bag.insertFirst("extra") << endl;

	displayBag(bag);

	for (int i = 0; i < 6; i++)
	{
		bag.deleteFirst();
		displayBag(bag);
		bag.addFirst(items[i]);
		displayBag(bag);
		bag.removeFirst();
		displayBag(bag);
		bag.insertFirst(items[i]);
		displayBag(bag);
		bag.remove(items[i]);
		displayBag(bag);
	}

	cout << "remove(\"extra\") returns " << bag.remove("extra") << endl;
	cout << "removeFirst() returns " << bag.removeFirst() << endl;
	cout << "deleteFirst() returns " << bag.deleteFirst() << endl;
} // end bagTester


void displayBag(BagInterface<string>* bagPtr)
{
	cout << "The bag contains " << bagPtr->getCurrentSize()
		<< " items:" << endl;
	vector<string> bagItems = bagPtr->toVector();

	int numberOfEntries = (int)bagItems.size();

	for (int i = 0; i < numberOfEntries; i++)
	{
		cout << bagItems[i] << " ";
	}  // end for
	cout << endl;
}  // end displayBag

void bagTester(BagInterface<string>* bagPtr)
{
	//cout << "是在哈囉" << endl;
	cout << "isEmpty: returns " << bagPtr->isEmpty() << endl;

	string items[] = { "1A", "2B", "3C", "4D", "5E", "6F" };
	cout << "Add 6 items to the bag: " << endl;

	for (int i = 0; i < 6; i++)
	{
		bagPtr->add(items[i]);
	}  // end for

	displayBag(bagPtr);
	cout << "isEmpty: returns " << bagPtr->isEmpty()
		<< "; should be 0 (false)" << endl;
	cout << "getCurrentSize returns : " << bagPtr->getCurrentSize()
		<< "; should be 6" << endl;
	cout << "Try to add another entry: add(\"extra\") returns "
		<< bagPtr->add("extra") << endl;
	displayBag(bagPtr);
}  // end bagTester

int main()
{
	BagInterface<string>* bagPtr = nullptr;
	char userChoice = 'a';//沒設定不給過?明明就複製貼上阿

	while (toupper(userChoice) != 'X') {
		cout << endl << "main" << endl << "Enter 'A' to test the array-based implementation\n"
			<< " 'L' to test the link-based implementation or 'X' to exit: ";
		cin >> userChoice;

		if (toupper(userChoice) == 'A')
		{
			ArrayBag<string> bag;
			cout << endl << "A" << endl;
			cout << "Testing the Array-Based Bag:" << endl;
			cout << "The initial bag is empty." << endl;
			bagTester(bag);
		}
		else
		{
			bagPtr = new LinkedBag<string>();
			cout << endl << "B" << endl;
			cout << "Testing the Link-Based Bag:" << endl;
			cout << "The initial bag is empty." << endl;
			bagTester(bagPtr);
			delete bagPtr;
			bagPtr = nullptr;
		}  // end if

		cout << "All done!\n\n" << endl;
	}

	return 0;
}  // end main
