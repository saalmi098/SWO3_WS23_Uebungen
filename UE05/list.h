#pragma once

typedef struct node_type {
    int                payload;
    struct node_type * p_next;
} node_type;

typedef node_type * list_type;
typedef void unary_function_type (int);

node_type * create_empty_list(void); // koennte genauso list_type returnen
void prepend (node_type * * pp_head, int const payload);
void apply (node_type * p_head, unary_function_type * pf);
void clear (node_type * * pp_head);
void reverse (node_type * * pp_head);