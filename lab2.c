#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define LINE_LENGTH 80
#define LIN_COUNT 20

int main(int argc, char* argv[]) {
	
	while (1) {
		char line[LINE_LENGTH];
		printf("%");
		if (!fgets(line, LINE_LENGTH, stdin))
			break;
		system(line);
	}
	return 0;
}