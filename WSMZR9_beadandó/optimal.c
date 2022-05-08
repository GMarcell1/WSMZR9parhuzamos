#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <omp.h>
#define N 16

int main()
{
    int szamsor[N] = {5,1,2,3,2,4,1,3,2,4,1,1,3,5,2,3};
    for(int i=0;i<N;i++)
    {
        printf("%d ", szamsor[i]);
    }
    printf("\n");
    int felosztas = floor(log(N)/log(2));
    int* seged = (int*)calloc(felosztas, sizeof(int));
    int s = 0;
    clock_t start, end;
    double ido;
    start = clock();
    #pragma omp parallel for reduction (+:s)
    for(int i=0;i<N;i+=felosztas)
    {
        #pragma omp parallel for reduction (+:s)
        for(int j=i+1;j<i+felosztas;j++)
        {
            s = szamsor[j-1]; 
            szamsor[j] += s;
        }
    }
    int novekvo = 0;
    #pragma omp for
    for(int i=felosztas-1;i<N;i+=felosztas)
    {
        if(i>felosztas-1)
        {
            seged[novekvo] = szamsor[i]+seged[novekvo-1];
            szamsor[i] = seged[novekvo];
            novekvo++;
        }
        else
        {
            seged[novekvo] = szamsor[i];
            novekvo++;
        }
    }
    novekvo = 0;
    #pragma omp for
    for(int i=felosztas;i<N;i+=felosztas)
    {
        #pragma omp parallel for reduction (+:s)
        for(int j=i;j<i+felosztas-1;j++)
        {
            s = seged[novekvo];
            szamsor[j] += s;
        }
        novekvo++;
    }
    end = clock();
    for(int i=0;i<N;i++)
        printf("%d ", szamsor[i]);

    ido = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\n%lf ido telt el.",ido);
    return 0;
}