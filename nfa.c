#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#define MAXN 100

int list[MAXN][MAXN];
int sizes[MAXN];
int wt[MAXN][MAXN];
int label[MAXN];
int n;

// take an input binary string, incrementement it by 1
void increment(int input[], int x) {
	int iter = 0, first = -1;
	while(iter < x) {
		if(input[iter] == 0) {
			first = iter;
			break;
		}
		iter++;
	}
	input[first] = 1;
	for(iter = first-1; iter >= 0; iter--) {
		input[iter] = 0;
	}
}

void printlist(int x) {
	int iter = 0;
	while(iter < sizes[x]) {
		printf("(%d, %d) ", list[x][iter], wt[x][iter]);
		iter++;
	} printf("\n");
}

void printer(int input[], int size) {
	int iter = size-1;
	while(iter >= 0) {
		printf("%d", input[iter--]);
	} printf("\n");
}

void set(int input[], int x) {
	int iter = 0;
	while(iter < x) {
		input[iter] = 0;
		iter++;
	}
}

void debug(int size) {
	int input[MAXN] = {0};
	int temp = 0, upper = 1<<size;
	while(temp < upper) {
		printer(input, size);
		increment(input, size);
		temp++;
	}
}

bool rec(int root, int input[], int size, int idx) {
	if(idx == size) {
		return label[root] == 1;
	}
	int iter;
	bool res = false;
	for(iter = 0; iter < sizes[root]; iter++) {
		if(wt[root][iter] == input[idx]) {
			res |= rec(list[root][iter], input, size, idx+1);
		}
		if(res)	return true;
	}
	return false;
}

int main() {
	scanf("%d", &n);
	int a, num_out, lab, dest, iter;
	for(iter = 1; iter <= n; iter++) {
		scanf("%d %d %d", &a, &lab, &num_out);
		label[a] = lab;
		int inner_iter;
		for(inner_iter = 0; inner_iter < num_out; inner_iter++) {
			scanf("%d %d", &lab, &dest);
			list[a][inner_iter] = dest;
			wt[a][inner_iter] = lab;
			sizes[a]++;
		}
	}
	// INPUT DONE //////////////////////////
	int input[MAXN] = {0}, size, counter = 0;
	if(label[1] == 1) {
		printf("e\n");
		counter++;
	}
	for(size = 0; counter < 10; size++) {
		int inner = 0, upper = 1<<size;
		set(input, size);
		while(inner++ < upper && counter < 10) {
			if(rec(1, input, size, 0)) {
				printer(input, size);
				counter++;
			}
			increment(input, size);
		}
	}
	return 0;
}
