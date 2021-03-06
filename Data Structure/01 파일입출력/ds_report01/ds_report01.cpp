// ds_report01.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include <stdlib.h>
#include <string.h>

typedef struct {
	char name[16];
	char sex;
	char address[16];
	char major[16];
	double gpa;
	int height;
	int weight;
}student;

int main()
{
	int line = 0;
	int i;
	char str[128];
	FILE *fp;
	fopen_s(&fp, "list.txt", "rt+");

	if (fp) {
		while (fgets(str, sizeof(str), fp)) {
			line++;
		}
		rewind(fp);

		student* slist;
		slist = (student*)calloc(line, sizeof(student));

		for (i = 0;i < line; i++) {
			fscanf(fp, "%s %c %s %s %lf %d %d", slist[i].name, &slist[i].sex, slist[i].address, slist[i].major, &slist[i].gpa, &slist[i].height, &slist[i].weight);
			printf("%s %c %s %s %.2f %d %d\n", slist[i].name, slist[i].sex, slist[i].address, slist[i].major, slist[i].gpa, slist[i].height, slist[i].weight);
		}
	}
	fclose(fp);
    return 0;
}

