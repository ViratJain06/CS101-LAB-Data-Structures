//Virat Jain
//2021CSB1220

#include <stdio.h>
#include <stdlib.h>

struct Btree_node{
    int n; //number of keys
    int *key; //array of keys
    int leaf; //Is leaf or not
    struct Btree_node **ptr_arr; //array of pointers of child node
}; //defining a node for btree

int t;
struct Btree_node *root=NULL; //defining a global root node

struct Btree_node* Btree_Create(){
    struct Btree_node *newNode; //creating a new node
    newNode = (struct Btree_node*)malloc(sizeof(struct Btree_node));  //allocating memory for node
    newNode->key = (int*)malloc((2*t-1)*sizeof(int)); //allocating memory for keys
    newNode->ptr_arr= (struct Btree_node **)malloc((2*t)*sizeof(struct Btree_node));  //allocating memory for pointers array for child node
    newNode->n = 0;
    newNode->leaf= 1;
    return newNode;
}

void Split_child( struct Btree_node *x,int i){
    struct Btree_node *sp = Btree_Create(); //creating a new node
    struct Btree_node *y = x->ptr_arr[i-1];  //setting left node as node of key
    sp->leaf = y->leaf;
    sp->n= t-1;
    for (int k=0;k<t-1;k++){
        sp->key[k]= y->key[k+t]; //coping right child nodes to new node
    }
    if (y->leaf == 0){
        for (int k=0;k<t;k++){
        sp->ptr_arr[k]= y->ptr_arr[k+t];
        }
    }
    y->n =t;
    for (int k= x->n;k>=i;k--){
        x->ptr_arr[k+1]=x->ptr_arr[k]; //shifting child nodes by one unit
    }
    x->ptr_arr[i]= sp;
    for (int k= x->n-1;k>=i-1;k--){
        x->key[k+1]=x->key[k]; //shifting key values by one unit
    }
    x->key[i-1]=y->key[t-1]; //inserting new key value in key node
    y->n--; //adjusting value of child node
    x->n++; //adjusting value of key node
}

void b_tree_Insert_non_full(struct Btree_node * In_key, int k){
    int i= In_key->n-1;
    if(In_key->leaf==1){
        while (i>=0 && k<In_key->key[i]){
            In_key->key[i+1]= In_key->key[i];
            i=i-1;
        }//shifting values greater then k in key node
        In_key->key[i+1]=k; //inserting k at in increasing order
        In_key->n++;
    }
    else{
        while(i>=0 && k<In_key->key[i]){
            i=i-1;
        }
        i+=1;
        if (In_key->ptr_arr[i]->n== 2*t-1){
            Split_child(In_key,i+1);
            if (k>In_key->key[i]){
                i+=1;
            }
        }//if node is not leaf then adjusting values of child pointers
        b_tree_Insert_non_full(In_key->ptr_arr[i],k);//adding k to child
    }
}

void B_tree_Insert (struct Btree_node * node,int k){
    struct Btree_node* c = root;
    if(c->n ==2*t-1){
        struct Btree_node *newnode = Btree_Create();
        root = newnode;
        newnode->leaf =0;
        newnode->n=0;
        newnode->ptr_arr[0]= c;
        Split_child(newnode,1);
        b_tree_Insert_non_full(newnode,k);
    }//if node is full then spliting the node and adding k to the splitted node
    else{
        b_tree_Insert_non_full(c,k);//if not full then inserting in increasing order
    }
    return;
}

int height_node(struct Btree_node* key_node){
    int h=0;
    for(; key_node!= NULL; key_node=key_node->ptr_arr[0]){
        h++;
        if(key_node->leaf== 1){
            h--;
            break;
        }
    }//until the node is not leaf then traversing till first leaf and adding 1 to height
    return h;

}

void btree_search(struct Btree_node * node ,int k){
    if (node== NULL || node->n==0){
        printf("Empty tree \n");
        return;
    }//boundary condition
    int i=0;
    while(i< node->n && k> node->key[i]){
        i++;
    }//moving at the ranges in which k lies
    if (i< node->n && k==node->key[i]){
        printf("Present \n");
        printf("The node contains:");
        for (int j=0;j<node->n;j++){
            printf(" %d",node->key[j]);
        }
        printf("\nThe height of this node is %d \n",height_node(node));
    }//if k is present in node then printing present
    else if (node->leaf){
        printf("Not Present \n");
    }
    else{
        btree_search(node->ptr_arr[i],k);
    }//searching in child nodes
}

void btree_min(struct Btree_node *root){
    if (!root || root->n==0){
        printf("The tree is empty\n");
    }
    if (root->leaf == 0){
        btree_min(root->ptr_arr[0]);
    }//traversing till first element of the first leaf node
    else{
        printf("The minimum element in B Tree is : %d \n",root->key[0]);
    }
}


void btree_inorder(struct Btree_node *root)
{
    int i;
    if (root){
        for (i = 0; i < root->n; i++)
        {
            if (!root->leaf){
                btree_inorder(root->ptr_arr[i]);//recursively calling traversal until reaching the leaf node
            }
            printf(" %d,", root->key[i]);//printing keys in node
        }
        if(!root->leaf){
            btree_inorder(root->ptr_arr[i]);//again calling for last child node
        }
    }
}


int main(){
    printf("Enter the minimum degree of the B-tree t:");
    scanf("%d",&t);
    root=Btree_Create();
    for (int i=50; i>0;i--){
        B_tree_Insert(root,i);
    }//inserting 50 values to an empty btree
    char choice;
    while (choice != 'E'){
        printf("options: I for insertion, S for search, M for finding minimum, T for traversing the B-tree, E for exit:");
        scanf(" %c" ,&choice);
        if (choice== 'I'){
            printf("Enter number of elements you wanted to enter: ");
            int num;
            scanf(" %d",&num);
            printf("Enter %d numbers to insert:",num);
            for(int j=0;j<num;j++){
                int n;
                char comma;
                scanf(" %d,",&n);
                B_tree_Insert(root,n);
            }
        }//Taking user input for inserting number and inserting it in btree
        else if( choice== 'T'){
            printf("Inorder traversal is: ");
            btree_inorder(root);
            printf("\n");
        }// traversing btree
        else if (choice== 'S'){
            printf("Enter element to search: ");
            int s;
            scanf("%d",&s);
            btree_search(root,s);
        }//searching eklement in btree and calling search function
        else if (choice == 'M'){
            //printf("Minimum element is: ");
            btree_min(root);
        }//finding minimum element in btree
        else if (choice=='E'){}
        else{
            printf("Enter a valid input\n");
        }

    }
    return 0;
}
