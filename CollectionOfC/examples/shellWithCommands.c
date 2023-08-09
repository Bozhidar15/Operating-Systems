#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/wait.h>

const size_t CMD_LEN = 4096;
const size_t NUM_ARGS = 100;

void read_command(char* buf) {
	char c;
	for (size_t i = 0; i < CMD_LEN - 1; i++) {
		int num_bytes = read(0, &c, 1);
		if (num_bytes < 0) {
			err(1, "could not read command");
		}

		if (c == '\n') {
			buf[i] = '\0';
			return;
		}
		buf[i] = c;
	}
	errx(1, "command too long");
}

void display_prompt(void) {
	write(1, "> ", 2);
}

void parse_command_args(char* cmd, char* args[]) {
	size_t start_of_next_arg = 0;
	size_t cur_arg = 0;

	for (size_t i = 0; cmd[i] != '\0'; i++) {
		if (cmd[i] == ' ') {
			cmd[i] = '\0';
			args[cur_arg] = &cmd[start_of_next_arg];
			start_of_next_arg = i + 1;
			cur_arg++;
		}
	}
	args[cur_arg] = &cmd[start_of_next_arg];
	args[cur_arg + 1] = NULL;
}

bool exec_builtin(char* args[]) {
	if (strncmp(args[0], "exit", strlen("exit")) == 0) {
		exit(0);
	}

	return false;
}

void exec_command_in_current_process(char* args[]) {
	int exec_status = execvp(args[0], args);
	if (exec_status < 0) {
		warn("could not execute command");
	}
}

void execute_command_args(char* args[]) {
	pid_t cmd_pid = fork();
	if (cmd_pid < 0) {
		err(1, "could not fork");
	}

	if (cmd_pid == 0) {
		exec_command_in_current_process(args);
	}

	int status;
	wait(&status);

	if (!WIFEXITED(status)) {
		warnx("command was killed");
		return;
	}
}

void execute_command(char* cmd) {
	char* args[NUM_ARGS];
	parse_command_args(cmd, args);

	if (exec_builtin(args)) {
		return;
	}

	execute_command_args(args);
}

int main(void) {
	char cmd[CMD_LEN];
	while (true) {
		display_prompt();
		read_command(cmd);
		execute_command(cmd);
	}
}
