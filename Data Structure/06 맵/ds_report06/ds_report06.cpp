// ds_report05.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef class node *nptr;

class node {
public:
	char data[32];
	int cnt;
	nptr lchild, rchild;
};

class heap_node {
public:
	char data[32];
	int cnt = 0;
};

void swap(heap_node* heap1, heap_node* heap2) {
	char tempd[32];

	int tempc = heap1->cnt;
	strcpy(tempd, heap1->data);

	heap1->cnt = heap2->cnt;
	strcpy(heap1->data, heap2->data);

	heap2->cnt = tempc;
	strcpy(heap2->data, tempd);
}

nptr create() {

	nptr nnode = (nptr)malloc(sizeof(node));
	nnode->lchild = nnode->rchild = NULL;
	nnode->cnt = 0;
	return nnode;

}


void search(nptr node, char* data, int* n_data) {
	
	if (node->cnt == 0) {
		strcpy(node->data, data);
		(*n_data)++;
	}
	if (!strcmp(data, node->data)) {
			(node->cnt)++;
	}
	else if (strcmp(data, node->data)<0) {
		if (node->lchild == NULL) {
			node->lchild = create();
		}
		search(node->lchild, data, n_data);
	}
	else {
		if (node->rchild == NULL) {
			node->rchild = create();
		}
		search(node->rchild, data, n_data);
	}
}

char* sort(char* str) {

	
	int i;
	for (i = 0;i < strlen(str) - 1;i++) {
		if (str[i] >= 48 && str[i] <= 57) {
			return NULL;
		}
	}
	
	if ((str[0] <= 64 || str[0] >= 91) && (str[0] <= 96 || str[0] >= 123)) {
		for (i = 0; i < strlen(str) - 1; i++) {
			str[i] = str[i + 1];
		}
		str[strlen(str) - 1] = NULL;
	}
	if ((str[strlen(str) - 1] <= 64 || str[strlen(str) - 1] >= 91) && (str[strlen(str) - 1] <= 96 || str[strlen(str) - 1] >= 123)) {
		str[strlen(str) - 1] = NULL;
	}
	return str;
}

//void MakeHeap(heap_node* heap, int *pidx, nptr node) {
//	
//	if (node) {
//		//printf("[%d] %s", node->cnt, node->data);
//		if ((*pidx) / 2 == 0) {
//			strcpy(heap[*pidx].data, node->data);
//			heap[*pidx].cnt = node->cnt;
//			(*pidx)++;
//		}
//		else {
//			printf("%d. [%d] %s\n", *pidx - 1, heap[*pidx - 1].cnt, heap[*pidx - 1].data);
//			if (heap[(*pidx) / 2].cnt < node->cnt) {
//
//				strcpy(heap[(*pidx)].data, heap[(*pidx) / 2].data);
//				heap[*pidx].cnt = heap[(*pidx) / 2].cnt;
//
//				strcpy(heap[(*pidx) / 2].data, node->data);
//				heap[(*pidx) / 2].cnt = node->cnt;
//				(*pidx++);
//			}
//			else {
//				strcpy(heap[*pidx].data, node->data);
//				heap[*pidx].cnt = node->cnt;
//				(*pidx)++;
//			}
//		}
//		
//		MakeHeap(heap, pidx, node->lchild);
//		MakeHeap(heap, pidx, node->rchild);
//	}
//}

void makeHeap(heap_node* heap, int* pidx, nptr node) {
	if (node) {
		if ((*pidx) / 2 == 0) {
			strcpy(heap[*pidx].data, node->data);
			heap[*pidx].cnt = node->cnt;
			(*pidx)++;
		}
		else {
			strcpy(heap[*pidx].data, node->data);
			heap[*pidx].cnt = node->cnt;
			int cur = *pidx;
			while (heap[cur / 2].cnt < heap[cur].cnt && cur>1) {
				swap(&heap[cur / 2], &heap[cur]);
				cur = cur / 2;
			}
			(*pidx)++;

		}
		makeHeap(heap, pidx, node->rchild);
		makeHeap(heap, pidx, node->lchild);

	}
}

void extract(heap_node* heap, int* pidx) {

	int i;
	int s;
	printf("[%d] %s\n", heap[1].cnt, heap[1].data);
	swap(&heap[1], &heap[*pidx]);
	(*pidx)--;

	for(i=1,s=1; 2*i<=(*pidx);i=s){
		if (heap[i].cnt < heap[2 * i].cnt || heap[i].cnt < heap[2 * i + 1].cnt) {
			if (heap[2 * i].cnt >= heap[2 * i + 1].cnt) {
				s = 2 * s;
			}
			else {
				s = 2 * s + 1;
			}
			swap(&heap[i], &heap[s]);
		}
		else {
			break;
		}
	}
}

void print(nptr root, int count) {
	if (root != NULL) {
		printf("[%d] %s\n", count, root->data);
		print(root->lchild, count + 1);
		print(root->rchild, count + 1);

	}
}

int main()
{
	int i = 1;
	int count = 0;
	FILE *fp;
	fopen_s(&fp, "test.txt", "rt");
	char str[32];
	
	nptr root = create();


	if (fp) {
		while (!feof(fp)) {
			fscanf(fp, "%s", str);
			if (sort(str) != NULL) {
				//printf("%s\n", str);
				search(root, str, &count);
			}
		}
	}
	//print(root, 0);
	heap_node* heap = (heap_node*)malloc((count+1) * sizeof(heap_node));
	
	makeHeap(heap, &i, root);
	//printf("%d", count);
	for (i = 1; i < 11;i++) {
		extract(heap, &count);
		//printf("[%d] %s\n", heap[i].cnt, heap[i].data);
	}

	return 0;
}

