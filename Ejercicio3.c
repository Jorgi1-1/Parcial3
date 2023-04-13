#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


void sigusr1_handler(int sig) 
{
    printf("Señal 1 recibida\n");
}


void sigusr2_handler(int sig) 
{
    printf("Señal 2 recibida\n");
}

int main() 
{
    pid_t pid_q, pid_v, pid_r, pid_p;

    pid_q = fork();
    if (pid_q == 0) 
    {
        alarm(4); 
        kill(getppid(), SIGUSR2); 
        exit(0); 
    }


    pid_v = fork();
    if (pid_v == 0) 
    {
        alarm(8); 
        kill(getppid(), SIGUSR1); 
        exit(0);
    }


    pid_r = fork();
    if (pid_r == 0) 
    {
        while (1) 
        {
            printf("Soy el proceso R con ID %d\n", getpid());
            sleep(1);
        }
        exit(0); 
    }

    pid_p = fork();
    if (pid_p == 0) 
    {
        while (1) 
        {
            printf("Soy el proceso P con ID %d\n", getpid());
            sleep(1);
        }
        exit(0); 
    }

    signal(SIGUSR1, sigusr1_handler);
    signal(SIGUSR2, sigusr2_handler);

    waitpid(pid_q, NULL, 0);
    waitpid(pid_v, NULL, 0);


    sleep(2);
    kill(pid_r, SIGKILL);
    kill(pid_p, SIGKILL);

    return 0;
}

