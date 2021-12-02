#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char line[101];
	
	long depth = 0;
	long forward = 0;
	while (fgets(line, 100, stdin))
	{
		printf("%s", line);
		if (strncmp(line, "forward ", 8) == 0)
			forward += atoi(line + 8);
		if (strncmp(line, "down ", 5) == 0)
			depth += atoi(line + 5);
		if (strncmp(line, "up ", 3) == 0)
			depth -= atoi(line + 3);
	}
	printf("answer %ld %ld %ld\n", depth, forward, depth * forward);
}