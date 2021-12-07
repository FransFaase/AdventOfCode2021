#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 12

class Node
{
public:
	Node() : nr0(0), nr1(0), children0(0), children1(0) {}
	int nr0;
	int nr1;
	Node* children0;
	Node* children1;
};

int main(int argc, char *argv[])
{
	char line[101];

	Node* tree = 0;
	int nr_lines = 0;
	while (fgets(line, 100, stdin) && nr_lines < 1000)
	{
		Node** r_tree = &tree;
		for (int i = 0; i < N; i++)
		{
			if (*r_tree == 0) *r_tree = new Node();
			if (line[i] == '0')
			{
				(*r_tree)->nr0++;
				r_tree = &(*r_tree)->children0;
			}
			else
			{
				(*r_tree)->nr1++;
				r_tree = &(*r_tree)->children1;
			}
		}
	}

	int result1 = 0;
	for (Node* t = tree; t != 0;)
	{
		result1 *= 2;
		if (t->nr0 > t->nr1)
		{
			printf("0");
			t = t->children0;
		}
		else
		{
			printf("1");
			result1++;
			t = t->children1;
		}
	}
	printf("\n");

	int result2 = 0;
	for (Node* t = tree; t != 0;)
	{
		result2 *= 2;
		if ((t->children1 == 0 && t->children0 != 0) || (t->children0 != 0 && t->nr0 <= t->nr1))
		{
			printf("0");
			t = t->children0;
		}
		else
		{
			printf("1");
			result2++;
			t = t->children1;
		}
	}
	printf("\n");

	printf("result %d %d %ld\n", result1, result2, (long)result1 * (long)result2);
}