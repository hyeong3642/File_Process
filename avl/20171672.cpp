/**
 * File processing, 2020
 * AVL.cpp
 * implementation of AVL tree
 */

#include <stdio.h>
#include <iostream>
using namespace std;

/**
 * Node represents a single node in AVL tree.
 */
typedef struct Node {
  int         key, bf;
  struct Node *left, *right;
} Node;

typedef Node *Tree;

/**
 * getNode returns a new node.
 * @return a new node
 */
Node *getNode() {
  /* write your code here */
  Node *tmp = new Node;
  tmp->key =0;
  tmp->bf=0;
  tmp->left = NULL;
  tmp->right = NULL;
  return tmp;
}
//find height of tree
int height(Node* tmp){
  //case of empty tree
  if(tmp ==NULL){
    return 0;
  }
  int left = height(tmp->left);
  int right = height(tmp->right);
  if(left>right){
    return left +1;
  }
  else{
    return right+1;
  }
}

//find maximal value of left child
int maxNode(Node* tmp){
  while(tmp->right!=NULL){
    tmp = tmp->right;
  }
  return tmp->key;
}

//find minimal value of rihgt child
int minNode(Node* tmp){
  while(tmp->left!=NULL){
    tmp = tmp->left;
  }
  return tmp->key;
}

//find number of node each right child, left child
int noNodes(Node* tmp ){
  if(tmp == NULL){
     return 0;}
  else{
    return noNodes(tmp->left) +noNodes(tmp->right)+1;
  }
}


/**
 * updateBF updates balancing factors of nodes in T
 * and finds the unbalanced node nearest to y.
 * @param T: an AVL tree
 * @param y: the inserted/deleted node
 * @param x: the unbalanced node nearest to y
 * @param p: parent node of x
 */
void updateBF(Tree *T, Node *y, Node **x, Node **p) {
  Node* a= *T; Node* b= NULL;
  while(b!=y){
    a->bf=height(a->left)-height(a->right);
    if(a->bf>1 || a->bf<-1){
      *x = a;
      *p = b;
    }
    b=a;
  }
  if(y->key<a->key){
    a = a->left;
  }
  else{
    a = a->right;
  }
}

/**
 * rotateLL implements LL rotation in subtree rooted with x.
 * @param T: an AVL tree
 * @param x: root node of subtree
 * @param p: parent node of x
 */
void rotateLL(Tree *T, Node *x, Node *p) {
  //change 3 pointer for LL
  Node* b = getNode();
  b = x->left;
  x->left = b->right;
  b->right = x;
  //when x is root
  if(p==NULL){
    *T=b;
  }
  else if(p->left == x){
    p->left = b;
  }
  else{
    p->right = b;
  }
}

/**
 * rotateRR implements RR rotation in subtree rooted with x.
 * @param T: an AVL tree
 * @param x: root node of subtree
 * @param p: parent node of x
 */
void rotateRR(Tree *T, Node *x, Node *p) {
  //change 3 pointer for RR
  Node* b= getNode();
  b = x->right;
  x->right = b->left;
  b->left = x;
  //when x is root
  if(p==NULL){
    *T=b;
  }
  else if(p->left == x){
    p->left = b;
  }
  else{
    p->right = b;
  }
}

/**
 * rotateLR implements LR rotation in subtree rooted with x.
 * @param T: an AVL tree
 * @param x: root node of subtree
 * @param p: parent node of x
 */
void rotateLR(Tree *T, Node *x, Node *p) {
  //change 5 pointer for LR
  Node* a = x->left;
  Node* b = a->right;
  x->left = b->right;
  a->right = b->left;
  b->left = a;
  b->right = x;
  //when x is root
  if(p==NULL){
    *T=b;
  }
  else if(p->left ==x){
    p->left = b;
  }
  else{
    p->right = b;
  }
}

/**
 * rotateRL implements RL rotation in subtree rooted with x.
 * @param T: an AVL tree
 * @param x: root node of subtree
 * @param p: parent node of x
 */
void rotateRL(Tree *T, Node *x, Node *p) {
  //change 5 pointer for RL
  Node* a = x->right;
  Node* b = a->left;
  x->right = b->left;
  a->left = b->right;
  b->right = a;
  b->left = x;
  //when x is root
  if(p==NULL){
    *T=b;
  }
  else if(p->left ==x){
    p->left = b;
  }
  else{
    p->right = b;
  }
}

/**
 * insertBST inserts newKey into T
 * and returns the inserted node.
 * @param T: a binary search tree
 * @param newKey: a key to insert
 * @return the inserted node
 */
Node *insertBST(Tree *T, int newKey) {
  // find lotation of node
  Node* q =NULL; Node* p = *T;
  while(p!=NULL){
    if(newKey==p->key){
      return p;
    }
    q=p;
    if(newKey<p->key){
      p=p->left;
    }
    else{
      p=p->right;
    }
  }
  // make node with new key
  Node* newNode = getNode();
  newNode->key = newKey;
  // insert
  if(*T==NULL){
    *T = newNode;
  }
  else if(newKey<q->key){
    q->left = newNode;
  }
  else{
    q->right= newNode;
  }
  return newNode;
}

/**
 * insertAVL inserts newKey into T.
 * @param T: an AVL tree
 * @param newKey: a key to insert
 */

