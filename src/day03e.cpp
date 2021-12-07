#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 12

void print_binary(int value)
{
	for (int b = N-1; b >= 0; b--)
		printf("%d", (value & (1 << b)) ? 1 : 0);
} 

int main(int argc, char *argv[])
{
	char line[101];

	int numbers[1000];
	int nr_lines = 0;
	while (fgets(line, 100, stdin) && nr_lines < 1000)
	{
		int value = 0;
		for (int i = 0; i < N; i++)
			value = 2 * value + line[i] - '0';
		numbers[nr_lines++] = value;
	}
	
	// oxygen
	int mask = 0;
	int match = 0;
	int result1;
	for (int b = N-1; b >= 0; b--)
	{
		int bit = (1 << b);
		printf("\n"); print_binary(mask);
		printf("\n"); print_binary(match);
		printf("\n"); print_binary(bit);

		int matched_lines = 0;
		int count = 0;
		for (int i = 0; i < nr_lines; i++)
		{
			int value = numbers[i];
			if ((value & mask) == match)
			{
				matched_lines++;
				printf("\n "); print_binary(value);
				if (value & bit)
				{
					result1 = value;
					count++;
				}
			}
		}
		printf("\n%d\n", count);
		if (count > matched_lines - count)
			match |= bit;
		mask |= bit;
	}
	
	mask = 0;
	match = 0;
	int result2;
	for (int b = N-1; b >= 0; b--)
	{
		int bit = (1 << b);
		printf("\n"); print_binary(mask);
		printf("\n"); print_binary(match);
		printf("\n"); print_binary(bit);

		int matched_lines = 0;
		int count = 0;
		for (int i = 0; i < nr_lines; i++)
		{
			int value = numbers[i];
			if ((value & mask) == match)
			{
				matched_lines++;
				printf("\n "); print_binary(value);
				if (value & bit)
				{
					result2 = value;
					count++;
				}
			}
		}
		printf("\n%d\n", count);
		if (count < matched_lines - count)
			match |= bit;
		mask |= bit;
	}
	printf("result %d %ld\n", result2, (long)result1 * (long)result2);
}