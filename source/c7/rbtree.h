#ifndef C7_RBTREE_H
#define C7_RBTREE_H

struct c7_rbnode;
struct c7_rbpool;

enum c7_order {C7_LT, C7_EQ, C7_GT};

typedef enum c7_order (*c7_compare_t)(const void *key, const void *value);

struct c7_rbtree {
  c7_compare_t compare;
  struct c7_rbpool *pool;
  struct c7_rbnode *root;
};

void c7_rbtree_init(struct c7_rbtree *tree,
		    c7_compare_t compare,
		    struct c7_rbpool *pool);

void c7_rbtree_deinit(struct c7_rbtree *tree);

struct c7_rbnode *c7_rbtree_find(struct c7_rbtree *tree, const void *key);
void *c7_rbtree_add(struct c7_rbtree *tree, const void *key);
  
#endif
