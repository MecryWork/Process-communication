#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<string.h>
#include<error.h>
#include"Funtion.h"
#include"CallBackHelper.h"
#include<iostream>
using namespace std;

void CFunc::GetProcess()
{

}
void CFunc::ClallBackResult()
{
    //to do
}

void CFunc::ClallBackProcess()
{
    printf("Thread Data:<%s> \n",m_shm_p);
}

void CFunc::DoFuncMan()
{
    CallBackThread myThread(this);
    myThread.Start();

    int running = 1;
    int shmid,semid,value;
    void *shm_p = NULL;
    struct sembuf sem_b;
    sem_b.sem_num = 0;
    sem_b.sem_flg = SEM_UNDO;

    if((semid = semget((key_t)123456,1,0666 | IPC_CREAT)) == -1)
    {
        exit(EXIT_FAILURE);
    }
    shmid = shmget((key_t)654321,(size_t)2048,0600 | IPC_CREAT);
    if(shmid == -1)
    {
        exit(EXIT_FAILURE);
    }
    shm_p = shmat(shmid,NULL,0);

    if(shm_p == NULL)
    {
        exit(EXIT_FAILURE);
    }
    while(running)
    {
        if((value = semctl(semid , 0 , GETVAL)) == 1)
        {
            cout<<"Read date :"<<endl;
            sem_b.sem_op = -1;
            if(semop(semid,&sem_b,1) == -1)
            {
                exit(EXIT_FAILURE);
            }
            m_shm_p = (char*)shm_p;
            printf("data <%s> \n",shm_p);
        }
        if(strcmp(((char*)shm_p),"end") == 0)
        {
            running--;
        }
    }
    shmdt(shm_p);
    if(shmctl(shmid,IPC_RMID,0) != 0)
    {
        exit(EXIT_FAILURE);
    }
    if(semctl(semid,0,IPC_RMID,0) != 0)
    {
        exit(EXIT_FAILURE);
    }

}
