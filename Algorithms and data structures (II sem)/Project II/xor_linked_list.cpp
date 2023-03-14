#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include<string>

class Node {
public:
        int key;
        uintptr_t ptrXOR;
        Node(int key, uintptr_t ptrXOR) {
                this->key = key;
                this->ptrXOR = ptrXOR;
        }
};

class LinkedList
{
public:
        Node* actual, * next, * prev, * last, * first;

        LinkedList() {
                actual = NULL;
                next = NULL;
                prev = NULL;
                last = NULL;
                first = NULL;
        }

        static uintptr_t ptrToInt(Node* ptr) {
                return reinterpret_cast<uintptr_t>(ptr);
        }

        static Node* intToPtr(uintptr_t integer) {
                return reinterpret_cast<Node*>(integer);
        }

        void moveActualRight() {
                if (actual == NULL || (prev == NULL && next == NULL)) return;
                if (actual == last) {
                        actual = first;
                        prev = NULL;
                        next = intToPtr(first->ptrXOR);
                        return;
                }
                prev = actual;
                actual = next;
                next = intToPtr(ptrToInt(prev) ^ actual->ptrXOR);
        }

        void moveActualLeft() {
                if (actual == NULL || (prev == NULL && next == NULL)) return;
                if (actual == first) {
                        actual = last;
                        next = NULL;
                        prev = intToPtr(last->ptrXOR);
                        return;
                }
                next = actual;
                actual = prev;
                prev = intToPtr(actual->ptrXOR ^ ptrToInt(next));
        }


        void ACTUAL() {
                if (actual != NULL) {
                        printf("                %d\n", actual->key);
                        return;
                }
                printf("                NULL\n");
        }

        void NEXT() {
                moveActualRight();
                ACTUAL();
        }

        void PREV() {
                moveActualLeft();
                ACTUAL();
        }

        void ADD_BEG(int key) {
                if (actual == NULL) {
                        Node* newFirstNode = new Node(key, 0);
                        actual = newFirstNode;
                        first = actual;
                        last = actual;
                }
                else if (prev == NULL) {
                        Node* newFirstNode = new Node(key, ptrToInt(actual));
                        prev = newFirstNode;
                        actual->ptrXOR = ptrToInt(next) ^ ptrToInt(prev);
                        first = prev;
                }
                else {
                        Node* newFirstNode = new Node(key, ptrToInt(first));
                        first->ptrXOR = ptrToInt(newFirstNode) ^ first->ptrXOR;
                        first = newFirstNode;
                }
        }

        void ADD_END(int key) {
                if (actual == NULL) {
                        Node* newLastNode = new Node(key, 0);
                        actual = newLastNode;
                        first = actual;
                        last = actual;
                }
                else if (next == NULL) {
                        Node* newLastNode = new Node(key, ptrToInt(actual));
                        next = newLastNode;
                        actual->ptrXOR = ptrToInt(next) ^ ptrToInt(prev);
                        last = next;
                }
                else {
                        Node* newLastNode = new Node(key, ptrToInt(last));
                        last->ptrXOR = ptrToInt(newLastNode) ^ last->ptrXOR;
                        last = newLastNode;
                }
        }

        void ADD_ACT(int key) {
                if (actual == first) {
                        ADD_BEG(key);
                        return;
                }
                Node* newNode = new Node(key, ptrToInt(actual) ^ ptrToInt(prev));
                uintptr_t prevprev = prev->ptrXOR ^ ptrToInt(actual);
                actual->ptrXOR = ptrToInt(newNode) ^ ptrToInt(next);
                prev->ptrXOR = ptrToInt(newNode) ^ prevprev;
                prev = newNode;
        }

        void DEL_BEG() {
                if (prev == NULL && next == NULL) {
                        delete actual;
                        actual = NULL;
                        last = NULL;
                        first = NULL;
                        return;
                }
                Node* newFirst = intToPtr(first->ptrXOR);
                Node* newSecond = intToPtr(ptrToInt(first) ^ newFirst->ptrXOR);
                if (actual == first) {
                        actual = last;
                        next = NULL;
                        prev = intToPtr(last->ptrXOR);
                }
                if (prev == first) {
                        prev = NULL;
                }
                delete first;
                first = newFirst;
                first->ptrXOR = ptrToInt(newSecond);
        }

        void DEL_END() {
                if (prev == NULL && next == NULL) {
                        delete actual;
                        actual = NULL;
                        last = NULL;
                        first = NULL;
                        return;
                }
                Node* newLast = intToPtr(last->ptrXOR);
                Node* newSecond = intToPtr(ptrToInt(last) ^ newLast->ptrXOR);
                if (actual == last) {
                        actual = newLast;
                        prev = newSecond;
                        next = NULL;
                }
                else if (next == last) {
                        next = NULL;
                }
                delete last;
                last = newLast;
                last->ptrXOR = ptrToInt(newSecond);
        }

