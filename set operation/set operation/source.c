/***********************************
* B011202 정요한
* 이산수학 과제 1 집합 연산하기
*
* 1 집합을 정의
* 2 길이에 맞게 출력
* 3 합집합 연산
* 4 교집합 연산
* 5 차집합 연산
* 6 대칭차집합 연산 (함수구현 X)
*
* 연산을 돕기위해 특정 원소가 비교 대상 집합의 멤버인지 확인하는 함수가
* 구현되어 있습니다.
************************************/
#include <stdio.h>
#include <stdlib.h>

typedef struct set_s {
	int   *elem;
	int   len;
}SET;
void defineSet(SET *set, char c);
void showSet(SET set);
int is_memberSet(int element, SET set);
SET unionSet(SET setA, SET setB);
SET interSet(SET setA, SET setB);
SET diffSet(SET setA, SET setB);

int main() {
	SET setX, setY;
	defineSet(&setX, 'x');
	defineSet(&setY, 'y');

	printf("집합 X = ");
	showSet(setX);
	printf("집합 Y = ");
	showSet(setY);

	SET setU = unionSet(setX, setY);
	printf("합집합 = ");


	showSet(setU);

	SET setI = interSet(setX, setY);
	printf("교집합 = ");
	showSet(setI);

	SET setXy = diffSet(setX, setY);
	printf("차집합(X-Y) = ");
	showSet(setXy);

	SET setYx = diffSet(setY, setX);
	printf("차집합(Y-X) = ");
	showSet(setYx);

	SET setSym = diffSet(setU, setI);
	printf("대칭차집합 = ");
	showSet(setSym);

	free(setU.elem);
	free(setX.elem);
	free(setY.elem);
	free(setI.elem);
	free(setXy.elem);
	free(setYx.elem);
	free(setSym.elem);

	return 0;
}

/******************************
*   !!집합 원소와 길이  정의하기
*******************************/

void defineSet(SET *set, char c) {
	int i;
	(c == 'x') ? printf("집합 X의 원소개수 입력: ") : printf("집합 Y의 원소개수 입력: ");
	scanf("%d", &(set->len));
	set->elem = (int*)malloc(sizeof(int)*(set->len));

	for (i = 0; i<(set->len); i++) {
		(c == 'x') ? printf("\t집합 X의 ") : printf("\t집합 Y의 ");
		printf("%d 번째 원소 입력 : ", i + 1);
		scanf("%d", (set->elem + i));
	}
}

/*******************
*   !!집합 출력하기
*******************/

void showSet(SET set) {
	int i;
	(set.len == 0) ? printf("NULL SET...") : printf("<");
	for (i = 0; i<set.len; i++)
		(i != set.len - 1) ? printf(" %d,", *(set.elem + i)) : printf(" %d>\n", *(set.elem + i));
}

/****************************************
*   !!전달된 집합에 적어도 하나 이상의
*   특정 원소가 존재하는지 확인
****************************************/
int is_memberSet(int element, SET set) {
	int i;
	int match = 0;
	if (set.len == 0) return match;
	for (i = 0; i<set.len; i++) {
		if (element == set.elem[i]) {
			return 1;
		}
		else {
			match = 0;
		}
	}

	return match;
}

/**************************************
*  !!합집합
**************************************/

SET unionSet(SET setA, SET setB) {
	SET setU;
	setU.len = 0;
	setU.elem = (int*)malloc(sizeof(int)*(setA.len + setB.len));
	int temp;    // 버블 정렬을 위한 임시변수
	int i, j;
	/********************************
	*  첫 번째 집합 원소 복사
	*********************************/
	for (i = 0; i<(setA.len); i++) {
		/*******************************
		*  첫 번째 집합의 한 원소가 새로
		*  생성된 집합의 원소가 아닐경우 값 복사
		********************************/
		if (!is_memberSet(setA.elem[i], setU)) {
			setU.elem[setU.len] = *(setA.elem + i);
			setU.len++;
		}
	}

	/*******************************
	*  두 번째 집합 원소 복사
	********************************/
	for (i = 0; i<(setB.len); i++) {
		/******************************
		*  두 번째 집합의 한 원소가 새로
		*  생성된 집합의 원소가 아닐경우 값 복사
		********************************/
		if (!is_memberSet(setB.elem[i], setU)) {
			setU.elem[setU.len] = *(setB.elem + i);
			setU.len++;
		}
	}

	for (i = 0; i<setU.len - 1; i++)
		for (j = 0; j < setU.len - 1 - i; j++) {
			if (setU.elem[j] > setU.elem[j + 1]) {
				temp = setU.elem[j];
				setU.elem[j] = setU.elem[j + 1];
				setU.elem[j + 1] = temp;
			}
		}

	return setU;
}

/*************************************
*  !!교집합
**************************************/
SET interSet(SET setA, SET setB) {
	SET setI;
	setI.len = 0;
	setI.elem = (int*)malloc(sizeof(int)*(setA.len + setB.len));
	int i;

	/*********************************
	* 해당 원소가 두번째 집합에
	* 있을경우 && 해당 원소가 생성된
	* 집합에 존재하지 않을 경우 값 복사
	**********************************/
	for (i = 0; i<setA.len; i++)
		if (is_memberSet(setA.elem[i], setB) && !is_memberSet(setA.elem[i], setI))
			setI.elem[setI.len++] = setA.elem[i];

	return setI;
}

/*************************************
*  !!차집합
**************************************/
SET diffSet(SET setA, SET setB) {
	SET setD;
	setD.len = 0;
	setD.elem = (int*)malloc(sizeof(int)*(setA.len));
	int i;

	for (i = 0; i< setA.len; i++)
		if (!is_memberSet(setA.elem[i], setB))
			setD.elem[setD.len++] = setA.elem[i];

	return setD;

}
