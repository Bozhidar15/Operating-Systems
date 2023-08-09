#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <err.h>

/*
	cut -d: -f7 /etc/passwd | sort | uniq -c | sort -n 
*/

int main(void) {
	
	
	int a[2];

	if(pipe(a) == -1) {
		err(1, "pipe failed");
	}

	pid_t pid;
	if((pid = fork()) == -1) {
		err(2, "first fork failed");
	}

	if(pid == 0) {
		close(a[0]);	
		//close(1);
		//dup(a[1]);
		if(dup2(a[1], 1) == -1) {
			err(3, "cut dup failed");
		}
		if(execlp("cut", "cut", "-d:", "-f7", "/etc/passwd", (char *) NULL) == -1) {
			err(4, "cut exec failed");
		}
	} else {
		close(a[1]);
	}

	int b[2];
	if(pipe(b) == -1) {
		err(4, "Second pipe failed");
	}

	if((pid = fork()) == -1) {
		err(5, "sort fork failed");
	}

	if(pid == 0) {
		close(b[0]);
		if(dup2(a[0], 0) == -1) {
			err(6, "error dup read end sort");
		}
		if(dup2(b[1], 1) == -1) {
			err(6, "error dup write end sort");
		}
		execlp("sort", "sort", (char *) NULL);
	} else {
		close(b[1]);
	}

	int c[2];

	if(pipe(c) == -1){
		err(6, "error pipe for uniq");
	}

	if((pid = fork()) == -1) {
		err(7, "error forking uniq");
	}
	
	if(pid == 0) {
		close(c[0]);

		if(dup2(b[0], 0) == -1) {
			err(9, "error dup read end uniq");
		}
		if(dup2(c[1], 1) == -1) {
			err(10, "error dup read end uniq");
		}

		if(execlp("uniq", "uniq", "-c", (char *)NULL) == -1) {
			err(11, "error exec uniq");
		}
	} else {
		close(c[1]);
	}

	close(a[0]);
	close(b[0]);

	while(wait(NULL) > 0);

	if(dup2(c[0], 0) == -1){
		err(11, "error dup read end sort -n");
	}

	if(execlp("sort", "sort", "-n", (char *)NULL) == -1){
		err(6, "error exec sort -n");
	}

	return 0;
}
