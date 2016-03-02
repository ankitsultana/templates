#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#define MAXN 10003
#define LL long long
#define LEFT(i) (i*2)
#define RIGHT(i) (i*2+1)
typedef struct node node;
typedef struct heap heap;

// Utilities that C doesn't provide
int min(int i, int j) { return i < j ? i : j; }
void swap(node **x, node **y) { node* temp = *x; *x = *y; *y = temp; }
LL expo(LL b, int e) { return e < 2?((e == 0)?1: b): ((e&1)?b*expo(b*b, e>>1):expo(b*b, e>>1));}
/*	Heap
 * * * * * * * * * * * * * */
struct node {
	int key, order;
	LL one, two;
	bool leaf;
	node *left, *right, *parent, *center;
};
node* create_node(int key, LL l, LL r) {
	node *temp = (node*)malloc(sizeof(node));
	temp->left = (temp->right = (temp->parent = (temp->center = NULL)));
	temp->key = key;
	temp->leaf = false;
	temp->one = l, temp->two = r;
	return temp;
}
int num_dgts(LL x) { int res = 0; while(x) { res++; x /= 10ll; } return res; }
struct heap {
	node *arr[MAXN];
	int size, pool;
};
heap* create_heap() {
	heap* temp = (heap*)malloc(sizeof(heap));
	temp->size = 0, temp->pool = 1000000;
	return temp;
}
void printer(heap *x) {
	int iter = 0;
	for(iter = 1; iter <= x->size; iter++) {
		printf("(%lld %lld)\n", x->arr[iter]->one, x->arr[iter]->two);
	} printf(" ========== \n");
}
bool compare(heap *x, int i, int j) {
	return x->arr[i]->key == x->arr[j]->key ?
		x->arr[i]->order < x->arr[j]->order: x->arr[i]->key < x->arr[j]->key;
}
void min_heapify(heap *x, int i) {		// min_heapify the given heap
	int iter = i, temp_idx;
	while(iter <= x->size/2) {
		if(RIGHT(iter) > x->size && compare(x, LEFT(iter), iter)) {
			temp_idx = LEFT(iter);
		} else if(RIGHT(iter) <= x->size && 
				compare(x, compare(x, LEFT(iter), RIGHT(iter)) ?LEFT(iter): RIGHT(iter), iter)) {
			temp_idx = compare(x, LEFT(iter), RIGHT(iter)) ?
					LEFT(iter): RIGHT(iter);
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
	val->order = --x->pool;
	x->arr[x->size] = val;
	bubble_up(x, x->size);
}
/*	End Heap  */
LL chop(LL x) {
	return x/expo(10ll, num_dgts(x)/2);  
}
LL last(LL x) {
	return x % expo(10ll, num_dgts(x)/2);  
}
LL convolve(LL x) {
	return chop(x) + last(x);
}

// Parts:
// 		1: Create a priority queue 		==> DONE
// 		2: Create tree and store nodes in queue while traversing
// 		3: Print the shit
heap* pq;
void tree(node** root, LL l, LL r, int d) {
	min_insert(pq, *root);
	tree(&(*root)->left, l, r, d+1);
	tree(&(*root)->center, l, r, d+1);
	tree(&(*root)->right, l, r, d+1);
}

/* Main Function
 * * * * * * * * * * */
char input[MAXN];
int main() {
	scanf("%s", input+1);
	pq = create_heap();
	LL l, r;
	int base_level = 100000;
	node* HEAD = create_node(base_level, l, r);
	return 0;
}

