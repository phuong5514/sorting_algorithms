#include "sorts.h"
#include "LinkedList.h"
#include <iostream>
#include <math.h>
using namespace std;

void interchangeSort(int* array, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (array[i] > array[j]) {
                swap(array[i], array[j]);
            }
        }
    }
};

void selectionSort(int* array, int n) {
    int* min = array;
    for (int i = 0; i < n - 1; i++) {
        min = array + i;
        for (int j = i; j < n; j++) {
            if (array[j] < *min) {
                min = array + j;
            }
        }
        swap(*min, array[i]);
    }

}

void bubbleSort(int* array, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (array[j] > array[j + 1]) {
                swap(array[j], array[j + 1]);
            }
        }
    }
};



void heapSort(int* array, int n) {
    buildMaxHeap(array, n);
    for (int heapSize = n - 1; heapSize >= 1; heapSize--) {
        swap(array[0], array[heapSize]);
        heapifyMax(array, heapSize, 0);
    }
};

void buildMaxHeap(int* array, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapifyMax(array, n, i);
    }
};

void heapifyMax(int* array, int heapSize, int i) {
    if (i < heapSize / 2) {
        int left = i * 2 + 1;
        int right = i * 2 + 2;
        int maxChild = -1;
        right < heapSize && array[right] > array[left] ? maxChild = right : maxChild = left;

        if (array[i] < array[maxChild]) {
            swap(array[i], array[maxChild]);
            heapifyMax(array, heapSize, maxChild);
        }
    }
};

void mergeSort(int* array, int l, int r) {
    if (l >= r) {
        return;
    }

    int mid = (l + r) / 2;
    mergeSort(array, l, mid);
    mergeSort(array, mid+1, r);

    merge(array, l, r, mid);
};

void merge(int* array, int left, int right, int mid) {
    int* tempArr = new int[right - left + 1];
    int leftArrIndex = left;
    int rightArrIndex = right;
    int k = 0;
    int min = -1;
    while (leftArrIndex <= mid && rightArrIndex <= right) {
        if (array[leftArrIndex] < array[rightArrIndex]) {
            min = array[leftArrIndex++];
        }
        else {
            min = array[rightArrIndex++];
        }
        tempArr[k++] = min;
    };

    while (leftArrIndex <= mid) {
        tempArr[k++] = array[leftArrIndex++];
    }

    while (rightArrIndex <= right) {
        tempArr[k++] = array[rightArrIndex++];
    }

    for (int i = 0; i < k; i++) {
        array[left + i] = tempArr[i];
    }
};

void quickSort(int* array, int l, int r) {
    if (l < r) {
        int pivot = partition(array, l, r);
        quickSort(array, l, pivot - 1);
        quickSort(array, pivot + 1, r);
    }
};

int partition(int* array, int l, int r) {
    int pivot = l;
    int lastS1 = l; 
    for (int i = l + 1; i <= r; i++) { // i = lastUnknown
        if (array[i] < array[pivot]) {
            lastS1++;
            swap(array[i], array[lastS1]);
        }
    }
    swap(array[pivot], array[lastS1]);
    return lastS1;
};

void radixSort(int* array, int n) {
    LinkedList<int>* buckets[10];
    for (int i = 0; i < 10; i++) {
        buckets[i] = new LinkedList<int>();
    }

    bool sorted = false;
    int k = 0;
    while (!sorted) {
        sorted = true;
        for (int i = 0; i < n; i++) {
            int index = (array[i] / (int)pow(10, k)) % 10;
            buckets[index]->insertLast(array[i]);
        }

        for (int j = 0, i = 0; j < 10 && i < n; i++) {
            while (buckets[j]->isEmpty()) {
                sorted = false;
                j++;
            }
            array[i] = buckets[j]->getFirst();
            buckets[j]->removeFirst();
        }
        
        k++;
    }

    for (int i = 0; i < 10; i++) {
        delete buckets[i];
    }
};