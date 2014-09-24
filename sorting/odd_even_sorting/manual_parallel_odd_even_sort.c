#include<stdio.h>
#include<string.h>
#include<omp.h>


#define ARRAY_SIZE 20000
#define NUM_THREADS 50

void sort_array(int *arr){

  unsigned int i=0;

  omp_set_num_threads(NUM_THREADS);

  printf("start time : %f\n",omp_get_wtime());
  for(i=0;i<ARRAY_SIZE;i++){
    
    unsigned int j=0;
    if (i & 1){
      
    #pragma omp parallel
    {
      int num_threads = omp_get_num_threads();
      int id = omp_get_thread_num();
      unsigned int j = 0;
      for(j=id*2+1;j<ARRAY_SIZE-1;j += num_threads){

	if (arr[j]>arr[j+1]){
	//swap
	arr[j] += arr[j+1];
	arr[j+1] = arr[j] - arr[j+1];
	arr[j] -= arr[j+1];
	}
      }

    }
   }
    else{
      int num_threads = omp_get_num_threads();
      int id = omp_get_thread_num();
      unsigned int j = 0;
      for(j=id*2;j<ARRAY_SIZE-1;j+=2){
	if (arr[j]>arr[j+1]){
	  //swap

	  arr[j] += arr[j+1];
	  arr[j+1] = arr[j] - arr[j+1];
	  arr[j] -= arr[j+1];
	}
      }
    }

    
  }

  printf("End time : %f\n",omp_get_wtime());

  for(i=0;i<ARRAY_SIZE;i++){
    printf("%d ",arr[i]);
  }
}


int main(int argc,char **argv){

  int arr[ARRAY_SIZE];
  memset(arr,0,sizeof(int)*ARRAY_SIZE);
  unsigned int i=0;
  
  for(i=0;i<ARRAY_SIZE;i++){
    arr[i] = i%4;
  }

  

  sort_array(arr);
  return 0;
}
