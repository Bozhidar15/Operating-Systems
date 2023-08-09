/*
	Да се напише програма на C, която изпълнява команда date.
*/

#include <unistd.h>
#include <stdlib.h>
#include <err.h>
#include <stdio.h>
#include <string.h>

void print_text(const char* text) {
	write(1, text, strlen(text));
}

int main(void)
{
	print_text("before\n");
	char* args[] = {
		"ps", "-u", "human", NULL
	};

	int exec_result = execvp(args[0], args);
	print_text("after\n");

	if (exec_result == -1) {
		err(99, "err execing");
	}

	exit(0);
}
