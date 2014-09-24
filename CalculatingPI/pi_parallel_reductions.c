#include<stdio.h>
#include<omp.h>


static long num_steps = 100000;
double step;


double compute_pi(){

  unsigned int i = 0;
  double pi,sum = 0.0;


 step = 1.0/(double)num_steps;
 
#pragma omp parallel for reduction(+ : sum)
 for(i=0;i<num_steps;i++)

{
  
  double x;

   x =(0.5 + (double)i)*step;
   sum = (sum + 4.0/(1.0 + x*x));

 }

 pi = sum * step;
 return pi;

}

int main(){

 
  printf("pi = %f",compute_pi());


  return 0;
}
