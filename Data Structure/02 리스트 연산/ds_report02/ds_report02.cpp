// ds_report02.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#define _CRT_SECURE_NO_WARNINGS
#include "StdAfx.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE 100

typedef struct {
	char name[8];
	char sex;
	char address[8];
	char major[16];
	float grade;
	int height;
	int weight;
}sinfo;

int cnt = 0;
int n;
sinfo* slist;

int count_student(FILE *fp) {

	char str[256];
	int i = 0;
	while (fgets(str, sizeof(str), fp) != NULL) {
		i++;
	}

	return i;
}

void input_student(FILE *fp, int n) {

	for (int i = 0;i<n;i++) {
		fscanf(fp, "%s %c %s %s %f %d %d",
		&slist[i].name, &slist[i].sex, &slist[i].address, &slist[i].major, &slist[i].grade, &slist[i].height, &slist[i].weight);
	}
}

void compare_name(int n) {

	int i, j;
	sinfo temp;

	for (i = 0;i<n - 1;i++) {
		for (j = 0;j<n - i - 1;j++) {
			if (strcmp(slist[j].name, slist[j + 1].name)) {
				temp = slist[j];
				slist[j] = slist[j + 1];
				slist[j + 1] = temp;
			}
		}
	}
}

void CREATE() {
	slist = (sinfo*)calloc(MAX_SIZE, sizeof(sinfo));
}

void INSERT2(sinfo tinfo) {

	if (cnt == 0) {
		slist[cnt++] = tinfo;
		return;
	}

	int i;
	int j;
	for (i = 0; i < cnt;i++) {
		if (strcmp(tinfo.name, slist[i].name) <= 0)
			break;
	}

	for (j = cnt - 1; j >= i;j--) {
		slist[j + 1] = slist[j];
	}

	slist[i] = tinfo;
	cnt++;

}

int LOAD(char *fn) {

	FILE* fp2;
	fopen_s(&fp2, fn, "rt+");
	sinfo tinfo;
	char str[512];
	while (fgets(str, 512, fp2)) {
		sscanf(str, "%s %c %s %s %f %d %d",
			tinfo.name, &tinfo.sex, tinfo.address, tinfo.major, &tinfo.grade, &tinfo.height, &tinfo.weight);
		INSERT2(tinfo);
	}

	fclose(fp2);
	return n;
}

void INSERT(char* tok2, char* tok3, char* tok4, char* tok5, char* tok6, char* tok7, char* tok8) {

	sinfo tinfo;
	strcpy(tinfo.name, tok2);
	tinfo.sex = tok3[0];
	strcpy(tinfo.address, tok4);
	strcpy(tinfo.major, tok5);
	tinfo.grade = atof(tok6);
	tinfo.height = atoi(tok7);
	tinfo.weight = atoi(tok8);

	INSERT2(tinfo);
}

void DELETE(char* tok2) {
	int i, j;
	for (i = 0;i < cnt;i++) {
		if (strcmp(slist[i].name, tok2) == 0)
			break;
	}

	if (cnt == 1) {
		printf("No %s in the list.\n", tok2);
		return;
	}

	for (j = i;j < cnt - 1;j++) {
		slist[j] = slist[j + 1];
	}
	cnt--;

	printf("%s is deleted.\n", tok2);
}

void SEARCH(char* tok2) {
	
	int i;

	for (i = 0;i < cnt;i++) {
		if (strcmp(slist[i].name, tok2) == 0) {
			printf("%s found: %s %c %s %s %f %d %d\n",
				tok2, slist[i].name, slist[i].sex, slist[i].address, slist[i].major, slist[i].grade, slist[i].height, slist[i].weight);
			return;
		}
	}

	printf("%s not found.\n", tok2);
}

void PRINT() {

	int i;
	for (i = 0; i < cnt; i++){
		printf("%s %c %s %s %.2f %d %d\n",
		slist[i].name, slist[i].sex, slist[i].address, slist[i].major, slist[i].grade, slist[i].height, slist[i].weight);
	}
}

int main() {

	char input[512];
	char tok1[20];
	char tok2[20];
	char tok3[20];
	char tok4[20];
	char tok5[20];
	char tok6[20];
	char tok7[20];
	char tok8[20];
	FILE *fp;
	fopen_s(&fp, "input.txt", "rt+");
	while (fgets(input, sizeof(input), fp)) {
		sscanf(input, "%s %s %s %s %s %s %s %s",
			tok1, tok2, tok3, tok4, tok5, tok6, tok7, tok8);
		if (!strcmp(tok1, "CREATE"))
			CREATE();
		else if (!strcmp(tok1, "LOAD"))
			LOAD(tok2);
		else if (!strcmp(tok1, "PRINT"))
			PRINT();
		else if (!strcmp(tok1, "INSERT"))
			INSERT(tok2, tok3, tok4, tok5, tok6, tok7, tok8);
		else if (!strcmp(tok1, "DELETE"))
			DELETE(tok2);
		else if (!strcmp(tok1, "SEARCH"))
			SEARCH(tok2);
		else {
			printf("등록되지 않은 명령어입니다. 명령어를 대문자로 다시 입력 해 주세요.\n");
		}
	}
	fclose(fp);
	return 0;
}