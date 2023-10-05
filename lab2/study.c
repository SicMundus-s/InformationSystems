#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

void *print_hello(void *thread_id) {
    long tid = (long)thread_id;
    printf("Hello from thread %ld!\n", tid);
    pthread_exit(NULL);
}


void test() {
    int array[] = {1, 2, 3, 4};
    int *p[] = { &array[1], &array[2], &array[0] };

    for(int i = 0; i < 3; i++)
    {
        printf("%d", *p[i]);
    }
}

//int main() {
//    test();
//
//    return 0;
//}


void samoeVajnoe() {
    int x = 10;
    void *voidp = &x; // Указывает на любой тип
    voidp++; // Можно применять операции
    register int y = 15; // Говорим процессора поместить это в быструю память
}

struct person
{
    char* name;
    int age;
};