# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
void radix_sort(char **,int,int);
char** countingSort(char** input,int n,int k,int i);
int main()
{
  char **input;
  char ch=' ';
  int n,k,i,j;
  srand(time(NULL));
  scanf("%d",&n);
  scanf("%d",&k);
  input = (char **)malloc(n*sizeof(char *));
  for(i=0;i<n;i++)
  {
    input[i]=(char *)malloc((k+1)*sizeof(char));
    for(j=0;j<k;j++)
    input[i][j]=(rand()%26)+97;
    input[i][k]='\0';
  }
  radix_sort(input,n,k);
  for(i=0;i<n;i++)
  {
    printf("%s\n",input[i]);
  }
 
  return 0;
}

void radix_sort(char **input,int n,int k)
{
  /* The function sorts the array input using radix sort
     Write the two versions of the radix sort here, one after another.
     To execute one of the version just comment out the other version.
   */
  int i;
  char** original = input;
  for(i=k-1;i>=0;i--){
	  input = countingSort(input,n,k,i);
  }
  for(i=0;i<n;i++){
    strcpy(original[i],input[i]);
  }
}

char** countingSort(char **input,int n,int k,int i)
{
  int count[95];
  char **output = (char**)malloc(n*sizeof(char*));
  memset(count,0,sizeof(count));
  int j;
  for(j=0;j<n;j++){
  	int k = input[j][i];	
  	count[k-32]++;
  	output[j] = (char*)malloc((k+1)*sizeof(char));
  }  
  for(j=1;j<95;j++){
	  count[j]+=count[j-1];	
  }
  for(j=n-1;j>=0;j--){
  	int k = input[j][i];
  	int loc = count[k-32];
  	count[k-32]--;
  	strcpy(output[loc-1],input[j]);
  }
  // for(j=0;j<n;j++){
  //   printf("I = %d and %s\n",i,output[j]);
  // }
  // printf("\n");
  return output;
}

