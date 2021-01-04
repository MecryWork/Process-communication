#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<string.h>
#include<error.h>
using namespace std;

int main()
{
    int running = 1;
    int shid,semid,value;
    void *sharem = NULL;
    struct sembuf sem_b;
    sem_b.sem_num = 0;
    sem_b.sem_flg = 0;

    if((semid = semget((key_t)123456,1,0666 | IPC_CREAT)) == -1)
    {
        exit(EXIT_FAILURE);
    }
    if( semctl(semid,0,SETVAL,0) == -1)
    {
        if(semctl(semid,0,IPC_RMID,0) != 0)
        {
            exit(EXIT_FAILURE);
        }
        exit(EXIT_FAILURE);
    }
    shid = shmget((key_t)654321,(size_t)2048,0600 | IPC_CREAT);
    if(shid == -1)
    {
        exit(EXIT_FAILURE);
    }
    sharem = shmat(shid,NULL,0);
    if(sharem == NULL)
    {
        exit(EXIT_FAILURE);
    }
    while(running)
    {
        if((value = semctl(semid , 0 , GETVAL)) == 0)
        {
            cout<<"write date :"<<endl;
            scanf("%s",sharem);
            sem_b.sem_op = 1;
            if(semop(semid,&sem_b,1) == -1)
            {
                exit(EXIT_FAILURE);
            }
        }
        if(strcmp(((char*)sharem),"end") == 0)
        {
            running--;
        }
    }

    return 0;
}

