// HW5.cpp : 定義主控台應用程式的進入點。
//

//#include "stdafx.h"
#include <iostream>
using namespace std;

#define MAX_TERMS 10 /*size of terms array*/

class PolynomialTerm {
public:
	int coef;
	int expo;
};                                                                          /////

class ArrayPolynomial {                                        /////
public:                                                                  /////
	PolynomialTerm terms[MAX_TERMS]; /////

	void clear() /////
	{
		for (int i = 0; i < MAX_TERMS; i++) {
			terms[i].coef = 0;
			terms[i].expo = 0;
		}

		return;
	}

	void inputTerms(int coef, int expo) /////
	{
// add your code here
		if (coef == 0)
			return;
		int flag, i, tail;
		for (i = 0; i < 10; i++) {//find where should the new element to insert
			if (expo == terms[i].expo) {//repeated input
				terms[i].expo = expo;
				terms[i].coef = coef;
				return;
			}
			if (expo > terms[i].expo) {
				flag = i;
				break;
			}
		}
		//因為新數據要插在flag上,所以從flag開始,所有舊數據往後移
			//找尾巴
		for (i = 0; i < 10; i++) //fine tail
			if (terms[i].coef == 0) {
				tail = i;
				break;
			}
		if (tail == 0) {
			terms[flag].expo = expo;
			terms[flag].coef = coef;
			return;
		}
		//開搬
		for (i = tail; i > flag; i--) {
			terms[i].expo = terms[i - 1].expo;
			terms[i].coef = terms[i - 1].coef;
		}

		//finally insert data in flag place
		terms[flag].expo = expo;
		terms[flag].coef = coef;

		return;
	}

	void addArrayBasedPoly(ArrayPolynomial& a, ArrayPolynomial& b) /////
	{// add your code here
		int i, j, k;
		PolynomialTerm temp[10];
		//clear(temp);
	
		for ( i = 0; i < MAX_TERMS ; i++) {
			temp[i].coef = 0;
			temp[i].expo = 0;
		}	

		for (i = 0, j = 0, k = 0; ;) {
			if (a.terms[i].coef == 0 && b.terms[j].coef == 0)
				break;

			if (a.terms[i].expo > b.terms[j].expo) {
				temp[k].expo = a.terms[i].expo;
				temp[k].coef = a.terms[i].coef;
				i++;k++;
			}
			else if (a.terms[i].expo == b.terms[j].expo) {
				temp[k].expo = a.terms[i].expo;
				temp[k].coef = a.terms[i].coef + b.terms[j].coef;
				i++;j++;k++;
			}
			else if (a.terms[i].expo < b.terms[j].expo) {
				temp[k].expo = b.terms[j].expo;
				temp[k].coef = b.terms[j].coef;
				j++; k++;
			}
		}

		for (i = 0, j = 0; i < 10; i++) {//開搬
			if (temp[i].coef != 0) {
				terms[j].coef = temp[i].coef;
				terms[j].expo = temp[i].expo;
				j++;
			}
		}
	}

	void reverseArrayBasedPoly() /////
	{// add your code here
		int i=0, j, k;
		int last;
		
		//find last one
		while (true){
			if (terms[0].coef == 0)	return;//只有一項的 下面都不用做 直接回傳
			
			if (terms[i].coef == 0)
				break;
			i++;
		} 
		last = i-1;
		
		//switch
		for (i = 0, j = last; ;i++, j--) {
			int t1, t2;
			t1 = terms[i].coef;//換係數
			terms[i].coef = terms[j].coef;
			terms[j].coef = t1;
			
			t2 = terms[i].expo;//換指數
			terms[i].expo = terms[j].expo;
			terms[j].expo = t2;
		
			if (i == j || (i + 1) == j)	
				break;
		}
		return;
	}

	void printArrayBasedPoly() /////
	{
		if (terms[0].coef == 0)
			return;

		if (terms[0].expo == 0)
			std::cout << terms[0].coef;
		else
			std::cout << terms[0].coef << "X^" << terms[0].expo;

		for (int i = 1; i < MAX_TERMS; i++) {
			if (terms[i].coef == 0)
				return;

			if (terms[i].expo == 0)
				std::cout << " + " << terms[i].coef;
			else
				std::cout << " + " << terms[i].coef << "X^" << terms[i].expo;
		}

		return;
	}

	int compute(int x)
	{
// add your code here
		int a, b, c, ans = 0, num;
		for (a = 0; a < MAX_TERMS; a++)
		{
			num = 1;
			for (b = 0; b < terms[a].expo; b++)
			{
				num = num * x;
			}
			ans += num * terms[a].coef;
		}

		return ans;


		return 0;
	}
};

class LinkedPolynomialTerm {
public:
	int coef;
	int expo;
	LinkedPolynomialTerm* nextTermPtr; /////
};                                                                  /////

class LinkPolynomial {                                /////
public:                                                          /////
	LinkedPolynomialTerm* polynomialTermPtr = nullptr; /////

	void clear() /////
	{
		LinkedPolynomialTerm* tmpPtr, *headPtr;

		while (polynomialTermPtr != nullptr) {
			tmpPtr = polynomialTermPtr;
			polynomialTermPtr = polynomialTermPtr->nextTermPtr;
			delete tmpPtr;
		}

		return;
	}

