#include <iostream>
using namespace std;

void Swap(int tab[], int index1, int index2) {
    int tmp;
    tmp = tab[index1];
    tab[index1] = tab[index2];
    tab[index2] = tmp;
}

void QuickSort(int tab[], int idsTab[], int left, int right) {
    int i, j, pivot;

    pivot = tab[(left + right) / 2];
    Swap(tab, (left + right) / 2, right);
    if (tab != idsTab) Swap(idsTab, (left + right) / 2, right);


    i = j = left;
    while (i < right) {
        if (tab[i] < pivot) {
            Swap(tab, i, j);
            if (tab != idsTab) Swap(idsTab, i, j);
            j++;
        }
        i++;
    }
    Swap(tab, j, right);
    if (tab != idsTab) Swap(idsTab, j, right);
    if (left < j - 1) QuickSort(tab, idsTab, left, j - 1);
    if (j + 1 < right) QuickSort(tab, idsTab, j + 1, right);

}

int main() {
    int numberOfFiles, pendriveSize, numberOfFilesPendrive1 = 0, numberOfFilesPendrive2 = 0;
    int sum = 0;

    scanf_s("%d %d", &numberOfFiles, &pendriveSize);

    int* filesSizes = new int[numberOfFiles];
    int* filesIds = new int[numberOfFiles];

    for (int i = 0; i < numberOfFiles; i++) {
        scanf_s("%d %d", &filesIds[i], &filesSizes[i]);
    }

    QuickSort(filesSizes, filesIds, 0, numberOfFiles - 1);

    for (int i = 0; i < numberOfFiles; i++) {
        sum += filesSizes[i];
        if (sum <= pendriveSize) {
            numberOfFilesPendrive1++;
        }
        else break;
    }
    sum = 0;

    for (int i = numberOfFilesPendrive1; i < numberOfFiles; i++) {
        sum += filesSizes[i];
        if (sum <= pendriveSize) {
            numberOfFilesPendrive2++;
        }
        else break;
    }

    int filesCopied = numberOfFilesPendrive1 + numberOfFilesPendrive2;
    int* pendrive1 = new int[numberOfFilesPendrive1];
    int* pendrive2 = new int[numberOfFilesPendrive2];

    for (int i = 0; i < numberOfFilesPendrive1; i++) {
        pendrive1[i] = filesIds[i];
    }

    for (int i = numberOfFilesPendrive1; i < filesCopied; i++) {
        pendrive2[i - numberOfFilesPendrive1] = filesIds[i];
    }

    QuickSort(pendrive1, pendrive1, 0, numberOfFilesPendrive1 - 1);
    QuickSort(pendrive2, pendrive2, 0, numberOfFilesPendrive2 - 1);    

    printf_s("%d\n1:", filesCopied);

    for (int i = 0; i < numberOfFilesPendrive1; i++) {
        printf_s(" %d", pendrive1[numberOfFilesPendrive1 - 1 - i]);
    }

    printf_s("\n2:");

    for (int i = 0; i < numberOfFilesPendrive2; i++) {
        printf_s(" %d", pendrive2[numberOfFilesPendrive2 - 1 - i]);
    }

    delete[] filesSizes;
    delete[] filesIds;
    delete[] pendrive1;
    delete[] pendrive2;

    return 0;
}