#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include <string.h>

int main() {
    FILE *fp;
    if((fp = fopen("textfile.txt", "r")) == NULL) {
        perror("fopen() error");
    }
    if (fork()) {
        sleep(2);
        char buf[16] = {"\0"};
        fread(buf, 10, 1, fp);
        printf("Parent read 10 bytes: %s\n", buf);
        fclose(fp);
    }
    else {
        char buf[16] = {"\0"};
        fread(buf, 10, 1, fp);
        printf("Child read 10 bytes: %s\n", buf);
    }
}

