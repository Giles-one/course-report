#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <linux/sem.h>

int semid1;
int semid2;

int main() {
    struct sembuf P,V;
    union semun arg;
    int *num1, *num2, *sum;

    num1 = (int *)mmap(NULL,sizeof(int),PROT_READ | PROT_WRITE, 
                        MAP_SHARED | MAP_ANONYMOUS ,-1,0);
    num2 = (int *)mmap(NULL,sizeof(int),PROT_READ | PROT_WRITE, 
                        MAP_SHARED | MAP_ANONYMOUS ,-1,0);
    sum  = (int *)mmap(NULL,sizeof(int),PROT_READ | PROT_WRITE,
                        MAP_SHARED | MAP_ANONYMOUS ,-1,0);
    *num1 = 0;
    *num2 = 0;
    *sum  = 0;
    
    semid1 = semget(IPC_PRIVATE, 1, IPC_CREAT | 00666);
    semid2 = semget(IPC_PRIVATE, 1, IPC_CREAT | 00666);
    
    arg.val = 1;
    if(semctl(semid1, 0, SETVAL, arg)==-1)
        perror("semctl setval error");
    arg.val = 0;
    if(semctl(semid2, 0, SETVAL, arg)==-1)
        perror("semctl setval error");
    
    V.sem_num = 0;
    V.sem_op = 1;
    V.sem_flg = SEM_UNDO;
    P.sem_num = 0;
    P.sem_op = -1;
    P.sem_flg = SEM_UNDO;
    
    if(fork() == 0) {
        while(1) {
            semop(semid1, &P, 1);
            printf("add<int>:please input the num1 and num2:");
            scanf("%d%d",num1,num2);
            semop(semid2, &V, 1);
        }

    } else {
        if(fork() == 0) {
            while(1) {
                semop(semid2, &P, 1);
                *sum = *num1 + *num2;
                printf("%d + %d = %d\n",*num1,*num2,*sum);
                semop(semid1, &V, 1);
            }

        }
    }
    wait(NULL);
    return 0;
}
