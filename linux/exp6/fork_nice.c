#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/resource.h>

int main () {
    int prio;
    pid_t pid;

    pid = fork();
    /* child process */
    if (pid == 0) {
        pid = getpid();
        printf("Child: pid = %d \n", pid);
        prio = getpriority(PRIO_PROCESS, pid);
        printf("sys init prio = %d \n", prio);

        nice(18);
        prio = getpriority(PRIO_PROCESS, pid);
        printf("after nice(18): \nsys init prio = %d \n", prio);
        while(1);
        return 0;
    }
    /* parent process */
    wait(NULL);
    return 0;
}