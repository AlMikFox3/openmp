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
  
 
  //measure time
  printf("start time : %f\n",omp_get_wtime());
  #pragma omp parallel
  {
    int id = omp_get_thread_num(),i = 0;
    int num_threads = omp_get_num_threads();
    double x = 0.0,sum = 0.0;
    

    if (id == 0){
      nthreads = num_threads;
    }
    for(i=id;i<num_steps;i+=num_threads){
      x = (0.5 + (double)i)*step;
      sum += 4.0/(1.0 + x*x);
    }

    #pragma omp atomic
    pi += sum * step;
    
  }
  printf("end time : %f\n",omp_get_wtime());


  return pi;

}


int main(int argc,char **argv){

  printf("pi = %f\n",compute_pi());

  return 0;
}
