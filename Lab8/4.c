#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
   int fd[2] = {0, 0};
   int result = 0;

   char msg[] = "Hello, Gosha!!!";
   char resstring[sizeof msg] = "";

   int semid = 0;
   key_t semkey = 0;
   struct sembuf mybuf = {0};
   char pathname[] = "4.c";

   semkey = ftok(pathname, 1);
   if((semid = semget(semkey, 1, 0666)) < 0) {
      if ((semid = semget(semkey, 1, 0666 | IPC_CREAT)) < 0)
      {
         printf("Can\'t create semaphore set\n");
         exit(EXIT_FAILURE);
      }

      mybuf.sem_num = 0;
      mybuf.sem_op  = 0;
      mybuf.sem_flg = 0;
      if(semop(semid, &mybuf, 1) < 0){
         printf("Can\'t sub 1 to semaphore\n");
         exit(-1);
      }
   }

   if(pipe(fd) < 0) {
     printf("Can\'t open pipe\n");
     exit(-1);
   }

   result = fork();

   if(result < 0) {
      printf("Can\'t fork child\n");
      exit(-1);
   } else if (result > 0) {
      for (int i = 0; i < 5; i++)
      {
         mybuf.sem_num = 0;
         mybuf.sem_op  = 1;
         mybuf.sem_flg = 0;
         if(semop(semid, &mybuf, 1) < 0){
            printf("Can\'t add 1 to semaphore\n");
            exit(-1);
         }
         size_t size = write(fd[1], msg, sizeof msg);
         if(size != sizeof msg) {
            printf("Can\'t write all string to pipe\n");
            exit(-1);
         }

         mybuf.sem_num = 0;
         mybuf.sem_op  = -2;
         mybuf.sem_flg = 0;
         if(semop(semid, &mybuf, 1) < 0){
            printf("Can\'t add 1 to semaphore\n");
            exit(-1);
         }

         ssize_t rsize = read(fd[0], resstring, 16);
         if (rsize < 0) {
            printf("Can\'t read string from pipe\n");
            exit(-1);
         }
         printf("Resstring parent: %s\n", resstring);
      }

      close(fd[0]);
      close(fd[1]);
      printf("Parent exit\n");

   } else {
      for (int i = 0; i < 5; i++)
      {
         mybuf.sem_num = 0;
         mybuf.sem_op  = -1;
         mybuf.sem_flg = 0;
         if(semop(semid, &mybuf, 1) < 0){
            printf("Can\'t add 1 to semaphore\n");
            exit(-1);
         }

         ssize_t rsize = read(fd[0], resstring, 16);
         if (rsize < 0) {
            printf("Can\'t read string from pipe\n");
            exit(-1);
         }
         printf("Resstring child: %s\n", resstring);

         mybuf.sem_num = 0;
         mybuf.sem_op  = 2;
         mybuf.sem_flg = 0;
         if(semop(semid, &mybuf, 1) < 0){
            printf("Can\'t add 1 to semaphore\n");
            exit(-1);
         }
         size_t size = write(fd[1], msg, sizeof msg);
         if (size != sizeof msg) {
            printf("Can\'t write all string to pipe\n");
            exit(-1);
         }
      }

      printf("Child exit\n");
      close(fd[0]);
      close(fd[1]);
   }

   return 0;
}
