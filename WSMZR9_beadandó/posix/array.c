#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#define N_THREADS 4

typedef struct array{
    int index;
    int* value;
}Array;

void create(Array* array, int size);
void insert(Array* array, int szam);
void delete(Array* array, int index);
void print_all(Array* array);
void insert_random(Array* array);
void free_array(Array* array);

int main()
{
    srand(time(NULL));
    Array array;
    pthread_t threads[N_THREADS];
    const int n = 10;
    create(&array, n);
    for(int i=0;i<10;i++)
    {
        insert(&array,rand());
    }
    print_all(&array);
    clock_t start, end;
    double time;
    start = clock();
    for(int i=0;i<N_THREADS;i++)
    {
        pthread_create(&threads[i],NULL,insert_random,&array);
    }
    end = clock();
    time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\n%lf ido telt el.",time);
    print_all(&array);
    delete(&array, 1);
    print_all(&array);
    free_array(&array);
    return 0;
}

void create(Array* array, int size)
{
    array->value = (int *)malloc(sizeof(int) * size);
    array->index = 0;
    printf("Tomb letrehozva, a merete %d.\n",size);
}

void insert(Array* array, int szam)
{
    array->value[array->index] = szam;
    array->index++;
}

void insert_random(Array* array)
{
    array->value[array->index] = array->index*2;
    array->index++;
}

void delete(Array* array, int index)
{
    for(int i=index;i<array->index;i++)
    {
        array->value[i] = array->value[i+1];
    }
    array->index--;
}

void print_all(Array* array)
{
    for(int i=0;i<array->index;i++)
    {
        printf("%d, ",array->value[i]);
    }
    printf("\n");
}

void free_array(Array* array)
{
    free(array->value);
}
