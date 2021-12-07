#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char line[101];

	int count[12] = { 0, 0, 0, 0, 0, };
	int nr_lines = 0;
	while (fgets(line, 100, stdin))
	{
		nr_lines++;
		for (int i = 0; i < 12; i++)
			if (line[i] == '1')
				count[i]++;
	}
	long int gamma = 0;
	long int epsilon = 0;
	for (int i = 0; i < 12; i++)
	{
		if (count[i] < nr_lines - count[i])
			gamma |= (1 << (11 - i));
		else
			epsilon |= (1 << (11 - i));
	}
	
	
	printf("answer %ld %ld %ld\n", gamma, epsilon, gamma * epsilon);
}