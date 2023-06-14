#include <stdio.h>
#include <stdlib.h>

//Virat Jain
//2021CSB1220
typedef struct node{
    int value;
    struct node *left;
    struct node *right;
    int height;
}node;
//creating a struct node for nodes and type defining it as node

node* Newnode(int val){
    node* N= (node*)malloc(sizeof(node));
    N->value= val;
    N->left=NULL;
    N->right=NULL;
    N->height=1;
    return N;
}
//this function allocates memory and makes a new node.

int Height(node* Node){
    int H=0;
    if (Node!=NULL){
        if (Height(Node->left)>=Height(Node->right))
            H=1+Height(Node->left);
        else if  (Height(Node->left)<Height(Node->right))
            H=1+Height(Node->right);
    }
    return H;
}
//this function returns height of particular node by recursively calculation height of left and right subtree.

int difference(node* t){
    int balance=0;
    if (t!=NULL){
       int lheight= Height(t->left);
        int rheight= Height(t->right);
        balance= lheight-rheight;
    }
    return balance;
}
//this function calculates the balance factor of the node using height function.

node* left_rotate(node* Node){
    node *t1= (node*)malloc(sizeof(node));
    t1=Node->right;
    node *t2= (node*)malloc(sizeof(node));
    t2= t1->left;

    t1->left=Node;
    Node->right=t2;

    Node->height=Height(Node);
    t1->height=Height(t1);
    return t1;
}
//this function left rotate the avl tree with balance factor more than one.

node* right_rotate(node* Node){
    node *t1= (node*)malloc(sizeof(node));
    t1= Node->left;
    node *t2= (node*)malloc(sizeof(node));
    t2= t1->right;

    t1->right=Node;
    Node->left=t2;

    Node->height=Height(Node);
    t1->height=Height(t1);
    return t1;
}
//similarly this function right rotates the tree by just connection of nodes

node* lr_rotate(node* Node){
    node *t1= (node*)malloc(sizeof(node));
    t1= Node->right;
    Node->right=right_rotate(t1);

    return left_rotate(Node);
}
//this function performs left right rotation using the left rotate and right rotate function.

node* rl_rotate(node* Node){
    node *t1= (node*)malloc(sizeof(node));
    t1= Node->left;
    Node->left=left_rotate(t1);
    return right_rotate(Node);
}
//this function performs right right rotation using the left rotate and right rotate function.

node* Balance_avl(node *N){

    int bf= difference(N);
    if (bf>1){
       int bf_left= difference(N->left);
        if (bf_left>0){
            return left_rotate(N);
        }
        else if (bf_left<0){
            return lr_rotate(N);
        }
    }
    else if (bf<-1){
        int bf_right=difference(N->right);
        if (bf_right<0){
            return right_rotate(N);
        }
        else if (bf_right>0){
            return rl_rotate(N);
        }
    }
    return N;
}
//this function balances the avl tree

node* Insert(node* root,int val){
    if (root==NULL){
        root= Newnode(val);
    }
    else if (val< root->value){
        root->left= Insert(root->left,val);
    }
    else if (val> root->value){
        root->right=Insert(root->right,val);
    }
    else
        return root;
    root->height=Height(root);
    int bf= difference(root);
    if (bf>1){
        if (val< root->left->value){
            return right_rotate(root);
        }
        else if (val> root->left->value){
            return lr_rotate(root);
        }
    }
    else if (bf<-1){
        if (val> root->right->value){
            return left_rotate(root);
        }
        else if (val< root->right->value){
            return rl_rotate(root);
        }
    }

    return root;
}
//it inserts the value in tree and then balance using different rotation according to the balance factor.

void Search(node* head,int x){
    if (head==NULL){
        printf("%d is not present in AVL tree\n",x);
        return;
    }
    else if (head->value==x){
        printf("Present \n");
        int bf=difference(head);
        int h=Height(head);
        printf("Balance factor of %d is %d \n",x,bf);
        printf("Height of %d in the AVL tree is %d \n",x,h-1);
        return;
    }
    else if (head->value>x){
        Search(head->left,x);
    }
    else{
        Search(head->right,x);
    }

}
//it searches the element in the tree just like we search in binary search tree.

void Preorder(node *root)
{
    if(root != NULL)
    {
        printf("%d ", root->value);
        Preorder(root->left);
        Preorder(root->right);
    }
}
//this function is for preorder traversal

void Inorder(node *root)
{
    if(root != NULL)
    {
        Inorder(root->left);
        printf("%d ", root->value);
        Inorder(root->right);
    }
}
//this is for inorder traversal.

int main()
{
    node* root= (node*)malloc(sizeof(node));
    root= NULL;
    for (int i=0;i<=24;i++){
        root=Insert(root,i);
    }
    printf("AVL tree constructed by inserting 0 to 24 elements \n");
    char input;
    int c=0;
    while (input!='q'){
    printf("i) Insert :\ns) search :\np) Print Preorder and Inorder in Separate lines:\nq) Quit: \n");
    printf("Enter Your Choice: ");
    scanf(" %c", &input);
    if (input=='i'){
        printf("Enter a data to insert: ");
        int key;
        scanf("%d", &key );
        root=Insert(root,key);
        printf("\n");
    }
    else if (input=='s'){
        printf("Enter data you want to search: ");
        int key;
        scanf("%d", &key );
        Search(root,key);
        printf("\n");
    }
    else if (input=='p'){
        printf("Preorder sequence:\n");
        Preorder(root);
        printf("\nInorder sequence: \n");
        Inorder(root);
        printf("\n \n");
    }
    else if (input=='q'){
            break;
    }
    }
    return 0;
}
