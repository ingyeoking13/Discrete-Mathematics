/*
	B011202 ������
	�̻���� ���α׷��� ������ ����
	{1, 2, ..., n } �� ������ ������ ���϶�.  P(n, r)�� C(n, r)
	�ݺ����� ����� ���� �����ذ�

	1 ����
	����� ������ �����ϴ�. C(7, 4)
	1234, 1235, 1236, 1237, 1245, 1246, 1247, 1256, 1257, 1267, 1345, 1346, 1347, 1456, 1567, 2345 ...

	������ ������ �����ϴ�. C(7, 4)

		  j
a[]	1 2 3 4
	a[j]>=7 ? false,  a[j]++, j< r -1 ? false

          j
	1 2 3 5
	a[j]>=7 ? false,  a[j]++, j< r -1 ? false

		  j
	1 2 3 6	
	a[j]>=7 ? false,  a[j]++, j< r -1 ? false

		  j
	1 2 3 7
	a[j]>=7 ? true, j--, a[j] >= 6 ? false, a[j]++, j< r-1 ? true, a[j+1] = a[j]+1, j++, j< r-1? false

		  j
	1 2 4 5	......

		  j
	1 5 6 7
	a[j]>=7 ? true, j--, a[j] >= 6 ? true, j--, a[j]>=5? true, j--, a[j]>=4? false
	a[j]++, j<r-1? true, a[j+1] = a[j]+1, j++, j<r-1? true, a[j+1] = a[j]+1, j++, j<r-1? true, a[j+1] = a[j] +1, j++, j<r-1? false

    2 3 4 5 ...... 4 5 6 7

	while (1) {
		... ���� ...
		for (j = rSize -1; n_C_r[i][j] >= nElmnt - (rSize - 1 - j);j--);
		for (n_C_r[i][j]++; j<rSize - 1; j++) n_C_r[i][j + 1] = n_C_r[i][j] + 1;
	}

	2 ����
	P(7,4)�� ���� �ݺ����� ����� Ž��������, �����ϴ� ���� ���� ã�� �� �Ͽ� ������ �� ��츦 ������ �����Ͽ����ϴ�.
	����, �켱������ ������ �� ��츦 �迭�� �����Ͽ� ������ �װ��� �����Ͽ� �����Ͽ����ϴ�.
	����� ������ �����ϴ�. 7!
	1234567, 1234576, 1234657, 1234675, 1234756, 1234765, 1235467, 1235476, 1235647, 1235674, ....
	������ �� ������ ������ �����ϴ�. 7! ( P(n, r)�� �����ϱ����� �� �ַ�ǿ����� �ణ �����Ǿ����ϴ�.)

				j
a[] 1 2 3 4 5 6 7
	j= rSize-1 , j && a[j-1] >= a[j] ? false
	j == 0 ? false, j--
	q=rSize-1, a[q] <= a[j] ? false
	swap(j, q)
	j++, q = rSize -1, q > j ? false

				j,q
	1 2 3 4 5 7 6
	j = rSize-1, j && a[j-1] >= a[j] ? true, j--, j && a[j-1] >= a[j] ? false,
	j == 0 ? false, j--
	q=rSize-1, a[q] <= a[j] ? false
	swap(j, q)
	j++, q = rSize -1, q > j ? true, swap(j, q), q--, j++, q > j ? false

				j,q
	1 2 3 4 6 5 7
	j = rSize-1, j && a[j-1] >= a[j] ? flase
	j == 0 ? false, j--
	q=rSize-1, a[q] <= a[j] ? false
	swap(j, q)
	j++, q = rSize -1, q > j ? false

				j,q
	1 2 3 4 6 7 5
	j = rSize-1, j && a[j-1] >= a[j] ? true, j--, j && a[j-1] >= a[j] ? false
	j == 0 ? false, j--
	q=rSize-1, a[q] <= a[j] ? true, q--, a[q] <= a[j] ? false
	swap(j, q)
	j++, q = rSize -1, q > j ? true, swap (j, q), q--, j++, q > j ? false

				j,q
	1 2 3 4 7 5 6
	j = rSize-1, j && a[j-1] >= a[j] ? false
	j == 0 ? false, j--
	q=rSize-1, a[q] <= a[j] ? false
	swap(j, q)
	j++, q = rSize -1, q > j ? false

				j,q
	1 2 3 4 7 6 5
	j = rSize-1, j && a[j-1] >= a[j] ? true, j--, j && a[j-1] >= a[j] ? true, j--, j && a[j-1] >= a[j] ? false
	j == 0 ? false, j--
	q=rSize-1, a[q] <= a[j] ? false
	swap(j, q)
	j++, q = rSize-1, q > j ? true, swap (j, q), q--, j++, q > j ? false

				j,q
	1 2 3 5 4 6 7
	j = rSize-1, j && a[j-1] >= a[j] ?  false
	j == 0 ? false, j--
	q=rSize-1, a[q] <= a[j] ? false
	swap(j, q)
	j++, q = rSize-1, q > j ? false

	1 2 3 5 4 7 6 ... 7 6 5 4 2 3 1

				j,q
	7 6 5 4 3 1 2
	j = rSize-1, j && a[j-1] >= a[j] ?  false
	j == 0 ? false, j--
	q=rSize-1, a[q] <= a[j] ? false
	swap(j, q)
	j++, q = rSize-1, q > j ? false

				j,q
	7 6 5 4 3 2 1
	j = rSize-1, j && a[j-1] >= a[j] ?  true until j==1, j--
	j == 0 ? true, return

	Jeong Yo Han
	Discrete Mathematics assignment permutations and combinations
	{1, 2, ..., n } permutations and combinations. P(n, r) & C(n, r)
	solving problem with iterative method
*/
#include <stdio.h>
#include <stdlib.h>
#define P(n,r) (facto(nElmnt)/facto(nElmnt-rSize))
#define C(n,r) (facto(nElmnt)/(facto(nElmnt-rSize)*facto(rSize)))

