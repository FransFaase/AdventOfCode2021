#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int get_nr(char* &s)
{
	int nr = 0;
	while ('0' <= *s && *s <= '9')
		nr = 10 * nr + *s++ - '0';
	return nr;
}

int values[2000];

int main(int argc, char *argv[])
{
	char line[10000];
	fgets(line, 10000, stdin);
	int n = 0;
	long long sum = 0;
	long long sum2 = 0;

	for (int i = 0; i < 2000; i++)
		values[i] = 0;
		
	for (char *s = line; '0' <= *s && *s <= '9';)
	{
		int v = get_nr(s);
		values[v]++;
		n++;
		sum += v;
		sum2 += v * v;
		if (*s == ',')
			s++;
	}

	/* First puzzle */
	long l_n = 0;
	long fuel = sum;
	for (int v = 0; ; v++)
	{
		int fuel_diff = 2 * l_n - n;
		if (fuel_diff > 0)
		{
			printf("%d %ld\n", v-1, fuel);
			break;
		}
		fuel += fuel_diff;
		
		l_n += values[v];
	}
	
	/* Second puzzle */
	l_n = 0;
	long l_sum = 0;
	fuel = (sum2 + sum)/2;
	for (int v = 0; ; v++)
	{
		int new_fuel = (sum2 + (1 - 2 * v) * sum + n * v * (v - 1))/2 - l_sum + v * l_n;
		if (new_fuel > fuel)
		{
			printf("%d %ld\n", v-1, fuel);
			break;
		}
		fuel = new_fuel;

		l_n += values[v];
		l_sum += v * values[v];
	}
}