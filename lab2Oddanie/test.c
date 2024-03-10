#include <stdio.h>
#include <time.h>
#include "opt_invsqrt.c"
#include "invsqrt.c"

int main(){
	float number = 64;
    clock_t start_time, ending_time;
    double time1, time2, time3;
    
    start_time = clock();
    for (int i = 0; i < 1000000; i++)
        {
            reverse_sqrtf(number);
        }
    ending_time = clock();
    time1 = (double)(ending_time - start_time) / CLOCKS_PER_SEC;
    
    printf("time 1 (reverse_sqrtf): %lf \n\n", time1);
    
    start_time = clock();
    for (int i = 0; i < 1000000; i++)
        {
            q_rsqrt(number);
        }
    ending_time = clock();
    time2 = (double)(ending_time - start_time) / CLOCKS_PER_SEC;
    
    printf("time 2 (q_rsqrt): %lf \n\n", time2);
    
    start_time = clock();
    for (int i = 0; i < 1000000; i++)
        {
            optymalized_invsqrt(number);
        }
    ending_time = clock();
    time3 = (double)(ending_time - start_time) / CLOCKS_PER_SEC;
    
    printf("time 3 (optymalized_invsqrt): %lf \n\n", time3);
}
