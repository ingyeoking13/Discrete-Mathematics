#include <stdio.h>
#include <stdlib.h>
#define P(n,r) (facto(nElmnt)/facto(nElmnt-rSize))
#define C(n,r) (facto(nElmnt)/(facto(nElmnt-rSize)*facto(rSize)))

void permutation(int, int);
void combination(int, int, char**);
int facto(int);

int main() {
	//**** PART 1, Declare and Allocation

	int nElmnt, rSize;
	int i;
	char *nOrdered;
	char **n_C_r;

	printf("@ n의 값을 입력 하세요 : ");
	scanf("%d", &nElmnt);

	nOrdered = (char*)malloc(nElmnt * sizeof(char));  //"1234...n" 길이의 문자배열

	printf("@ r의 값을 입력 하세요 : ");
	scanf("%d", &rSize);

	n_C_r = (char**)malloc(C(nElmnt,rSize) * sizeof(char));
	for (i = 0; i < C(nElmnt,rSize); i++) {
		n_C_r[i] = (char*)malloc(rSize*sizeof(char));
	}

	//**** PART 2, Call Function
	permutation(nElmnt, rSize);
	combination(nElmnt, rSize, n_C_r);
	
	return 0;
}

void permutation(int nElmnt, int rSize) {

	printf("원소의 %d-순열(총%d개)\n", rSize, P(nElmnt,rSize));
	return;
}

void combination(int nElmnt, int rSize, char** n_C_r) {

	int i, j=0;
	
	for (i = 0; i < rSize; i++)
		n_C_r[j][i] = i + 49;

	while (1) {

		for (i = 0; i < rSize; i++) {
			printf("%c", n_C_r[j][i]);
			(i <rSize-1) ? printf("") : printf("\n");
		}
		
		if (j >= C(nElmnt, rSize)-1) return;
		else j++;

		for (i = 0; i < rSize ; i++)
			n_C_r[j][i] = n_C_r[j-1][i];
		
		for (i = rSize - 1; n_C_r[j][i] >= 48+nElmnt-(rSize-1-i);)
			if (--i < 0)
				return;

		for (n_C_r[j][i]++;i<rSize-1;i++) n_C_r[j][i+1] = n_C_r[j][i]+1;
	}
}

int facto(int n) {

	int f = 1;
	int i;

	for (i = 1; i <= n; i++) f *= i;
	
	return f;
}