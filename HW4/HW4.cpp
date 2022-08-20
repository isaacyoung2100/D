// HW4.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//


//#include "stdafx.h"
#include <iostream>
using namespace std;

#define MAX_TERMS 10 /*size of terms array*/
typedef struct {
	int coef;
	int expo;
} polynomialTerm;

typedef struct linkedTerm {
	int coef;
	int expo;
	linkedTerm* nextTermPtr;
} linkedPolynomialTerm;

void show(linkedPolynomialTerm* headptr)
{
	if (headptr == NULL)
		return;
	cout << headptr->coef << "X^" << headptr->expo << " ";
	show(headptr->nextTermPtr);
}

void clear(polynomialTerm t[])
{
	for (int i = 0; i < MAX_TERMS; i++) {
		t[i].coef = 0;
		t[i].expo = 0;
	}
	
	return;
}

void clear(linkedPolynomialTerm*& polynomialTermPtr)
{
	linkedPolynomialTerm* tmpPtr;

	while (polynomialTermPtr != nullptr) {
		tmpPtr = polynomialTermPtr;
		polynomialTermPtr = polynomialTermPtr->nextTermPtr;
		delete tmpPtr;
	}
}

void inputTerms(polynomialTerm t[], int coef, int expo)
{
// add your code here
	if (coef == 0)
		return;
	int flag, i, tail;
	for (i = 0; i < 10; i++) {//find where should the new element to insert
		if (expo == t[i].expo) {//repeated input
			t[i].expo = expo;
			t[i].coef = coef;
			return;
		}
		if (expo > t[i].expo) {
			flag = i;
			break;
		}
	}
	//因為新數據要插在flag上,所以從flag開始,所有舊數據往後移
		//找尾巴
	for (i = 0; i < 10; i++) //fine tail
		if (t[i].coef == 0) {
			tail = i;
			break;
		}
	if (tail == 0) {
		t[flag].expo = expo;
		t[flag].coef = coef;
		return;
	}
	//開搬
	for (i = tail; i > flag; i--) {
		t[i].expo = t[i - 1].expo;
		t[i].coef = t[i - 1].coef;
	}

	//finally insert data in flag place
	t[flag].expo = expo;
	t[flag].coef = coef;

	return;
}

void inputLinkTerms(linkedPolynomialTerm*& headPtr, int coef, int expo)
{

	// add your code here	
	if (coef == 0)
		return;

	linkedPolynomialTerm* newPtr = new linkedPolynomialTerm; newPtr->coef = coef; newPtr->expo = expo; newPtr->nextTermPtr = nullptr;

	if (headPtr == nullptr) {//first one
		headPtr = newPtr;
		return;
	}
	if (newPtr->expo > headPtr->expo) {//新加的次方最大
		newPtr->nextTermPtr = headPtr;
		headPtr = newPtr;
		return;
	}
	if (newPtr->expo == headPtr->expo) {//新加的次方一樣
		newPtr->nextTermPtr = headPtr->nextTermPtr;
		headPtr = newPtr;
		return;
	}

	linkedPolynomialTerm* currPtr = new linkedPolynomialTerm, * prePtr;
	prePtr = headPtr;
	currPtr = prePtr->nextTermPtr;

	while (1) {//inserting

		if (currPtr == nullptr) {//尾
			prePtr->nextTermPtr = newPtr;
			return;
		}
		else if (newPtr->expo > currPtr->expo) {//停在哪個間隔
			prePtr->nextTermPtr = newPtr;
			newPtr->nextTermPtr = currPtr;
			return;
		}
		else if (newPtr->expo == currPtr->expo) {//如果相同直接覆蓋//如果第二個就相同
			prePtr->nextTermPtr = newPtr;
			newPtr->nextTermPtr = currPtr->nextTermPtr;
			return;
		}

		prePtr = currPtr;
		currPtr = currPtr->nextTermPtr;
	}
}


