#include <iostream>
#include <unistd.h>
#include <sys/wait.h>



pid_t wait_till_pid(pid_t pid) {
    while (true) {
    pid_t p = wait(nullptr);
        if (p==-1 || p == pid) {
            return p;
        }
    }
}