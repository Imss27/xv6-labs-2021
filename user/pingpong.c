#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    int p[2];
    char buf[2];
    char *parmsg = "a";
    char *chimsg = "b";
    pipe(p);

    if(fork() == 0) {
    	if(read(p[0], buf, 1) == 1) {
	    close(p[0]);
	    printf("%d: received ping\n", getpid());
	}
	if(write(p[1], chimsg, 1) == 1) {
	    close(p[1]);
	}
	exit(0);
    }
    else {
    	if(write(p[1], parmsg, 1) == 1) {
	    close(p[1]);
	}   
	wait(0);
	if(read(p[0], buf, 1) == 1) {
	    close(p[0]);
	    printf("%d: received pong\n", getpid());
	}
	exit(0);
    }
}
