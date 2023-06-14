#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int val;
    struct node* next;
}node;
//defining a structure of node also applying type define
node* straight_ll(int n){
    node* head=(node*)malloc(sizeof(node));
    //dynamically allocating a memory for node head
    node* temp= head;
    for (int i=1;i<=n+1;i++){
        node* newnode=(node*)malloc(sizeof(node));
        //forming a new node
        temp->val=i;
        temp->next=newnode;
        temp=temp->next;
        temp->next=NULL;
        //forming a linked list of n length
    }
    return head;
}
node* circular_ll(int n,int c){
    node* head=(node*)malloc(sizeof(node));
    //dynamically allocating a head node
    node* temp=head;
    node* start=NULL;
    for (int i=1;i<n+c;i++){
        node* newnode=(node*)malloc(sizeof(node));
        temp->val=i;
        temp->next=newnode;
        temp=temp->next;
        temp->next=NULL;
        //forming a linked list of n+c length
        if (i==c){
            start=temp;
        }
        //storing the start of a cycle in a linked list
    }
    temp->next=start;
    temp->val=n+c;
    //attaching the last node with the start
    return head;
}
void print_ll(node* head){
    //this is a print function used to print a linked with with a start node of head
    node* curr=head;
    while(curr->next!=NULL){
        printf("%d ->",curr->val);
        curr=curr->next;
    }
    printf("NULL");
}

int detectCycle(node* head){
    //this function detects the cycle in a linked list
    node* slowptr=head;
    node* fastptr=head;
    while(fastptr!=NULL && fastptr->next!=NULL){
        //using the fast and slow approach to detect cycle
        slowptr=slowptr->next;
        fastptr=fastptr->next->next;
        if (fastptr==slowptr){
            return 1;
        }
    }
    return 0;
}

void DetectFindStart(node* head){
    //this function detects the start of the cycle and also the length of cycle
    node* slowptr=head;
    node* fastptr=head;
    int c=0;
    slowptr=slowptr->next;
    fastptr=fastptr->next->next;
    while(fastptr!=slowptr){
        slowptr=slowptr->next;
        fastptr=fastptr->next->next;
    }//this loops detect the cycle first
    int res = 1;
    node* temp = slowptr;
    while (temp->next != slowptr)
    {
        res++;
        temp = temp->next;
    }//this loop counts the number of nodes in the cycle by visiting eaach node in cycle
    slowptr=head;
    while(slowptr->next!=fastptr->next){
        slowptr=slowptr->next;
        fastptr=fastptr->next;
        c++;
    }//this loops detects the start node by putting slowptr at head and moving both pointer by one step
    //until their next point to same node
    if (res>0){
    printf("The linked list has a cycle of length %d and the distance of the start node of the cycle from the head of the linked list is %d.",res,c+1);
    }//printing the result
    else{
        printf("ERROR!!! length of cycle should be more than 2 cycle should be more ");
    }
    return;
}


int main(){
    printf("Press Y for linked list with a cycle and N for without cycles: ");
    char ch;
    scanf("%c",&ch);
    //taking input from user
    if (ch=='N'){
    printf("Enter the size (number of edges) of linked list without cycle: ");
    int s;
    scanf("%d",&s);
    node* head=straight_ll(s);//forming a straight linked list of length s
    //print_ll(head);
    int ans=detectCycle(head);//using detect cuycle function
    if(ans==0)
        printf("The linked list contains no cycle");
    else{
        printf("The linked list contains cycle. Hence Invalid");
    }//printing rersult
    }
    else if(ch=='Y'){
        printf("Enter the length of cycle in the linked list: ");
        int l,c;
        scanf("%d",&l);
        printf("Enter the distance (number of edges) of the start node of the cycle from the head of the linked list:");
        scanf("%d",&c);
        node* circle=circular_ll(l,c);//forming a circular linked list with l as length of cycle and c as length from starting node
        //print_ll(circle);
        int ans1=detectCycle(circle);
        if (ans1==1){
         DetectFindStart(circle);//applying find start function and printing output
        }
        else{
            printf("Invalid");
        }
    }
    return 0;
}
