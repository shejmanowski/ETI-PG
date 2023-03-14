#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include<string>

class Node {
public:
        int key;
        Node* next, * prev;
        Node(int key, Node* next, Node* prev) {
                this->key = key;
                this->next = next;
                this->prev = prev;
        }
};

class LinkedList
{
public:
        Node* actual, * first;

        LinkedList() {
                actual = NULL;
                first = NULL;
        }

        void moveActualRight() {
                if (actual == NULL) return;
                actual = actual->next;
        }

        void moveActualLeft() {
                if (actual == NULL) return;
                actual = actual->prev;
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
                        Node* newFirstNode = new Node(key, NULL, NULL);
                        newFirstNode->next = newFirstNode;
                        newFirstNode->prev = newFirstNode;
                        actual = newFirstNode;
                        first = actual;
                        return;
                }
                Node* newFirstNode = new Node(key, first, first->prev);
                if (SIZE() == 1) first->next = newFirstNode;    
                first->prev->next = newFirstNode;
                first->prev = newFirstNode;
                first = newFirstNode;
        }

        void ADD_END(int key) {
                if (actual == NULL) {
                        Node* newLastNode = new Node(key, NULL, NULL);
                        newLastNode->next = newLastNode;
                        newLastNode->prev = newLastNode;
                        actual = newLastNode;
                        first = actual;
                        return;
                }
                Node* newLastNode = new Node(key, first, first->prev);
                if (SIZE() == 1) first->next = newLastNode;
                first->prev->next = newLastNode;
                first->prev = newLastNode;
        }

        void ADD_ACT(int key) {
                if (actual == first) {
                        ADD_BEG(key);
                        return;
                }
                Node* newNode = new Node(key, actual, actual->prev);
                actual->prev->next = newNode;
                actual->prev = newNode;
        }

        void DEL_BEG() {
                if (actual == NULL) return;
                if (SIZE() == 1) {
                        delete actual;
                        actual = NULL;
                        first = NULL;
                        return;
                }
                if (actual == first) actual = first->prev;
                Node* tmp = first;
                first = first->next;
                first->prev = tmp->prev;
                tmp->prev->next = first;
                delete tmp;
        }

        void DEL_END() {
                if (actual == NULL) return;
                if (SIZE() == 1) {
                        delete actual;
                        actual = NULL;
                        first = NULL;
                        return;
                }
                if (actual == first->prev) actual = first->prev->prev;
                Node* tmp = first->prev;
                first->prev = first->prev->prev;
                first->prev->next = first;
                delete tmp;
        }

        void PRINT_FORWARD() {
                if (actual == NULL) {
                        printf("                NULL\n");
                        return;
                }
                Node* toPrint = first;
                printf("                ");
                for (int i = 0; i < SIZE(); i++) {
                        printf("%d ", toPrint->key);
                        toPrint = toPrint->next;
                }
                printf("\n");
        }

        void PRINT_BACKWARD() {
                if (actual == NULL) {
                        printf("                NULL\n");
                        return;
                }
                Node* toPrint = first->prev;
                printf("                ");
                for (int i = 0; i < SIZE(); i++) {
                        printf("%d ", toPrint->key);
                        toPrint = toPrint->prev;
                }
                printf("\n");
        }


        void DEL_ACT() {
                if (actual == first) {
                        DEL_BEG();
                        return;
                }
                if (actual == first->prev) {
                        DEL_END();
                        return;
                }
                actual->next->prev = actual->prev;
                actual->prev->next = actual->next;
                Node* tmp = actual;
                moveActualLeft();
                delete tmp;
        }

        void DEL_VAL(int key) {
                while (first->key == key) {
                        DEL_BEG();
                        if (actual == NULL) {
                                return;
                        }
                }
                while (first->prev->key == key) {
                        DEL_END();
                        if (actual == NULL) {
                                return;
                        }
                }
                if (actual == NULL) {
                        return;
                }
                Node* toDel = first;
                int check = 1;
                while (toDel != first || check) {
                        if (toDel->key == key) {
                                toDel->next->prev = toDel->prev;
                                toDel->prev->next = toDel->next;
                                Node* tmp = toDel;
                                if (toDel == actual) actual = actual->prev;
                                toDel = toDel->next;
                                delete tmp;
                        }
                        else
                        {
                                toDel = toDel->next;
                        }
                        check = 0;
                }
        }

        int SIZE() {
                if (first == NULL) return 0;
                int size = 0;
                Node* tmp = first;
                while (tmp->next != first) {
                        tmp = tmp->next;
                        size++;
                }
                size++;
                return size;
        }
}; 

