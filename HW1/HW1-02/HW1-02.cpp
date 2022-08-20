#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
typedef struct node {
    int x;
    struct node* next;
}Node;
//
//pirnt LinkList 很好用的遞迴函數
//
void display(Node* headptr)
{
    if (headptr == nullptr)
        return;
    printf("%d ", headptr->x);
    display(headptr->next);
}
//
//
Node* insert(Node* headptr, Node* newptr)
{
    if (headptr == nullptr)
        return newptr;

    if (newptr->x <= headptr->x) {//first
        newptr->next = headptr;
        headptr = newptr;
    }
    else {
        Node* currptr, * preptr;
        preptr = headptr;   currptr = preptr->next;//前面檢查過不是加在頭前, 讓curr從第二個開始

        while (1) {
            if (currptr == nullptr) {//last
                preptr->next = newptr;
                newptr->next = nullptr;
                break;
            }
            if (newptr->x <= currptr->x) {//middle
                preptr->next = newptr;
                newptr->next = currptr;
                break;
            }

            preptr = preptr->next;
            currptr = currptr->next;
        }
    }
    return headptr;
}
//
//
Node* remove(Node* headptr, int num)
{
    if (headptr->x == num) {//斷頭
        return headptr->next;//可能剩最後一個，這樣回傳的就是nullptr
    }
    else {
        Node* preptr = headptr, * currptr = headptr->next;

        while (1) {
            if (currptr->x == num) {
                while (currptr->next != nullptr && currptr->next->x == num) {//may have more than one repeated numbers
                    currptr = currptr->next;
                }
                preptr->next = currptr->next;
                break;
            }
            preptr = preptr->next;
            currptr = currptr->next;
        }
    }
    return headptr;
}
//
//
//
int main()
{
    Node* headptr, * newptr, * currenptr, * nextptr;//四個必需指標
    headptr = nullptr;

    int sum = 0;

    char c;
    while (1) {
        fflush(stdin);
        printf("Input or Delete?(i\\d)");
        cin >> c;

        if (c == 'i' || c == 'I') {
            printf("Input which integer?");
            newptr = new Node();//將新數據存在newptr中
            cin >> newptr->x;newptr->next = nullptr;

            headptr = insert(headptr, newptr);
            cout << endl;
        }
        else {
            printf("Delete which integer?");
            int num;
            cin >> num;

            headptr = remove(headptr, num);
            cout << endl;
        }

        //printf("sum= %d\n", sum);
        display(headptr);
        printf("\n\n");
        //不能太早優化
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
