# include <stdio.h>
# include <stdlib.h>
# include <time.h>

void hybridSort(int *,int);
void bubblesort(int arr[],int l,int u); 
int partition(int arr[],int l,int u);

void quicksort(int arr[],int l,int u,int k)
{
  if(u>=l){
    if(u-l+1 > k){
    int pivot = partition(arr,l,u);
      quicksort(arr,l,pivot-1,k); 
      quicksort(arr,pivot+1,u,k);
    }
    else{
      bubblesort(arr,l,u);  
    }
  }
}
int partition(int arr[],int l, int u)
{
  int pivot = u;
  int index = l;
  int i;
  for(i=l;i<u;i++){
    if(arr[pivot] > arr[i]){
      int tmp = arr[index];
      arr[index] = arr[i];
      arr[i] = tmp;
      index++;  
    } 
  }
  int tmp = arr[pivot];
  arr[pivot] = arr[index];
  arr[index] = tmp;
  return index;

}

void bubblesort(int arr[],int l,int u)
{
  int i=0,j;
  for(i=l;i<=u;i++){
    for(j=l;j<=u-i +l - 1;j++){
      if(arr[j] > arr[j+1]){
        int tmp = arr[j];
        arr[j] = arr[j+1];
        arr[j+1] = tmp;
      }     
    }
  }
}

int main()
{
  int *arr,n;
  // srand((unsigned int)time(NULL));
  scanf("%d",&n);
  arr = (int *)malloc(n*sizeof(int));
  hybridSort(arr,n);
  return 0;
}


void hybridSort(int *arr, int n)
{
    int i,j;
    for(i=0;i<n;i++){
      // scanf("%d",&arr[i]);
      arr[i] = rand();
    }
    int k = 1,duparr[n];
    for(i=k;i<=100;i++){
      for(j=0;j<n;j++){
        duparr[j] = arr[j];
      }
      clock_t begin = clock();
      quicksort(duparr,0,n-1,i);
      clock_t end = clock();
      double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
      printf("%d %lf\n",i,time_spent);
    }
         
}
