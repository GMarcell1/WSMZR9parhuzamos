#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <pthread.h>
#define ARRAY_SIZE 10000
//internetről a 1229
#define PRIME_NUMBER_SIZE 1229

int array[ARRAY_SIZE];
int prime_number[PRIME_NUMBER_SIZE];

void init_array();
void print();
void prime_number_finder();

typedef struct parallel{
    int index_start;
    int index_end;
    int prime;
}Parallel;

void posix_task(Parallel* task);

int main()
{
    srand(time(NULL));
    const int threads_number = 8;
    pthread_t threads[threads_number];
    Parallel tasks[threads_number];
    clock_t start, end;
    double time;
    start = clock();
    init_array();
    prime_number_finder();
    //print();
    int sizeperthread = ARRAY_SIZE/threads_number;
    int index = 0;
    for(int i=0;i<ARRAY_SIZE;i+=sizeperthread)
    {
        tasks[index].index_start = i;
        tasks[index].index_end = i+sizeperthread;
        tasks[index].prime = 0;
        index++;
    }
    for(int i=0;i<threads_number;i++)
    {
        pthread_create(&threads[i],NULL,posix_task,&tasks[i]);
    }
    int sum = 0;
    for(int i=0;i<threads_number;i++)
    {
        sum += tasks[i].prime;
    }
    end = clock();
    time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%d primszam van a %d db random generalt szamsorban.",sum,ARRAY_SIZE);
    printf("\n%lf ido telt el az osszehasonlitas soran.",time);
    return 0;
}

void init_array()
{
    for(int i=0;i<ARRAY_SIZE;i++)
    {
        array[i] = rand()%10000;
    }
}

void print()
{
    for(int i=0;i<ARRAY_SIZE;i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void posix_task(Parallel* task)
{
    for(int i=task->index_start;i<task->index_end;i++)
    {
        for(int j=0;j<PRIME_NUMBER_SIZE;j++)
        {
            if(array[i] == prime_number[j])
            {
                task->prime++;
            }
        }
    }
}

void prime_number_finder()
{
    prime_number[0] = 2;
    int index = 1;
    int a = 0;
    for(int i=3;i<=10000;i++)
    {
        a = 0;
        for(int j=2;j<=i-1;j++)
        {
            if(i % j == 0)
            {
                a = 1;
                break;
            }
        }
        if(a == 0)
        {
            prime_number[index] = i;
            index++;
        }
    }
}