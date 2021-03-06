// ds_report05.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef class node *nptr;

class node {
public:
	int data;
	int nchilds;
	nptr *childs;
	void build(int n, int* data);
	void print();
	int degree();
	int depth();
	int width();
};

void node::build(int n, int* cdata) {
	
	int i;
	if (this->data < 0) {
		this->data = cdata[0];
		this->nchilds = n - 1;
		this->childs = (nptr*)calloc(this->nchilds, sizeof(nptr));
		for (i = 0; i < this->nchilds; i++) {
			this->childs[i] = (nptr)malloc(sizeof(node));
			this->childs[i]->data = cdata[i + 1];
			this->childs[i]->nchilds = 0;
			this->childs[i]->childs = NULL;
		}
		return;
	}
	if (this->data == cdata[0]) {
		this->nchilds = n - 1;
		this->childs = (nptr*)calloc(this->nchilds, sizeof(nptr));
		for (int i = 0; i < this->nchilds; i++) {
			this->childs[i] = (nptr)malloc(sizeof(node));
			this->childs[i]->data = cdata[i + 1];
			this->childs[i]->nchilds = 0;
			this->childs[i]->childs = NULL;
		}
		return;
	}
	for (int i = 0; i < this->nchilds; i++) {
		this->childs[i]->build(n, cdata);
	}
}

void node::print() {

	int i;
	printf("[%d]", this->data);
	for (i = 0; i < nchilds; i++) {
		printf("%d ", this->childs[i]->data);
	}
	printf("\n");
	for (i = 0; i < nchilds; i++)
		this->childs[i]->print();
}

int Get_Max(int a, int b) {
	if (a > b)
		return a;
	else
		return b;
}

int node::degree() {

	int max = this->nchilds;
	int i;
	if (this->nchilds == 0)
		return 0;
	for (i = 0; i < this->nchilds; i++) {
		max = Get_Max(max, this->childs[i]->degree());
	}

	return max;
}

int node::depth() {

	int cnt = 1;
	int i;
	if (this->nchilds == 0)
		return 1;
	for (i = 0; i < this->nchilds; i++) {

		cnt = Get_Max(cnt, this->childs[i]->depth());
		
	}

	return cnt+1;
}

int node::width() {
	if (this->nchilds == 0) {
		return 0;
	}
	else if (this->nchilds == 1) {
		return this->childs[0]->width();
	}
	int* arr = (int*)malloc(sizeof(int)*this->nchilds);


	for (int i = 0; i < this->nchilds; i++) {
		arr[i] = this->childs[i]->depth();
	}
	for (int i = 0; i < this->nchilds - 1; i++) {
		for (int j = i + 1; j < this->nchilds; j++) {
			if (arr[i] < arr[j]) {
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
	return arr[0] + arr[1];
}

int main()
{
	int i;
	int n_tok = 0;
	FILE *fp;
	fopen_s(&fp, "test.txt", "rt");
	char str[256];
	int tok[10];

	node root;

	if (fp) {
		while (fgets(str, 256, fp) != NULL) {
			for (i = 0; i < 10; i++) {
				tok[i] = -1;
			}
			sscanf(str, "%d %d %d %d %d %d %d %d %d %d",
				&tok[0], &tok[1], &tok[2], &tok[3], &tok[4],
				&tok[5], &tok[6], &tok[7], &tok[8], &tok[9]);
			for (i = 0, n_tok = 0; i < 10; i++) {
				if (tok[i] >= 0)
					n_tok++;
			}
			root.build(n_tok, tok);
		}
	}
		root.print();
		printf("degree: %d\n", root.degree());
		printf("depth: %d\n", root.depth());
		printf("width: %d\n", root.width());
    return 0;
}

