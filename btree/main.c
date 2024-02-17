/*
二叉树插入顺序：小数往左，大数往右
比当前节点小的数放到左子树，比当前节点大的数放到右子树
*/

#include <stdio.h>
#include <stdlib.h>

#define NAMESIZE 32

struct score_st {
    int id;
    char name[NAMESIZE];
    int math;
    int chinese;
};

struct node_st {
    struct score_st data;
    struct node_st *l, *r;
};

/*
根据id，插入节点。如果data的id小于等于当前节点，就挂到左子树，否则挂到右子树
*/
int insert(struct node_st **root, struct score_st *data)
{
    struct node_st *node = NULL;
    if (*root == NULL) {
        // 空树
        node = malloc(sizeof(*node));
        if (node == NULL) {
            return -1;
        }

        node->data = *data;
        node->l = NULL;
        node->r = NULL;

        *root = node;
        return 0;
    }

    if (data->id <= (*root)->data.id) {
        return insert(&(*root)->l, data);
    } else {
        return insert(&(*root)->r, data);
    }
}

struct score_st find(struct node_st *root, int id)
{
    if (id == root->data.id) {
        return &root->data;
    }

    if (id < root->data.id) {
        find()
    }
}

int main()
{
    int arr[] = {1, 2, 3, 7, 6, 5, 9, 8, 4};
    struct node_st *tree = NULL;
    struct score_st tmp;

    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        tmp.id = arr[i];
        snprintf(tmp.name, NAMESIZE, "stu%d", arr[i]);
        tmp.math = rand() % 100;
        tmp.chinese = rand() % 100;
        insert(&tree, &tmp);
    }

    int tmpid = 2;
    find(tree, tmpid);

    exit(0);
}