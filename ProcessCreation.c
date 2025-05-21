#include <stdio.h>
#include <unistd.h>
int main() {
    pid_t pid;
    pid = fork(); 
    if (pid < 0) {
        printf("Fork  failed.\n");
        return 1;
    }
    else if (pid == 0) {
        printf("Child : PID = %d, Parent PID = %d\n", getpid(), getppid());
    }
    else {
        printf("Parent Process: PID = %d, Child PID = %d\n", getpid(), pid);
    }
    return 0;
}
