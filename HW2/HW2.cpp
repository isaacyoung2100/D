// HW2.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//
#include <stdio.h>
#include "memory.h"
#include<iostream>
using namespace std;

#define MAX_degree 10 /*MAX degree of polynomial+1*/

typedef struct {
	int degree;
	int coef[MAX_degree];
} polynomial;

#define MAX_TERMS 20 /*size of terms array*/
typedef struct {
	int coef;
	int expo;
} polynomial_term;

polynomial_term terms[MAX_TERMS];
int avail = 0;

polynomial Zero(polynomial p)
{
	memset(&p, 0, sizeof(p));

	return p;
}

int IsZero(polynomial p)
{// add your code	零多項式回傳1
	for (int i = 0; i <= p.degree ; i++) {
		if (p.coef[i] != 0) {//代表係數中有值
			return 0;
		}
	}
	
	return 1;
}

int Lead_Exp(polynomial p)//return leading power
{
	return p.degree;
}

int COMPARE(int i, int j)
{// add your code	
	if (i < j)
		return -1;
	else if (i == j)
		return 0;
	else 
		return 1;
}

int Coef(polynomial p, int expo)//return 該項係數
{
	return p.coef[expo];
}

polynomial Attach(polynomial p, int coef, int expo)//p3 是 degree為零,ceo[10]陣列全為零 的結構
{// add your code	
	if (expo > p.degree)//the part of leading degree//這需要嗎哈哈
		p.degree = expo;
	
	p.coef[expo] = p.coef[expo] + coef;//the part of each ceof

	return p;//回傳結構
}

polynomial Remove(polynomial p, int expo)
{// add your code	
	p.coef[expo] = 0;//set that coefficient to 0

	for (int i = p.degree; i >= 0; i--) {//search and renew degree
		if (p.coef[i] != 0) {//i is power
			p.degree = i;
			
			break;
		}
	}
	return p;
}

void attach(int coef, int expo)
{
	if (avail >= MAX_TERMS)
		return;

	terms[avail].coef = coef;
	terms[avail++].expo = expo;
}

void PrintPoly1(polynomial p)
{
	for (int i = p.degree; i >= 0; i--) {
		if (p.coef[i] != 0) {
			if (p.degree == i) {
				if (i == 0)
					printf("%d", p.coef[i]);
				else
					printf("%dX^%d", p.coef[i], i);
			}
			else {
				if (i == 0)
					printf(" + %d", p.coef[i]);
				else
					printf(" + %dX^%d", p.coef[i], i);
			}
		}
	}
}

void PrintPoly2(polynomial_term t[], int start, int finish)
{// add your code	
	int j = start;
	for (int i = start; i <= finish; i++) {
		if (i != start) 
			cout << " + ";
		
		if (t[i].expo == 0) {
			cout << t[i].coef;
			break;
		}
		
		cout << t[i].coef << "X^" << t[i].expo ;
	}

}

polynomial padd1(polynomial p1, polynomial p2)
{
	polynomial p3;
	int sum;

	p3.degree = 0;
	p3 = Zero(p3);

	while (!IsZero(p1) && !IsZero(p2)) {//if both are not zero polynominal 全零回傳1

		switch (COMPARE(Lead_Exp(p1), Lead_Exp(p2))) {//Lead_Exp return that degree//compare which poly is bigger//lead_exp p.degree
		case -1://a < b == p1 < p2
			p3 = Attach(p3, Coef(p2, Lead_Exp(p2)), Lead_Exp(p2));//return that coe,here is leading one//attach 1.leading power and 2.its coefficient to p3
			p2 = Remove(p2, Lead_Exp(p2));//remove 1.leading exo and 2.its coe // which implies the second huge item should be leading
			break;
		
		case  0:
			sum = Coef(p1, Lead_Exp(p1)) + Coef(p2, Lead_Exp(p2));

			if (sum)
				p3 = Attach(p3, sum, Lead_Exp(p1));

			p1 = Remove(p1, Lead_Exp(p1));
			p2 = Remove(p2, Lead_Exp(p2));
			break;
		
		case 1:
			p3 = Attach(p3, Coef(p1, Lead_Exp(p1)), Lead_Exp(p1));
			p1 = Remove(p1, Lead_Exp(p1));
		}
	}//run until both p1, p2 to become zero poly

	while (!IsZero(p1)) {
		p3 = Attach(p3, Coef(p1, Lead_Exp(p1)), Lead_Exp(p1));
		p1 = Remove(p1, Lead_Exp(p1));
	}
	while (!IsZero(p2)) {
		p3 = Attach(p3, Coef(p2, Lead_Exp(p2)), Lead_Exp(p2));
		p2 = Remove(p2, Lead_Exp(p2));
	}

	return p3;
}

