#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Name- Virat Jain
//Entry Number- 2021csb1220
void function1( int array1[],int n){
    //this is the first function which computes the cumulative sum
    int clarr[n];//defining cumulative sum array
    clarr[0]=array1[0];
    for (int j=1;j<n;j++){
            clarr[j]=array1[j]+clarr[j-1];
    }//this loops calculate cumulative sum of array and stores it in clarr
    clock_t t1;
    t1 = clock();
    for (int k=1;k<n;k++){
        clarr[k]+=5;
    }//this loops updates the value at every index as it is cumulative
    int inc=clarr[1]-clarr[0];
    t1 = clock() - t1;
    double time_taken = ((double)t1)/CLOCKS_PER_SEC; // in seconds
    printf("The time taken for query 1 by function 1 is %f\n", time_taken);
    printf("The incremented value of the first index element is %d\n",inc);
    clock_t t2;
    t2 = clock();
    array1[1]+=5;//updating in original array
    int sum_=clarr[n-6];//sum of n-5 element
    t2 = clock() - t2;
    double time_taken2 = ((double)t2)/CLOCKS_PER_SEC; // in seconds
    printf("The time taken for query 2 by function 1 is %f\n", time_taken2);
    printf("The sum of first n-5 elements is %d\n",sum_);
    return;
}

void function2( int array1[],int n){
    //this is the second function which computes the binary index tree of an array
    int bitree[n+1];//defining binary index array
    memset(bitree+0,0,sizeof(bitree));//initializng values of BIT as 0
    for (int i=0;i<n;i++){
        int j=i+1;
        for (;j<=n;j+= j&-j){
            bitree[j]+=array1[i];
        }
    }//this loops construct binary index tree
    clock_t t1;
    t1 = clock();
    int y=1;
    for (;y<=n;y+= y&-y){
        bitree[y]+=5;
    }//updating value 5 at index 1 in BIT array
    array1[1]+=5;//updating in original array
    int z=2;
    int sum1 = 0;
     for(; z > 0; z -= z&-z){
        sum1+= bitree[z];//finding the updated value
        }//sum1 represents the updated value of the array
        t1 = clock() - t1;
    double time_taken = ((double)t1)/CLOCKS_PER_SEC; // in seconds
    printf("The time taken for query 1 by function 2 is %f\n", time_taken);
    printf("The incremented value of the first index element is %d\n",sum1);
    clock_t t2;
    t2 = clock();
    int x=n-5;
    int sum = 0;
     for(; x > 0; x -= x&-x){
        sum += bitree[x];}//this loops calculates the sum of contributing values in BIT array
        t2 = clock() - t2;
    double time_taken2 = ((double)t2)/CLOCKS_PER_SEC; // in seconds
    printf("The time taken for query 2 by function 2 is %f\n", time_taken2);
        printf("The sum of first n-5 elements is %d\n",sum);
}
int main()
{
    char choice;
    printf("Please enter a choice: ");
    scanf("%c", &choice);//taking the choice input from user
    if (choice=='a'){
        int num,c=1;
       FILE *fptr= fopen("ExampleFile.txt","r");//opening the txt file
       if (fptr==NULL){
        printf(" Error ,could not open file");
       }//condition for unsucessful attempt
       else{
        fscanf(fptr,"%d",&num);
        while(fscanf(fptr,"%d",&num)!=EOF){
            c++;
        }//counting the total numbers of integers in the file and storing it
        fclose(fptr);
        printf("The array size is %d\n",c);
        FILE *fileptr= fopen("ExampleFile.txt","r");
        int arr[c];//creating the the of the required size
        for(int k=0;k<c;k++){
            fscanf(fileptr,"%d",&arr[k]);
        }//taking formatted input from the file and storing it in a array
        printf("By function_1 \n");
        function1(arr,c);//passing the constructed array in function 1
        printf("By function_2 \n");
        function2(arr,c);//same array in function 2
        fclose(fileptr);
       }
    }
    else if(choice=='b'){

       int *ptr=NULL,i=0;
       ptr=(int*)malloc(1*sizeof(int));//allocating memory for the pointer to take input
       if (ptr== NULL)
       {
           printf("Memory not allocted.\n");
       }

       else{
            printf("Please input an integer array with space-separator and press Enter when done:\n");
            scanf("%d",&ptr[i]);
            while (1){
                    if (getchar()=='\n')
                    {
                        break;
                    }//breaking condition for dynamic inputs
                    else{
                        i++;
                ptr = (int*)realloc(ptr,sizeof(int)*(i));//reallocating memory for next input until EOF occurs
                scanf("%d",&ptr[i]);
                }
            }
            printf("The array size is %d \n",i+1);
        printf("By function_1 \n");
        function1(ptr,i+1);//passing the dynamically allocated array in function 1
        printf("By function_2 \n");
        function2(ptr,i+1);//passing the same array in function 2
       }
    }
        return 0;
}
