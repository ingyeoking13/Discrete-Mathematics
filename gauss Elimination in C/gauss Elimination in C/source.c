/*
	B011202 정요한
	Gauss (*Jordan) Elimination using 2D array in C

	함수의 종류는 다음과 같습니다.
	
	void print_row(double **s_arr, int size);
	 배열의 모든 엘리먼트를 출력합니다.
	
	double conv_double(const char *string, int word);
	 입력받은 문자열을 double type으로 2D 배열에 저장합니다.
	eg) 1 2 3 5
		2 4 16 6
		3 6 12 15
	
	void divide_row(double **s_arr, int index, int size);
	 배열의 column index를 argument로 받아, 행 자신을 각 행의 column index로 나눕니다.
	 이는 각 행의 column index를 자신의 수로 나누게 되므로
	 모든 행의 column ndex를 1로 만들게 됩니다.
	 따라서, 다음에 따라오는 행 뺄셈을 수행하여 행의 index를 0으로 만들게
	 기대할 수 있습니다.
	eg)	1 2 3 5
		1 2 8 3
		1 2 4 5
		^
		|_____ column index

    void substract_row(double **s_arr, int index, int size);
	 배열의 row index를 argument로 받아, 각 행들에 대해 한 행을 뺼셈 하게됩니다.
	 자신의 행에 대해 뺄셈은 하지 않음으로써, 나머지 모든 행의 column 들을 0으로 만듭니다
	eg)	1 2 3 5  <--- row index
		0 2 8 3
		0 2 4 5

	divide_row와 substract_row는 반복문에 들어감으로써 전부 행에대해 수행될 수 있습니다.
	행렬의 size만큼 반복을 돌리면 결과는 마지막 row의 마지막 column(우항값을 제외한)
	에 대해 전부 나눠진 값이므로, 다시 각 행의 각 열 만큼 나누게 됩니다.
	이로써 행렬은 이상적인 행렬 identity matrix로 됩니다.

	***추가사항
	swap_row, pivot_fine 함수는 divide_row의 예외적인 상황을 처리하기 위해 사용됩니다.
	행렬의 (1, 1) , (2, 2) .. 등의 대각선 원소들이 0인 경우 행렬을 이상적인 상태로 
	재배치하는데 사용됩니다.
	
*/



#include <stdio.h>
#include <stdlib.h>

void print_row(double **s_arr, int size);
double conv_double(const char *string, int word);
void divide_row(double **s_arr, int index, int size);
void substract_row(double **s_arr, int index, int size);
void swap_row(double **s_arr, int *pivot, int size);
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
		substract_row(arr, i, size);
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

/*
	행렬을 출력하기
*/

void print_row(double **arr, int size) {
	int i, j;
	printf("output : \n");
	for (i = 0; i < size; i++) {
		for (j = 0; j < size + 1; j++) {
			(j != size) ? printf("%f ", arr[i][j]) : printf("%f\n", arr[i][j]);
		}
	}
};

/*
	사용자 입력을 변환
*/

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

// 전달받은 column index를 기준으로 각 행의
// column index를 1로 만듭니다. 이때 기준행은 index와 같습니다.
// 전달받은 인수를 기준으로 각 행 자신의 column들을 나눕니다.
// 이는 각 행의 column index를 1로 만들게 됩니다.
// 만약 기준 행의 column index가 0이라면 0이 아닌
// 다른 행을 기준 행으로 설정하기위해
// swap_row 함수를 호출하게됩니다.

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

/*
	전달 받은 row index를 기준으로 모든 행을 뺍니다.
	앞에서 수행된 divide 때문에 다른 모든 행의 기준 column은
	0이 됩니다. 여기서 예외는 0 인 column이 존재할때는 이상적이므로
	빼지 않습니다.
*/

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


// divide_row 에서의 예외사항을 처리하기 위한 함수입니다.
// 우선 전달 받은column index가 0이 아닌 것이 존재하는지
// pivot_find를 확인하고 조건문에 사용합니다.
// eg) 0 2 3 5 <=== 기준행 index 0
//     0 1 5 3
//     4 0 0 1 <=== find and swap


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

int pivot_fine(double **s_arr, int pivot, int size) {
	int i;

	for (i = pivot; i < size; i++) {
		if (s_arr[i][pivot] != 0)
			return -1;
	}

	return 0;
}

