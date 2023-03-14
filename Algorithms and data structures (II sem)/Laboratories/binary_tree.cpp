#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

class Node
{
public:
        Node* left, * right, * parent;
        int key;
        Node(int key) : left(NULL), right(NULL), key(key)
        {
                this->parent = NULL;
        }
};

void insert(Node* N, int key)
{
        if (N->key == key)
                return;
        if (N->key < key)
                if (N->right)
                        insert(N->right, key);
                else
                {
                        N->right = new Node(key);
                        N->right->parent = N;
                        
                }
        else
                if (N->left)
                        insert(N->left, key);
                else
                {
                        N->left = new Node(key);
                        N->left->parent = N;
                }
}

Node* search(Node* N, int key)
{
        if (N == NULL)
                return NULL;
        if (N->key == key)
                return N;
        if (N->key < key)
                return search(N->right, key);
        return search(N->left, key);
}

void findMinKey(Node* N, int* minKey) {
        if (N->key < *minKey) *minKey = N->key;
        if (N->left != NULL) {
                findMinKey(N->left, minKey);
        }
        if (N->right != NULL) {
                findMinKey(N->right, minKey);
        }
}

void printMinKey(Node* N, int key) {
        Node* subN = search(N, key);
        if (subN != NULL) {
                int minKey = subN->key;
                findMinKey(subN, &minKey);
                printf("%d\n", minKey);
        }
        else printf("-\n");
}

void printVertex(Node* N) {
        if (N != NULL) {
                printVertex(N->left);
                if (N->left == NULL && N->right == NULL) {
                        printf("%d ", N->key);
                }
                printVertex(N->right);
        }
}

void printVertices(Node* N, int key) {
        Node* subN = search(N, key);
        if (subN != NULL) {
                printVertex(search(N, key));
                printf("\n");
        }
        else printf("-\n");
}

void countSize(Node* N, int* size) {
        *size = *size + 1;
        if (N->left != NULL) {
                countSize(N->left, size);
        }
        if (N->right != NULL) {
                countSize(N->right, size);
        }
}

void printTreeSize(Node* N, int key) {
        Node* subN = search(N, key);
        if (subN != NULL) {
                int treeSize = 0;
                countSize(subN, &treeSize);
                printf("%d\n", treeSize);
        }
        else printf("-\n");
}

void countLeafs(Node* N, int * number) {
        if (N != NULL) {
                countLeafs(N->left, number);
                if (N->left == NULL && N->right == NULL) {
                        *number = *number + 1;
                }
                countLeafs(N->right, number);
        }
}

void printNumberOfLeafs(Node* N, int key) {
        Node* subN = search(N, key);
        if (subN != NULL) {
                int numberOfLeafs = 0;
                countLeafs(subN, &numberOfLeafs);
                printf("%d\n", numberOfLeafs);
        }
        else printf("-\n");
}

void sumVertices(Node* N, int* sum) {
        if (N != NULL) {
                *sum += N->key;
                sumVertices(N->parent, sum);
        }
}

void printSumOfVertices(Node* N, int key) {
        int sumOfVertices = 0;
        Node* subN = search(N, key);
        if (subN != NULL) {
                sumVertices(subN, &sumOfVertices);
                printf("%d\n", sumOfVertices);
        }
        else printf("-\n");
}

void postorder(Node* N) {
        if (N != NULL) {
                postorder(N->left);
                postorder(N->right);
                printf("%d ", N->key);
        }
}

void printPostorder(Node* N, int key) {
        Node* subN = search(N, key);
        if (subN != NULL) {
                postorder(subN);
        }
        else printf("-\n");
}

void deleteTree(Node* N)
{
        if (N == NULL) return;
        deleteTree(N->left);
        deleteTree(N->right);
        delete N;
}

int main()
{
        char cmd;
        int key;
        Node* root = NULL, * out;

        while (scanf("%c %d", &cmd, &key) > 0)
        {
                if (cmd == 'I')
                        if (root != NULL)
                                insert(root, key);
                        else
                                root = new Node(key);
                else if (cmd == 'S')
                        out = search(root, key);        
                else if (cmd == 'M')
                        printMinKey(root, key);
                else if (cmd == 'L')
                        printVertices(root, key);
                else if (cmd == 'R')
                        printTreeSize(root, key);
                else if (cmd == 'C')
                        printNumberOfLeafs(root, key);
                else if (cmd == 'Q')
                        printSumOfVertices(root, key);
                else if (cmd == 'T')
                        printPostorder(root, key);
        }
        deleteTree(root);
        return 0;
}