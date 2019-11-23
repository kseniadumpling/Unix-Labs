#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include <string.h>

int main() {
    char cwd[256];
    if (fork()) {
		printf("\nParent first path\n");
			if(getcwd(cwd, sizeof(cwd)) == 0) {
			perror("getcwd() error");
		}
		printf("%s\n",cwd);
		cwd[0] = '\0';
		sleep(3);
		printf("\nParent second path\n");
			if(getcwd(cwd, sizeof(cwd)) == 0) {
			perror("getcwd() error");
		}
			printf("%s\n",cwd);
		sleep(1);	
    }
    else {
		if(chdir("./temp") != 0){
			perror("chdir() error");
		}
		printf("\nChild path\n");
		if(getcwd(cwd, sizeof(cwd)) == NULL) {
			perror("getcwd() error");
		}
		printf("%s\n",cwd);
		sleep(1);	
    }
}

