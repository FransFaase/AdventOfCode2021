#include <stdio.h>
#include <string.h>

struct Rule
{
	char f1;
	char f2;
	char t;
	long long int count;
	long long int n_count;
} rules[100];
int nr = 0;

Rule* find(char f1, char f2)
{
	for (int i = 0; i < nr; i++)
		if (f1 == rules[i].f1 && f2 == rules[i].f2)
			return &rules[i];
	return 0;
}

int main(int argc, char *argv[])
{
	char templ[101];
	fgets(templ, 100, stdin);
	
	int tl = strlen(templ);
	if (templ[tl-1] == '\n') tl--;
	if (templ[tl-1] == '\r') tl--;
	templ[tl] = '\0';
	
	printf("%s\n", templ);
	
	char buffer[100];
	fgets(buffer, 99, stdin);
	while (fgets(buffer, 99, stdin))
	{
		rules[nr].f1 = buffer[0];
		rules[nr].f2 = buffer[1];
		rules[nr].t = buffer[6];
		rules[nr].count = 0;
		nr++;
	}
	
	for (int i = 0; i < nr; i++)
		printf("%d %c%c -> %c\n", i, rules[i].f1, rules[i].f2, rules[i].t);
		
	for (int i = 0; i < tl-1; i++)
	{
		Rule *r = find(templ[i], templ[i+1]);
		if (r == NULL)
			printf("ERROR\n");
		else
			r->count++;
	}
	
	for(int i = 0; i < nr; i++)
		if (rules[i].count > 0)
			printf("%c%c %ld\n", rules[i].f1, rules[i].f2, rules[i].count);
	printf("\n");
	
	for (int step = 0; step < 40; step++)
	{
		for (int i = 0; i < nr; i++)
			rules[i].n_count = 0;

		for (int i = 0; i < nr; i++)
		{
			Rule *r1 = find(rules[i].f1, rules[i].t);
			if (r1 == NULL)
				printf("ERROR\n");
			else
				r1->n_count += rules[i].count;
			Rule *r2 = find(rules[i].t, rules[i].f2);
			if (r2 == NULL)
				printf("ERROR\n");
			else
				r2->n_count += rules[i].count;
		}

		long long int letters[26];
		for (int i = 0; i < 26; i++)
			letters[i] = 0;
		letters[templ[0] - 'A']++;
		
		long long int sum = 0;
		for (int i = 0; i < nr; i++)
		{
			
			rules[i].count = rules[i].n_count;
			if (rules[i].count > 0)
				printf("%c%c %ld\n", rules[i].f1, rules[i].f2, rules[i].count);
			sum += rules[i].count;
			letters[rules[i].f2 - 'A'] += rules[i].count;
		}
		long long int min_nr = -1;
		long long int max_nr = 0;
		for (int i = 0; i < 26; i++)
			if (letters[i] > 0)
			{
				printf("%c = %ld, ", 'A' + i, letters[i]);
				if (min_nr == -1 || letters[i] < min_nr)
					min_nr = letters[i];
				if (letters[i] > max_nr)
					max_nr = letters[i];
			}
		printf(" %lld %lld %lld %lld\n\n", sum + 1, min_nr, max_nr, max_nr - min_nr);
	}
}
