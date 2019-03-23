#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED
#include<iostream>
using namespace std;

struct node
{
    int data;
    node *left;
    node *right;
    int height;
};

class tree
{
public:
    int arraySize;
    int *levelOrderArray;
    tree(){levelOrderArray=NULL; arraySize=0;}
    int height(node*);
    int getBalance(node*);
    node* leftRotate(node*);
    node* rightRotate(node*);
    node* insertNode(node*,int);
    node* minValue(node*);
    node* deleteNode(node*, int);
    void levelOrder(node*);
    void inorderFilling(node*,int);
};

#endif // AVLTREE_H_INCLUDED
