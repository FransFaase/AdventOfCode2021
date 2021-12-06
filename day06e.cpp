#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define S 1000


int get_nr(char * &s)
{
	int nr = 0;
	while ('0' <= *s && *s <= '9')
		nr = 10 * nr + *s++ - '0';
	return nr;
}

#define N 100000

long age[N];
int nr_fish = 0;

struct longlong
{
	long n[10];
	int l;
	
	longlong()
	{
		for (int i = 0; i < 10; i++)
			n[i] = 0;
		l = 0;
	}
	
	longlong& operator=(int i)
	{
		for (int i = 1; i < 10; i++)
			n[i] = 0;
		n[0] = i;
		l = 1;
	}
	
	longlong& operator=(longlong v)
	{
		for (int i = 0; i < 10; i++)
			n[i] = v.n[i];
		l = v.l;
	}
	
	longlong& operator+=(longlong& v)
	{
		int carry = 0;
		for (int i = 0; i < 10; i++)
		{
			n[i] += carry + v.n[i];
			carry = 0;
			if (n[i] >= 10000)
			{
				n[i] -= 10000;
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
				printf("%04ld", n[i]);
		}
		if (l == 0)
			printf("0");
		printf(" ");
	}
};

int main(int argc, char *argv[])
{
	longlong foa[9];
	//for (int i = 0; i < 9; i++)
	//	foa[i] = 0;

	char line[10000];
	fgets(line, 10000, stdin);

	
	for (char *s = line; '0' <= *s && *s <= '9'; s++)
	{
		int a = get_nr(s);
		//age[nr_fish++] = a;
		foa[a].inc();
		printf("%d,", a);
	}
	printf("\n");
	//for (int i = 0; i < nr_fish; i++)
	//	printf("%d,", age[i]);
	//printf(" ");
	for (int i = 0; i < 9; i++)
		foa[i].print();
	printf("\n");
	
	for (int d = 0; d < 256; d++)
	{
		int new_nr_fish = nr_fish;
		/*
		for (int i = 0; i < nr_fish; i++)
		{
			age[i]--;
			if (age[i] < 0)
			{
				age[i] = 6;
				age[new_nr_fish++] = 8;
				
				if (new_nr_fish > N)
				{
					printf("Error!");
					return 0;
				}
			}
		}
		*/
		
		longlong spawn = foa[0];
		for (int i = 0; i < 8; i++)
			foa[i] = foa[i+1];
		foa[6] += spawn;
		foa[8] = spawn;
		
		//nr_fish = new_nr_fish;
		printf("%2d: ", d+1);
		//for (int i = 0; i < nr_fish; i++)
		//	printf("%d,", age[i]);
		//printf(" %d |", nr_fish);
		for (int i = 0; i < 9; i++)
			foa[i].print();
			
		longlong sum;
		for (int i = 0; i < 9; i++)
			sum += foa[i];
		sum.print();
		printf("\n");
	}		
}