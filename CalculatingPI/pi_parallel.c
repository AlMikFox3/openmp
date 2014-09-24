#include<stdio.h>
#include<omp.h>
#include<string.h>

#define NUM_THREADS 5

static long num_steps = 100000;
double step;

double compute_pi(){

  int nthreads = 1;
  double pi = 0.0;

  step = 1.0/(double)num_steps;

  //set the number of threads here
  omp_set_num_threads(NUM_THREADS);
  
  //Create an array of size NUM_THREADS to store the results
  double sum[NUM_THREADS];
  memset(sum,0.0,NUM_THREADS*sizeof(double));

  //measure time
  printf("start time : %f\n",omp_get_wtime());
  #pragma omp parallel
  {
    int id = omp_get_thread_num(),i = 0;
    int num_threads = omp_get_num_threads();
    double x = 0.0;
    

    if (id == 0){
      nthreads = num_threads;
    }
    for(i=id;i<num_steps;i+=num_threads){
      x = (0.5 + (double)i)*step;
      sum[id] += 4.0/(1.0 + x*x);
    }
    
  }
  printf("end time : %f\n",omp_get_wtime());

  unsigned int ic = 0;
  for(ic = 0;ic<nthreads;ic++){
    pi +=sum[ic];
  }
  pi *= step;

  return pi;

}


int main(int argc,char **argv){

  printf("pi = %f\n",compute_pi());

  return 0;
}
