# include <stdio.h>
# include <stdlib.h>
#include<math.h>
int n;
int check_MAX_heap(int *,int,int);
void build_MAX_heap(int *,int, int);
int extract_MAX(int *,int, int);
void insert(int *,int,int,int);
void change(int *,int,int,int,int);
void maxHeapify(int*,int,int,int);
void printHeap(int* ,int);
int main()
{
  char ch=' ';
  int *arr,k,i,new;
  scanf("%d",&k);
  scanf("%d",&n); /* To have anything non-trivial, n should be >2*n*k*/
  arr = (int *)malloc(2*n*sizeof(int));
  for(i=0;i<n;i++)
    {
      scanf("%d",&arr[i]);
    }
  if(!check_MAX_heap(arr,n,k)){
//     printf("Not max heap\n");
     build_MAX_heap(arr,n,k);
  }
  do
    {
      while(getchar()!='\n'); /* To clear the buffer of any leftover characters*/
      ch=getchar();
//      printf("%c\n",ch);
      switch(ch)
	{
	case 'i':
	  scanf("%d",&new);
	  insert(arr,n,k,new);
	  n++;
	  break;
	case 'd':
	  printf("%d",extract_MAX(arr,n,k));
	  n--;
	  break;
	case 'c':
	  scanf("%d",&i);
	  scanf("%d",&new);
	  change(arr,n,k,i,new);
	  break;
	}
    }while(ch!='q');
  return 0;
}
void printHeap(int arr[],int n)
{
	int i=0;
	for(i;i<n;i++){
		printf("%d ",arr[i]);
	}	
	printf("\n");
}
void swap(int arr[],int i,int largest){
	int k = arr[i];
	arr[i] = arr[largest];
	arr[largest] = k;
}

int check_MAX_heap(int arr[],int n,int k)
{
  /* The function returns 0 if arr is NOT a k-ary MAX-heap.*/
  int i=0,j;
  for(i=0;i<n/k;i++){
	int largest = arr[i];
	for(j=i*k+1;j<n && j<=(i+1)*k;j++){
	if(arr[j]>largest){
			largest = arr[j];
			break;
		}
	}	
	if(largest!=arr[i]){
		return 0;
	}
  }
  return 1;
}

void maxHeapify(int arr[],int n,int k,int i)
{	int largest=i,j;
	do{
		if(largest!=i){
			swap(arr,largest,i);			
		}
		i = largest;
		for(j=i*k+1;j<n && j<=(i+1)*k;j++){
			if(arr[largest] < arr[j]){
				largest = j;
			}
		}
		
	}while(largest!=i);
	
}

void build_MAX_heap(int arr[],int n,int k)
{
  /* This function shuffle the elements of arr till it is a k-ary MAX-heap*/
	int i = ceil((n/k))-1;
	for(i;i>=0;i--){
		maxHeapify(arr,n,k,i);
	}	
}

void insert(int arr[],int n,int k,int new)
{
  /* This function inserts a new element into the k-ary MAX-heap arr*/
//	printf("N = %d\n",n);
	arr[n] = new;
	int i=n;
	for(i;i>=0;i=(ceil(i/k)-1)){	
		int parent = ceil(i/k)-1;
		if(parent<0){
			parent = 0;
		}
		if(arr[parent] < arr[i]){
//			printf("Swap %d %d\n",i,parent);
			swap(arr,parent,i);
		}
		else{
			break;
		}
	}
}

int extract_MAX(int arr[],int n,int k)
{
  /* This function extracts the maximum element of a k-ary MAX-heap and returns it*/
	 int tmp = arr[0];
 	 arr[0] = arr[n-1];
         maxHeapify(arr,n,k,0);
         return tmp;
}

void change(int arr[],int n,int k,int i,int new)
{
  /* This function changes the value of arr[i]= new and makes arr a k-ary max-heap*/
 	arr[i] = new;
  	maxHeapify(arr,n,k,i);
	int j = i;
	for(j;j>=0;i=(ceil(j/k)-1)){
		int parent = ceil(j/k)-1;
		if(parent<0){
			parent = 0;
		}
		if(arr[parent] < arr[j]){
			swap(arr,parent,j);
		}
		else{
			break;
		}
        } 			
}
