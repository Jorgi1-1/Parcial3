#include <stdio.h>
#include <pthread.h>
#include <stdlib.h> 

int buffer = 0;

int square(int x) 
{
    return x * x;
}

void* producer(void* arg) 
{
    while (1) 
    {
        if (buffer == 0) 
        {
            int num;
            printf("Insert a number: ");
            scanf("%d", &num);
            buffer = num;
        }
    }
}

void* consumer(void* arg) 
{
    while (1) 
    {
        if (buffer != 0) 
        {
            if (buffer < 0) 
            {
                printf("Buffer is negative. Exiting program.\n");
                exit(0);
            } else 
            {
                int result = square(buffer);
                printf("%d's square is: %d\n", buffer, result);
                buffer = 0;
            }
        }
    }
}

int main() 
{
    pthread_t thread_1, thread_2;

    pthread_create(&thread_1, NULL, producer, NULL);
    pthread_create(&thread_2, NULL, consumer, NULL);

    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);

    return 0;
}
