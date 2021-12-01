#include <stdio.h>

int main(int argc, char *argv[])
{
	unsigned long count = 0;
	
	long numbers[3] = { 0L, 0L, 0L, };
	long prev_sum;
	long cur;
	long sum = 0;
	for (int nr = 0; scanf("%ld\n", &cur) > 0; nr++)
	{
		sum += cur - numbers[nr%3];
		numbers[nr%3] = cur;
		//printf("%5ld + %5ld + %5ld = %5ld", numbers[0], numbers[1], numbers[2], sum);
		if (nr >= 3 && sum > prev_sum)
		{
			count++;
			//printf(" %ld", count);
		}
		//printf("\n");
		prev_sum = sum;
	}
	printf("%ld\n", count);
}