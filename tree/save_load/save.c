/*
把树用广义表描述，存储到文件

*/

#include <stdio.h>
#include <stdlib.h>

#define FNAME "out"

#define NAMESIZE 32

struct node_st {
    char data;
    struct node_st *l, *r;
};

static struct node_st *g_tree = NULL;

/*
根据id，插入节点。如果data的id小于等于当前节点，就挂到左子树，否则挂到右子树
*/
int insert(struct node_st **root, int data)
{
    struct node_st *node = NULL;
    if (*root == NULL) {
        // 空树
        node = malloc(sizeof(*node));
        if (node == NULL) {
            return -1;
        }

        node->data = data;
        node->l = NULL;  // 防止野指针
        node->r = NULL;  // 防止野指针

        *root = node;
        return 0;
    }

    if (data <= (*root)->data) {
        return insert(&(*root)->l, data);
    } else {
        return insert(&(*root)->r, data);
    }
}


void draw_tree_node(struct node_st *root, int level)
{
    int i, j;
    if (root == NULL) {
        return;
    }

    // 画根节点
    printf("%c\n", root->data);

    // 画右子树
    if (root->r != NULL) {
        for (i = 0; i < level * 3; i++) {
            printf(" ");
        }
        printf("|");
        printf("--");
        draw_tree_node(root->r, level + 1);
    }

    // 画左子树
    if (root->l != NULL) {
        for (i = 0; i < level * 3; i++) {
            printf(" ");
        }
        printf("|");
        printf("--");
        draw_tree_node(root->l, level + 1);
    }
}

/*
可以采用类似于tree命令的方式画树
*/
void draw_tree(struct node_st *root)
{
    draw_tree_node(root, 0);
    printf("\n\n");
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
    printf("%c\n", root->data);

    // 再画左子树
    draw_(root->l, level + 1);
}

void draw(struct node_st *root)
{
    draw_(root, 0);
    printf("\n\n");
}

int save_(struct node_st *root, FILE *fp)
{
    fputc('(', fp);

    if (root == NULL) {
        // 叶子节点的孩子
        fputc(')', fp);
        return 0;
    }

    fputc(root->data, fp);

    save_(root->l, fp);
    save_(root->r, fp);

    fputc(')', fp);
    return 0;
}

int save(struct node_st *root, const char *path)
{
    FILE *fp = fopen(path, "w");
    if (fp == NULL) {
        return -1;
    }

    save_(root, fp);

    return 0;
}

int main()
{
    char arr[] = "cefadjbh";
    struct score_st *datap;

    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]) - 1; i++) {
        insert(&g_tree, arr[i]);
    }

    // 画树
    draw(g_tree);
    printf("\n\n");

    draw_tree(g_tree);
    printf("\n");

    save(g_tree, FNAME);

    exit(0);
}