class Queue {
public: 
        LinkedList* list;
        Node* back, * front;
        int isEmpty;

        Queue(LinkedList* list) {
                this->list = list;
                back = NULL;
                front = NULL;
                isEmpty = true;
        }

        void PUSH(int key) {
                if (list->SIZE() == 0) {
                        list->ADD_BEG(key);
                        back = list->actual;
                        front = list->actual;
                        isEmpty = false;
                }
                else if (list->SIZE() == COUNT()) {
                        list->actual = back;
                        list->ADD_ACT(key);
                        back = back->prev;
                }
                else if (!back) {
                        isEmpty = false;
                        list->first->prev->key = key;
                        back = list->first->prev;
                        front = list->first->prev;
                }
                else {
                        back = back->prev;
                        back->key = key;
                }
        }

        const int COUNT() {
                if (front == NULL || isEmpty) return 0;
                int size = 0;
                Node* tmp = front;
                while (tmp != back) {
                        tmp = tmp->prev;
                        size++;
                }
                size++;
                return size;
        }

        void delend() {
                if (back == list->first->prev) {
                        back = back->next;
                }
                list->DEL_END();
        }

        void delbeg() {
                if (back == list->first) {
                        back = back->next;
                }
                list->DEL_BEG();
        }

        void POP() {
                //if (!back) return;
                if (front != back && !isEmpty) {
                        printf("                %d\n", front->key);
                        front = front->prev;
                }
                else if (front == back && !isEmpty) {
                        printf("                %d\n", front->key);
                        isEmpty = true;
                }
                else {
                        printf("                NULL\n");
                }
        }

        void PRINT_QUEUE() {
                printf("                ");
                if (!back || isEmpty) {
                        printf("NULL\n");
                        return;
                }
                Node* tmp = front;
                while (tmp != back) {
                        printf("%d ", tmp->key);
                        tmp = tmp->prev;
                }
                printf("%d\n", back->key);
        }

        void GARBAGE_SOFT() {
                if (isEmpty) {
                        Node* tmp = list->first;
                        for (int i = 0; i < list->SIZE(); i++) {
                                tmp->key = 0;
                                tmp = tmp->next;
                        }
                        return;
                }
                Node* tmp = back;
                while (tmp->prev != front) {
                        tmp = tmp->prev;
                        tmp->key = 0;
                }
        }

        void GARBAGE_HARD() {
                if (isEmpty) {
                        while (list->first) {
                                list->DEL_BEG();
                        }
                        return;
                }
                Node* tmp1 = back->prev;
                while (tmp1 != front) {
                        if (tmp1 == list->first) {
                                list->DEL_BEG();
                                return;
                        }
                        if (tmp1 == list->first->prev) {
                                list->DEL_END();
                                return;
                        }
                        tmp1->next->prev = tmp1->prev;
                        tmp1->prev->next = tmp1->next;
                        Node* tmp = tmp1;
                        tmp1 = tmp1->prev;
                        delete tmp;
                }
        }
};


int main()
{
        char cmd[20];
        int key;
        LinkedList list;
        Queue queue(&list);


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
                        queue.delbeg();
                }
                if (strcmp(cmd, "DEL_END") == 0) {
                        queue.delend();
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
                if (strcmp(cmd, "SIZE") == 0) {
                        printf("                %d\n", list.SIZE());
                }
                if (strcmp(cmd, "COUNT") == 0) {
                        printf("                %d\n", queue.COUNT());
                }
                if (strcmp(cmd, "PUSH") == 0) {
                        scanf("%d", &key);
                        queue.PUSH(key);
                }
                if (strcmp(cmd, "POP") == 0) {
                        queue.POP();
                }
                if (strcmp(cmd, "PRINT_QUEUE") == 0) {
                        queue.PRINT_QUEUE();
                }
                if (strcmp(cmd, "GARBAGE_SOFT") == 0) {
                        queue.GARBAGE_SOFT();
                }
                if (strcmp(cmd, "GARBAGE_HARD") == 0) {
                        queue.GARBAGE_HARD();
                }
        }
        return 0;
}