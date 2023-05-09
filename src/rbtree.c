#include "rbtree.h"
#include <stdlib.h>
#include <stdio.h>

void rbtree_insert_fixup(rbtree *t, node_t *z);
void rbtree_delete_fixup(rbtree *t, node_t *x);
void right_rotate(rbtree *t, node_t *x);
void left_rotate(rbtree *t, node_t *x);
void transplant(rbtree *t, node_t *x, node_t *y);

/*------------------------------------------------------------------------------*/

// TODO: initialize struct if needed
rbtree *new_rbtree(void)
{
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  node_t *nilnode = (node_t *)calloc(1,sizeof(node_t));

  nilnode->color = RBTREE_BLACK;
  p->nil = nilnode;
  p->root = nilnode;

  return p;
}

/*------------------------------------------------------------------------------*/

// TODO: reclaim the tree nodes's memory
void delete_rbtree(rbtree *t){

  node_t *cur = t->root;
  node_t *temp;

  while (cur != t->nil){

    if (cur->left != t->nil){
        cur = cur->left;
    }

    else if (cur->right != t->nil){
      temp = cur->right;

      while (temp->left != t->nil){
          temp = temp->left;
      }

      cur = temp;
    }

    else {
      temp = cur;
      cur = cur->parent;

      if (cur != t->nil && temp == cur->left){
          cur->left = t->nil;
      } 
      else if (cur != t->nil && temp == cur->right){
          cur->right = t->nil;
      }

      free(temp);
    }
  }

  free(t->nil);
  free(t);
}

/*------------------------------------------------------------------------------*/

// solve
// TODO: implement insert
node_t *rbtree_insert(rbtree *t, const key_t key){
  
  node_t *new_node = (node_t *)calloc(1, sizeof(node_t));
  new_node->key = key;
  new_node->left = t->nil;
  new_node->right = t->nil;
  new_node->color = RBTREE_RED; // 삽입 색은 무조건 레드!
  node_t *y = t->nil;
  node_t *x = t->root;

  while(x != t->nil){
    y = x;

    if(new_node->key < x->key){
      x = x->left;
    }
    else{
      x = x->right;
    }
  }
  
  new_node->parent = y;

  if(y == t->nil){
    t->root = new_node;
  }
  else if(new_node->key < y->key){
    y->left = new_node;
  }
  else{
    y->right = new_node;
  }
  
  rbtree_insert_fixup(t, new_node);

  return new_node;
}


void rbtree_insert_fixup(rbtree *t, node_t *z){

  node_t *y;
  
  while (z->parent->color == RBTREE_RED) {
    if (z->parent == z->parent->parent->left) {
      y = z->parent->parent->right;
      
      if (y->color == RBTREE_RED) {
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      }
      else {
        if (z == z->parent->right) {
          z = z->parent;
          left_rotate(t, z);
        }
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        right_rotate(t, z->parent->parent);
      }
    }
    else {
      y = z->parent->parent->left;

      if (y->color == RBTREE_RED) {
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      }
      else {
        if (z == z->parent->left) {
          z = z->parent;
          right_rotate(t, z);
        }

        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        left_rotate(t, z->parent->parent);
      }
    }
  }

  t->root->color = RBTREE_BLACK;
}

/*------------------------------------------------------------------------------*/

// TODO: implement find
node_t *rbtree_find(const rbtree *t, const key_t key){

  node_t *cur = t->root;

  while (cur != t->nil && cur->key != key){
    if(key < cur->key){
      cur = cur->left;
    } 
    else{
      cur = cur->right;
    }
  }

  if (cur != t->nil){
    return cur;
  } 
  else{
    return NULL;
  }

}

/*------------------------------------------------------------------------------*/

// TODO: implement find
node_t *rbtree_min(const rbtree *t){

  if(t->nil == t->root){
    return NULL;
  }

  node_t *cur = t->root;

  while (cur->left != t->nil) {
    cur = cur->left;
  }

  return cur;
}


// TODO: implement find
node_t *rbtree_max(const rbtree *t){

  if(t->nil == t->root){
    return NULL;
  }

  node_t *cur = t->root;

  while (cur->right != t->nil) {
    cur = cur->right;
  }

  return cur;
  //return t->root;
}

