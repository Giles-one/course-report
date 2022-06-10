#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

#define __NR_get_proc_run_time 335
struct cpu_time_struct {
    unsigned long utime;
    unsigned long stime;
};

pid_t pid;
struct cpu_time_struct cpu_time = {0 ,0};

void child_exit_handler(int no) {
    if (syscall(__NR_get_proc_run_time, pid, &cpu_time)) {
        perror("get proc run time error");
        waitpid(pid, NULL, 0);
        exit(-1);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("usage: ./exp prog \n");
        exit(-1);
    }
    signal(SIGCHLD, child_exit_handler);
    pid = fork();
    if (pid < 0) {
        perror("fork error \n");
        exit(-1);
    } else if (pid == 0) {
        execl(argv[1],argv[1] , NULL);
    }

    pause();
    printf("utime: %ld \n", cpu_time.utime);
    printf("stime: %ld \n", cpu_time.stime);
    waitpid(pid, NULL, 0);

    return 0;
}