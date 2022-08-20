// HW3.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//


//#include "stdafx.h"
#include <iostream>

using namespace std;

#define MAX_TERMS 10

typedef struct {
	int coef;
	int expo;
} polynomialTerm;

void clear(polynomialTerm t[])
{
	for (int i = 0; i < MAX_TERMS; i++) {
		t[i].coef = 0;
		t[i].expo = 0;
	}

	return;
}

void printArrayBasedPoly(polynomialTerm t[])
{
	if (t[0].coef == 0)
		return;

	if (t[0].expo == 0)
		cout << t[0].coef;
	else
		cout << t[0].coef << "X^" << t[0].expo;

	for (int i = 1; i < MAX_TERMS; i++) {
		if (t[i].coef == 0)
			return;

		if (t[i].expo == 0)
			cout << " + " << t[i].coef;
		else
			cout << " + " << t[i].coef << "X^" << t[i].expo;
	}
}

void inputTerm(polynomialTerm t[], int coef, int expo)
{//    0 1 2 3 4
	// 1 2 3 4 0
	// 2 1 2 3 4
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

	for (i = 0; i < 10; i++) {
		cout << temp[i].coef << " ";
	}
	cout << endl;
	for (i = 0; i < 10; i++) {
		cout << temp[i].expo << " ";
	}
	cout << endl <<endl;
	for (i = 0, j = 0 ; i < 10; i++) {
		if (temp[i].coef != 0) {
			d[j].coef = temp[i].coef;
			d[j].expo = temp[i].expo;
			j++;
		}
	}
	for (i = 0; i < 10; i++) {
		cout << d[i].coef << " ";
	}
	cout << endl;
	for (i = 0; i < 10; i++) {
		cout << d[i].expo << " ";
	}
	
	
	return;
}

int main()//_tmain(int argc, _TCHAR* argv[])
{
	polynomialTerm a[MAX_TERMS], b[MAX_TERMS], d[MAX_TERMS];
	int coef, expo;

	while (1) {
		clear(a); clear(b); clear(d);

		for (int i = 0; i < MAX_TERMS; i++) {
			cout << "\ninput a's coefficient and exponent: ";
			cin >> coef >> expo;

			if (expo == 0 && coef == 0)
				break;

			inputTerm(a, coef, expo);

		}
		for (int i = 0; i < 10; i++) {
			cout << a[i].coef << " ";
		}
		cout << endl;
		for (int i = 0; i < 10; i++) {
			cout << a[i].expo << " ";
		}
		cout << endl;

		cout << "\n\na = ";
		printArrayBasedPoly(a);
		cout << "\n";

		for (int i = 0; i < MAX_TERMS; i++) {
			cout << "\ninput b's coefficient and exponent: ";
			cin >> coef >> expo;

			if (expo == 0 && coef == 0)
				break;

			inputTerm(b, coef, expo);
		}

		cout << "\n\nb = ";
		printArrayBasedPoly(b);
		cout << "\n";

		// d =a + b, where a, b, and d are polynomials
		addArrayBasedPoly(a, b, d);
		cout << "\na + b = ";
		printArrayBasedPoly(d);
		cout << "\n";
	}
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
