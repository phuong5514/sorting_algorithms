#include "testing.h"

states S[3]{ sorted, reversed, random };

void test(int n[]) {
	for (int i = 0; i < 5; i++) {
		for (states state : S) {
			int* array = generateArray(n[i], state);

		}
	}
};