void addArrayBasedPoly(polynomialTerm a[], polynomialTerm b[], polynomialTerm d[])
{// add your code here
	int i, j, k;
	polynomialTerm temp[10];
	clear(temp);
	//陣列: 0 1 2 3 4 5 6 7 8 9
	//次方: 9 8 7 6 5 4 3 2 1 0(高到低 沒有就是零
	   //a: 8 7 5 4 1 0
	   //   i
	   //b: 9 8 6 3 2 1 0
	   //     j
	   //d: 9 k
	for (i = 0, j = 0, k = 0; ;) {
		if (a[i].coef == 0 && b[j].coef == 0)
			break;

		if (a[i].expo > b[j].expo) {
			//存入d
			temp[k].expo = a[i].expo;
			temp[k].coef = a[i].coef;

			i++;
			k++;

		}
		else if (a[i].expo == b[j].expo) {
			temp[k].expo = a[i].expo;
			temp[k].coef = a[i].coef + b[j].coef;

			i++;
			j++;
			k++;
		}
		else if (a[i].expo < b[j].expo) {
			//存入d
			temp[k].expo = b[j].expo;
			temp[k].coef = b[j].coef;

			j++;
			k++;
		}
	}
	/*
	for (i = 0; i < 10; i++) {
		cout << temp[i].coef << " ";
	}
	cout << endl;
	for (i = 0; i < 10; i++) {
		cout << temp[i].expo << " ";
	}
	cout << endl << endl;*/

	for (i = 0, j = 0; i < 10; i++) {//開搬
		if (temp[i].coef != 0) {
			d[j].coef = temp[i].coef;
			d[j].expo = temp[i].expo;
			j++;
		}
	}
	/*
	for (i = 0; i < 10; i++) {
		cout << d[i].coef << " ";
	}
	cout << endl;
	for (i = 0; i < 10; i++) {
		cout << d[i].expo << " ";
	}
	*/
	
	return;
}

linkedPolynomialTerm* addLinkBasedPoly(linkedPolynomialTerm* aPtr, linkedPolynomialTerm* bPtr)
{
	// add your code here
	linkedPolynomialTerm* dPtr = nullptr, * dcurrPtr = nullptr;
	linkedPolynomialTerm* acurrPtr = aPtr;
	linkedPolynomialTerm* bcurrPtr = bPtr;
	linkedPolynomialTerm* newPtr;
	/*show(acurrPtr);
	cout << endl;
	show(bcurrPtr);
	cout << endl;
	*/
	while (1)
	{

		if (acurrPtr == nullptr && bcurrPtr == nullptr)
			break;
		//cout << 'w';
		newPtr = new linkedPolynomialTerm;

		if (acurrPtr != nullptr && bcurrPtr != nullptr && (acurrPtr->expo == bcurrPtr->expo))//次方相等
		{
			//cout << "a" << endl;
			newPtr->expo = acurrPtr->expo;
			newPtr->coef = acurrPtr->coef + bcurrPtr->coef;
			newPtr->nextTermPtr = nullptr;

			if (newPtr->coef == 0) {
				acurrPtr = acurrPtr->nextTermPtr;
				bcurrPtr = bcurrPtr->nextTermPtr;
				continue;//原本這裡放break整個跳出去了
			}
			else if (dPtr == nullptr) { //頭相等
				dPtr = newPtr;
				dcurrPtr = dPtr;
			}
			else {
				dcurrPtr->nextTermPtr = newPtr;
			}
			dcurrPtr = newPtr;
			acurrPtr = acurrPtr->nextTermPtr;
			bcurrPtr = bcurrPtr->nextTermPtr;
		}
		else if (acurrPtr != nullptr && (bcurrPtr == nullptr || acurrPtr->expo > bcurrPtr->expo))//a次方較高
		{
			//cout << "b" << endl;
			newPtr->expo = acurrPtr->expo;
			newPtr->coef = acurrPtr->coef;
			newPtr->nextTermPtr = nullptr;

			if (dPtr == nullptr) {
				dPtr = newPtr;
				dcurrPtr = dPtr;
			}
			else {
				dcurrPtr->nextTermPtr = newPtr;
			}
			dcurrPtr = newPtr;
			acurrPtr = acurrPtr->nextTermPtr;
		}
		else if (bcurrPtr != nullptr && (acurrPtr == nullptr || bcurrPtr->expo > acurrPtr->expo))//b次方較高
		{
			//cout << "c" << endl;
			newPtr->expo = bcurrPtr->expo;
			newPtr->coef = bcurrPtr->coef;
			newPtr->nextTermPtr = nullptr;

			if (dPtr == nullptr) {
				dPtr = newPtr;
				dcurrPtr = dPtr;
			}
			else {
				dcurrPtr->nextTermPtr = newPtr;
			}
			dcurrPtr = newPtr;
			bcurrPtr = bcurrPtr->nextTermPtr;
		}
	}
	//依展示函數做修改
	/*
	if (dPtr == nullptr)//三個都是空的
	{
		//cout << 't';
		dPtr = new linkedPolynomialTerm;
		dPtr->coef = 0; dPtr->expo = 0; dPtr->nextTermPtr = nullptr;
		
	}*/
	return dPtr;
}

