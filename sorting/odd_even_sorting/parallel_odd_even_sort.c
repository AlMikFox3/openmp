#include<stdio.h>
#include<omp.h>
#include<string.h>




#define ARRAY_SIZE 200000
#define NUM_THREADS 1000


void sort_array(int *arr)
{
  unsigned int i = 0;

  printf("Start Time : %f\n",omp_get_wtime());
  for(i=0;i<ARRAY_SIZE;i++){
    //    printf("Num_threads : %d\n",omp_get_num_threads());
    unsigned int j=0;
    if (i & 1){
#pragma omp parallel for
      for(j=1;j<ARRAY_SIZE - 1;j+=2){
	//printf("num_threads 2 : %d\n",omp_get_num_threads());
	if (arr[j]>arr[j+1]){
	  //swap the two
	  arr[j] += arr[j+1];
	  arr[j+1] = arr[j] - arr[j+1];
	  arr[j] -= arr[j+1];
	}

      }
    }
    else{
#pragma omp parallel for
      for(j=0;j<ARRAY_SIZE-1;j+=2){
	if(arr[j]>arr[j+1]){
	  //swap the two
	  arr[j] += arr[j+1];
	  arr[j+1] = arr[j] - arr[j+1];
	  arr[j] -= arr[j+1];
           	}
      }
    }

  }
  printf("End Time : %f\n",omp_get_wtime());
  /*
  for(i=0;i<ARRAY_SIZE;i++){

    printf("%d ",arr[i]);
  }
  */
}




int main(int argc,char **argv)
{

  int arr[ARRAY_SIZE];
  memset(arr,0,sizeof(int) * ARRAY_SIZE);

  unsigned int i=0;
  for(i=0;i<ARRAY_SIZE;i++){

    arr[i] = i%4;
  }
  
  sort_array(arr);
  
  return 0;
}
