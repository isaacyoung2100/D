// Array Input or Delete 0-2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include<stdio.h>
#include<stdlib.h>

using namespace std;

int find_add_place(int num, int lenght, int a[])
{
	int site;
	for (int i = 0; i < lenght; i++) {
		if (lenght == 1) {//first one
			site = 0;
			break;
		}
		if (num <= a[i]) {//middle
			site = i;
			break;
		}
		if (i == lenght - 1) {//last one
			site = i;
			break;
		}
	}
	return site;
}
void insert(int number, int length, int site, int a[])
{
	if (site == 0 || site == length - 1) {//insert place is first or last
		a[site] = number;
	}
	else {
		for (int i = length - 1; i >= site; i--)
			a[i] = a[i - 1];

		a[site] = number;
	}
	return;
}
void printout_array(int length, int arr[])
{
	for (int i = 0; i < length; i++) {
		printf("%d ", arr[i]);
	}printf("\n");
	return;
}
int main()
{
	int arr[100], length = 0, number;
	char ans;

	while (1) {
		fflush(stdin);
		printf("Input or Delete?");
		cin >> ans;

		if (ans == 'I' || ans == 'i') {
			length++;

			printf("Input which integer?");
			cin >> number;

			int site;
			site = find_add_place(number, length, arr);//find where the new number should be insert

			insert(number, length, site, arr);
		}
		else {//ans=='D'
			printf("Delete which integer?");
			cin >> number;

			int start, counter = 0;
			for (int i = 0; i < length; i++){//fine where, and how much should be delete
				if (arr[i] == number) {
					start = i, counter++;

					while (arr[++i] == number) 
						counter++;
				}
			}

			for (int i = start; (i + counter) < length; i++)//modify the array
				arr[i] = arr[i + counter];
			length -= counter;
		}

		printout_array(length, arr);
		fflush(stdin);
	}
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
