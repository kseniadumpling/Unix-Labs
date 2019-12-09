/* Creating, attaching and manipulating shared memory */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
 
#define SHM_SIZE 1023

extern int etext, edata, end;
 
main(void) {
 	int	shmid[3];
    char *shm[3];
    char *str;
 	
    for (int i = 0; i < 3; i++) {

        if ((shmid[i] = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666)) < 0) {
            perror("shmget fail");
            exit(1);
 	    }
        if ((shm[i] = (char *) shmat(shmid[i], 0, 0)) ==  (char *)-1) {
            perror("shmat fail");
            exit(2);
 	    }
        printf("Shared memory %d: %p\n", i, shm[i]);

        str = shm[i];	          	/* str now references shared mem */
        for (int j = 0; j < 1023; j++) {
            *str++ = 'a' + i;      /* Put some info there    */
        }
        *str = 0;                   /* Terminate the sequence */

        printf("Info in shared memory %d: %s\n", i, shm[i]);
    }
    *(shm[0] + 1024) = 'W';
    printf("\nTrying to change 1024th byte of first seq of shared memory: %s\n", shm[0]);
    printf("(and after changes let's look on the second one): %s\n", shm[1]);

    *(shm[0] + 2) = 'W';
    printf("\nTrying to change 3rd byte of first seq of shared memory: %s\n", shm[0]);

    for (int i = 0; i < 3; i++) {
        shmdt(shm[i]);
	    shmctl(shmid[i], IPC_RMID, (struct shmid_ds *) 0 );
    }
	exit(0);
 }