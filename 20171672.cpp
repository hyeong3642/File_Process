#include <iostream>
using namespace std;

struct Node{
  int Key;
  Node* left;
  Node* right;
  Node(int k, Node* l, Node* r){
    Key= k;
    left =l;
    right =r;
  }
};

Node* getNode(int k, Node* l, Node* r){
  return new Node(k,l,r);
}

void insertBST(Node*& T, int newKey){
    // find lotation of node
  Node* q =NULL; Node* p = T;
  while(p!=NULL){
    if(newKey==p->Key){
      return;
    }
    q=p;
    if(newKey<p->Key){
      p=p->left;
    }
    else{
      p=p->right;
    }
  }
  // make node with new key
  Node* newNode = getNode(newKey, NULL, NULL);
  // insert
  if(T==NULL){
    T = newNode;
  }
  else if(newKey<q->Key){
    q->left = newNode;
  }
  else{
    q->right= newNode;
  }
  return;
}

//find height of tree
int height(Node* tmp){
  //case of empty tree
  if(tmp ==NULL){
    return -1;
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
  return tmp->Key;
}

//find minimal value of rihgt child
int minNode(Node* tmp){
  while(tmp->left!=NULL){
    tmp = tmp->left;
  }
  return tmp->Key;
}

//find number of node each right child, left child
int noNodes(Node* tmp ){
  if(tmp == NULL){
     return 0;}
  else{
    return noNodes(tmp->left) +noNodes(tmp->right)+1;
  }
}

void deleteBST(Node*& T, int deleteKey){
  //find lotation of node
  Node* q =NULL; Node* p = T;
  while(p!=NULL){
    if(deleteKey==p->Key){
      break;
    }
    q=p;
    if(deleteKey<p->Key){
      p=p->left;
    }
    else{
      p=p->right;
    }
  }
  if(p==NULL){
    return;
  }
  //no child
  if(p->left==NULL && p->right==NULL){
    //case of root
    if(p==T){
      T =NULL;
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
        T = p->left;
      }
      else{
        T=p->right;
      }
      return;
    }
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
    p->Key = r;
    //delete node according to flag value
    if(flag==0){
      deleteBST(p->left, r);
    }
    else{
      deleteBST(p->right, r);
    }
  }
}

void inorderBST1(Node* tmp){
if(tmp!=NULL){
  inorderBST1(tmp->left);
  cout << tmp->Key<<" ";
  inorderBST1(tmp->right);
}
}

void inorderBST(Node* tmp){
  inorderBST1(tmp);
  cout << endl;
}

int testcases[] = {25, 500, 33, 49, 17, 403, 29, 105, 39, 66, 305, 44, 19, 441, 390 ,12, 81, 50, 100, 999};
int main(){
    Node* T=NULL;
    //삽입 및 삽입 순서대로 삭제
    for(int i=0; i<20; i++){
      insertBST(T, testcases[i]); inorderBST(T);
    }
    for(int i=0; i<20; i++){
      deleteBST(T, testcases[i]); inorderBST(T);
    }
    //초기화
    delete(T); T=NULL;

    //재삽입 및 삽입 역순으로 삭제
    for(int i=0; i<20; i++){
      insertBST(T, testcases[i]); inorderBST(T);
    }
    for(int i=19; i>-1; i--){
      deleteBST(T, testcases[i]); inorderBST(T);
    }
    return 0;}
