#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


enum {
        CMD_LENGTH,
        CMD_PRINT,
        CMD_ADD,
        CMD_PUSH,
        CMD_POP,
        CMD_DEL,
        CMD_ADD_NUMB,
        CMD_DEL_VAL,
        CMD_ERROR
} ecmd;

struct Elem {
        int key;
        Elem* next;
        Elem(Elem* e, int k) : next(e), key(k) { }
};

char cmd;
int n;
bool isEmptyQueue;
Elem* first, * last, * front, * back;


int parseEnum(char cmd) {
        return cmd == 'L' ? CMD_LENGTH :
                cmd == 'P' ? CMD_PRINT :
                cmd == 'A' ? CMD_ADD :
                cmd == 'E' ? CMD_PUSH :
                cmd == 'D' ? CMD_POP :
                cmd == 'G' ? CMD_DEL :
                cmd == 'C' ? CMD_ADD_NUMB :
                cmd == 'R' ? CMD_DEL_VAL :
                CMD_ERROR;
}

Elem* search(int key)
{
        if (!first) return NULL;
        Elem* tmp = first;
        while (tmp->key != key && tmp != last) tmp = tmp->next;
        if (tmp->key == key) return tmp;
        else return NULL;
}

void printAll() {
        if (!front || isEmptyQueue) printf("                       -\n");
        else {
                Elem* tmp = front;
                printf("                       ");
                while (tmp != back) {
                        printf("%d->", tmp->key);
                        tmp = tmp->next;
                }
                printf("%d\n", back->key);
        }
}

int totalLength()
{
        if (!first) return 0;
        int len(1);
        Elem* tmp = first;
        while (tmp->next != first) { tmp = tmp->next; len++; }
        return len;
}

void addEmptySlot() {
        if (!first) {
                first = new Elem(NULL, NULL);
                first->next = first;
                last = first;
                return;
        }
        last->next = new Elem(first, NULL);
        last = last->next;
}

void pushElement(int key) {
        isEmptyQueue = false;
        if (!front) {
                if (!first) addEmptySlot();
                first->key = key;
                front = first;
                back = first;
        }
        else if (back == last && first == front) {
                addEmptySlot();
                back = back->next;
                back->key = key;
        }
        else if(back == last) {
                first = first->next;
                back = back->next;
                back->key = key;
                last = back;
        }
        else {
                back = back->next;
                back->key = key;
        }
}

void delEmpty() {
        if (!first) return;
        if (!back) {
                first = NULL;
                last = NULL;
                return;
        }
        back->next = front;
        first = front;
        last = back;
}

void popElement() {
        if (!front) {
                printf("- ");
                return;
        }
        printf("%d ", front->key);
        if (front == back) {
                front = NULL;
                back = NULL;
                return;
        }
        front = front->next;
}



void delVal(int key) {
        if (!first) { return; }
        if (!search(key)) { printf("                       -\n"); }
        else {
                Elem* tmp = search(key);
                if (totalLength() == 1) {
                        front = NULL;
                        back = NULL;
                        first = NULL;
                        last = NULL;
                        delete tmp;
                        return;
                }
                Elem* tmp2 = first;
                while (tmp2->next != tmp) {
                        tmp2 = tmp2->next;
                }
                if (tmp == front) {
                        if (front == first) {
                                front = front->next;
                                first = front;
                        }
                        else{ front = front->next; }
                        
                }
                if (tmp == back) {
                        back = tmp2;
                }
                tmp2->next = tmp->next;
                delete tmp;
        }
}

int main()
{
        int key, number;
        isEmptyQueue = true;
        while (scanf("%c", &cmd) > 0) {
                switch (parseEnum(cmd))
                {
                case CMD_LENGTH:
                        printf("                       %d\n", totalLength());
                        break;

                case CMD_PRINT:
                        printAll();
                        break;
                        
                case CMD_ADD:
                        addEmptySlot();
                        break;

                case CMD_PUSH:
                        while(scanf("%d", &key) > 0){
                                pushElement(key);
                        }                       
                        break;

                case CMD_POP:
                        scanf("%d", &number);
                        if (number >= 0) {
                                printf("                       ");
                                for (int i = 0; i < number; i++) {
                                        popElement();
                                }
                                printf("\n");
                        }
                        break;

                case CMD_DEL:
                        delEmpty();
                        break;

                case CMD_ADD_NUMB:
                        scanf("%d", &number);
                        for (int i = 0; i < number; i++) {
                                addEmptySlot();
                        }
                        break;

                case CMD_DEL_VAL:
                        scanf("%d", &key);
                        delVal(key);
                        break;

                case CMD_ERROR:
                default:
                        break;
                }

        }
        return 0;
}