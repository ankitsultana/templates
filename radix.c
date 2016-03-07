/*
 * Author: Ankit Sultana
 * ID:     2014A7PS070P
 */
//#define DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#define MAXN 100 	// Number of different words
#define MAXP 100
#define MAXLEN 100
#define RADIX 27
#define DECODE(x) (int)(x - 'a' + 1)
#define ENCODE(x) (char)(x == 0?'$': (x + 96))
int* arr[MAXN];
int num_pages[MAXN], pages[MAXP][MAXN], num_page, num_dist, max_len;

int max(int x, int y) {
	return x > y ? x: y;
}

void counting_sort(int* arr[], int k) {
	int temp[RADIX] = {0}, iter;
	int *res[MAXN];
	for(iter = 0; iter < num_dist; iter++) {
		temp[arr[iter][k]]++;
	}
	for(iter = 1; iter < RADIX; iter++) {
		temp[iter] += temp[iter-1];
	}
	for(iter = num_dist - 1; iter >= 0; iter--) {
		res[--temp[arr[iter][k]]] = arr[iter];
	}
	for(iter = 0; iter < num_dist; iter++)
		arr[iter] = res[iter];
}

void printcrap(int *arr[], int idx) {
	int iter = 0;
	while(arr[idx][iter] != 0)
		printf("%c", ENCODE(arr[idx][iter])), iter++;
}

void addword(char word[], int size, int p) {
	if(size == 0)	return ;
	int iter = 0;
	for(iter = 0; iter < size; iter++) {
		if(word[iter] >= '0' && word[iter] <= '9')
			return ;
		else if(word[iter] >= 'a' && word[iter] <= 'z') {
		} else if(word[iter] >= 'A' && word[iter] <= 'Z') {
			word[iter] = word[iter] - 'A' + 'a';
		} else {
			assert(false);
		}
	}
#ifdef DEBUG
	printf("ADDING: ");
	int fack;
	for(fack = 0; fack < size; fack++) {
		printf("%c", word[fack]);  
	} printf("\n");
#endif
	// word is valid
	int idx = -1;
	for(iter = 0; iter < num_dist; iter++) {  // check if word read already
		int i = 0;
		while(arr[iter][i] != 0 && i < size && arr[iter][i] == DECODE(word[i])) {
			i++;
		}
		if(i == size && arr[iter][i] == 0) {
			idx = iter;
			break;
		}
	}
	if(idx == -1)
		idx = num_dist++;
	if(num_pages[idx] > 0 && pages[idx][num_pages[idx] - 1] == p) {
		// not a new page
	} else {
		pages[idx][num_pages[idx]++] = p;
	}
	max_len = max(max_len, size);
	for(iter = 0; iter < size; iter++) {
		arr[idx][iter] = DECODE(word[iter]);
	}
}

void mygetline(char input[], int *size) {
	*size = 0;
	char x = getchar();
	while((x = getchar()) != '\n') {
		input[(*size)++] = x;
	}
	input[*size] = '\0';
}

void scanline(int p) {
	int iter = 0, s, size;
	char input[1000];
	mygetline(input, &size);
#ifdef DEBUG
	printf("%s\n", input);
#endif
	if(input[size-1] == '\n' || input[size-1] == EOF)
		size--;
	char word[MAXLEN];
	for(s = 0, iter = 0; iter < size; iter++) {
		if(input[iter] == ' ' || input[iter] == '.') {	// delimiters
			addword(word, s, p);
			s = 0;
		} else {
			word[s++] = input[iter];
		}
	}
}

int main() {
	int iter;
	for(iter = 0; iter < MAXN; iter++) {
		arr[iter] = (int*) malloc(sizeof(int) * MAXLEN);
		int i;
		for(i = 0; i < MAXLEN; i++)
			arr[iter][i] = 0;
	}
	num_dist = 0, max_len = 0;
	int p = 0;
	while(scanf("%d", &p) != EOF) {
		fflush(stdin);
		scanline(p);
	}
#ifdef DEBUG
	for(iter = 0; iter < num_dist; iter++) {
		int i = 0;
		while(arr[iter][i] != 0) {
			printf("%c", ENCODE(arr[iter][i]));
			i++;
		} printf("\n");
	}
#endif
	for(iter = 0; iter < num_dist; iter++)
		arr[iter][max_len+1] = iter;
	// Assume have all words collected and encoded to base 27
	// and stored int* arr[];
	// Also original index is stored as last element, arr[idx][max_len+1]
	for(iter = max_len - 1; iter >= 0; iter--)
		counting_sort(arr, iter);
	for(iter = 0; iter < num_dist; iter++) {
		int one, idx = arr[iter][max_len+1];
		printcrap(arr, iter);
		printf(" ");
		for(one = 0; one < num_pages[idx]; one++) {
			printf("%d", pages[idx][one]);
			if(one != num_pages[idx] - 1) {
				printf(", ");
			}
		}
		printf("\n");
	}
	return 0;
}
