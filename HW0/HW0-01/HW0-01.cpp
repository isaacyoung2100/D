// HW0-01.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//


#include "stdio.h"
#include "stdlib.h"
#include "iostream"

using namespace std;

#define MAX 5

struct Node
{
	int item;
	Node* next;
};

typedef Node* nodePtr;

Node* inputData(int num, nodePtr headPtr)
{
	nodePtr currentPtr = headPtr;

	nodePtr tmpPtr = (nodePtr)malloc(sizeof(Node));
	tmpPtr->item = num;
	tmpPtr->next = NULL;

	if (headPtr == NULL)
		return tmpPtr;
	else {
		while (currentPtr->next != NULL)
			currentPtr = currentPtr->next;

		currentPtr->next = tmpPtr;

		return headPtr;
	}
}

void printArrayForward(int A[])
{
	//Enter your code
	for (int i = 0; i < MAX; i++)
		printf("%d ", A[i]);
}


void printArrayBackward(int A[], int i)
{
	//Enter your code
	if (i == MAX)
		return;
	else
		printArrayBackward(A, i+1);

	printf("%d ", A[i]);
}

void printListForward(nodePtr ptr)
{
	//Enter your code
	while (1) {
		if (ptr == NULL)
			break;
		printf("%d ", ptr->item);
		ptr = ptr->next;
	}
}

void printListBackward(nodePtr ptr)
{
	//Enter your code
	if (ptr == NULL)
		return;
	else
		printListBackward(ptr->next);

	printf("%d ", ptr->item);
}

int main()
{
	int num;
	int A[MAX] = { 0 };
	nodePtr headPtr = NULL;

	printf("Input %d numbers: ", MAX);

	for (int i = 0; i < MAX; i++) {
		cin >> num;
		A[i] = num;
		headPtr = inputData(num, headPtr);
	}

	printf("\nArray Forward Iteratively:  ");
	printArrayForward(A);
	printf("\nArray Backward Recursively: ");
	printArrayBackward(A, 0);

	printf("\nList Forward Iteratively:  ");
	printListForward(headPtr);
	printf("\nList Backward Recursively: ");
	printListBackward(headPtr);

	printf("\n");
	system("PAUSE");
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
