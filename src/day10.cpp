#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	long int answer = 0;
	
	long long int scores[100];
	int n = 0;
	
	char buffer[201];
	while (fgets(buffer, 200, stdin))
	{
		printf("%s", buffer);
		int l = strlen(buffer);
		if (buffer[l-1] == '\n') { buffer[l-1] = '\0'; l--; }
		if (buffer[l-1] == '\r') buffer[l-1] = '\0';
		
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
			printf(" %ld\n", score);
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
	}
	printf("%ld\n", answer);
	printf("%lld\n", scores[n/2]);
}