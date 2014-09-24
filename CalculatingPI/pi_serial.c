#include<stdio.h>
#include<omp.h>


static long num_steps = 100000;
double step;


double compute_pi(){

  unsigned int i = 0;
  double x,sum = 0.0,pi;


 step = 1.0/(double)num_steps;
 
 for(i=0;i<num_steps;i++){
   x =(0.5 + (double)i)*step;
   sum += 4.0/(1.0 + x*x);

 }

 pi = sum*step;
 return pi;

}

int main(){

 
  printf("pi = %f",compute_pi());


  return 0;
}
