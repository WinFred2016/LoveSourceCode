#define _GNU_SOURCE

#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/utsname.h>
#include <unistd.h>

#define STACK_4M    (4 * 1024 * 1024)

static char child_stack[STACK_4M];

static int child_func() {

    printf("PID: %ld\n", (long)getpid());
    printf("PPID: %ld\n", (long)getppid());

    return 0;
}

int main() {

    pid_t child_pid = clone(child_func, child_stack + STACK_4M, SIGCHLD, NULL);

    printf("clone() = %ld\n", (long)child_pid);
    waitpid(child_pid, NULL, 0);
    return 0;
}
