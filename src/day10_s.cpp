#include <stdio.h>
#include <string.h>


int nr_fixes(char *line, int f, int t)
{
	if (f > t)
		return 0;

	int i_f = f;
	int i_t = t;
	
	int init_fixes = 0;
	while (f <= t && (line[f] == '_' || line[f] == ')' || line[f] == ']' || line[f] == '}' || line[f] == '>'))
	{
		if (line[f] != '_')
			init_fixes++;
		f++;
	}
	while (f <= t && (line[t] == '_' || line[t] == '(' || line[t] == '[' || line[t] == '{' || line[t] == '<'))
	{
		if (line[t] != '_')
			init_fixes++;
		t--;
	}
	if (f > t)
	{
		for (int i = 0; i < i_f; i++)
			printf(" ");
		for (int i = i_f; i <= i_t; i++)
			printf("%c", line[i]);
		printf(" = %d\n", init_fixes);
		return init_fixes;
	}
			
	int min_fixes = -1;
	
	char seek = ' ';
	switch(line[f]) {
		case '(': seek = ')'; break;
        case '[': seek = ']'; break;
		case '{': seek = '}'; break;
	    case '<': seek = '>'; break;
	}
	for (int i = f+1; i <= t; i++)
		if (line[i] == seek)
		{
			int fixes = nr_fixes(line, f+1, i-1) + nr_fixes(line, i+1, t);
			if (min_fixes == -1 || fixes < min_fixes)
				min_fixes = fixes;
		}
	
	switch (line[t]) {
		case ')': seek = '('; break;
        case ']': seek = '['; break;
		case '}': seek = '{'; break;
	    case '>': seek = '<'; break;
	}
	for (int i = f+1; i < t; i++)
		if (line[i] == seek)
		{
			int fixes = nr_fixes(line, f, i-1) + nr_fixes(line, i+1, t-1);
			if (min_fixes == -1 || fixes < min_fixes)
				min_fixes = fixes;
		}
	
	if (min_fixes == -1)
		min_fixes = 2 + nr_fixes(line, f+1, t-1);
	
	for (int i = 0; i < i_f; i++)
		printf(" ");
	for (int i = i_f; i <= i_t; i++)
		printf("%c", line[i]);
	printf(" = %d\n", init_fixes + min_fixes);
	
	return init_fixes + min_fixes;
}

int main(int argc, char *argv[])
{
	long int answer = 0;
	
	long long int scores[100];
	int n = 0;
	
	long answer3 = 0;
	long answer3b = 0;
	
	char buffer[201];
	while (fgets(buffer, 200, stdin))
	{
		printf("%s", buffer);
		int l = strlen(buffer);
		if (buffer[l-1] == '\n') { buffer[l-1] = '\0'; l--; }
		if (buffer[l-1] == '\r') { buffer[l-1] = '\0'; l--; }
		
		char stack[100];
		int d = 0;

		bool incorrect = false;		
		char *s = buffer;
		for (;*s != '\0'; s++)
		{
			     if (*s == '(') stack[d++] = ')';
			else if (*s == '[') stack[d++] = ']';
			else if (*s == '{') stack[d++] = '}';
			else if (*s == '<') stack[d++] = '>';
			else if (d > 0 && stack[d-1] == *s) d--;
			else
			{
				printf("Error at '%s': expect %c\n", s, stack[d-1]);
				switch (*s) {
					case ')': answer += 3; break;
					case ']': answer += 57; break;
					case '}': answer += 1197; break;
					case '>': answer += 25137; break;
				}
				incorrect = true;
				break;
			}
			//printf("%d ", d);
		}
		if (!incorrect && d > 0)
		{
			printf("Incomplete: ");
			long long score = 0;
			while(--d >= 0)
			{
				printf("%c", stack[d]);
				score *= 5;
				if (stack[d] == ')') score += 1;
				if (stack[d] == ']') score += 2;
				if (stack[d] == '}') score += 3;
				if (stack[d] == '>') score += 4;
				
			}
			printf(" %lld\n", score);
			for (int i = 0; i < n; i++)
			{
				if (score < scores[i])
				{
					long long s = scores[i];
					scores[i] = score;
					score = s;
				}
			}
			scores[n++] = score;
		}
		
		// remove matching
		for (bool go = true; go;)
		{
			go = false;
			for (char *s = buffer; *s != '\0';)
			{
				if (*s == '_') { s++; continue; }
				char seek = ' ';
				switch(*s) {
					case '(': seek = ')'; break;
					case '[': seek = ']'; break;
					case '{': seek = '}'; break;
					case '<': seek = '>'; break;
				}
				if (seek == ' ') { s++; continue; }
				char *f = s;
				do s++;
				while (*s == '_');
				if (*s == seek)
				{
					*f = '_';
					*s = '_';
					s++;
					go = true;
				}
			}
		}
		printf("%s\n", buffer);
		int c = 0;
		for (char *s = buffer; *s != '\0'; s++)
			if (*s != '_')
				c++;
		int fixes = nr_fixes(buffer, 0, l-1);
		printf("min repairs = %d %d\n", c, fixes);
		answer3 += c;
		answer3b += fixes;
	}
	printf("%ld\n", answer);
	printf("%lld\n", scores[n/2]);
	printf("%ld\n", answer3);
	printf("%ld\n", answer3b);
}