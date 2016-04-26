//#include "csapp.h"
#define MAXARGS 128
#define MAXLINE 128
#define N 2

//unixerr.c
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
pid_t fork(void);
int execvp(const char *filename, char *const argv[]);
pid_t waitpid(pid_t pid, int *iptr, int options);


void unix_error(char* msg) {
	int errnum = errno;
	fprintf(stderr, "%s (%d: %s) \n", msg, errnum, strerror(errnum));
	exit(EXIT_FAILURE);
}

int builtin_command(char **argv) {
	if (!strcmp(argv[0], "quit"))
		exit(0);
	if (!strcmp(argv[0], "&"))
		return 1;
	return 0;
}

//splits a string into an array of arguments
int parseline(char* buf, char **argv) {
	char* delim;
	int argc;
	int bg;
	
	buf[strlen(buf)-1] = ' ';
	while (*buf && (*buf == ' '))
		buf++;
		
	argc = 0;
	while ((delim = strchr(buf, ' '))) {
		argv[argc++] = buf;
		*delim = '\0';
		buf = delim + 1;
		while (*buf && (*buf == ' '))
			buf++;
	}
	argv[argc] = NULL;
	
	if (argc == 0)
		return 1;
	
	if ((bg = (*argv[argc-1] == '&')) != 0)
		argv[--argc] = NULL;
		
	return bg;
}

void eval(char* cmdline) {
	char* argv[MAXARGS];
	char buf[MAXLINE];
	int bg;
	pid_t pid;
	int status;
	
	strcpy(buf, cmdline);
	bg = parseline(buf, argv);
	if (argv[0] == NULL)
		return;
		
	if (!builtin_command(argv)) {
		if ((pid = fork()) == 0) {
			if (execvp(argv[0], argv) < 0) {
				printf("%s: Command not found.\n", argv[0]);
				exit(0);
			}
		}
		
		if (!bg) {
			int status;
			if (waitpid(pid, &status, 0) < 0)
				unix_error("waitfg: waitpid error");
		}
		else
			printf("%d %s", pid, cmdline);
	}
	
	//reaping dead children only applies to background operations
	//foreground operations do not produce children
	while((pid = waitpid(-1, &status, 0)) > 0)
	{
		if(WIFEXITED(status))
		{
			printf("child %d terminated normally with exit status=%d\n", pid, WEXITSTATUS(status));
		}
		else
		{
			printf("child %d terminated abnormally\n", pid);
		}
	}
	
	if(errno != ECHILD)
	{
		unix_error("waitpid error");
	}
	
	return;
	
}

int main() {

	while(1) {
		char cmdline[MAXLINE];
		printf("> ");
		fgets(cmdline, MAXLINE, stdin);
		
		// replace \t with spaces
		for (int i = 0; cmdline[i] != '\0'; ++i) {
			if (cmdline[i] == '\t')
				cmdline[i] = ' ';
		}
		
		if (feof(stdin))
			exit(0);
			
		eval(cmdline);
	}
}
