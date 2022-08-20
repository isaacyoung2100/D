
#include <iostream>
using namespace std;

#define MAX_TERMS 10 /*size of terms array*/

class PolynomialTerm {
public:
	int coef;
	int expo;
};

class ArrayPolynomial {
public:
	PolynomialTerm terms[MAX_TERMS];

	void clear() /////
	{
		for (int i = 0; i < MAX_TERMS; i++) {
			terms[i].coef = 0;
			terms[i].expo = 0;
		}

		return;
	}

	void inputTerms(int coef, int expo)
	{
		int i = 0;
		
		for (; terms[i].coef != 0 && i < MAX_TERMS; i++);

		terms[i].coef = coef;
		terms[i].expo = expo;

		return;
	}

	void printArrayBasedPoly()
	{
		if (terms[0].coef == 0)
			return;

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

		return;
	}

	//#print #call findArrayBasedPolyMaxTerm(2-a)
	//2-a
	void showArrayBasedPolyMaxTerm()
	{
		PolynomialTerm term = findArrayBasedPolyMaxTerm(0);//找最大

		if (term.coef == 0)
			return;

		if (term.expo == 0)
			cout << term.coef;
		else
			cout << term.coef << "X^" << term.expo;
	}
	
	//#find Max
	PolynomialTerm findArrayBasedPolyMaxTerm(int i)
	{
		// add yor code here
		if (terms[i].coef == 0)
			return terms[i];
		
		PolynomialTerm term = findArrayBasedPolyMaxTerm(i+1);	
		PolynomialTerm cur = terms[i];

		if (term.expo >= cur.expo && term.coef >= cur.coef)
			return term;
		else
			return cur;

	}

	//#全數向左平移一個(2-e)
	//2-e
	void ArrayBasedRotateTerms() {
		// add yor code here
//#find the position of last item
		int LastOnePosition, i = 0;
		while (terms[i].coef)i++; --i;
		LastOnePosition = i; 

//#0 = temp #0 = 1, 1 = 2, ..., LastOne = temp
		PolynomialTerm temp = terms[0];
		for (i = 0; i <= LastOnePosition; i++) {//Rotate
			if (i == LastOnePosition) {
				terms[i].coef = temp.coef;
				terms[i].expo = temp.expo;
				break;
			}
			terms[i].coef = terms[i+1].coef;
			terms[i].expo = terms[i+1].expo;
		}

		return;
	}

	//#Copy in b array and Modify(2-d)
	void compactCopy(ArrayPolynomial& poly)
	{	
		this->clear();
		//Array a 不能被動刀
		//#如果有同項相加#排序#複製
		// add yor code here
		int i = 0, SIZE = 0;
//#size	
		for (i = 0; poly.terms[i].coef != 0; i++);
		SIZE = i;
		
//#insertion
		int j = 0, AlterSize = 1, flag = 0;

		while (1) {
			if (AlterSize > SIZE) {
				break;
			}
		//#insert one by one
			PolynomialTerm temp;
			temp.coef = poly.terms[j].coef;temp.expo = poly.terms[j].expo;

		//#compare with this terms, and find place to insert
			for (i = 0; i < AlterSize; i++) {
				if (temp.expo >= terms[i].expo) {
					cout << temp.expo << " >= " << terms[i].expo << "  ";
					flag = i;
					break;
				}
			}

		//#insert
			if (temp.expo == terms[flag].expo) {//相等直接該樣相加
				terms[j].coef += terms[j].coef;
			}
			else if(temp.expo > terms[flag].expo){//比較大就要搬
				for (i = (AlterSize - 1); i >= flag; i--) {
					if (i == flag) {
						terms[flag].coef = temp.coef;
						terms[flag].expo = temp.expo;
						
						break;
					}
					terms[i].coef = terms[i - 1].coef;
					terms[i].expo = terms[i - 1].expo;
				}
			}

			j++;
			AlterSize++;
		}

		return;
	}
};

class LinkedPolynomialTerm {
public:
	int coef;
	int expo;
	LinkedPolynomialTerm* nextTermPtr;
};

class LinkedPolynomial {
public:
	LinkedPolynomialTerm* polynomialTermPtr = nullptr;


	void clear()
	{
		LinkedPolynomialTerm* tmpPtr;

		while (polynomialTermPtr != nullptr) {
			tmpPtr = polynomialTermPtr;
			polynomialTermPtr = polynomialTermPtr->nextTermPtr;
			delete tmpPtr;
		}

		return;
	}

