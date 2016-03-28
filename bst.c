#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#define MAXN 100
typedef struct task task;
typedef struct node node;
typedef struct bst bst;

struct task {
    int i, r, c, p;
};
struct node {
    task T;
    node *left, *right, *parent;
};
void node_copy(node *lhs, node *rhs) {
    lhs->T.i = rhs->T.i, lhs->T.r = rhs->T.r, lhs->T.c = rhs->T.c, lhs->T.p = rhs->T.p;
    lhs->left = rhs->left;
    lhs->right = rhs->right;
    lhs->parent = rhs->parent;
}
void task_copy(task *lhs, task *rhs) {
    assert(lhs != NULL && rhs != NULL);
    lhs->i = rhs->i;
    lhs->r = rhs->r;
    lhs->c = rhs->c;
    lhs->p = rhs->p;
}
struct bst {
    node* HEAD;
    int size;
};

node* get_new_node() {
    node* new_node = (node*) malloc(sizeof(node));
    new_node->left = new_node->right = new_node->parent = NULL;
    return new_node;
}
task* get_new_task() {
    return (task*) malloc(sizeof(task));
}

bst* create_bst() {
    bst* temp = (bst*) malloc(sizeof(bst));
    temp->HEAD = NULL;
    temp->size = 0;
    return temp;
}
void bst_insert(bst* root, task t) {
    node x;
    x.left = NULL, x.right = NULL, x.parent = NULL;
    task_copy(&x.T, &t);
    node** temp = &(root->HEAD), *par = NULL;
    while(*temp != NULL) {
        if(x.T.p <= (*temp)->T.p) {
            par = *temp;
            temp = &(*temp)->left;
        } else {
            par = *temp;
            temp = &(*temp)->right;
        }
    }
    *temp = get_new_node();
    x.parent = par;
    node_copy(*temp, &x);
}

// Transplant node at two to one's position
// one has to be non NULL
void bst_transplant(bst *root, node *one, node *two) {
    if(one->parent == NULL) {
        root->HEAD = two;
        if(root->HEAD != NULL)
            root->HEAD->parent = NULL;
    } else {
        if(one == one->parent->left) {
            one->parent->left = two;
        } else {
            one->parent->right = two;
        }
        if(two != NULL) {
            two->parent = one->parent;
        }
    }
}

// Delete highest key node
void bst_delete(bst *root) {
    node* temp = root->HEAD;
    if(temp == NULL)    return ;
    while(temp->right != NULL) {
        temp = temp->right;
    }
    bst_transplant(root, temp, temp->left);
}
node* get_highest_node(bst *root) {
    node* temp = root->HEAD;
    if(temp == NULL)    return temp;
    while(temp->right != NULL)  temp = temp->right;
    return temp;
}

task arr[MAXN];
task* processor;

void print_bst(node *temp) {
    if(temp == NULL)    return ;
    printf("NODE: %d\n", temp->T.i);
    print_bst(temp->left);
    print_bst(temp->right);
}

int main() {
    freopen("input.in", "rb", stdin);
    bst* my_bst = create_bst();
    int a, b, c, d, n = 0;
    while(scanf("%d %d %d %d", &a, &b, &c, &d) != EOF) {
        arr[n].i = a, arr[n].r = b, arr[n].c = c, arr[n].p = d;
        n++;
    }
    int iter = 0, done = 0, t = 0;
    processor = NULL;
    while(true) {
        // decrease time
        if(processor != NULL) {
            processor->c--;
            if(processor->c == 0) {
                processor = NULL, done++;
            }
        }
        if(done == n)   break;
        // insert new tasks
        while(iter < n && arr[iter].r <= t) {
            bst_insert(my_bst, arr[iter++]);
        }
        // insert highest priority task in processor
        if(my_bst->HEAD != NULL) {
            node* highest = get_highest_node(my_bst);
            if(processor == NULL) {
                processor = get_new_task();
                task_copy(processor, &highest->T);
                bst_delete(my_bst);
            } else if(processor->p < highest->T.p) {
                task temp_t = *processor;
                task_copy(processor, &highest->T);
                bst_delete(my_bst);
                bst_insert(my_bst, temp_t);
            }
        }
        if(processor != NULL) {
            printf("%d ", processor->i);
        } else {
            printf("0 ");
        }
        if(my_bst->HEAD != NULL)
            assert(my_bst->HEAD->parent == NULL);
        t++;
    } printf("\n");
    return 0;
}
