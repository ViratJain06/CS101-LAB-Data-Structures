#include <stdio.h>

//Name- Virat Jain
//Entry number- 2021CSB1220

void swap(int *a, int *b)
{
    int temp = *a;
      *a = *b;
      *b = temp;
}

void maxheapify(int arr[], int n, int i)
{
    int lr = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && arr[l] > arr[lr])
        lr = l;
    if (r < n && arr[r] > arr[lr])
        lr = r;
    if (lr != i) {
        swap(&arr[i], &arr[lr]);
        maxheapify(arr, n, lr);
    }
}

void minheapify(int arr[], int n, int i)
{
    int sr = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && arr[l] < arr[sr])
        sr = l;
    if (r < n && arr[r] < arr[sr])
        sr = r;
    if (sr != i) {
        swap(&arr[i], &arr[sr]);
        minheapify(arr, n, sr);
    }
}

void buildmaxHeap(int arr[], int n)
{
    int start = (n / 2) - 1;
    for (int i = start; i >= 0; i--) {
        maxheapify(arr, n, i);
    }
}

void buildminHeap(int arr[], int n)
{
    int start = (n / 2) - 1;
    for (int i = start; i >= 0; i--) {
        minheapify(arr, n, i);
    }
}

int extract_max( int arr[],int n){
    if (n<1){
        return -1;
    }
    int max_ele=arr[0];
    arr[0]=arr[n-1];
    n=n-1;
    maxheapify(arr,n,0);
    return max_ele;

}

int kthLargest_max(int arr[],int n, int k){
    buildmaxHeap(arr,n);
    for (int i=1;i<k;i++){
        extract_max(arr,n);
        n=n-1;
    }
    return extract_max(arr,n);
}

int kthLargest_min(int a[], int n, int k)
 {
 int minHeap[k];
 for(int i=0;i<k;i++){
      minHeap[i] = a[i];
 }
 buildminHeap(minHeap,k);
 for(int i=k;i<n;i++)
 {
      if(a[i]>minHeap[0])
      {
           minHeap[0]=a[i];
           minheapify(minHeap,k,0);
      }
 }
 return minHeap[0];
 }


int main()
{
    int n,k;
    printf("Enter number of elements n and k: ");
    scanf("%d ",&n);
    scanf("%d",&k);
    printf("Enter %d numbers: ",n);
    int arr[n],crr[n];
    for (int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    printf("%d th largest with Algorithm 2(Min_heap) ",k);
    printf("%d \n",kthLargest_min(arr,n,k));
    printf("%d th largest with Algorithm 1(Max_heap) ",k);
    printf("%d \n",kthLargest_max(arr,n,k));
    return 0;
}