void permutation(int, int, int**);
void combination(int, int, int**);
void show(int, int, int**);
int facto(int);

int main() {
	//**** PART 1, Declare and Allocation
	int nElmnt, rSize, i;
	int **n_C_r;

	printf("@ n�� ���� �Է� �ϼ��� : ");
	scanf("%d", &nElmnt);
	printf("@ r�� ���� �Է� �ϼ��� : ");
	scanf("%d", &rSize);

	//***** Dynamic Memory Allocation
	n_C_r = (int**)malloc(C(nElmnt, rSize) * sizeof(int*));
	for (i = 0; i < C(nElmnt, rSize); i++)
		n_C_r[i] = (int*)malloc(rSize * sizeof(int));

	//***** Array Initialize
	for (i = 0; i < rSize; i++)
		n_C_r[0][i] = i + 1;

	//**** PART 2, Call Function
	combination(nElmnt, rSize, n_C_r);
	printf("������ %d-����(��%d��) : ", rSize, C(nElmnt, rSize));
	show(nElmnt, rSize, n_C_r);

	printf("������ %d-����(��%d��) : ", rSize, P(nElmnt, rSize));
	permutation(nElmnt, rSize, n_C_r);
	printf("\n");
	return 0;
}

void permutation(int nElmnt, int rSize, int** n_P_r) {
#define swap(a, b, c){temp = n_P_r[a][b]; n_P_r[a][b] = n_P_r[a][c]; n_P_r[a][c] =temp;}

	int l = 0, j, q, k, temp;

	while (1) {

		for (j = 0; j < rSize; j++) {
			printf("%d", n_P_r[l][j]);
			j < rSize - 1 ? printf("") : printf(", ");
		}

		for (j = rSize - 1; j&& n_P_r[l][j - 1] >= n_P_r[l][j]; j--);
		if (!j--) {
			if (l == C(nElmnt, rSize) - 1)
				return;
			else {
				l++;
				continue;
			}
		}

		for (q = rSize - 1; n_P_r[l][q] <= n_P_r[l][j]; q--);

		swap(l, j, q);

		for (j++, q = rSize - 1; q > j; q--, j++)
			swap(l, j, q);

		continue;
	}
#undef swap
}

void combination(int nElmnt, int rSize, int** n_C_r) {

	int i = 0, j;

	while (1) {

		i++;
		if (i >= C(nElmnt, rSize)) return;
		for (j = 0; j < rSize; j++)
			n_C_r[i][j] = n_C_r[i - 1][j];

		for (j = rSize - 1; n_C_r[i][j] >= nElmnt - (rSize - 1 - j); j--);

		for (n_C_r[i][j]++; j<rSize - 1; j++) n_C_r[i][j + 1] = n_C_r[i][j] + 1;
	}
}

int facto(int n) {

	int f = 1;
	int i;

	for (i = 1; i <= n; i++) f *= i;

	return f;
}

void show(int nElmnt, int rSize, int** n_C_r) {
	int i, j;
	for (i = 0; i < C(nElmnt, rSize); i++)
		for (j = 0; j < rSize; j++) {
			printf("%d", n_C_r[i][j]);
			j < rSize - 1 ? printf("") : i<C(nElmnt, rSize) - 1 ? printf(", ") : printf("\n");
		}
}

