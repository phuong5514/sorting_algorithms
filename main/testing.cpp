#define _CRT_SECURE_NO_WARNINGS
#include "testing.h"
#include "sorts.h"
#include "arraySampling.h"
#include <string>
#include <iostream>
#include <chrono>

void (*iterationSorts[5])(int*, int) = { interchangeSort, selectionSort, bubbleSort, heapSort, radixSort };
void (*DACSorts[2])(int*, int, int) = { mergeSort, quickSort };
const char* iSortNames[5] = { "interchangeSort", "selectionSort", "bubbleSort", "heapSort", "radixSort" };
const char* DACSortNames[2] = { "mergeSort", "quickSort" };

// ref: https://stackoverflow.com/questions/21592040/simple-time-tracker-in-c
states S[3]{ sorted, reversed, random };
std::string stateStrings[3] = { "sorted", "reversed", "random" };
void test(int n[]) {
	for (int i = 0; i < 5; i++) {
		for (states state : S) {
			int* array = generateArray(n[i], state);
			for (int j = 0; j < 5; j++) {
				int* cArray = copyArray(array, n[i]);
				std::string filename = std::string(iSortNames[j]) + '_' + stateStrings[state] + '_' + std::to_string(n[i]) + ".txt";
				FILE* file = fopen(filename.c_str(), "w");

				double runtime;
				if (file != nullptr) {
					std::cout << "File opened successfully: " << filename << std::endl;

					auto start = std::chrono::high_resolution_clock::now();
					iterationSorts[j](cArray, n[i]);
					auto end = std::chrono::high_resolution_clock::now();
					auto runtime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

					fputs(std::to_string(runtime.count()).c_str(), file);
					fputc(':', file);
					for (int k = 0; k < n[i]; k++) {
						fprintf(file, "%d ", cArray[k]);
						fputc(' ', file);

					}
					fclose(file);
					
				}
				else {
					std::cerr << "Error opening file \"" + filename + "\"" << filename << std::endl;
				}
				delete[] cArray;
				cArray = nullptr;
				std::cout << iSortNames[j] << "completed" << std::endl;
			}


			for (int j = 0; j < 2; j++) {
				int* cArray = copyArray(array, n[i]);
				std::string filename = std::string(DACSortNames[j]) + '_' + stateStrings[state] + '_' + std::to_string(n[i]) + ".txt";
				FILE* file = fopen(filename.c_str(), "w");
				double runtime;
				if (file != nullptr) {
					std::cout << "File opened successfully: " << filename << std::endl;

					auto start = std::chrono::high_resolution_clock::now();
					DACSorts[j](cArray, 0, n[i] - 1);
					auto end = std::chrono::high_resolution_clock::now();
					auto runtime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

					fputs(std::to_string(runtime.count()).c_str(), file);
					fputc(':', file);
					for (int k = 0; k < n[i]; k++) {
						fprintf(file, "%d ", cArray[k]);
						fputc(' ', file);

					}
					fclose(file);
					
				}
				else {
					std::cerr << "Error opening file \"" + filename + "\"" << filename << std::endl;
				}
				delete[] cArray;
				cArray = nullptr;
			}

			delete[] array;
		}
	}
};

int* copyArray(const int* array, const int n) {
	int* newArr = new int[n];
	for (int i = 0; i < n; i++) {
		newArr[i] = array[i];
	}
	return newArr;
};