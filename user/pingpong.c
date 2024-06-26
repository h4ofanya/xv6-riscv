#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[]){
    int fd1[2];
    int fd2[2];
    char buf;


    pipe(fd1);
    pipe(fd2);

    int pid = fork();
    if (pid < 0) {
        fprintf(2, "fork error!\n");
        exit(1);
    }

    if (pid == 0) {
        // child process
        close(fd1[1]);
        close(fd2[0]);

        int btye = read(fd1[0], &buf, 1);
        if(btye > 0){
            printf("%d: receive ping\n", getpid());
            write(fd2[1], " ", 1);
        }

        close(fd1[0]);
        close(fd2[1]);
    }else{
        close(fd1[0]);
        close(fd2[1]);

        write(fd1[1], " ", 1);
        int btye = read(fd2[0], &buf, 1);

        if(btye > 0) {
            printf("%d: receive pong\n", getpid(), buf);
        }
        close(fd1[1]);
        close(fd2[0]);
    }

    exit(0);
}