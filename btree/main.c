/*
二叉树插入顺序：小数往左，大数往右
比当前节点小的数放到左子树，比当前节点大的数放到右子树

todo 设置递归层数的上限
*/

#include <stdio.h>
#include <stdlib.h>
#include <queue.h>

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

static struct node_st *g_tree = NULL;

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
    print_s(&root->data);

    // 再画左子树
    draw_(root->l, level + 1);
}

void draw(struct node_st *root)
{
    draw_(root, 0);
    printf("\n\n");
    getchar();
}

static int get_num(struct node_st *root)
{
    if (root == NULL) {
        return 0;
    }

    return get_num(root->l) + get_num(root->r) + 1;
}

static struct node_st *find_min(struct node_st *root)
{
    if (root->l == NULL) {
        return root;
    }
    return find_min(root->l);
}

static struct node_st *find_max(struct node_st *root)
{
    if (root->r == NULL) {
        return root;
    }
    return find_max(root->r);
}

static void turn_left(struct ndoe_st **root)
{
    // 左旋
    // 原来的根节点作为左子树
    // 原来的右节点作为根节点
    struct node_st *cur = *root;
    *root = cur->r;
    cur->r = NULL;
    find_min(*root)->l = cur;

    // struct node_st *tmp = find_min(*root);
    // tmp->l = cur;
    // draw_tree(g_tree);
}

static void turn_right(struct node_st **root)
{
    // 右旋
    // 原来的根节点作为右子树
    // 原来的左子节点作为根节点
    struct node_st *cur = *root;
    *root = cur->l;
    cur->l = NULL;
    find_max(*root)->r = cur;
    // draw_tree(g_tree);

    // struct node_st *tmp = find_max(*root);
    // tmp->r = cur;
}

void balance(struct node_st **root)
{
    if (*root == NULL) {
        return;
    }
    while(1) {
        // chatgpt给出的平衡条件，两边节点的高度差值不超过1
        // 视频中的平衡条件，左子树的节点数和右子树的节点数的差值不超过1
        int sub = get_num((*root)->l) - get_num((*root)->r);
        if (sub >=-1 && sub <= 1) {
            break;
        }

        if (sub < -1) {
            turn_left(root);
        } else {
            turn_right(root);
        }
    }

    balance(&(*root)->l);  // 平衡左子树
    balance(&(*root)->r);  // 平衡右子树
}

int delete_left_up(struct node_st **root, int id)
{
    //删除根节点后，把左子树的节点作为新的根节点
    struct node_st **node = root;

    while (*node != NULL) {
        if (id < (*node)->data.id) {
            node = &(*node)->l;
        }
        if (id > (*node)->data.id) {
            node = &(*node)->r;
        }
        if (id == (*node)->data.id) {
            break;
        }
    }

    //没找到
    if (*node == NULL) {
        return 0;
    }

    struct node_st *cur = *node;

    if (cur->l == NULL) {
        *node = cur->r;
    } else {
        *node = cur->l;
        find_max(cur->l)->r = cur->r;
    }
    free(cur);
    return 0;
}

int delete_right_up(struct node_st **root, int id)
{
    //删除根节点后，把右子树的节点作为新的根节点
    struct node_st **node = root;

    while (*node != NULL) {
        if (id < (*node)->data.id) {
            node = &(*node)->l;
        }
        if (id > (*node)->data.id) {
            node = &(*node)->r;
        }
        if (id == (*node)->data.id) {
            break;
        }
    }

    //没找到
    if (*node == NULL) {
        return 0;
    }

    struct node_st *cur = *node;

    if (cur->r == NULL) {
        *node = cur->l;
    } else {
        *node = cur->r;
        find_min(cur->r)->l = cur->l;
    }
    free(cur);
    return 0;
}

void travel_pre_order(struct node_st *root)
{
    // 先序遍历
    if (root == NULL) {
        return;
    }

    print_s(&root->data);
    travel_pre_order(root->l);
    travel_pre_order(root->r);
}

void travel_post_order(struct node_st *root)
{
    // 后序遍历
    if (root == NULL) {
        return;
    }

    travel_post_order(root->l);
    travel_post_order(root->r);
    print_s(&root->data);
}

void travel_inorder(struct node_st *root)
{
    // 中序遍历
    if (root == NULL) {
        return;
    }

    travel_inorder(root->l);
    print_s(&root->data);
    travel_inorder(root->r);
}

void travel_level_order(struct node_st *root)
{
    // 层序遍历
    QUEUE *qu = queue_create(sizeof(struct node_st *));
    struct node_st *cur;
    if (qu == NULL) {
        return;
    }

    queue_en(qu, &root);

    while(1) {
        int ret = queue_de(qu, (void *)&cur);
        if (ret == -1) {
            break;
        }
        print_s(&cur->data);

        if(cur->l != NULL) {
            queue_en(qu, &cur->l);
        }
        if (cur->r != NULL) {
            queue_en(qu, &cur->r);
        }
    }

    queue_destory(qu);
}

int main()
{
    int arr[] = {1, 2, 3, 7, 6, 5, 9, 8, 4};
    struct score_st tmp, *datap;

    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        tmp.id = arr[i];
        snprintf(tmp.name, NAMESIZE, "stu%d", arr[i]);
        tmp.math = rand() % 100;
        tmp.chinese = rand() % 100;
        insert(&g_tree, &tmp);
    }

    // 画树
    // draw(tree);
    draw_tree(g_tree);

    printf("\n");

    // 平衡二叉树
    balance(&g_tree);
    draw_tree(g_tree);

    //遍历
    travel_pre_order(g_tree);
    printf("\n\n");

    travel_inorder(g_tree);
    printf("\n\n");

    travel_post_order(g_tree);
    printf("\n\n");

    travel_level_order(g_tree);
    printf("\n\n");


#if 0
    // 删除
    int tmpid = 5;
    // delete_left_up(&g_tree, tmpid);
    delete_right_up(&g_tree, tmpid);
    draw_tree(g_tree);
#endif

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