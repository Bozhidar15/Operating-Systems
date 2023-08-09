#include <sys/wait.h>
#include <stdlib.h>
#include <err.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>


int main (int argc, char **argv) {
	const char *cmd = "echo";
	if (argc == 2) {
		cmd = argv[1];
		if (strlen(cmd) > 4) {
			errx(1, "Error: Command must be up to 4 chars long");
		}
	}

	int counter = 0;

	while(1) {
		counter++;

		int p[2];
		if (pipe(p) == -1) {
			err(2, "Error creating pipe");
		}

		pid_t child;
		if ((child = fork()) == -1) {
			err(3, "Error fork");
		}

		if (child == 0) {
			close(p[0]);
	
			char c;
			int lastByte;

			char buff1[5];
			int index1 = 0;

			while ((lastByte = read(0, &c, 1)) == 1) {
				if (c == 0x20 || c == 0x0A) {
					break;
				}
				
				if (index1 >= 4) {
					errx(11, "Error: Argument can be max 4 characters");
				}

				buff1[index1] = c;
				index1++;	
			}	
			
			buff1[index1] = '\0';

			if (lastByte == -1) {
				err(4, "Error reading from stdin");
			}

			char buff2[1024];
			int index2 = 0;
			 while ((lastByte = read(0, &c, 1)) == 1) {
                                if (c == 0x20 || c == 0x0A) {
                                        break;
                                }

				if (index2 >= 4) {
                                        errx(11, "Error: Argument can be max 4 characters");
                                }


                                buff2[index2] = c;
                                index2++;
                        }

			   buff2[index2] = '\0';

                        if (lastByte == -1) {
                                err(4, "Error reading from stdin");
                        }

			if (index1 == 0 && index2 == 0) {
				if (dup2(p[1], 1) == -1) {
					err(5, "Error duplicating pipe for writing");
				}

				if (execlp("echo", "echo", "finished", NULL) == -1) {
					err(6, "Error sending message to parrent");
				}
			} else {
				close(p[1]);
			
				if (index2 > 0) {


					if (execlp(cmd, cmd, buff1, buff2, NULL) == -1) {
						err(7, "Error executing %s", cmd);
					}
				} else {
					if (execlp(cmd, cmd, buff1, NULL) == -1) {
                                                err(7, "Error executing %s", cmd);
                                        }
				}
			}
		}

		close(p[1]);

		if (wait(NULL) == -1) {
                        err(9, "Error waiting child");
                }


		char c;
		int lastByte;
		if ((lastByte = read(p[0], &c, 1)) == -1) {
			err(8, "Error reading response from child");
		}

		close(p[0]);

		if (lastByte == 0) {
			continue;
		}
		
	//	dprintf(1, "Finished after %d cycles", counter);

		exit(0);
	}


}
