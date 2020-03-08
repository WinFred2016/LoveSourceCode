#define _GNU_SOURCE

#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/utsname.h>
#include <unistd.h>

#define STACK_4M (4 * 1024 * 1024)

static char child_stack[STACK_4M];

static int child_func()
{

    printf("hello6666\n");
    printf("PID: %ld\n", (long)getpid());
    printf("PPID: %ld\n", (long)getppid());

    char *mount_point = "/proc";
    mkdir(mount_point, 0555);
    printf("hello6777777\n");
    printf("hello11111");
    if (mount("proc", mount_point, "proc", 0, NULL) == -1)
    {
        printf("error when mount\n");
    }
    printf("hello11111");
    pid_t pid = fork();
    if (pid == 0)
    {

        printf("hello");
        char *const args[] = {"/bin/bash", "ls"};
        execv(args[0], args);
    }
    else
    {
        printf("hello22222");
        wait(NULL);
    }

    return 0;
}

int main()
{

    pid_t child_pid = clone(child_func, child_stack + STACK_4M,  CLONE_NEWNS | CLONE_NEWPID | CLONE_NEWUSER | SIGCHLD, NULL);

    printf("clone() = %ld\n", (long)child_pid);
    waitpid(child_pid, NULL, 0);
    return 0;
}
