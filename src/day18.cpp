#include <stdio.h>
#include <string.h>

struct Pair
{
	int n;
	Pair *l;
	Pair *r;
	Pair(int _n) : n(_n), l(0), r(0) {}
	Pair(Pair *_l, Pair *_r) : n(-1), l(_l), r(_r) {}
};

Pair *parse(char *&s)
{
	if (*s == '[')
	{
		s++;
		Pair *l = parse(s);
		s++;
		Pair *r = parse(s);
		s++;
		return new Pair(l, r);
	}
	else
	{
		int n = 0;
		while ('0' <= *s && *s <= '9')
			n = 10 * n + *s++ - '0';
		return new Pair(n);
	}
}

void print(Pair *p)
{
	if (p->n == -1)
	{
		printf("[");
		print(p->l);
		printf(",");
		print(p->r);
		printf("]");
	}
	else
	{
		printf("%d", p->n);
	}
}

Pair *stack[10];
int d = 0;
Pair *cur;

void next()
{
	if (stack[d]->n != -1)
	{
		while (d > 0 && stack[d] == stack[d-1]->r)
		{
			d--;
			if (d == 0)
			{
				cur = 0;			
				return;
			}
		}
		stack[d] = stack[d-1]->r;
	}
	while (stack[d]->l != 0)
	{
		stack[d+1] = stack[d]->l;
		d++;
	}
	cur = stack[d];
}

void start(Pair *p)
{
	d = 0;
	stack[d] = p;
	next();
}

Pair *&cur_ref()
{
	if (stack[d-1]->l == stack[d])
		return stack[d-1]->l;
	else
		return stack[d-1]->r;
}

Pair *&parent()
{
	if (stack[d-2]->l == stack[d-1])
		return stack[d-2]->l;
	else
		return stack[d-2]->r;
}

Pair *add(Pair *l, Pair *r)
{
	Pair *p = new Pair(l, r);
	//printf("after addition: "); print(p); printf("\n");

/*
	for (;;)
	{
		next();
		if (d == 0)
			break;
		printf("%d:", d); print(stack[d]); printf(" ");
	}
	printf("\n");
*/		
	for (bool go = true; go;)
	{
		go = false;
		
		// explode
		// find first depth pair
		Pair *prev = 0;
		start(p);
		while (cur != 0 && d < 5)
		{
			prev = cur;
			//print(cur); printf(" ");
			next();
		}
		if (d == 5)
		{
			go = true;
			Pair *&pp = parent();
			int ln = cur->n;
			next();
			int rn = cur->n;
			//printf(" %d,%d  ", ln, rn);
			if (prev != 0)
				prev->n += ln;
			next();
			if (cur != 0)
				cur->n += rn;
			pp = new Pair(0);
			//printf("after explode:  ");print(p);printf("\n");
		}
		if (go) continue;
		
		// splits
		start(p);
		while (cur != 0 && cur->n < 10)
			next();
		if (cur != 0)
		{
			go = true;
			int n = cur->n;
			int ln = n/2;
			int rn = n - ln;
			cur->l = new Pair(ln);
			cur->r = new Pair(rn);
			cur->n = -1;
			//printf("after split:    ");print(p);printf("\n");
		}
	}
	return p;
}

long long magnitude(Pair *p)
{
	return p->n == -1 ? 3 * magnitude(p->l) + 2 * magnitude(p->r) : p->n;
}

int main(int argc, char *argv[])
{
	char buffer[1001];
	strcpy(buffer, "[[[[4,3],4],4],[7,[[8,4],9]]]");
	char *s = buffer;
	Pair *l = parse(s);
	strcpy(buffer, "[1,1]");
	s = buffer;
	Pair *r = parse(s);
	add(l, r);
	printf("\n\n");
	
	fgets(buffer, 1000, stdin);
	s = buffer;
	Pair *p = parse(s);
	//print(p);
	//printf("\n");
	
	while (fgets(buffer, 1000, stdin))
	{
		s = buffer;
		Pair *p2 = parse(s);
		//print(p2);
		//printf("\n");
		printf("  "); print(p); printf("\n+ "); print(p2); printf("\n= ");
		
		p = add(p, p2);
		print(p);
		printf("\n\n");
	}
	print(p); printf("\n");
	
	printf("%lld\n", magnitude(p));
	
	return 0;
}