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

void print_s(struct score_st *d)
{
    printf("%d %s %d %d\n", d->id, d->name, d->math, d->chinese);
    // printf("%d\n", d->id);
}

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
        node->l = NULL;  // 防止野指针
        node->r = NULL;  // 防止野指针

        *root = node;
        return 0;
    }

    if (data->id <= (*root)->data.id) {
        return insert(&(*root)->l, data);
    } else {
        return insert(&(*root)->r, data);
    }
}

struct score_st *find(struct node_st *root, int id)
{
    if (root == NULL) {
        return NULL;
    }
    if (id == root->data.id) {
        return &root->data;
    }

    if (id <= root->data.id) {
        return find(root->l, id);
    }
    if (id > root->data.id) {
        return find(root->r, id);
    }
}

void draw_tree_node(struct node_st *root, int level)
{
    int i, j;
    if (root == NULL) {
        return;
    }

    // 画根节点
    printf("%d\n", root->data.id);


    // 画左子树
    if (root->l != NULL) {
        for (i = 0; i < level * 3; i++) {
            printf(" ");
        }
        printf("|");
        printf("--");
        draw_tree_node(root->l, level + 1);
    }

    // 画右子树
    if (root->r != NULL) {
        for (i = 0; i < level * 3; i++) {
            printf(" ");
        }
        printf("|");
        printf("--");
        draw_tree_node(root->r, level + 1);
    }
}

/*
可以采用类似于tree命令的方式画树
*/
void draw_tree(struct node_st *root)
{
    draw_tree_node(root, 0);
}

void draw_(struct node_st *root, int level)
{
    if (root == NULL) {
        return;
    }

    // 先画右子树
    draw_(root->r, level + 1);

    // 再画当前节点
    for (int i = 0; i < level; i++) {
        printf("    ");
    }
    print_s(&root->data);

    // 再画左子树
    draw_(root->l, level + 1);
}

void draw(struct node_st *root)
{
    draw_(root, 0);
}


int main()
{
    int arr[] = {1, 2, 3, 7, 6, 5, 9, 8, 4};
    struct node_st *tree = NULL;
    struct score_st tmp, *datap;

    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        tmp.id = arr[i];
        snprintf(tmp.name, NAMESIZE, "stu%d", arr[i]);
        tmp.math = rand() % 100;
        tmp.chinese = rand() % 100;
        insert(&tree, &tmp);
    }

    // 画树
    // draw(tree);
    draw_tree(tree);

#if 0
    int tmpid = 12;
    datap = find(tree, tmpid);
    if(datap == NULL) {
        printf("can not find id: %d\n", tmpid);
    } else {
        print_s(datap);
    }
#endif
    exit(0);
}