	//#Create new item and let it be headPtr
	void inputTerms(int coef, int expo)
	{
		LinkedPolynomialTerm* tmpPtr;

		tmpPtr = new LinkedPolynomialTerm;
		tmpPtr->coef = coef;tmpPtr->expo = expo;
		tmpPtr->nextTermPtr = polynomialTermPtr;

		polynomialTermPtr = tmpPtr;
		// add your code here 
		return;
	}

	void printLinkBasedPoly()
	{
		LinkedPolynomialTerm* termPtr = polynomialTermPtr;

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

	void showLinkBasedPolyMaxTerm()
	{
		LinkedPolynomialTerm* termPtr = findLinkBasedPolyMaxTerm(polynomialTermPtr);

		if (termPtr == nullptr)
			return;

		if (termPtr->expo == 0)
			cout << termPtr->coef;
		else
			cout << termPtr->coef << "X^" << termPtr->expo;
	}
	//LinkedPolynomialTerm* termPtr = findLinkBasedPolyMaxTerm(polynomialTermPtr);
	LinkedPolynomialTerm* findLinkBasedPolyMaxTerm(LinkedPolynomialTerm* currPtr)
	{
		// add yor code here
		if (currPtr->nextTermPtr == nullptr)
			return currPtr;

		LinkedPolynomialTerm* Max = findLinkBasedPolyMaxTerm(currPtr->nextTermPtr);
		return ((Max->expo > currPtr->expo) ? Max : currPtr);
	}

	void LinkBasedRotateTerms() 
	{
		if (polynomialTermPtr->nextTermPtr == nullptr)	return;
		// add yor code here
		LinkedPolynomialTerm* curPtr, *headtmpPtr;
		curPtr = headtmpPtr = polynomialTermPtr;

		polynomialTermPtr = polynomialTermPtr->nextTermPtr;
		while (true)
		{
			if (curPtr->nextTermPtr == nullptr) {
				curPtr->nextTermPtr =headtmpPtr;
				headtmpPtr->nextTermPtr = nullptr;
				break;
			}
			curPtr = curPtr->nextTermPtr;
		}

		return;
	}

	void compactCopy(LinkedPolynomial& poly)
	{
		// add yor code here
		delete polynomialTermPtr;
		polynomialTermPtr = new LinkedPolynomialTerm;

		LinkedPolynomialTerm* headPtr, * curPtr;
		LinkedPolynomialTerm* poheadPtr, * pocurPtr;

		poheadPtr = poly.polynomialTermPtr;
		//#先創頭#複製
		headPtr = new LinkedPolynomialTerm;
		headPtr->coef = poheadPtr->coef;headPtr->expo = poheadPtr->expo;headPtr->nextTermPtr = nullptr;

		pocurPtr = poheadPtr->nextTermPtr;
		while (pocurPtr) {//加身體

			LinkedPolynomialTerm* newPtr = new LinkedPolynomialTerm(); newPtr->coef = pocurPtr->coef; newPtr->expo = pocurPtr->expo; newPtr->nextTermPtr = nullptr;
			//#new 加哪 #加
			LinkedPolynomialTerm* run = headPtr;
			while (run)//找加哪
			{
				if (newPtr->expo > run->expo) {//大
					break;
				}
				if (newPtr->expo == run->expo) {//相等
					run->expo += newPtr->coef;
					break;
				}
				run = run->nextTermPtr;
			}

			if (run == headPtr) {//new比頭大
				newPtr->nextTermPtr = headPtr;
				headPtr = newPtr;
			}
			else if (run == nullptr) {//new 加屁股
				for (run = headPtr; run->nextTermPtr != nullptr; run = run->nextTermPtr);//找尾椎
				run->nextTermPtr = newPtr;
			}
			else { //if(newPtr->coef > run->coef){//new 加身體中間
				curPtr = headPtr;
				while (1) {
					if (curPtr->nextTermPtr == run) {//cur跑到run前面 new插在run前
						curPtr->nextTermPtr = newPtr;
						newPtr->nextTermPtr = run;
						break;
					}
					curPtr = curPtr->nextTermPtr;
				}
			}
			
			pocurPtr = pocurPtr->nextTermPtr;
		}
		polynomialTermPtr = headPtr;
		return;
	}
};
