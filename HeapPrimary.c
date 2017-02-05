#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define MAXQUEUE 20
int front = -1;
int rear = -1;

typedef struct node{ 
         struct node* left;
         struct node* right;
         struct node* parent;
         int value;
         int priority;
 }node;

void Insertion(node*);
int is_empty(int *front,int *rear)
{
	if(*front == -1 && *rear == -1){
		return 1;
	}
	return 0;

}

int is_full(int* front,int* rear)
{
	if((*rear+1)%MAXQUEUE == *front){
		return 1;
	}
	return 0;
}
void enqueue(node* a[],int* front,int* rear, node* value)
{
	if(!is_full(front,rear)){
		if(is_empty(front,rear)){
			*rear = 0;
			*front = 0;
			a[*rear] = value;
			// printf("Hola,Inserted %d\n",a[*rear]->value);	
		}
		else{
			*rear = (*rear + 1)%MAXQUEUE;
			a[*rear] = value;
			// printf("%dLola,Inserted %d\n",*rear,a[*rear]->value);
		}
		// printf("Rear = %d, Front %d & value = %d\n",*rear,*front,a[*rear]->value);
	}
	else{
		printf("It is full\n");
	}
}

node* dequeue(node* a[],int * front,int *rear)
{
	if(!is_empty(front,rear)){
		// printf("%d %dHello\n",*front,*rear);
		if(*front == *rear){
			int tmp = *front;
			*front = -1;
			*rear = -1;	
			return a[tmp];
		}
		else{
			int tmp = *front;
			*front = ((*front)+1)%MAXQUEUE;
			return a[tmp];
		}
	}
	else{
		node* tmp = (node*)malloc(sizeof(node));
		tmp->value =INT_MAX;
		return tmp;
	}	
}

void swap(node* tmp, node* largest){
	int k = tmp->value;
	int l = tmp->priority;
	tmp->value = largest->value;
	tmp->priority = largest->priority;
	largest->value = k;
	largest->priority = l;
}

void insertInHeap(node* a[],int n,node* start)
{	
	while(start->left != NULL && start->right != NULL){
		enqueue(a,&front,&rear,start->left);
		enqueue(a,&front,&rear,start->right);		
		start = dequeue(a,&front,&rear);
		// printf("Dequeued %d\n",start->value);		
	}
	int k = 0;
	k = start->left == NULL ? 0:1;
	// printf("k = %d & %d\n",k,start->value);
	node* tmp = (node*)malloc(sizeof(node));
	tmp->left = NULL;
	tmp->right = NULL;
	tmp->parent = start;
	tmp->value = n;
	tmp->priority = n;
	if(k){
		start->right = tmp;
		Insertion(start->right);
	}
	else{
		start->left = tmp;
		Insertion(start->left);
	}
	front = -1;
	rear = -1;
}

void maxHeapify(node* tmp)
{	
	node* largest = tmp;
	if(tmp->left && tmp->left->value > tmp->value){
		largest = tmp->left;
	}
	if(tmp->right && tmp->right->value > largest->value){
		largest = tmp->right;
	}
	if(tmp != largest){	
		swap(tmp,largest);
		maxHeapify(largest);
	}

}
void Insertion(node* newNode){
	node* tmp = newNode;
	while(tmp->parent != NULL){
		if(tmp->value > tmp->parent->value){
			// printf("Swapped %d %d\n",tmp->value,tmp->parent->value);
			swap(tmp,tmp->parent);
			tmp = tmp->parent;

		}
		else{
			break;
		}
	}
}
int getHighPriority(node* a[],node* start){
	front = -1;
	rear = -1;
	node* tmp = start;
	int k = start->value;
	while(tmp->left != NULL && tmp->right != NULL){
		enqueue(a,&front,&rear,tmp->left);
		enqueue(a,&front,&rear,tmp->right);		
		tmp = dequeue(a,&front,&rear);		
	}
	if(tmp->right != NULL){
		enqueue(a,&front,&rear,tmp->right);
	}
	if(tmp->left != NULL){
		enqueue(a,&front,&rear,tmp->left);
	}
	node* check = dequeue(a,&front,&rear);
	while(check->value != INT_MAX){
		tmp = check;
		check = dequeue(a,&front,&rear);
	}
	swap(start,tmp);
	if(tmp->parent){
		node* parent = tmp->parent;
		if(parent->left && parent->left->value == tmp->value){
			parent->left = NULL;
		}
		else{
			parent->right = NULL;
		}
		maxHeapify(start);
	}
	return k;
}

void printHeap(node* a[],node* start){
	printf("%d ",start->value );
	while(start && start->left && start->right){
		printf("%d %d ",start->left->value,start->right->value);	
		enqueue(a,&front,&rear,start->left);
		enqueue(a,&front,&rear,start->right);		
		start = dequeue(a,&front,&rear);
	}
	if(start->left){
		printf(" Last left %d ", start->left->value);
	}
	if(start->right){
		printf("Last right %d",start->right->value);
	}
	printf("\n");
}
int main()
{	
	node* a[MAXQUEUE];
	struct node* start = (node*)malloc(sizeof(node));
	start->left = NULL;
	start->right = NULL;
	start->parent = NULL;
	int k,i;
	scanf("%d",&k);	
	start->value = k,start->priority = k;
	int heap[21];
	for(i=0;i<9;i++){
		scanf("%d",&k);
		insertInHeap(a,k,start);
	}
	printHeap(a,start);
	for(i=9;i>=0;i--){
		k = getHighPriority(a,start);
		printf("%d\n",k);
		// printHeap(a,start);
	}
	
}
