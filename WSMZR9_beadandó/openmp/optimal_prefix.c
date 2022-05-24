#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <omp.h>
#define N 64

int main()
{
    srand(time(NULL));
    int sequence[N];
    for(int i=0;i<N;i++)
    {
        sequence[i] = rand() % 10;
    }
    
    clock_t start, end;
    double time;
    int logarithm = floor(log(N)/log(2));
    int partition = N / logarithm;
    int* subarray = (int*)calloc(logarithm, sizeof(int));

    int s = 0;
    start = clock();
    #pragma omp parallel for reduction (+:s)
    for(int i=0;i<N;i+=partition)
    {
        #pragma omp parallel for reduction (+:s)
        for(int j=i+1;j<i+partition;j++)
        {
            if(j > N-1)
                continue;
            s = sequence[j-1];
            sequence[j] += s;
        }
    }

    int index_subarray = 0;
    #pragma omp for
    for(int i=partition-1;i<N;i+=partition)
    {
        if(i>partition-1)
        {
            subarray[index_subarray] = sequence[i]+subarray[index_subarray-1];
            sequence[i] = subarray[index_subarray];
            index_subarray++;
        }
        else
        {
            subarray[index_subarray] = sequence[i];
            index_subarray++;
        }
    }
    index_subarray = 0;
    #pragma omp for
    for(int i=partition;i<N;i+=partition)
    {
        #pragma omp parallel for reduction (+:s)
        for(int j=i;j<i+partition-1;j++)
        {
            if(j > N-1)
                continue;
            s = subarray[index_subarray];
            sequence[j] += s;
        }
        index_subarray++;
    }
    end = clock();
    for(int i=0;i<N;i++)
       printf("%d ", sequence[i]);

    time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nOpenMP: %lf ido telt el.",time);
    return 0;
}