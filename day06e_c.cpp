#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int get_nr(char * &s)
{
	int nr = 0;
	while ('0' <= *s && *s <= '9')
		nr = 10 * nr + *s++ - '0';
	return nr;
}


struct LargeNum
{
	long n[10];
	int l;
	
	LargeNum()
	{
		for (int i = 0; i < 10; i++)
			n[i] = 0;
		l = 0;
	}
	
	LargeNum& operator=(int i)
	{
		for (int i = 1; i < 10; i++)
			n[i] = 0;
		n[0] = i;
		l = 1;
	}
	
	LargeNum& operator=(LargeNum v)
	{
		for (int i = 0; i < 10; i++)
			n[i] = v.n[i];
		l = v.l;
	}
	
	LargeNum& operator+=(LargeNum& v)
	{
		int carry = 0;
		for (int i = 0; i < 10; i++)
		{
			n[i] += carry + v.n[i];
			carry = 0;
			if (n[i] >= 1000000000)
			{
				n[i] -= 1000000000;
				carry = 1;
			}
			if (i == l && n[i] > 0)
				l++;
		}
	}
	void inc()
	{
		n[0]++;
		l = 1;
	}
			
	
	void print()
	{
		for (int i = l-1; i >= 0; i--)
		{
			if (i == l-1)
				printf("%ld", n[i]);
			else
				printf("%09ld", n[i]);
		}
		if (l == 0)
			printf("0");
		printf(" ");
	}
};

int main(int argc, char *argv[])
{
	LargeNum foa[9];

	char line[10000];
	fgets(line, 10000, stdin);

	
	for (char *s = line; '0' <= *s && *s <= '9'; s++)
	{
		int a = get_nr(s);
		foa[a].inc();
	}
	
	for (int d = 0; d < 256; d++)
	{
		LargeNum spawn = foa[0];
		for (int i = 0; i < 8; i++)
			foa[i] = foa[i+1];
		foa[6] += spawn;
		foa[8] = spawn;
		
		printf("%2d: ", d+1);
		for (int i = 0; i < 9; i++)
			foa[i].print();
			
		LargeNum sum;
		for (int i = 0; i < 9; i++)
			sum += foa[i];
		sum.print();
		printf("\n");
	}		
}