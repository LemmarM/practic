#pragma once
#include <math.h>

int numberRank(long int N)
{
	int rank = 1;
	for (; N > 9; N /= 10)
		rank++;

	return rank;
};

void checkFor3(long long int* num, int max, int* sign) {
	int i = 0, i_s = 0;
	for (; i < max; i++)
		if (*(sign + i) == 2) {
			*(num + i - i_s) = *(num + i - i_s) * pow(10, numberRank(*(num + i - i_s + 1))) + *(num + i - i_s + 1);
			for (int ii = 1; i + ii < max; ii++)
				*(num + i + ii - i_s) = *(num + i + ii - i_s + 1);
			i_s++;
		};
};

long long int calculatingSum(long long int* num, int* sign, int max) {
	long long int res = *num;
	int i = 1, i_num = 0;
	for (; i < max; i++) {
		switch (*(sign + i - 1)) {
		case 0: res += *(num + i - i_num);
			break;
		case 1: res -= *(num + i - i_num);
			break;
		case 2: i_num++;
			break;
		};
	};
	return res;
};

void ternaryNumber(int* sign, int max, int count) {
	++* (sign + max - 2);
	if ((count % 3) == 0)
		for (int i = max - 2; i > 0; i--)
			if (*(sign + i) == 3) {
				*(sign + i) = 0;
				++* (sign + i - 1);
			};
};