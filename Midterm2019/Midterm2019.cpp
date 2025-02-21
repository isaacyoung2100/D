﻿
//

//#include "pch.h"
#include <iostream>
#include <string>
#include <cctype>
#include "polynomial1.h"
#include "BagInterface.h"
#include "ArrayBag.h"
#include "LinkedBag.h"


#define SIZE 10

void input(string sMessage, string& sInputString)
{
	cout << sMessage << endl;
	cin >> sInputString;
	return;
}

void output(string sMessage)
{
	if (sMessage.length() > 0)
		cout << endl << sMessage << endl;

	return;
}

int inputNumber(string sMessage, int A[])
{
	int i;

	for (i = 0; i < SIZE; i++) {
		cout << sMessage;
		cin >> A[i];

		if (A[i] == 0)
			break;
	}

	return i;
}

// ================ Question 1 Begins Here ==================

int findMax(int A[], int start, int end)
{
	// add yor code here
	if (start == end)
		return A[start];

	int max = findMax(A, start + 1, end);
	int now = A[start];
	return ((max > now) ? max : now);
}

void doQ1()
{
	int aArray[SIZE];
	int size = inputNumber("Enter a number (0 to end): ", aArray);

	cout << endl << "Input numbers: ";

	for (int i = 0; i < size; i++)
		cout << aArray[i] << " ";

	cout << endl << "Maximum: " << findMax(aArray, 0, size - 1) << endl;

	return;
}

// ================ Question 1 Ends Here ==================

// ================ Question 2 Begins Here =================
void doQ2()
{
	ArrayPolynomial aArrPoly, bArrPoly;
	LinkedPolynomial aLinkPol, bLinkPol;

	int coef, expo;

	aArrPoly.clear(); bArrPoly.clear();//全部皆設零


	for (int i = 0; i < MAX_TERMS; i++) {
		cout << "\n\ninput a's coefficient and exponent: ";
		cin >> coef >> expo;

		if (expo == 0 && coef == 0)
			break;

		aArrPoly.inputTerms(coef, expo);//#見洞就插

		cout << "\n\na = ";
		aArrPoly.printArrayBasedPoly();//#print
		cout << "\nMaximum term = ";
		aArrPoly.showArrayBasedPolyMaxTerm();//#Find Max item(2-a) #and Printout
		
		//#全數向左平移一個(2-e)
		aArrPoly.ArrayBasedRotateTerms();

		cout << "\n\na = ";
		aArrPoly.printArrayBasedPoly();//#print
		cout << "\nMaximum term = ";
		aArrPoly.showArrayBasedPolyMaxTerm();//#prinout the Max item
		
		//#Copy and Modify(2-d)
		bArrPoly.compactCopy(aArrPoly);

		cout << "\n\nb = ";
		bArrPoly.printArrayBasedPoly();//#Printout
		cout << "\nMaximum term = ";
		bArrPoly.showArrayBasedPolyMaxTerm();//#prinout the Max item

		//--------------------
			
		aLinkPol.inputTerms(coef, expo);//#Create new item and let it be headPtr

		cout << "\n\na = ";
		aLinkPol.printLinkBasedPoly();//#Printout
		cout << "\nMaximum term = ";
		aLinkPol.showLinkBasedPolyMaxTerm();//#Find Max item(2-b) #and Printout

		//Rotation
		aLinkPol.LinkBasedRotateTerms();

		cout << "\n\na = ";
		aLinkPol.printLinkBasedPoly();//
		cout << "\nMaximum term = ";
		aLinkPol.showLinkBasedPolyMaxTerm();//

		//#Copy and Modify
		bLinkPol.compactCopy(aLinkPol);

		cout << "\n\nb = ";
		bLinkPol.printLinkBasedPoly();//
		cout << "\nMaximum term = ";
		bLinkPol.showLinkBasedPolyMaxTerm();//
	}
}
// ================ Question 2 Ends Here ==================

// ================ Question 3 Begins Here ==================

void displayBag(ArrayBag<string>& bag)
{
	cout << "The bag contains " << bag.getCurrentSize() << " items: ";
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
	string items[] = { "Banana", "Cherry", "Apple", "Cherry", "Banana", "Cherry" };

	cout << "Add 6 items to the bag: " << endl;

	for (int i = 0; i < 6; i++)
		bag.add(items[i]);

	displayBag(bag);

	ArrayBag<string> anotherBag;

	anotherBag.copy(bag);
	displayBag(anotherBag);

	anotherBag.compact();
	displayBag(anotherBag);
} // end bagTester

void displayBag(LinkedBag<string>* bagPtr)
{
	cout << "The bag contains " << bagPtr->getCurrentSize() << " items: ";
	vector<string> bagItems = bagPtr->toVector();

	int numberOfEntries = (int)bagItems.size();

	for (int i = 0; i < numberOfEntries; i++)
	{
		cout << bagItems[i] << " ";
	}  // end for

	cout << endl;
}  // end displayBag

void bagTester(LinkedBag<string>* bagPtr)
{
	string items[] = { "Banana", "Cherry", "Apple", "Cherry", "Banana", "Cherry" };

	cout << "Add 6 items to the bag: " << endl;

	for (int i = 0; i < 6; i++)
		bagPtr->add(items[i]);

	displayBag(bagPtr);

	LinkedBag<string>* anotherBagPtr = nullptr;
	anotherBagPtr = new LinkedBag<string>();
	
	anotherBagPtr->copy(bagPtr);
	displayBag(anotherBagPtr);

	anotherBagPtr->compact();
	displayBag(anotherBagPtr);
}  // end bagTester

void doQ3()
{
	char userChoice = ' ';

	while (toupper(userChoice) != 'X') {
		cout << "Enter 'A' to test the array-based implementation\n"
			<< " 'L' to test the link-based implementation or 'X' to exit: ";
		cin >> userChoice;

		if (toupper(userChoice) == 'A')
		{
			ArrayBag<string> bag;
			cout << "Testing the Array-Based Bag:" << endl;
			cout << "The initial bag is empty." << endl;
			bagTester(bag);
		}
		else
		{
			LinkedBag<string>* bagPtr = nullptr;
			bagPtr = new LinkedBag<string>();
			cout << "Testing the Link-Based Bag:" << endl;
			cout << "The initial bag is empty." << endl;
			bagTester(bagPtr);
			delete bagPtr;
			bagPtr = nullptr;
		}  // end if

		cout << "All done!\n\n" << endl;
	}
}

// ================ Question 3 Ends Here ==================

// ============== Main Program Begins Here ================

int main()
{
	string sCommand, sName, sNum, sMessage;

	while (1) {
		cout << endl;
		cout << "1. Recursive function" << endl;
		cout << "2. Polynomial functions" << endl;
		cout << "3. Bag functions" << endl;
		input("Enter Question Number( 1 ~ 3 ) or 0 to Exit:", sNum);

		switch (sNum[0] - '0') {
		case 0:
			return 0;
		case 1:
			doQ1();
			break;
		case 2:
			doQ2();
			break;
		case 3:
			doQ3();
			break;
		}
	}
}

// ============== Main Program Ends Here ================

// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
