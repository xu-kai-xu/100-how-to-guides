/*
把广义表读出来，还原成树

*/

#include <stdio.h>
#include <stdlib.h>

#define NAMESIZE 32
#define FNAME "out"

struct node_st {
    char data;
    struct node_st *l, *r;
};

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
    // getchar();
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

struct node_st *load_(FILE *fp)
{
    struct node_st *root = NULL;
    int c;
    c = fgetc(fp);

    if (c != '(') {
        fprintf(stderr, "fgetc() failed\n");
        exit(1);
    }

    // 不可能有2个连续的左括号
    c = fgetc(fp);

    if (c == ')') {
        return NULL;
    }
    root = malloc(sizeof(*root));
    if (root == NULL) {
        exit(1);
    }
    root->data = c;
    root->l = load_(fp);
    root->r = load_(fp);
    c = fgetc(fp);  // 读掉右括号
    printf("c = %c\n", c);
    if (c != ')') {
        fprintf(stderr, "fgetc get `)` failed\n");
        exit(1);
    }
    return root;
}

struct node_st *load(const char *path)
{
    struct node_st *root = NULL;
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        return NULL;
    }

    root = load_(fp);
    fclose(fp);
    return root;
}

void free_tree(struct node_st *root)
{
    if (root == NULL) {
        return;
    }
    free_tree(root->l);
    free_tree(root->r);
    free(root);
    // printf("%p\n", root);
    // printf("data = %c\n", root->data);
    // printf("%p\n", root->l);
    // printf("%p\n", root->r);
}

int main()
{
    struct node_st *root = load(FNAME);

    // 画树
    draw(root);
    // draw_tree(root);
    printf("\n");

    //释放内存
    free_tree(root);

    exit(0);
}