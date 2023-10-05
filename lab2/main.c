#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define NUM_THREADS 5
#define BUFFER_SIZE 4
#define N 8 // Для циклов, можно её так же и в глобал переменные

int buffer[BUFFER_SIZE];
int fill = 0;
int use = 0;

sem_t empty;
sem_t full;

void *printAlphabetFromNumberThread(void *arg){
    char letter = *((char*) arg); // char* поскольку нам нужно привести к указателю типа char т.к указатели выделяют память в зависимости от от типа

    // Получаем номер потока
    pthread_t tid = pthread_self();
    int threadNumber = (int)(size_t)tid;

    for (int i = 0; i < threadNumber; ++i) {
        printf("%c", letter);
    }

    printf("\n");
    return NULL;
}

void *producer(void *arg) {
    int item;

    for (int i = 0; i < N; ++i) {
        item = i;

        sem_wait(&empty); // уменьшает значение sem на 1 ( 0 > ) когда 0 блокируется и отдаёт управление

        buffer[fill] = item;
        printf("Produced: %d\n", item);
        fill = (fill + 1) % BUFFER_SIZE; // Этот момент стоит прояснить, так мы создаём кольцевое обращаение по индексу
        /*use = (use + 1) % 4; - увеличит use на 1 (1 % 4 = 1).
        use = (use + 1) % 4; - увеличит use еще на 1 (2 % 4 = 2).
        use = (use + 1) % 4; - увеличит use еще на 1 (3 % 4 = 3).
        use = (use + 1) % 4; - увеличит use еще на 1 (4 % 4 = 0 4 возвращает на начало буфера).*/
        sem_post(&full); // увеличивает значение sem на 1
    }

    return NULL;
}

void *consumer(void *arg) {
    int item;

    for (int i = 0; i < N; ++i) {
        sem_wait(&full);

        item = buffer[use];
        printf("Consumed: %d\n", item);
        use = (use + 1) % BUFFER_SIZE;

        sem_post(&empty);
    }

    return NULL;
}

int main() {
    pthread_t threads[5];
    char letters[] = {'A', 'B', 'C', 'D', 'E'};

    for (int i = 0; i < 5; ++i) {
        pthread_create(&threads[i], NULL, printAlphabetFromNumberThread, &letters[i]);
    }

    for (int i = 0; i < 5; ++i) {
        pthread_join(threads[i], NULL);
    }

    printf("----------------task2---------------\n");

    pthread_t producer_thread, consumer_thread;

    sem_init(&empty, 0, BUFFER_SIZE); // В этом месте можно хорошо ломать программу играясь со значениями
    sem_init(&full, 0, 0);

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(consumer_thread, NULL);
    pthread_join(producer_thread, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}

