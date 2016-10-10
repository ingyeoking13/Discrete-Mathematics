#include <stdio.h>
#include <stdlib.h>

double conv_double(const char *string, int word);
void swap_row(double **s_arr, int *pivot, int size);
void divide_row(double **s_arr, int index, int size);
void substract_row(double **s_arr, int index, int size);
void print_row(double **s_arr, int size);
int pivot_fine(double **s_arr, int pivot, int size);

int main() {
	double **arr;
	int size;
	char inputStr[100];
	int i, j, err = 0;
	double pegs;

	printf("Matrix size : ");
	fgets(inputStr, 5, stdin);
	size = atoi(inputStr);

	arr = (double**)malloc(sizeof(double)*size);
	for (i = 0; i<size; i++)
		arr[i] = (double*)malloc(sizeof(double)*(size + 1));

	printf("input value : \n");
	for (i = 0; i < size; i++) {
		fgets(inputStr, sizeof(inputStr), stdin);
		for (j = 0; j < size + 1; j++) {
			arr[i][j] = conv_double(inputStr, j);
		}
	}


	for (i = 0; i < size; i++) {
		divide_row(arr, i, size);
		//print_row(arr, size);
		substract_row(arr, i, size);
		//print_row(arr, size);
	}

	for (i = 0; i <size; i++)
		if (arr[i][i] != 1) {
			pegs = arr[i][i];
			arr[i][i] /= pegs;
			arr[i][size] /= pegs;
		}

	print_row(arr, size);

	return 0;

}

void print_row(double **arr, int size) {
	int i, j;
	printf("output : \n");
	for (i = 0; i < size; i++) {
		for (j = 0; j < size + 1; j++) {
			(j != size) ? printf("%f ", arr[i][j]) : printf("%f\n", arr[i][j]);
		}
	}
};

double conv_double(const char *string, int word) {
	char str_to_dbl[10] = { 0 };
	int null = 0;
	int i = 0;
	int j = 0;

	while (null < word + 1) {
		if (string[i] == '\n') break;
		if (string[i] == 0x20) null++;

		if (null == word) {
			str_to_dbl[j] = string[i];
			j++;
		}
		i++;
	}
	double value = atof(str_to_dbl);
	return value;
}

void swap_row(double **s_arr, int *pivot1, int size) {
	double temp[10];
	int i, j;
	int pivot = *pivot1;
	if (pivot_fine(s_arr, pivot, size))
		for (i = pivot; i < size; i++) {
			if (s_arr[i][pivot] != 0) {
				*pivot1 = pivot;
				for (j = 0; j < size + 1; j++) {
					temp[j] = s_arr[pivot][j];
					s_arr[pivot][j] = s_arr[i][j];
					s_arr[i][j] = temp[j];
					if (j == size + 1) goto END;
				}
			}
		}

	else
		printf("No Answer. Belows are trash values.");

	return;

END:
	return;
}

void divide_row(double **s_arr, int index, int size) {
	int i, j;
	double pegs;
	for (i = 0; i < size; i++) {
		pegs = s_arr[i][index];
		if (s_arr[index][index] == 0) {
			swap_row(s_arr, &index, size);
			print_row(s_arr, size);
			pegs = s_arr[i][index];
		}
		if (pegs != 0)
			for (j = 0; j < size + 1; j++)
				s_arr[i][j] = s_arr[i][j] / pegs;
	}
}

void substract_row(double **s_arr, int index, int size) {
	int i, j;
	double pegs;
	for (i = 0; i < size; i++) {
		pegs = s_arr[i][index];
		for (j = 0; j < size + 1; j++)
			if (index != i && pegs == 1)
				s_arr[i][j] = s_arr[i][j] - s_arr[index][j];
	}

}

int pivot_fine(double **s_arr, int pivot, int size) {
	int i;

	for (i = pivot; i < size; i++) {
		if (s_arr[i][pivot] != 0)
			return -1;
	}

	return 0;
}

