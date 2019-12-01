/*
** semmonitor.cpp -- checks the number of processes which is waiting for resourses unlock
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

int main(void) {
	key_t key;
	int semid;

	if ((key = ftok(".", 'J')) == -1) {
		perror("ftok");
		exit(1);
	}

	/* grab the semaphore set created by seminit.c: */
	if ((semid = semget(key, 1, 0)) == -1) {
		perror("semget");
		exit(1);
	}

    int numberOfProcesses = 0;
    while (true) {
        if ((numberOfProcesses = semctl(semid, 0, GETNCNT)) == -1) {
            perror("semctl");
		    exit(1);
        }
        printf("Number of waiting processes: %d\n", numberOfProcesses);
        sleep(2);
    }
	return 0;
}