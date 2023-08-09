/*
	Да се напише програма на C, която създава процес дете и демонстрира
принцина на конкурентност при процесите.
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <wait.h>
#include <string.h>

void print_msg(const char* msg) {
	write(1, msg, strlen(msg));
}

int main(void)
{
	int n = 5;

	pid_t a = fork();
	if (a == -1) {
		err(1, "BOO");
	}
	if (a > 0) {
		dprintf(1, "I am the parent, fork returned %d and my pid is %d\n",
				a, getpid());
		for (int i = 0; i < n; i++) {
			dprintf(1, "parent (my pid is %d)\n", getpid());
		}

		int status;
		wait(&status);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
			dprintf(1, "child ended successfully\n");
		} else {
			dprintf(1, "error while executing child\n");
		}
	} else {
		dprintf(1, "I am the child, fork returned %d and my pid is %d\n",
				a, getpid());
		for (int i = 0; i < n; i++) {
			dprintf(1, "child (my pid is %d)\n", getpid());
		}
	}

	return 0;
}
