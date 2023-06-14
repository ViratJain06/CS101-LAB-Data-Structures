#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *num1,int* num2){
    int temp=*num1;
    *num1=*num2;
    *num2=temp;
}
//for swapping two values

void quickSort(int arr[], int low, int high)
{
    if (low < high) {
        int pos;
        int pivot=arr[high];//taking last element as pivot
        for (pos=low; pos<high; pos++){
            if (arr[pos] == pivot)
                break;
         }
        swap(&arr[pos], &arr[high]);
        pos = low;
        for (int j = low; j < high ; j++)
        {
            if (arr[j] <= pivot)
             {
                swap(&arr[pos], &arr[j]);
                pos++;
            }
        }
        swap(&arr[pos], &arr[high]);//doing partition along the pivot element
        quickSort(arr, low, pos - 1);//recursively calling for both partitions
        quickSort(arr, pos + 1, high);
    }
}

int median(int arr[],int n){
    quickSort(arr,0,n-1);
    return arr[n/2];
}//this function is for finding medians

int kthSmallest_MOM(int arr[],int lo, int hi , int k ){
    int n=hi-lo+1;
    if (k>0 && k<=n){
        int j,mid[(n+4)/5];
        for (j=0; j<n/5; j++)
            mid[j] = median(arr+lo+j*5, 5);//array of medians
        if (n%5!=0){
            mid[j]=median(arr+lo+j*5,n%5);
            j++;
            }//handeling last group
        int MedOfMed;
        if (j==1)
            MedOfMed=mid[0];
        else
            MedOfMed=kthSmallest_MOM(mid,0,j-1,j/2);//finding medians of small group of medians
    int pos;
    for (pos=lo; pos<hi; pos++){
        if (arr[pos] == MedOfMed)
           break;
    }//taking medofmed as pivot element
    swap(&arr[pos], &arr[hi]);
    pos = lo;
    for (int j = lo; j < hi ; j++)
    {
        if (arr[j] <= MedOfMed)
        {
            swap(&arr[pos], &arr[j]);
            pos++;
        }
    }//doing partition along the medians 
    swap(&arr[pos], &arr[hi]);
    if (pos-lo == k-1)
        return arr[pos];
    else if (pos-lo > k-1)  
        return kthSmallest_MOM(arr, lo, pos-1, k);
    else
        return kthSmallest_MOM(arr, pos+1, hi, k-pos+lo-1);
    }//recursively calling the function for sub partitions
    return 9999999;//when k is larger then n
}

int func1(int arr[],int n,int k){
    quickSort(arr,0,n-1);
    return arr[k-1];
}//function 1 for quick sort

int func2(int arr[],int n,int k){
    return kthSmallest_MOM(arr,0,n-1,k);
}//function 2 for median of median algorithm


int main(){
    FILE * ptr= fopen("ExampleFile.txt","r");//opening the file
    int n,k;
    fscanf(ptr,"%d",&n);//taking input from text file
    fscanf(ptr,"%d",&k);
    int arr[n],arr1[n];
    for (int i=0;i<n;i++){
        fscanf(ptr,"%d",&arr[i]);
    }

    printf("The size of the array is %d \n",n);
    printf("The value of K is %d \n",k);

    fclose(ptr);
    // closing the file and Printing the size of array

    for (int i=0;i<n;i++){
        arr1[i]=arr[i];
    }//copying elements to arr1 as instructed

    clock_t t1,t2,t3,t4;//defining time variables
    double time1,time2;//for calculating time in clock per seconds
    t1 = clock();
    printf("Calling func1:\n");
    printf("The %dth smallest element returned by func1 is %d \n",k,func1(arr1,n,k));
    t2 = clock();
    time1 = (long double)(t2-t1)/CLOCKS_PER_SEC;
    printf("The time taken by func1 is %lf\n",time1);
    //printing kth smallest by function 1 and its time of execution
    t3=clock();
    printf("Calling func2:\n");
    printf("The %dth smallest element returned by func1 is %d \n",k,func2(arr,n,k));
    t4=clock();
    time2 = (long double)(t4-t3)/CLOCKS_PER_SEC;
    printf("The time taken by func2 is %lf\n",time2);
    //printing kth smallest by function 2 and its time of execution
    return 0;  
}