	void inputLinkTerms(int coef, int expo) /////
	{

		// add your code here	
		if (coef == 0)
			return;

		LinkedPolynomialTerm* newPtr = new LinkedPolynomialTerm; newPtr->coef = coef; newPtr->expo = expo; newPtr->nextTermPtr = nullptr;

		if (polynomialTermPtr == nullptr) {//first one
			polynomialTermPtr = newPtr;
			return;
		}
		if (newPtr->expo > polynomialTermPtr->expo) {//新加的次方最大
			newPtr->nextTermPtr = polynomialTermPtr;
			polynomialTermPtr = newPtr;
			return;
		}
		if (newPtr->expo == polynomialTermPtr->expo) {//新加的次方一樣
			newPtr->nextTermPtr = polynomialTermPtr->nextTermPtr;
			polynomialTermPtr = newPtr;
			return;
		}

		LinkedPolynomialTerm* currPtr = new LinkedPolynomialTerm, * prePtr;
		prePtr = polynomialTermPtr;
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

	void addLinkBasedPoly(LinkPolynomial& aPol, LinkPolynomial& bPol) /////
	{
		// add your code here
		LinkedPolynomialTerm* dcurrPtr = nullptr;
		LinkedPolynomialTerm* acurrPtr = aPol.polynomialTermPtr;
		LinkedPolynomialTerm* bcurrPtr = bPol.polynomialTermPtr;
		LinkedPolynomialTerm* newPtr;
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
			newPtr = new LinkedPolynomialTerm;

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
				else if (polynomialTermPtr == nullptr) { //頭相等
					polynomialTermPtr = newPtr;
					dcurrPtr = polynomialTermPtr;
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

				if (polynomialTermPtr == nullptr) {
					polynomialTermPtr = newPtr;
					dcurrPtr = polynomialTermPtr;
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

				if (polynomialTermPtr == nullptr) {
					polynomialTermPtr = newPtr;
					dcurrPtr = polynomialTermPtr;
				}
				else {
					dcurrPtr->nextTermPtr = newPtr;
				}
				dcurrPtr = newPtr;
				bcurrPtr = bcurrPtr->nextTermPtr;
			}
		}
	
	}

	void reverseLinkBasedPoly() /////
	{// add your code here
		PolynomialTerm temp[MAX_TERMS];
		int i=0, j, k, counter=0;
		LinkedPolynomialTerm* tempPtr = polynomialTermPtr;
		if (tempPtr == nullptr)
			return;
		
		//複製進陣列
		while (tempPtr){
			temp[i].coef = tempPtr->coef;
			temp[i].expo = tempPtr->expo;
			tempPtr = tempPtr->nextTermPtr; i++; counter++;
		}

		//開始改內容
		for (tempPtr = polynomialTermPtr, i = counter - 1; ; i--, tempPtr = tempPtr->nextTermPtr) {
			tempPtr->coef = temp[i].coef;
			tempPtr->expo = temp[i].expo;
			
			if (i == 0)
				break;
		}
		return;
	}

	void printLinkBasedPoly()                                                            /////
	{
		LinkedPolynomialTerm* termPtr = polynomialTermPtr; /////

		if (termPtr == nullptr)
			return;

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

		return;
	}

	int compute(int x)
	{
// add your code here
		int count = 0, add, a, b, c;
		LinkedPolynomialTerm* find;
		find = polynomialTermPtr;
		if (find == nullptr)
			return 0;
		for (;;)
		{
			add = 1;
			for (a = 0; a < find->expo; a++)
			{
				add = add * x;
			}
			count += find->coef * add;
			if (find->nextTermPtr == nullptr)
				break;
			find = find->nextTermPtr;
		}
		return count;
	}
};

int main()//int _tmain(int argc, _TCHAR* argv[])
{
	ArrayPolynomial a, b, d;                                                              /////
	LinkPolynomial aPol, bPol, dPol;                                             /////

	int coef, expo, x;

	// aPtr = bPtr = dPtr = nullptr; /////

	while (1) {
		a.clear(); b.clear(); d.clear();                                    /////
					  // aPtr->clear(aPtr); bPtr->clear(bPtr); dPtr->clear(dPtr); /////


		for (int i = 0; i < MAX_TERMS; i++) {
			cout << "\ninput a's coefficient and exponent: ";
			cin >> coef >> expo;

			if (expo == 0 && coef == 0)
				break;

			a.inputTerms(coef, expo);             /////
			aPol.inputLinkTerms(coef, expo); /////
		}

		cout << "\n\na = ";
		a.printArrayBasedPoly();     /////
		cout << "\na = ";
		aPol.printLinkBasedPoly(); /////
		cout << "\n";

		for (int i = 0; i < MAX_TERMS; i++) {
			cout << "\ninput b's coefficient and exponent: ";
			cin >> coef >> expo;

			if (expo == 0 && coef == 0)
				break;

			b.inputTerms(coef, expo);             /////
			bPol.inputLinkTerms(coef, expo); /////
		}

		cout << "\n\nb = ";
		b.printArrayBasedPoly();      /////

		cout << "\nb = ";
		bPol.printLinkBasedPoly(); /////

		cout << "\n";

		// d =a + b, where a, b, and d are polynomials

		d.addArrayBasedPoly(a, b); /////
		cout << "\na + b = ";
		d.printArrayBasedPoly();     /////

		dPol.addLinkBasedPoly(aPol, bPol); /////
		cout << "\na + b = ";
		dPol.printLinkBasedPoly();               /////

		cout << "\n";

		d.reverseArrayBasedPoly(); /////
		cout << "\nreversed d = ";
		d.printArrayBasedPoly();     /////

		dPol.reverseLinkBasedPoly(); /////
		cout << "\nreversed d = ";
		dPol.printLinkBasedPoly();               /////

		cout << "\n";

		cout << "\ninput X: ";
		cin >> x;

		cout << "\nd = ";
		cout << d.compute(x);      //////

		cout << "\nd = ";
		cout << dPol.compute(x); //////

		cout << "\n";

		aPol.clear(); bPol.clear(); dPol.clear(); /////
	}

	return 0;
}
