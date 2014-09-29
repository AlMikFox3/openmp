#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<vector>

using namespace std;

#define NUM_THREADS 10

vector<int>::iterator arr[NUM_THREADS];



void serial_list_traversal(vector<int> &v){
 
  double start_time = omp_get_wtime(),end_time=0;;
   vector<int>::iterator it = v.begin();
 
 while(it!=v.end()){
    //do some heavy processing here
    int heavy_processing_count = 1000000;
    while(heavy_processing_count--);
    printf("%d\n",*it);
    it++;
  }
  end_time = omp_get_wtime();
  printf("serial program\nstart time : %f\nend time : %f\n",start_time,end_time);
}



void parallel_list_traversal(vector<int> &v){

  double start_time = omp_get_wtime(),end_time;
  
  vector<int>::iterator it = v.begin();
  int k=0;
  while(it!=v.end()){
    arr[k++]=it;
    it+=10;
  }


#pragma omp parallel
{
  #pragma omp for
  for(int j=0;j<k;j++){
    vector<int>::iterator start = arr[j];
    int count = 10;
    while(count--){
      //Do some heavy processing here
      int heavy_processing_count = 1000000;
      while(heavy_processing_count--);
      printf("<%d,%d>\n",omp_get_thread_num(),*start);
      start++;
    }

  }

 }
 end_time = omp_get_wtime();
printf("parallel program\nstart time : %f\nend time : %f\n",start_time,end_time);

}

int main(int argc,char *argv[]){
  
  if (argc !=2 ){
    printf("Require 1 argument : \n");
    return 0;
  }
  
  omp_set_num_threads(NUM_THREADS);
  vector<int> v;
  unsigned int i=0,n;
  n=atoi(argv[1]);

  for(i=0;i<n;i++){
    v.push_back(i);
     }
  
   serial_list_traversal(v);
   parallel_list_traversal(v);
  
  return 0;
}
