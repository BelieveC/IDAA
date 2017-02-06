# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <math.h>
struct stat{
  int item;
  int lenLong;
  float avgComp;
  float stdDev;
};
struct node{
  char key[10];
  struct node* next;
}typedef node;
struct stat hash_ETH(char **,int);
struct stat hash_cpp(char **,int);
struct stat hash_cc1(char **,int);

int main()
{
  char **input;
  struct stat hash_stat;
  int n,k,i,j;
  srand(time(NULL));
  n=1632;
  k=5;
  input = (char **)malloc(n*sizeof(char *));
  for(i=0;i<n;i++)
  {
    input[i]=(char *)malloc((k+1)*sizeof(char));
    for(j=0;j<k;j++)
      input[i][j]=(rand()%95)+32;
    input[i][k]='\0';
  }
  printf("ETH\n");
  for(i=1040;i<=1050;i++)
  {
    hash_stat = hash_ETH(input,i);
    printf("%d,%f,%f\n",i,hash_stat.avgComp,hash_stat.stdDev);
  }
  printf("GNU-cc1\n");
  for(i=1040;i<=1050;i++)
  {
    hash_stat = hash_cc1(input,i);
    printf("%d,%f,%f\n",i,hash_stat.avgComp,hash_stat.stdDev);
  }
  printf("GNU-cpp\n");
  for(i=1040;i<=1050;i++)
  {
    hash_stat = hash_cpp(input,i);
    printf("%d,%f,%f\n",i,hash_stat.avgComp,hash_stat.stdDev);
  }

  return 0;
}

struct stat hash_ETH(char **input,int tablesize)
{
  struct stat hash_stat;

  /* write the program to perform ETH on the given input and given hash table size.
     collect statistics as specified in the question and store it in the structure hash_stat
     */ 
  int n=1632,k=5,i,j;
  node** hash_table = (node**)malloc(tablesize*sizeof(node*)); 
  for(i=0;i<tablesize;i++){
    hash_table[i] = (node*)malloc(sizeof(node));
    hash_table[i]->next = NULL;
  }
  for(i=0;i<n;i++){
    int h = 1;
    for(j=0;j<k;j++){
      h = input[i][j]*((h%257)+1); 	
    }
    h = h%tablesize;
    node*tmp = hash_table[h];
    while(tmp->next!=NULL){
      tmp = tmp->next;
    }
    node* tmp2 = (node*)malloc(sizeof(node));
    strcpy(tmp2->key,input[i]);
    tmp2->next = NULL;
    tmp->next = tmp2;
  }
  hash_stat.item = n;
  int comparison[n],tcount,max=0;
  float total=0;
  for(i=0;i<n;i++){
    int h = 1;
    for(j=0;j<k;j++){
      h = input[i][j]*((h%257)+1); 	
    }
    h = h%tablesize;
    node*tmp = hash_table[h];
    tcount=0;
    while(tmp && (strcmp(tmp->key,input[i])!=0)){
      tmp = tmp->next;
      tcount++;
    }
    if(max < tcount) max = tcount;
    total+=tcount;
    comparison[i] = tcount;
  }
  hash_stat.lenLong = max;
  float avg = (total)/n;
  hash_stat.avgComp = avg;
  float deviation=0;
  for(i=0;i<n;i++){
    deviation+=pow((avg-comparison[i]),2);
  }
  deviation/=n;
  deviation = sqrt(deviation);
  hash_stat.stdDev = deviation;
  return hash_stat;
}

struct stat hash_cpp(char **input,int tablesize)
{
  struct stat hash_stat;

  /* write the program to perform GNU-cpp on the given input and given hash table size.
     collect statistics as specified in the question and store it in the structure hash_stat
     */
  int n=1632,k=5,i,j;
  node** hash_table = (node**)malloc(tablesize*sizeof(node*)); 
  for(i=0;i<tablesize;i++){
    hash_table[i] = (node*)malloc(sizeof(node));
    hash_table[i]->next = NULL;
  }
  for(i=0;i<n;i++){
    int h = 0;
    for(j=0;j<k;j++){
      h = input[i][j]+4*h; 	
    }
    h<<1;
    h>>1;
    h = h%tablesize;
    node*tmp = hash_table[h];
    while(tmp->next!=NULL){
      tmp = tmp->next;
    }
    node* tmp2 = (node*)malloc(sizeof(node));
    strcpy(tmp2->key,input[i]);
    tmp2->next = NULL;
    tmp->next = tmp2;
  }
  hash_stat.item = tablesize;
  int comparison[n],tcount,max=0;
  float total=0;
  for(i=0;i<n;i++){
    int h = 1;
    for(j=0;j<k;j++){
      h = input[i][j]*((h%257)+1); 	
    }
    h = h%tablesize;
    node*tmp = hash_table[h];
    //printf("%p\n",tmp);
    tcount=0;
    while(tmp && (strcmp(tmp->key,input[i])!=0)){
      tmp = tmp->next;
      //	printf("%d %p\n",h,tmp);
      tcount++;
    }
    if(max < tcount) max = tcount;
    total+=tcount;
    comparison[i] = tcount;
  }
  hash_stat.lenLong = max;
  float avg = (total)/n;
  hash_stat.avgComp = avg; 
  float deviation=0;
  for(i=0;i<n;i++){
    deviation+=pow((avg-comparison[i]),2);
  }
  deviation/=n;
  deviation = sqrt(deviation);
  hash_stat.stdDev = deviation;
  return hash_stat;
}

struct stat hash_cc1(char **input,int tablesize)
{
  struct stat hash_stat;

  /* write the program to perform GNU-cc1 on the given input and given hash table size.
     collect statistics as specified in the question and store it in the structure hash_stat
     */
  int n=1632,k=5,i,j;
  node** hash_table = (node**)malloc(tablesize*sizeof(node*)); 
  for(i=0;i<tablesize;i++){
    hash_table[i] = (node*)malloc(sizeof(node));
    hash_table[i]->next = NULL;
  }
  for(i=0;i<n;i++){
    int h = 0;
    for(j=0;j<k;j++){
      h = input[i][j]+4*h; 	
    }
    h<<2;
    h>>2;
    h = h%tablesize;
    node*tmp = hash_table[h];
    while(tmp->next!=NULL){
      tmp = tmp->next;
    }
    node* tmp2 = (node*)malloc(sizeof(node));
    strcpy(tmp2->key,input[i]);
    tmp2->next = NULL;
    tmp->next = tmp2;
  }
  hash_stat.item = tablesize;
  int comparison[n],tcount,max=0;
  float total=0;
  for(i=0;i<n;i++){
    int h = 1;
    for(j=0;j<k;j++){
      h = input[i][j]*((h%257)+1); 	
    }
    h = h%tablesize;
    node*tmp = hash_table[h];
    tcount=0;
    while(tmp && (strcmp(tmp->key,input[i])!=0)){
      tmp = tmp->next;
      tcount++;
    }
    if(max < tcount) max = tcount;
    total+=tcount;
    comparison[i] = tcount;
  }
  hash_stat.lenLong = max;
  float avg = (total)/n;
  hash_stat.avgComp = avg; 
  float deviation=0;
  for(i=0;i<n;i++){
    deviation+=pow((avg-comparison[i]),2);
  }
  deviation/=n;
  deviation = sqrt(deviation);
  hash_stat.stdDev = deviation;
  return hash_stat;
}
