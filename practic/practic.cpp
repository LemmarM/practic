#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


int numberRank(long int N)
{
	int rank = 1;
	for (; N > 9; N /= 10)
		rank++;

	return rank;
};

void checkFor3(long long int * num, int max, int * sign) {
	int i = 0, i_s = 0;
		for (; i < max; i++)
			if (*(sign + i) == 2) {
				*(num + i - i_s) = *(num + i - i_s) * pow(10, numberRank(*(num + i - i_s + 1))) + *(num + i - i_s + 1);
				for (int ii = 1; i + ii < max; ii++)
					*(num + i + ii - i_s) = *(num + i + ii - i_s + 1);
				i_s++;
			};
};

long long int calculatingSum(long long int * num, int * sign, int max) {
	long long int res =  *num;
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

void ternaryNumber(int * sign, int max, int count) {
	++*(sign + max - 2);
	if ((count % 3) == 0)
		for (int i = max - 2; i > 0; i--)
			if (*(sign + i) == 3) {
				*(sign + i) = 0;
				++*(sign + i - 1);
			};
};

int main() {
	setlocale(LC_ALL, "Rus");
	long long int* numbers, res = 0, i = 0;
	int i_s = 0, max = 0, required_res = 0, count_out = 0, size = 0, count = 0, * sign, i_num = 0;
	char* filename;
	FILE* result;

	printf("Введите максимальное число ряда чисел:");
	while (scanf("%i", &max) == 0) {
		fseek(stdin, 0, SEEK_END);
		printf("\nВведите корректное число: ");
	};

	printf("Желаемый результат: ");
	while (scanf("%i", &required_res) == 0) {
		fseek(stdin, 0, SEEK_END);
		printf("\nВведите корректное число: ");
	};

	numbers = (long long int*)calloc(max, sizeof(long long int));
	filename = (char*)calloc(7, sizeof(char));
	sign = (int*)calloc(max - 1, sizeof(long long int));
	
	if (!numbers || !filename || !sign) {
		printf("Ошибка выделения памяти. Перезапустите программу.");
		return -1;
	};

	sprintf(filename, "result");

	result = fopen(filename,"w");
	if (!result) {
		printf("Ошибка при создании файла.");
			return -1;
	};


	while (count < pow(3, max - 1)) {
		i_s = 0;
		for (i = 0; i < max; i++)
			*(numbers + i) = i + 1;

		checkFor3(numbers, max, sign);
		
		res = calculatingSum(numbers, sign, max);
		if (res == required_res) {
		count_out++;
		fprintf(result,"%lli", *(numbers));
	
		for (i = 0, i_num = 0; i < max-1; i++)
				if (*(sign + i) != 2) {
					if (*(sign + i) == 0)
						fprintf(result," + %lli", *(numbers + i + 1 - i_num));
					if (*(sign + i) == 1)
						fprintf(result," - %lli", *(numbers + i + 1 - i_num));
				}
				else
					i_num++;
			fprintf(result," = %lli \n", res);
		};
		count++;
		ternaryNumber(sign, max, count);
	};
	if (count_out != 0)
		fprintf(result,"\n\nВсего результатов: %i", count_out);
	else
		fprintf(result,"Результаты отсутвуют.");

	fclose(result);
	size = numberRank(count_out) + numberRank(max) + numberRank(required_res) + 13;
	realloc(filename, size);

	sprintf(filename, "result_%i_%i_%i.txt", max, required_res, count_out);
	if (rename("result", filename) != 0) {
		printf("Файл с результатами уже существует.");
		return -1;
	};

	if (count_out != 0)
		printf("\n\nВсего результатов: %i\nРезультат записан в файл %s", count_out, filename);
	else
		printf("Результаты отсутвуют.");
	return 0;
};