void insertAVL(Tree *T, int newKey) {
  /**
   * print "NO" if not rotates
   * print "LL" if rotates LL
   * print "RR" if rotates RR
   * print "LR" if rotates LR
   * print "RL" if rotates RL
   */
  Node* inserted = insertBST(T,newKey);
  Node* unbalanced = NULL;
  Node* unbalancedpar = NULL;
  //insert first, find unbalanced
  updateBF(T, inserted, &unbalanced, &unbalancedpar);
  //already balanced
  if(unbalanced==NULL){
    cout << "NO";
  }
  else{
    //left higher
    if((unbalanced->bf)>1){
      //decide LL OR LR
      if(((unbalanced->left->bf)>0)){
        cout << "LL";
        rotateLL(T,unbalanced,unbalancedpar);
      }
      else{
        cout << "LR";
        rotateLR(T,unbalanced,unbalancedpar);
      }
    }
    //right higher
    else if(unbalanced->bf<-1){
      //decide RL OR RR
      if((unbalanced->right->bf)>0){
        cout << "RL";
        rotateRL(T,unbalanced,unbalancedpar);
      }
      else{
        cout << "RR";
        rotateRR(T,unbalanced,unbalancedpar);
      }
    }
  }
}
/**
 * deleteBST deletes deleteKey from T
 * and returns the parent node of the deleted node.
 * @param T: a binary search tree
 * @param deleteKey: a key to delete
 * @return the parent node of the deleted node
 */
Node *deleteBST(Tree *T, int deleteKey){
  //find lotation of node
  Node* q =NULL; Node* p = *T;
  while(p!=NULL){
    if(deleteKey==p->key){
      break;
    }
    q=p;
    if(deleteKey<p->key){
      p=p->left;
    }
    else{
      p=p->right;
    }
  }
  if(p==NULL){
    return NULL;
  }
  //no child
  if(p->left==NULL && p->right==NULL){
    //case of root
    if(q==NULL){
      *T =NULL;
      return NULL;
    }
    else{
      if(q->left==p){
        q->left ==NULL;
      }
      else{
        q->right ==NULL;
      }
    }
  }
  // one child
  if(p->left==NULL || p->right==NULL){
    // case of root
    if(q==NULL){
      if(p->left!=NULL){
        *T = p->left;
      }
      else{
        *T=p->right;
      }
      return NULL;
    }
    else{
      if(p->left!=NULL){
        if(q->left==p){
          q->left = p->left;
        }
        else{
          q->right = p->left;
        }
      }
      else{
        if(q->left==p){
          q->left = p->right;
        }
        else{
          q->right=p->right;
        }
      }
      return q;
    }
  }
  //two child
  else{
    //0 is left, 1 is right
    bool flag;
    int r;
    int leheight=height(p->left);
    int riheight=height(p->right);
    if(leheight>=riheight){
      r = maxNode(p->left);
      flag = 0;
    }
    //to change node with child who has higher height
    else if(riheight>leheight){
      r = minNode(p->right);
      flag = 1;
    }
    else{
      if(noNodes(p->left)>=noNodes(p->right)){
        r = maxNode(p->left);
        flag = 0;
      }
      else{
        r = minNode(p->right);
        flag=1;
      }
    }
    //change key for proper value
    p->key = r;
    //delete node according to flag value
    if(flag==0){
      deleteBST(&p->left, r);
    }
    else{
      deleteBST(&p->right, r);
    }
  }
  return q;
}

/**
 * deleteAVL deletes deleteKey from T.
 * @param T: an AVL tree
 * @param deleteKey: a key to delete
 */
void deleteAVL(Tree *T, int deleteKey) {
  /**
   * print "NO" if not rotates
   * print "LL" if rotates LL
   * print "RR" if rotates RR
   * print "LR" if rotates LR
   * print "RL" if rotates RL
   */
  Node* inserted = deleteBST(T,deleteKey);
  Node* unbalanced = NULL;
  Node* unbalancedpar = NULL;
  //delete first, find unbalanced
  updateBF(T, inserted, &unbalanced, &unbalancedpar);
  //already balanced
  if(unbalanced==NULL){
    cout << "NO";
  }
  else{
    //left higher
    if((unbalanced->bf)>1){
      if(((unbalanced->left->bf)>0)){
        cout << "LL";
        rotateLL(T,unbalanced,unbalancedpar);
      }
      else{
        cout << "LR";
        rotateLR(T,unbalanced,unbalancedpar);
      }
    }
    //right higher
    else if(unbalanced->bf<-1){
      if((unbalanced->right->bf)>0){
        cout << "RL";
        rotateRL(T,unbalanced,unbalancedpar);
      }
      else{
        cout << "RR";
        rotateRR(T,unbalanced,unbalancedpar);
      }
    }
  }

}
/**
 * inorderAVL implements inorder traversal in T.
 * @param T: an AVL tree
 */
void inorderAVL(Tree T) {
  /* write your code here */
  if(T!=NULL){
    inorderAVL(T->left);
    cout << T->key << " ";
    inorderAVL(T->right);
  }
}

int main() {
  /* Do not modify the code below */

  int testcase[] = { 40, 11, 77, 33, 20, 90, 99, 70, 88, 80, 66, 10, 22, 30, 44, 55, 50, 60, 25, 49 };

  Tree T = NULL;

  // insertion
  for (int i=0; i<20; i++) { printf("%d ", testcase[i]); insertAVL(&T, testcase[i]); printf(" : "); inorderAVL(T); printf("\n"); }

  // deletion
  for (int i=0; i<20; i++) { printf("%d ", testcase[i]); deleteAVL(&T, testcase[i]); printf(" : "); inorderAVL(T); printf("\n"); }

  T = NULL;

  // reinsertion
  for (int i=0; i<20; i++) { printf("%d ", testcase[i]); insertAVL(&T, testcase[i]); printf(" : "); inorderAVL(T); printf("\n"); }

  // redeletion
  for (int i=19; 0<=i; i--) { printf("%d ", testcase[i]); deleteAVL(&T, testcase[i]); printf(" : "); inorderAVL(T); printf("\n"); }
}
