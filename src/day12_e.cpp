#include <stdio.h>
#include <string.h>

struct Node
{
	char name[10];
	int nr;
	bool multiple;
	int visited;
} nodes[20];
int nr = 0;

Node* find(const char *name)
{
	for (int i = 0; i < nr; i++)
	{
		if (strcmp(nodes[i].name, name) == 0)
			return nodes + i;
	}
	strcpy(nodes[nr].name, name);
	nodes[nr].nr = nr;
	nodes[nr].multiple = 'A' <= *name && *name <= 'Z';
	nodes[nr].visited = 0;
	return &nodes[nr++];
}

#define N 20

bool edge[N][N];

Node *path[100];
int n = 0;

long count = 0;

bool small_twice = false;

void search(Node *f)
{
	bool this_twice = false;
	if (!f->multiple)
	{
		if (!small_twice && f->visited == 1)
		{
			this_twice = true;
			small_twice = true;
		}
		else if (f->visited > 0)
			return;
	}
	path[n] = f;
	if (f->nr == 1)
	{
		//for (int i = 0; i < n; i++)
		//	printf("%s-", path[i]->name);
		//printf("\n");
		count++;
		return;
	}
	f->visited++;
	n++;
	for (int i = 1; i < nr; i++)
	{
		if (edge[f->nr][i])
			search(&nodes[i]);
	}
	n--;
	f->visited--;
	if (this_twice)
		small_twice = false;
}

long perm = 0;
long max_count = 0;

void modify(int i)
{
	if (i == nr)
	{
		perm++;
		count = 0;
		search(&nodes[0]);
		printf(" %ld\n", count);
		if (count > max_count)
			max_count = count;
		return;
	}
	nodes[i].multiple = false;
	modify(i+1);
	for (int j = 2; j < i; j++)
		if (edge[i][j] && nodes[j].multiple)
			return;
	nodes[i].multiple = true;
	modify(i+1);
}

int main(int argc, char *argv[])
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			edge[i][j] = false;
			
	find("start");
	find("end");
	
	char buffer[100];
	while (fgets(buffer, 99, stdin))
	{
		Node *f, *t;
		char *s = buffer;
		char *n = s;
		while (('a' <= *s && *s <= 'z') || ('A' <= *s && *s <= 'Z'))
			s++;
		*s = '\0';
		f = find(n);
		n = ++s;
		while (('a' <= *s && *s <= 'z') || ('A' <= *s && *s <= 'Z'))
			s++;
		*s = '\0';
		t = find(n);
		edge[f->nr][t->nr] = true;
		edge[t->nr][f->nr] = true;
	}
	
	for (int i = 0; i < nr; i++)
	{
		printf("%s %d\n", nodes[i].name, nodes[i].multiple);
	}
	for (int i = 0; i < N; i++)
		for (int j = i+1; j < N; j++)
			if (edge[i][j])
				printf("%s-%s\n", nodes[i].name, nodes[j].name);
	
	small_twice = true;
	count = 0;
	search(&nodes[0]);
	printf("%ld\n", count);

	small_twice = false;
	count = 0;
	search(&nodes[0]);
	printf("%ld\n", count);
	
	printf("%d\n", nr);
	perm = 0;
	modify(2);
	printf("%ld %ld\n", perm, max_count);
}