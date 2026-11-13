
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

void sig_handler(int signo)
{
    printf("Timer Invoked.\n");
}

int main(void)
{
    struct itimerval it;

    signal(SIGALRM, sig_handler);

    it.it_value.tv_sec = 3;
    it.it_value.tv_usec = 0;

    it.it_interval.tv_sec = 2;
    it.it_interval.tv_usec = 0;

    if (setitimer(ITIMER_REAL, &it, NULL) == -1) {
        perror("setitimer");
        exit(1);
    }

    while (1) {
        if (getitimer(ITIMER_REAL, &it) == -1) {
            perror("getitimer");
            exit(1);
        }

        printf("%ld sec, %ld usec.\n",
               (long)it.it_value.tv_sec,
               (long)it.it_value.tv_usec);

        sleep(1);
    }

    return 0;
}
