#include <stdio.h>
#include <fcntl.h>
#include <string>
#include <sys/prctl.h>
#include <unistd.h>

static char *argv0;
static size_t name_len;

size_t strscpy(char *s, const char *ss, size_t siz) {
    for (size_t i=0; i<siz ; i++) {
        s[i] = ss[i];
    }
	return siz;
}

static void init_argv0(int argc, char **argv) {
    argv0 = argv[0];
    name_len = (argv[argc - 1] - argv[0]) + strlen(argv[argc - 1]) + 1;
}

static void fill_zero(int argc, char **argv) {
    for (int i = 0 ; i<argc ; i++) {
        char *s = argv[i];
        for (int j = 0 ; j < strlen(s) ; j++) {
    	        s[j] = '\0';
        }
    }
}

void set_nice_name(int argc, char **argv, const char *name) {
    init_argv0(argc, argv);
    fill_zero(argc,argv);
    memset(argv0, 0, name_len);
    strscpy(argv0, name, strlen(name)+1);
    prctl(PR_SET_NAME, name);
}

#define set_nice_name(s) set_nice_name(argc,argv,s)
