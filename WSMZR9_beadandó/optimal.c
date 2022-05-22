#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <omp.h>
#define N 8182
int main()
{
    srand(time(NULL));
    int szamsor[N];
    for(int i=0;i<N;i++)
    {
        szamsor[i] = rand() % 10;
    }
    clock_t start, end;
    double ido;
    int logaritmus = floor(log(N)/log(2));
    int felosztas = N / logaritmus;
    int* seged = (int*)calloc(logaritmus, sizeof(int));

    int s = 0;
    start = clock();
    #pragma omp parallel for reduction (+:s)
    for(int i=0;i<N;i+=felosztas)
    {
        #pragma omp parallel for reduction (+:s)
        for(int j=i+1;j<i+felosztas;j++)
        {
            if(j > N-1)
                continue;
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
            if(j > N-1)
                continue;
            s = seged[novekvo];
            szamsor[j] += s;
        }
        novekvo++;
    }
    end = clock();
    //for(int i=0;i<N;i++)
     //   printf("%d ", szamsor[i]);

    ido = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nOpenMP: %lf ido telt el.",ido);
    return 0;
}
