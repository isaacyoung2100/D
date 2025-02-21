﻿#include "stdio.h"
#include "stdlib.h"
#include <iostream>
#include <string>

using namespace std;

void input(string sMessage, string& sInputString)
{
    cout << sMessage << endl;
    cin >> sInputString;

    return;
}

void writeBackwardI(string s)
{
    int length = s.size();

    if (length == 0)  // base case 
        return;

    for (int i = length - 1; i >= 0; i--)
        cout << s[i];
}

void writeBackwardR1(string s)
{
    int length = s.size();

    if (length == 0)  // base case 
        return;

    cout << s[length - 1];
    writeBackwardR1(s.substr(0, length - 1));
}

void writeBackwardR2(string s)
{
    int length = s.size();

    if (length == 0)  // base case 
        return;

    writeBackwardR2(s.substr(1, length - 1));
    cout << s[0];
}


int countI(string s, char c)
{
    int counter = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == c)
            counter++;
    }
    return counter;
}

int countR(string s, char c)
{
    int length = s.size(), co = 0;
    if (length == 0)
        return 0;

    if (c == s[0])
        co = 1;

    return (co + countR(s.substr(1, length - 1), c));
}

unsigned char findI(string s)
{
    char min = s[0];
    for (int i = 0; i < s.size(); i++)
        if (s[i] < min)
            min = s[i];

    return min;
}

char findR(string s)
{
    int min, now;
    int length = s.size();
    if (length == 1)
        return s.at(0);

    --length;
    now = s.at(length);
    min = findR(s.substr(0, length));
    return (min < now ? min : now);
}

string removeI(string s)
{
    int length = s.size();
    int a, b, c = length - 1;
    for (a = 0; a < c; a++)
    {
        if (s[a] == s[a + 1])
        {
            for (b = a; b < length - 1; b++)
            {
                s[b] = s[b + 1];
            }
            s[length - 1] = ' ';
            a--;
            c--;
        }
    }
    return s;
}

string removeR(string s)
{
    int size = s.size();
    if (size == 1)
        return s;

    string a;
    a = removeR(s.substr(1, size - 1));

    if (a.at(0) == s.at(0)) {
        return a;
    }
    else if (a.at(0) != s.at(0)) {
        string ans;
        ans = s.at(0) + a;
        return ans;
    }
}

int TI(int m, int n)
{
    int ans = 0;
    if (m == 0 || n == 0)
        return 0;
    if (m > n)
    {
        for (int a = 0; a < n; a++)
        {
            ans = ans + m;
        }
        return ans;
    }
    else {
        for (int a = 0; a < m; a++)
        {
            ans = ans + n;
        }
        return ans;
    }

    /*
     T(m, n) = 0, if m = 0 or n = 0
     T(m, n) = m + ... + m (n times), if m > n
     T(m, n) =  n + ... + n (m times), otherwise
    */

    return m * n;
}

int TR(int m, int n)
{
    if (m == 0 || n == 0)
        return 0;
    if (m > n)
    {
        return m + TR(m, n - 1);
    }
    else
    {
        return n + TR(m - 1, n);
    }
    /*
     T(m, n) = 0, if m = 0 or n = 0
     T(m, n) = m + T( m, n - 1 ), if m > n
     T(m, n) =  n + T( m - 1, n ), otherwise
    */
}

int main()
{
    string commandStr;
    string inputStr, appendStr;
    char inputChr;
    int m, n;

    while (1) {
        input("\nEnter command: "
            "\n I to input a string, A to append a string, B to write the string backward, "
            "\n C to count the given character , F to find the smallest character,"
            "\n R to remove the repeated characters, T to compute, and X to Exit", commandStr);

        if (commandStr == "I" || commandStr == "i") {
            cout << "\nInput the string: ";
            cin >> inputStr;
        }
        else if (commandStr == "A" || commandStr == "a") {
            cout << "\nInput the string: ";
            cin >> appendStr;
            inputStr += appendStr;
            cout << "\nThe new string: " << inputStr << endl;
        }
        else if (commandStr == "B" || commandStr == "b") {
            if (inputStr.length() > 0) {
                cout << endl;
                writeBackwardI(inputStr);
                cout << endl;
                writeBackwardR1(inputStr);
                cout << endl;
                writeBackwardR2(inputStr);
                cout << endl;
            }
        }
        else if (commandStr == "C" || commandStr == "c") {
            if (inputStr != "") {
                cout << "\nInput the character: ";
                cin >> inputChr;
                cout << "\nCount of " << inputChr << ": " << countI(inputStr, inputChr);
                cout << "\nCount of " << inputChr << ": " << countR(inputStr, inputChr) << endl;
            }
        }
        else if (commandStr == "R" || commandStr == "r") {
            if (inputStr != "") {
                cout << endl << "Repeated characters removed: " << removeI(inputStr);
                cout << endl << "Repeated characters removed: " << removeR(inputStr) << endl;;
            }
        }
        else if (commandStr == "F" || commandStr == "f") {
            if (inputStr != "") {
                cout << endl << "Smallest character found: " << findI(inputStr);
                cout << endl << "Smallest character found: " << findR(inputStr) << endl;
            }
        }
        else  if (commandStr == "T" || commandStr == "t")
        {
            cout << "\nInput two values, m and n: ";
            cin >> m >> n;
            cout << endl << "The result is " << TI(m, n);
            cout << endl << "The result is " << TR(m, n) << endl;
        }
        else  if (commandStr == "X" || commandStr == "x")
            return 0;
        else
            cout << "\nUnknown command!";
    }
    return 0;
}