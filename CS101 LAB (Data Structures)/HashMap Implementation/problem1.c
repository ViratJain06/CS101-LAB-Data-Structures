//Virat Jain
//2021CSB1220

#include <stdio.h>
#include <stdlib.h>

int size; //defining the size of hashtable

struct node
{
    int key;
    struct node *next;
    struct node *prev;
};//defining a node of linked list

struct node **arr; //defining an array of pointers to the linked list off particular index

int hash_func(int k){
    int index= k%size;
    if (index<0)
        index=index+size;
    return index;
}//this function returns the value after calculating by hash function

void insert(int value)
{
    int idx = hash_func(value);

    struct node *newNode = malloc(sizeof(struct node));//defining a new node to be inserted
    newNode->key = value;//setting value of key
    newNode->next = arr[idx];//inserting node to the start of the linked list
    newNode->prev= NULL;//defining previous as null

    if(arr[idx] != NULL){
        newNode->next=arr[idx];
        arr[idx]->prev=newNode;
    }//inserting a node if the array index is not null
    arr[idx]=newNode;//setting head node as the array index
}

void delete_ht(int key) {

    int idx= hash_func(key);
    struct node *nd = arr[idx];//defining the node to be deleted

    while (nd) {
        if(nd->key== key ){
            if (nd->prev && nd->next) {
                nd->prev->next = nd->next;
                nd->next->prev = nd->prev;
            }//when key is in between two nodes
            else if (nd->next && !nd->prev) {
                arr[idx]= nd->next;
                nd->next->prev= NULL;
            } //when key is the first node of that index
            else if (nd->prev && !nd->next) {
                nd->prev->next = NULL;
            }//when key is the last node of index
            else{
               arr[idx]=NULL;
            }//when key is only node in that index
            free(nd);//deleting the nd node
            return;
        }
        nd= nd->next;//traversing the list until target key is found
    }
    printf("Element not found\n");//when the key is not found
}

void search(int key)
{
    int index=hash_func(key);

    struct node* item =arr[index];
    if(item == NULL)
        printf("Searched element not found\n");//when the array index is empty
    else
    {
        struct node* i=item;
        for(;i!=NULL;i=i->next)
        {//this for loop traverse the particular index until the target key is not found
            if(i->key == key)
                {
                    printf("search element found in slot number %d\n",index);
                    break;
                }
        }
        if(i==NULL)
            printf("Searched element not found\n");//when the key node is not found after loop is over

    }
}

void display()
{
    int i;

    for(i = 0; i < size; i++)
    {//this loop traverse the whole hash table
        struct node *temp = arr[i];
        printf("Index %d : ", i);
        if (temp== NULL){
           printf("NULL\n");
        }//if the array index is empty
        else{
            while(temp)
            {
                printf("%d ", temp->key);
                temp = temp->next;
            }//printing the linked list present at a particular index
            printf("\n");
        }

    }
}

int main()
{
    printf("Enter hash table size m: ");
    scanf("%d", &size);//taking user input for the size of hashtable
    if (size <= 0)
    {
        printf("Enter Valid input\n");
        return 0;
    }//if size of hash table is negetive or zero
    arr = (struct node **)malloc(size * sizeof(struct node));
    for (int i = 0; i < size; i++)
    {
        arr[i] = NULL;
    }//initializing the hash table by null

    int choice;
    while (choice != 5)
    {
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Display\n");
        printf("5. Quit\n");
        printf("Enter your choice : ");
        scanf(" %d", &choice);//taking user input for choice
        if (choice == 1) // If chosen function is 1
        {
            printf("Enter value to insert : ");
            int k;
            scanf("%d", &k);
            insert(k);
        }//inserting element in hash table
        else if (choice == 2)
        {
            printf("Enter value to delete : ");
            int k;
            scanf("%d", &k);
            delete_ht(k);
        }//deleting element in hash table
        else if (choice == 3)
        {
            printf("Enter the element to be searched : ");
            int k;
            scanf("%d", &k);
            search(k);
        }//searching element in hash table
        else if (choice == 4)
        {
            display();
        }//displaying the hash table
        else if (choice==5)
        {
        }
        else
        {
            printf("Enter valid input\n");
        }//for invalid inputs
    }

    return 0;
}
