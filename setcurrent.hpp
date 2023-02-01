#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#define GET_CURRENT_FAILED "null"
#define SET_CURRENT_FAILED -1
#define SET_CURRENT_SUCCESS 0

std::string getcurrent() {
    int fd = open("/proc/self/attr/current", O_RDONLY);
    if (fd < 0) return GET_CURRENT_FAILED;
    char buf[1024] = {};
    read(fd, buf, sizeof(buf));
    return std::string(buf);
}

int setcurrent(const char *con) {
    int fd = open("/proc/self/attr/current", O_WRONLY);
    if (fd < 0) return SET_CURRENT_FAILED;
    write(fd, con, strlen(con)+1);
    return SET_CURRENT_SUCCESS;
}
