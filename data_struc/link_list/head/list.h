#ifndef LIST_H__
#define LIST_H__

typedef int datatype;

typedef struct node_st {
    datatype data;
    struct node_st *next;
} list;

list *list_create();

list *list_node_find(list *me, datatype *data);

int list_insert_at(list *me, int i, datatype *data);

int list_insert_at_start(list *me, datatype *data);

int list_insert_at_end(list *me, datatype *data);

int list_order_insert(list *me, datatype *data);

int list_delete_at(list *me, int i, datatype *data);

int list_delete(list *me, datatype *data);

int list_delete_at_start(list *me);

int list_delete_at_end(list *me);

int list_isempty(list *me);

void list_display(list *me);

void list_destory(list *me);



#endif /* LIST_H__ */