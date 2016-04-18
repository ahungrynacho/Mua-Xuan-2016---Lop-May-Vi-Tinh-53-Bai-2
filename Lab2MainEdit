#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_LENGTH 80
#define LIN_COUNT 20

int main(int argc, char* argv[])
{

char line[LINE_LENGTH];

while (strcmp(line, "quit") != 0 || strcmp(line, "quit ") != 0
       || strcmp(line, "quit\t") != 0 || strcmp(line, " quit") != 0 || strcmp(line, "\tquit") != 0)
    {
        printf("prompt>");
        printf("%");
    
        fgets(line, LINE_LENGTH, stdin);
    
        if(sizeof(line) > LINE_LENGTH)
        {
            printf("Cannot enter a command more than 80 chars");
        }
    
        //Removes \n
        if ((strlen(line)>0) && (line[strlen(line) - 1] == '\n'))
            line[strlen(line) - 1] = '\0';
    
        //Execute command
        //execve(line, char *const argv[],char *const envp[]);
        
        //Exit command
        if (strstr(line, "quit") != NULL || strstr(line, "quit ") != NULL || strstr(line, "quit\t") != NULL ||
            strstr(line, " quit") != NULL || strstr(line, "\tquit") != NULL)
        {
            exit(0);
        }
    }
    return 0;
}