void printArrayBasedPoly(polynomialTerm terms[])
{
	if (terms[0].coef == 0) {
		cout << terms[0].coef;//偷改簡潔方便，那串列順便
		return;
	}

	if (terms[0].expo == 0)
		cout << terms[0].coef;
	else
		cout << terms[0].coef << "X^" << terms[0].expo;

	for (int i = 1; i < MAX_TERMS; i++) {
		if (terms[i].coef == 0)
			return;

		if (terms[i].expo == 0)
			cout << " + " << terms[i].coef;
		else
			cout << " + " << terms[i].coef << "X^" << terms[i].expo;
	}
}

void printLinkBasedPoly(linkedPolynomialTerm* polyPtr)
{
	linkedPolynomialTerm* termPtr = polyPtr;

	if (termPtr == nullptr) {
		cout << "0";//如果傳進來的的是nullptr，便print 0(零多項式)
		return;
	}

	if (termPtr->expo == 0)
		cout << termPtr->coef;
	else
		cout << termPtr->coef << "X^" << termPtr->expo;

	termPtr = termPtr->nextTermPtr;

	while (termPtr != nullptr) {

		if (termPtr->coef == 0)
			return;

		if (termPtr->expo == 0)
			cout << " + " << termPtr->coef;
		else
			cout << " + " << termPtr->coef << "X^" << termPtr->expo;

		termPtr = termPtr->nextTermPtr;
	}
}

int main()//int _tmain(int argc, _TCHAR* argv[])
{
	polynomialTerm a[MAX_TERMS], b[MAX_TERMS], d[MAX_TERMS];
	linkedPolynomialTerm* aPtr, * bPtr, * dPtr;

	int coef, expo;

	aPtr = bPtr = dPtr = nullptr;


	while (1) {
		clear(a); clear(b); clear(d);
		clear(aPtr); clear(bPtr); clear(dPtr);

		for (int i = 0; i < MAX_TERMS; i++) {
			cout << "\ninput a's coefficient and exponent: ";
			cin >> coef >> expo;

			if (expo == 0 && coef == 0)
				break;

			inputTerms(a, coef, expo);
			inputLinkTerms(aPtr, coef, expo);
			//show(aPtr);
		}

		cout << "\n\na = ";
		printArrayBasedPoly(a);
		cout << "\na = ";
		printLinkBasedPoly(aPtr);
		cout << "\n";

		for (int i = 0; i < MAX_TERMS; i++) {
			cout << "\ninput b's coefficient and exponent: ";
			cin >> coef >> expo;

			if (expo == 0 && coef == 0)
				break;

			inputTerms(b, coef, expo);
			inputLinkTerms(bPtr, coef, expo);
			//show(bPtr);
		}

		cout << "\n\nb = ";
		printArrayBasedPoly(b);

		cout << "\nb = ";
		printLinkBasedPoly(bPtr);

		cout << "\n";

		// d =a + b, where a, b, and d are polynomials
		addArrayBasedPoly(a, b, d);
		cout << "\na + b = ";
		printArrayBasedPoly(d);

		dPtr = addLinkBasedPoly(aPtr, bPtr);
		cout << "\na + b = ";
		printLinkBasedPoly(dPtr);

		cout << "\n";
	}
	return 0;
}

// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
