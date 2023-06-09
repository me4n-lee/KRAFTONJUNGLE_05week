#include "rbtree.h"
#include <stdlib.h>
#include <stdio.h>

rbtree *new_rbtree(void);
void delete_rbtree(rbtree *t);
node_t *rbtree_insert(rbtree *t, const key_t key);
void rbtree_insert_fixup(rbtree *t, node_t *z);
node_t *rbtree_find(const rbtree *t, const key_t key);
node_t *rbtree_min(const rbtree *t);
node_t *rbtree_max(const rbtree *t);
int rbtree_erase(rbtree *t, node_t *p);
void rbtree_delete_fixup(rbtree *t, node_t *x);
void right_rotate(rbtree *t, node_t *x);
void left_rotate(rbtree *t, node_t *x);
void transplant(rbtree *t, node_t *x, node_t *y);

/*------------------------------------------------------------------------------*/

// TODO: initialize struct if needed
rbtree *new_rbtree(void){

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

// TODO: implement insert
node_t *rbtree_insert(rbtree *t, const key_t key){
  
  // 새로운 노드를 만들어 준다. insert fixup에 활용하기 위해서!
  node_t *new = (node_t *)calloc(1, sizeof(node_t));
  new->key = key; // 매개변수의 key값을 new에 저장
  new->left = t->nil;
  new->right = t->nil;
  new->color = RBTREE_RED; // 삽입 색은 무조건 레드!

  node_t *y = t->nil;
  node_t *x = t->root;

  // 트리가 비어있는 경우 또는 적절한 위치를 찾을 때까지 반복
  while(x != t->nil){
    y = x;

    if(new->key < x->key){
      x = x->left;
    }
    else{
      x = x->right;
    }
  }
  
  new->parent = y;

  // Case 1: 새 노드가 루트 노드가 될 경우
  if(y == t->nil){
    t->root = new;
  }
  // Case 2: 새 노드가 부모 노드의 왼쪽 자식이 될 경우
  else if(new->key < y->key){
    y->left = new;
  }
  // Case 3: 새 노드가 부모 노드의 오른쪽 자식이 될 경우
  else{
    y->right = new;
  }
  
  rbtree_insert_fixup(t, new);

  return new;
  //return t->root;
}


void rbtree_insert_fixup(rbtree *t, node_t *z){

  node_t *y;
  
  // Case 1: z의 부모 노드가 RED일 때까지 반복
  while (z->parent->color == RBTREE_RED) {
    // Case 2: z의 부모가 z의 할아버지의 왼쪽 자식일 경우
    if (z->parent == z->parent->parent->left) {
      y = z->parent->parent->right;
      
      // Case 2.1: z의 삼촌이 RED일 경우
      if (y->color == RBTREE_RED) {
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      }
      else {
        // Case 2.2: z가 부모의 오른쪽 자식이고, 삼촌이 BLACK인 경우
        if (z == z->parent->right) {
          z = z->parent;
          left_rotate(t, z);
        }

        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        right_rotate(t, z->parent->parent);
      }
    }
    // Case 3: z의 부모가 z의 할아버지의 오른쪽 자식일 경우
    else {
      y = z->parent->parent->left;

      // Case 3.1: z의 삼촌이 RED인 경우
      if (y->color == RBTREE_RED) {
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      }
      else {
        // Case 3.2: z가 부모의 왼쪽 자식이고, 삼촌이 BLACK인 경우
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

node_t *rbtree_min(const rbtree *t){

  if(t->nil == t->root){
    return NULL;
  }

  node_t *cur = t->root;

  while (cur->left != t->nil) {
    cur = cur->left;
  }

  return cur;
  //return t->root;
}


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

node_t *rbtree_erase_min(const rbtree *t, node_t *p) {
    node_t *cur = p;

    while (cur->left != t->nil) {
        cur = cur->left;
    }

    return cur;
}


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
    y = rbtree_erase_min(t, p->right);

    // while(y->left != t->nil){
    //   y = y->left;
    // }

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
      
      // Case 1: x의 형제 w가 RED인 경우
      if (w->color == RBTREE_RED){
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        left_rotate(t, x->parent);
        w = x->parent->right;
      }

      // Case 2: x의 형제 w는 BLACK이고, w의 두 자식이 모두 BLACK인 경우
      if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK) {
        w->color = RBTREE_RED;
        x = x->parent;
      }
      else{ 
        // Case 3: x의 형제 w는 BLACK, w의 오른쪽 자식은 BLACK, w의 왼쪽 자식은 RED인 경우
        if (w->right->color == RBTREE_BLACK) {
            w->left->color = RBTREE_BLACK;
            w->color = RBTREE_RED;
            right_rotate(t, w);
            w = x->parent->right;
        }

        // Case 4: x의 형제 w는 BLACK이고, w의 오른쪽 자식은 RED인 경우
        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->right->color = RBTREE_BLACK;
        left_rotate(t, x->parent);
        x = t->root;
      }
    }
    else {
      node_t *w = x->parent->left;

      // Case 1: x의 형제 w가 RED인 경우
      if (w->color == RBTREE_RED){
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        right_rotate(t, x->parent);
        w = x->parent->left;
      }

      // Case 2: x의 형제 w는 BLACK이고, w의 두 자식이 모두 BLACK인 경우
      if (w->right->color == RBTREE_BLACK && w->left->color == RBTREE_BLACK) {
        w->color = RBTREE_RED;
        x = x->parent;
      }
      else 
      {
        // Case 3: x의 형제 w는 BLACK, w의 왼쪽 자식은 BLACK, w의 오른쪽 자식은 RED인 경우
        if (w->left->color == RBTREE_BLACK) {
          w->right->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          left_rotate(t, w);
          w = x->parent->left;
        }

        // Case 4: x의 형제 w는 BLACK이고, w의 왼쪽 자식은 RED인 경우
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

void left_rotate(rbtree *t, node_t *x) {

  node_t *y = x->right;
  x->right = y->left;

  // y의 왼쪽 자식 노드가 nil이 아니라면, 그 노드의 부모를 x로 설정
  if (y->left != t->nil) {
    y->left->parent = x;
  }

  y->parent = x->parent;

  // x의 부모가 nil이라면, x는 root였으므로, y를 새로운 root로 설정
  if (x->parent == t->nil) {
    t->root = y;
  }
  // x가 왼쪽 자식이었다면, x의 부모의 왼쪽 자식을 y로 설정
  else if (x == x->parent->left) {
    x->parent->left = y;
  } 
  // x가 오른쪽 자식이었다면, x의 부모의 오른쪽 자식을 y로 설정
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


void transplant(rbtree *t, node_t *x, node_t *y){

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