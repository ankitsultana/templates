#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#define MAXN 100
#define MAXW 100
typedef struct node node;
typedef struct bst bst;

struct node {
    char word[MAXW];
    int left_ht, right_ht, factor;
    node *left, *right, *parent;
};
void word_copy(char lhs[], char rhs[]) {
    int iter = 0;
    while(rhs[iter] != '\0') {
        lhs[iter] = rhs[iter];
        iter++;
    }
}
void node_copy(node *lhs, node *rhs) {
    word_copy(lhs->word, rhs->word);
    lhs->left = rhs->left;
    lhs->right = rhs->right;
    lhs->parent = rhs->parent;
}
struct bst {
    node* HEAD;
    int size;
};

node* get_new_node() {
    node* new_node = (node*) malloc(sizeof(node));
    new_node->left = new_node->right = new_node->parent = NULL;
    new_node->left_ht = new_node->right_ht = new_node->factor = 0;
    return new_node;
}

bst* create_bst() {
    bst* temp = (bst*) malloc(sizeof(bst));
    temp->HEAD = NULL;
    temp->size = 0;
    return temp;
}
node* bst_insert(bst* root, char word[MAXW]) {
    node *res = NULL;
    node x;
    x.left = NULL, x.right = NULL, x.parent = NULL;
    word_copy(x.word, word);
    node** temp = &(root->HEAD), *par = NULL;
    while(*temp != NULL) {
        if(strcmp(x.word, (*temp)->word) <= 0) {
            (*temp)->left_ht++;
            (*temp)->factor++;
            par = *temp;
            temp = &(*temp)->left;
        } else {
            (*temp)->right_ht++;
            (*temp)->factor--;
            par = *temp;
            temp = &(*temp)->right;
        }
        if((*temp) != NULL) {
            if((*temp)->factor > 1 || (*temp)->factor < -1)
                res = (*temp);
        }
    }
    *temp = get_new_node();
    x.parent = par;
    node_copy(*temp, &x);
    return res;
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

void print_bst(node *temp) {
    if(temp == NULL)    return ;
    printf("%s\n", temp->word);
    print_bst(temp->left);
    print_bst(temp->right);
}

void left_rotate(bst *my_bst, node *x) {
    node *y = x->right;
    assert(y != NULL);
    x->right = y->left;
    if(x->right != NULL) {
        x->right->parent = x;
    }
    y->parent = x->parent;
    if(y->parent == NULL) {
        my_bst->HEAD = y;
    } else if(x->parent->left == x) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}
void right_rotate(bst *my_bst, node *y) {
    node *x = y->left;
    y->left = x->right;
    if(y->left != NULL) {
        y->left->parent = y;
    }
    x->parent = y->parent;
    if(y->parent == NULL) {
        my_bst->HEAD = x;
    } else if(y->parent->left == y) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
}

char input[MAXN][MAXW];

void balance(bst* my_bst, node *root) {
    if(root->factor == -2 && root->left->factor == -1) {
        right_rotate(my_bst, root);
    } else if(root->factor == -2 && root->left->factor == 1) {
        left_rotate(my_bst, root->left);
        right_rotate(my_bst, root);
        if(root->parent->left != NULL) {
        }
    } else if(root->factor == 2 && root->right->factor == -1) {
        right_rotate(my_bst, root->right);
        left_rotate(my_bst, root);
    } else if(root->factor == 2 && root->right->factor == 1) {
        left_rotate(my_bst, root);
    } else {
        return ;
    }
    if(root->parent != NULL) {
        root->parent->factor = 1;
        root->parent->left_ht = root->parent->right_ht = 1;
    }
    root->factor = 0;
    root->left_ht = root->right_ht = 0;
}

int main() {
    bst* my_bst = create_bst();
    my_bst->HEAD = get_new_node();
    int cnt = 0;
    node* temp;
    while(scanf("%s", input[cnt++]) != EOF) {
        temp = bst_insert(my_bst, input[cnt-1]);
        if(temp != NULL) {
            // avl_the_shit
        }
    }
    print_bst(my_bst->HEAD);
    return 0;
}
