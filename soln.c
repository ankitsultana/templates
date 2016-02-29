#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#define MAXN 1002
#define LEFT(i) (i*2)
#define RIGHT(i) (i*2+1)
typedef struct node node;
typedef struct heap heap;

// Utilities that C doesn't provide
int min(int i, int j) { return i < j ? i : j; }
void swap(node **x, node **y) { node* temp = *x; *x = *y; *y = temp; }
// Awesome heap
struct node {
	int key, order;
	node *left, *right, *parent;
	char c;
};
node* create_node(int key, char c) {
	node *temp = (node*)malloc(sizeof(node));
	temp->left = (temp->right = (temp->parent = NULL));
	temp->key = key, temp->c = c;
	return temp;
}
struct heap {
	node *arr[MAXN];
	int size, pool;
};
void printer(heap *x) {
	int iter = 0;
	for(iter = 1; iter <= x->size; iter++)	printf("%d ", x->arr[iter]->key);
	printf("\n");
}
bool compare(heap *x, int i, int j) {
	return x->arr[i]->key == x->arr[j]->key ?
		x->arr[i]->order < x->arr[j]->order: x->arr[i]->key < x->arr[j]->key;
}
void min_heapify(heap *x, int i) {		// min_heapify the given heap
	int iter = i, temp_idx;
	while(iter <= x->size/2) {
		if(RIGHT(iter) > x->size && compare(x, LEFT(iter), i)) {
			temp_idx = LEFT(iter);
		} else if(RIGHT(iter) <= x->size && compare(x, compare(x, LEFT(iter), RIGHT(iter))? LEFT(iter): RIGHT(iter), iter)) {
			temp_idx = compare(x, RIGHT(iter), LEFT(iter))?
				RIGHT(iter): LEFT(iter);
		} else {
			break;
		}
		swap(&x->arr[iter], &x->arr[temp_idx]);
		iter = temp_idx;
	}
}
node* extract_min(heap *x) {	// Take out topmost pointer and return it
	node* temp = x->arr[1];
	swap(&x->arr[1], &x->arr[x->size]);
	x->size--;
	min_heapify(x, 1);
	return temp;
}
void bubble_up(heap *x, int idx) {
	while(idx > 1) {
		if(!compare(x, idx/2, idx)) {
			swap(&x->arr[idx/2], &x->arr[idx]);
			idx /= 2;
		} else {
			break;
		}
	}
}
void min_insert(heap *x, node *val) {
	x->size++;
	val->order = ++x->pool;
	x->arr[x->size] = val;
	bubble_up(x, x->size);
}
void dfs(node *root) {
	printf("%c\n", root->c);
	if(root->left != NULL)
		dfs(root->left);
	if(root->right != NULL)
		dfs(root->right);
}
void post_order(node *root) {
	if(root->left != NULL)
		post_order(root->left);
	if(root->right != NULL)
		post_order(root->right);
	printf("%c", root->c);
}
void in_order(node *root) {
	if(root->left != NULL)
		in_order(root->left);
	printf("%c", root->c);
	if(root->right != NULL)
		in_order(root->right);
}

int freq[MAXN] = {0};
char input[MAXN];
char out_mapper[100][100];

void huffman(node* root, char tillnow[], int d) {
	if(root->left == NULL && root->right == NULL) {	// leaf
		assert(root->c >= 'A' && root->c <= 'Z');
		int iter;
		for(iter = 0; iter < d; iter++) {
			out_mapper[root->c][iter] = tillnow[iter];
		}
		out_mapper[root->c][d] = '\0';
		return ;
	}
	tillnow[d] = '0';
	if(root->left != NULL)
		huffman(root->left, tillnow, d+1);
	tillnow[d] = '1';
	if(root->right != NULL)
		huffman(root->right, tillnow, d+1);
}

int main() {
	scanf("%s", input+1);
	int size = strlen(input+1), iter;
	for(iter = 1; iter <= size; iter++) {
		freq[input[iter]]++;
	}
	heap *my_heap = (heap*)malloc(sizeof(heap));;
	my_heap->pool = 0;
	node *temp_node[MAXN];
	for(iter = 'A'; iter <= 'Z'; iter++) {
		if(freq[iter] > 0) {
			temp_node[iter] = create_node(freq[iter], iter);
			min_insert(my_heap, temp_node[iter]);
		}
	}
	int answer = my_heap->size;
	while(my_heap->size > 1) {
		node *one = extract_min(my_heap), *two = extract_min(my_heap);
		assert(one != two);
		node *more = create_node(one->key + two->key, '0');
		more->left = one, more->right = two;
		one->parent = more, two->parent = more;
		min_insert(my_heap, more);
		answer++;
	}
	printf("%d\n", answer);
	node *HEAD = extract_min(my_heap);
	post_order(HEAD);
	printf("\n");
	in_order(HEAD);
	printf("\n");
	char tillnow[100];
	huffman(HEAD, tillnow, 0);
	for(iter = 1; iter <= size; iter++)
		printf("%s", out_mapper[input[iter]]);
	printf("\n");
	return 0;
}
