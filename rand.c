#include <stdlib.h>

int randInRange(int min, int max) {
	int result, temp;
	if (min > max) {
		temp = max;
		min = max;
		max = temp;
	}
	result = ((rand() % (max - min + 1)) + min);
	return result;
}

_Bool randomBool() {
	return rand() % 2;
}
