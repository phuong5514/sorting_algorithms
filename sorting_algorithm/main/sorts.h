#pragma once

void interchangeSort(int *array, int n);
void selectionSort(int* array, int n);
void bubbleSort(int* array, int n);


void heapSort(int* array, int n);
void buildMaxHeap(int* array, int n);
void heapifyMax(int* array, int heapSize, int i);

void mergeSort(int* array, int l, int r);
void merge(int* array, int left, int right, int mid);

void quickSort(int* array, int l, int r);
int partition(int* array, int l, int r);

void radixSort(int* array, int n);