        void PRINT_FORWARD(){
                if (actual == NULL) {
                        printf("                NULL\n");
                        return;
                }
                Node* toPrint = first;
                Node* next = intToPtr(first->ptrXOR);
                Node* tmp;
                printf("                ");
                while (next != NULL) {
                        printf("%d ", toPrint->key);
                        tmp = next;
                        next = intToPtr(ptrToInt(toPrint) ^ next->ptrXOR);
                        toPrint = tmp;
                }
                printf("%d \n", toPrint->key);
        }

        void PRINT_BACKWARD() {
                if (actual == NULL) {
                        printf("                NULL\n");
                        return;
                }
                Node* toPrint = last;
                Node* prev = intToPtr(last->ptrXOR);
                Node* tmp;
                printf("                ");
                while (prev != NULL) {
                        printf("%d ", toPrint->key);
                        tmp = prev;
                        prev = intToPtr(ptrToInt(toPrint) ^ prev->ptrXOR);
                        toPrint = tmp;
                }
                printf("%d \n", toPrint->key);
        }

        void DEL_VAL(int key) {
                while (first->key == key) {
                        DEL_BEG();
                        if (actual == NULL) {
                                return;
                        }
                }
                while (last->key == key) {
                        DEL_END();
                        if (actual == NULL) {
                                return;
                        }
                }
                if (actual == NULL) {
                        return;
                }
                Node* toDel = first;
                Node* next = intToPtr(first->ptrXOR);
                Node* tmp;
                while (next != NULL) {
                        Node* prev = intToPtr(toDel->ptrXOR ^ ptrToInt(next));
                        if (toDel->key == key) {
                                uintptr_t left = ptrToInt(toDel) ^ prev->ptrXOR;
                                uintptr_t right = ptrToInt(toDel) ^ next->ptrXOR;
                                prev->ptrXOR = left ^ ptrToInt(next);
                                next->ptrXOR = right ^ ptrToInt(prev);
                                if (toDel == this->next) {
                                        this->next = next;
                                }
                                else if (toDel == this->prev) {
                                        this->prev = prev;
                                }
                                else if (toDel == this->actual) {
                                        this->actual = prev;
                                        this->prev = intToPtr(left);
                                }
                                delete toDel;
                                tmp = next;
                                next = intToPtr(ptrToInt(prev) ^ next->ptrXOR);
                                toDel = tmp;
                        }
                        else {
                                tmp = next;
                                next = intToPtr(ptrToInt(toDel) ^ next->ptrXOR);
                                toDel = tmp;
                        }
                }
        }

        void DEL_ACT() {
                if (actual == first) {
                        DEL_BEG();
                        return;
                }
                else if (actual == last) {
                        DEL_END();
                        return;
                }
                uintptr_t left = ptrToInt(actual) ^ prev->ptrXOR;
                uintptr_t right = ptrToInt(actual) ^ next->ptrXOR;
                prev->ptrXOR = left ^ ptrToInt(next);
                next->ptrXOR = right ^ ptrToInt(prev);
                actual = prev;
                prev = intToPtr(left);
        }
};

int main()
{
        char cmd[20];
        int key;
        LinkedList list;


        while (scanf("%19s", cmd) > 0)
        {
                if (strcmp(cmd, "ACTUAL") == 0) {
                        list.ACTUAL();
                }
                if (strcmp(cmd, "NEXT") == 0) {
                        list.NEXT();
                }
                if (strcmp(cmd, "PREV") == 0) {
                        list.PREV();
                }
                if (strcmp(cmd, "ADD_BEG") == 0) {
                        scanf(" %d", &key);
                        list.ADD_BEG(key);
                }
                if (strcmp(cmd, "ADD_END") == 0) {
                        scanf("%d", &key);
                        list.ADD_END(key);
                }
                if (strcmp(cmd, "ADD_ACT") == 0) {
                        scanf("%d", &key);
                        list.ADD_ACT(key);
                }
                if (strcmp(cmd, "DEL_BEG") == 0) {
                        list.DEL_BEG();
                }
                if (strcmp(cmd, "DEL_END") == 0) {
                        list.DEL_END();
                }
                if (strcmp(cmd, "DEL_ACT") == 0) {
                        list.DEL_ACT();
                }
                if (strcmp(cmd, "DEL_VAL") == 0) {
                        scanf("%d", &key);
                        list.DEL_VAL(key);
                }
                if (strcmp(cmd, "PRINT_FORWARD") == 0) {
                        list.PRINT_FORWARD();
                }
                if (strcmp(cmd, "PRINT_BACKWARD") == 0) {
                        list.PRINT_BACKWARD();
                }
        }

        return 0;
}