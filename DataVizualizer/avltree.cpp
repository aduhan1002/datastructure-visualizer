#include "avltree.h"
#include<math.h>

int tree:: height(node *h)
{
    if(h==NULL)
    {
        return -1;
    }
    else
    {
        return h->height;
    }
}

int tree :: getBalance(node* b)
{
    return(height(b->left)-height(b->right));
}

node* tree :: leftRotate(node *temp)
{
    node *y=temp->right;
    node *t2=y->left;

    y->left=temp;
    temp->right=t2;
    temp->height=1+max(height(temp->left),height(temp->right));
    y->height=1+max(height(y->left),height(y->right));
    return y;
}

node* tree :: rightRotate(node *y)
{
    node *x = y->left;
    node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    // Return new root
    return x;
}

node* tree :: insertNode(node *root,int data)
{
    if(root==NULL)
    {
        root=new node;
        root->data=data;
        root->left=root->right=NULL;
        root->height=0;
        arraySize++;
        return root;
    }
    else if(data==root->data)
    {
        return root;
    }
    else if(data<root->data)
    {
        root->left=insertNode(root->left,data);
    }
    else
    {
        root->right=insertNode(root->right,data);
    }
    root->height=1+max(height(root->left),height(root->right));

    int balance=getBalance(root);

    if(balance>1 && data<root->left->data)
    {

    return rightRotate(root);
    }

    if(balance<-1 && data>root->right->data)
    {
      return leftRotate(root);
    }
     if (balance > 1 && data > root->left->data)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && data < root->right->data)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

node* tree :: minValue(node *root)
{
    while(root->left!=NULL)
    {
        root=root->left;
    }
    return root;
};

node* tree :: deleteNode(node *root,int data)
{
    if(root==NULL)
    {
        return root;
    }
    else if(data>root->data)
    {
        root->right=deleteNode(root->right,data);
    }
    else if(data<root->data)
    {
        root->left=deleteNode(root->left,data);
    }
    else
    {
        if(root->left==NULL)
        {
            node *temp=root->right;
            delete(root);
            return temp;
        }
        else if(root->right==NULL)
        {
            node *temp=root->left;
            delete(root);
            return temp;
        }
        else
        {
        node *temp=minValue(temp->right);
        root->data=temp->data;
        root->right=deleteNode(root->right,temp->data);
        }
      }  //updated height
        root->height=1+max(height(root->left),height(root->right));
        int balance=getBalance(root);
        if(balance>1 && getBalance(root->left)>=0)
        {
            return rightRotate(root);
        }
        if(balance>1 && getBalance(root->left)<0)
        {
            root->left=leftRotate(root->left);
            return rightRotate(root->right);
        }
        if(balance<-1 && getBalance(root->left)<=0)
        {
            return rightRotate(root);
        }
        if(balance<-1 && getBalance(root->left)>0)
        {
            root->right=rightRotate(root->right);
            return leftRotate(root);
        }
}

void tree :: inorderFilling(node *root,int pos)
{
    if(root==NULL)
        return;
    inorderFilling(root->left,2*pos + 1);
    levelOrderArray[pos]=root->data;
    inorderFilling(root->right, 2*pos +2);
}

void tree :: levelOrder(node *root)
{
    if(root==NULL)
        return;
    if(levelOrderArray!=NULL)
    {
        delete(levelOrderArray);
    }
    levelOrderArray=new int[(int)pow(2,arraySize)-1]{0};
    inorderFilling(root,0);
}
