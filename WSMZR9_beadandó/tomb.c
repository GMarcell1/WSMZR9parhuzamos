#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#define N_THREADS 4

typedef struct tomb{
    int index;
    int* ertek;
}Tomb;

void letrehoz(Tomb* tomb, int meret);
void hozzaad(Tomb* tomb, int szam);
void torol(Tomb* tomb, int index);
void kiir(Tomb* tomb);
void hozzaad_random(Tomb* tomb);

int main()
{
    srand(time(NULL));
    Tomb tomb;
    pthread_t threads[N_THREADS];
    const int n = 10;
    letrehoz(&tomb, n);
    for(int i=0;i<10;i++)
    {
        hozzaad(&tomb,rand());
    }
    kiir(&tomb);
    for(int i=0;i<N_THREADS;i++)
    {
        pthread_create(&threads[i],NULL,hozzaad_random,&tomb);
    }
    kiir(&tomb);
    torol(&tomb, 1);
    kiir(&tomb);
    return 0;
}

void letrehoz(Tomb* tomb, int meret)
{
    tomb->ertek = (int *)malloc(sizeof(int) * meret);
    tomb->index = 0;
    printf("Tomb letrehozva, a merete %d.\n",meret);
}

void hozzaad(Tomb* tomb, int szam)
{
    tomb->ertek[tomb->index] = szam;
    tomb->index++;
}

void hozzaad_random(Tomb* tomb)
{
    tomb->ertek[tomb->index] = tomb->index*2;
    tomb->index++;
}

void torol(Tomb* tomb, int index)
{
    for(int i=index;i<tomb->index;i++)
    {
        tomb->ertek[i] = tomb->ertek[i+1];
    }
    tomb->index--;
}

void kiir(Tomb* tomb)
{
    for(int i=0;i<tomb->index;i++)
    {
        printf("%d, ",tomb->ertek[i]);
    }
    printf("\n");
}
