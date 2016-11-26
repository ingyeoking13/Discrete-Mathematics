/***********************************
* B011202 ������
* �̻���� ���� 1 ���� �����ϱ�
*
* 1 ������ ����
* 2 ���̿� �°� ���
* 3 ������ ����
* 4 ������ ����
* 5 ������ ����
* 6 ��Ī������ ���� (�Լ����� X)
*
* ������ �������� Ư�� ���Ұ� �� ��� ������ ������� Ȯ���ϴ� �Լ���
* �����Ǿ� �ֽ��ϴ�.
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

	printf("���� X = ");
	showSet(setX);
	printf("���� Y = ");
	showSet(setY);

	SET setU = unionSet(setX, setY);
	printf("������ = ");


	showSet(setU);

	SET setI = interSet(setX, setY);
	printf("������ = ");
	showSet(setI);

	SET setXy = diffSet(setX, setY);
	printf("������(X-Y) = ");
	showSet(setXy);

	SET setYx = diffSet(setY, setX);
	printf("������(Y-X) = ");
	showSet(setYx);

	SET setSym = diffSet(setU, setI);
	printf("��Ī������ = ");
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
*   !!���� ���ҿ� ����  �����ϱ�
*******************************/

void defineSet(SET *set, char c) {
	int i;
	(c == 'x') ? printf("���� X�� ���Ұ��� �Է�: ") : printf("���� Y�� ���Ұ��� �Է�: ");
	scanf("%d", &(set->len));
	set->elem = (int*)malloc(sizeof(int)*(set->len));

	for (i = 0; i<(set->len); i++) {
		(c == 'x') ? printf("\t���� X�� ") : printf("\t���� Y�� ");
		printf("%d ��° ���� �Է� : ", i + 1);
		scanf("%d", (set->elem + i));
	}
}

/*******************
*   !!���� ����ϱ�
*******************/

void showSet(SET set) {
	int i;
	(set.len == 0) ? printf("NULL SET...") : printf("<");
	for (i = 0; i<set.len; i++)
		(i != set.len - 1) ? printf(" %d,", *(set.elem + i)) : printf(" %d>\n", *(set.elem + i));
}

/****************************************
*   !!���޵� ���տ� ��� �ϳ� �̻���
*   Ư�� ���Ұ� �����ϴ��� Ȯ��
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
*  !!������
**************************************/

SET unionSet(SET setA, SET setB) {
	SET setU;
	setU.len = 0;
	setU.elem = (int*)malloc(sizeof(int)*(setA.len + setB.len));
	int temp;    // ���� ������ ���� �ӽú���
	int i, j;
	/********************************
	*  ù ��° ���� ���� ����
	*********************************/
	for (i = 0; i<(setA.len); i++) {
		/*******************************
		*  ù ��° ������ �� ���Ұ� ����
		*  ������ ������ ���Ұ� �ƴҰ�� �� ����
		********************************/
		if (!is_memberSet(setA.elem[i], setU)) {
			setU.elem[setU.len] = *(setA.elem + i);
			setU.len++;
		}
	}

	/*******************************
	*  �� ��° ���� ���� ����
	********************************/
	for (i = 0; i<(setB.len); i++) {
		/******************************
		*  �� ��° ������ �� ���Ұ� ����
		*  ������ ������ ���Ұ� �ƴҰ�� �� ����
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
*  !!������
**************************************/
SET interSet(SET setA, SET setB) {
	SET setI;
	setI.len = 0;
	setI.elem = (int*)malloc(sizeof(int)*(setA.len + setB.len));
	int i;

	/*********************************
	* �ش� ���Ұ� �ι�° ���տ�
	* ������� && �ش� ���Ұ� ������
	* ���տ� �������� ���� ��� �� ����
	**********************************/
	for (i = 0; i<setA.len; i++)
		if (is_memberSet(setA.elem[i], setB) && !is_memberSet(setA.elem[i], setI))
			setI.elem[setI.len++] = setA.elem[i];

	return setI;
}

/*************************************
*  !!������
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