void padd2(int starta, int finisha, int startb, int finishb, int* startd, int* finishd)
{
	int sum;

	*startd = avail;

	while (starta <= finisha && startb <= finishb) {
		switch (COMPARE(terms[starta].expo, terms[startb].expo)) {
		case -1:
			attach(terms[startb].coef, terms[startb].expo);
			startb++;
			break;
		case  0:
			sum = terms[starta].coef + terms[startb].coef;

			if (sum)
				attach(sum, terms[starta].expo);
			starta++;
			startb++;
			break;
		case 1:
			attach(terms[starta].coef, terms[starta].expo);
			starta++;
		}
	}

	for (; starta <= finisha; starta++)
		attach(terms[starta].coef, terms[starta].expo);
	for (; startb <= finishb; startb++)
		attach(terms[startb].coef, terms[startb].expo);

	*finishd = avail - 1;
}

int main()//main function
{
	//polynomial_term: 是每項的係數與次方
	//polynomial     : 是此多項式Leading power,及係數們
	polynomial a, b, d;
	int coef, expo, sum;

	int starta = 0, finisha, startb, finishb, startd, finishd;
	//create a array that size is max_term=20, and the type of this array is [polynomial_term], every element is set to 0
	memset(terms, 0, sizeof(terms));//term store both arrays

	a.degree = b.degree = d.degree = 0;
	//申請內存並將其初始化為零
	a = Zero(a);
	b = Zero(b);
	d = Zero(d);

	while (1) {//insert the first polynomial: a[]
		printf("\ninput a's coefficient and exponent: ");
		scanf_s("%d %d", &coef, &expo);

		if (expo == 0 && coef == 0)
			break;

		a.coef[expo] = coef;//insert coefficient respectively

		if (expo > a.degree)
			a.degree = expo;
		//record int terms
		terms[avail].coef = coef;
		terms[avail].expo = expo;
		avail++;
	}

	finisha = avail - 1;//where array a[] stoped(前面多加減掉
	startb = avail;//where array b[] started

	printf("\n\na = ");
	PrintPoly1(a);//print out
	printf("\na = ");
	PrintPoly2(terms, starta, finisha);//print out
	printf("\n");

	while (1) {//insert the second polynomial: b[]
		printf("\ninput b's coefficient and exponent: ");
		scanf_s("%d %d", &coef, &expo);

		if (expo == 0 && coef == 0)
			break;

		b.coef[expo] = coef;

		if (b.degree < expo)
			b.degree = expo;

		terms[avail].coef = coef;
		terms[avail].expo = expo;
		avail++;
	}

	finishb = avail - 1; //(前面多加減掉

	printf("\n\nb = ");
	PrintPoly1(b);//print out
	printf("\nb = ");
	PrintPoly2(terms, startb, finishb);//print out

	/* d =a + b, where a, b, and d are polynomials */

	d = padd1(a, b);//重頭戲1
	printf("\n\nd = ");
	PrintPoly1(d);//print out

	padd2(starta, finisha, startb, finishb, &startd, &finishd);//重頭戲2
	printf("\nd = ");
	PrintPoly2(terms, startd, finishd);//print out

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
