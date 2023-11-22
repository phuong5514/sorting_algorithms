#include "arraySampling.h"
#include <random>

enum states
{
	sorted,
	reversed,
	random
};

int* generateArray(int n, states state) {
	int* array = new int[n];
	switch (state)
	{
	case sorted: // 1, 2, 3, ..., n
		for (int i = 0; i < n; i++) {
			array[i] = i + 1;
		}
		break;
	case reversed: // n, n-1, n-2, ..., 1
		for (int i = 0; i < n; i++) {
			array[i] = n - i;
		}
		break;
	case random:
		for (int i = 0; i < n; i++) {
			array[i] = rand() % n + 1; // random int from 1 to n
		}
		break;
	default:
		delete[] array;
		array = nullptr;
		break;
	}
	return array;
};