/*------------------------------------------------------------------------------*/

// TODO: implement erase
int rbtree_erase(rbtree *t, node_t *p){

  node_t *y = p;
  node_t *x = t->nil;
  color_t y_origin_color = y->color;

  if(p->left == t->nil){
    x = p->right;
    transplant(t,p,p->right);
  }
  else if(p->right == t->nil){
    x = p->left;
    transplant(t,p,p->left);
  }
  else{
    y = p->right;

    while(y->left != t->nil){
      y = y->left;
    }

    y_origin_color = y->color;
    x = y->right;

    if(y->parent == p){
      x->parent = y;
    }
    else{
      transplant(t,y,y->right);
      y->right=p->right;
      y->right->parent = y;
    }

    transplant(t,p,y);
    y->left = p->left;
    y->left->parent = y;
    y->color = p->color;
  }

  if(y_origin_color == RBTREE_BLACK){
    rbtree_delete_fixup(t,x);
  }

  free(p);

  return 0;
}


void rbtree_delete_fixup(rbtree *t, node_t *x){

  while (x != t->root && x->color == RBTREE_BLACK) {
    if (x == x->parent->left){
      node_t *w = x->parent->right;
      
      if (w->color == RBTREE_RED){
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        left_rotate(t, x->parent);
        w = x->parent->right;
      }

      if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK) {
        w->color = RBTREE_RED;
        x = x->parent;
      }
      else{ 
        if (w->right->color == RBTREE_BLACK) {
            w->left->color = RBTREE_BLACK;
            w->color = RBTREE_RED;
            right_rotate(t, w);
            w = x->parent->right;
        }

        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->right->color = RBTREE_BLACK;
        left_rotate(t, x->parent);
        x = t->root;
      }
    }
    else {
      node_t *w = x->parent->left;

      if (w->color == RBTREE_RED){
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        right_rotate(t, x->parent);
        w = x->parent->left;
      }

      if (w->right->color == RBTREE_BLACK && w->left->color == RBTREE_BLACK) {
        w->color = RBTREE_RED;
        x = x->parent;
      }
      else 
      {
        if (w->left->color == RBTREE_BLACK) {
          w->right->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          left_rotate(t, w);
          w = x->parent->left;
        }

        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->left->color = RBTREE_BLACK;
        right_rotate(t, x->parent);
        x = t->root;
      }
    }
  }

  x->color = RBTREE_BLACK;
}

/*------------------------------------------------------------------------------*/

// solve
int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n){

  node_t *cur = rbtree_min(t);
  int i = 0;

  while (cur != t->nil && i < n) {
    arr[i++] = cur->key;

    if (cur->right != t->nil) {
      cur = cur->right;
      while (cur->left != t->nil) {
        cur = cur->left;
      }
    }
    else {
      while (cur->parent != t->nil && cur == cur->parent->right) {
        cur = cur->parent;
      }
      cur = cur->parent;
    }
  }
 

  return 0;
}

/*------------------------------------------------------------------------------*/

void left_rotate(rbtree *t, node_t *x) 
{
  node_t *y = x->right;
  x->right = y->left;

  if (y->left != t->nil) {
    y->left->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == t->nil) {
    t->root = y;
  } 
  else if (x == x->parent->left) {
    x->parent->left = y;
  } 
  else {
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;
}


void right_rotate(rbtree *t, node_t *x){
  node_t *y = x->left;
  x->left = y->right;
  
  if (y->right != t->nil) {
    y->right->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == t->nil) {
    t->root = y;
  } 
  else if (x == x->parent->right) {
    x->parent->right = y;
  } 
  else {
    x->parent->left = y;
  }
  y->right = x;
  x->parent = y;
}


void transplant(rbtree *t, node_t *x, node_t *y)
{
  if(x->parent == t->nil){
    t->root = y;
  }else if(x == x->parent->left){
    x->parent->left = y;
  }else{
    x->parent->right = y;
  }
  y->parent = x->parent;
} 

/*------------------------------------------------------------------------------*/