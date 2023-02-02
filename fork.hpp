#include <unistd.h>
#include <sys/wait.h>
#include <sys/prctl.h>

int fork();

int fork_no_orphan() {
    int pid = fork();
    if (pid)
        return pid;
    prctl(PR_SET_PDEATHSIG, SIGKILL);
    if (getppid() == 1)
        _exit(1);
    return 0;
}

int fork_dont_care() {
    if (int pid = fork()) {
        waitpid(pid, nullptr, 0);
        return pid;
    } else if (fork()) {
        _exit(0);
    }
    return 0;
}
