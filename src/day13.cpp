#include <stdio.h>

#define N 2000
#define M 2000

bool field[N][M];

int get_nr(char* &s)
{
	int nr = 0;
	while ('0' <= *s && *s <= '9')
		nr = 10 * nr + *s++ - '0';
	return nr;
}


int main(int argc, char *argv[])
{
	for (int x = 0; x < N; x++)
		for (int y = 0; y < N; y++)
			field[x][y] = false;
	char buffer[100];
	int n = 2000;
	int m = 2000;
	while (fgets(buffer, 99, stdin))
	{
		char *s = buffer;
		if (*s < '0' || *s > '9')
			break;
		
		int x = get_nr(s);
		s++;
		int y = get_nr(s);
		field[y][x] = true;
		if (x > n) n = x+1;
		if (y > m) m = y+1;
	}
	for (int y = 0; y < m; y++)
	{
		for (int x = 0; x < n; x++)
			printf("%c", field[y][x] ? '#' : '.');
		printf("\n");
	}
	printf("\n");
	while (fgets(buffer, 99, stdin))
	{
		printf("%s", buffer);
		char *s = buffer + 13;
		int mirror = get_nr(s);
		printf("%c %d\n", buffer[11], mirror);
		if (buffer[11] == 'x')
		{
			if (n < 2*mirror)
				n = 2*mirror;
			for (int i = 0; i < N; i++)
				for (int j = 0; j < mirror; j++)
					if (field[i][2*mirror - j])
					{
						field[i][2*mirror - j] = false;
						field[i][j] = true;
					}
			n = mirror;
		}
		else
		{
			if (m < 2*mirror)
				m = 2*mirror;
			for (int i = 0; i < mirror; i++)
				for (int j = 0; j < M; j++)
					if (field[2*mirror - i][j])
					{
						field[2*mirror - i][j] = false;
						field[i][j] = true;
					}
			m = mirror;
		}
		for (int y = 0; y < m; y++)
		{
			for (int x = 0; x < n; x++)
				printf("%c", field[y][x] ? '#' : '.');
			printf("\n");
		}
		int count = 0;
		for (int x = 0; x < n; x++)
			for (int y = 0; y < m; y++)
				if (field[y][x])
					count++;
		printf("%d\n", count);
		printf("\n");
	}
}