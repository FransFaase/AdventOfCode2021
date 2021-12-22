#include <stdio.h>

int get_nr(char *&s)
{
	bool min = false;
	if (*s == '-')
	{
		min = true;
		s++;
	}
	long r = 0;
	while ('0' <= *s && *s <= '9')
		r = 10 * r + *s++ - '0';
	if (min)
		r = -r;
	return r;
}	

struct Range
{
	long min;
	long max;
	Range() : min(100000), max(-1000000) {}
	bool in(int i) { return min <= i && i <= max; }
	void join(Range &other)
	{
		if (other.min < min) min = other.min;
		if (other.max > max) max = other.max;
	}
	
	void parse(char *&s)
	{
		min = get_nr(s);
		s += 2;
		max = get_nr(s);
	}
};

struct Command
{
	bool skip;
	bool on;
	Range x;
	Range y;
	Range z;
};

Command coms[500];
int n = 0;

int main(int argc, char *argv[])
{
	Range rx;
	Range ry;
	Range rz;

	char buffer[101];
	while (fgets(buffer, 100, stdin))
	{
		char *s = buffer;
		if (s[1] == 'n')
		{
			coms[n].on = true;
			s += 5;
		}
		else
		{
			coms[n].on = false;
			s += 6;
		}
		coms[n].skip = false;
		coms[n].x.parse(s);
		s += 3;
		coms[n].y.parse(s);
		s += 3;
		coms[n].z.parse(s);
		
		rx.join(coms[n].x);
		ry.join(coms[n].y);
		rz.join(coms[n].z);
		
		//printf("%s x=%ld..%ld,y=%ld..%ld,z=%ld..%ld\n", coms[n].on ? "on" : "off", coms[n].x.min, coms[n].x.max, coms[n].y.min, coms[n].y.max, coms[n].z.min, coms[n].z.max);
		n++;
	}
	printf("\n");
	
	long long count = 0;
	for (int x = -50; x <= +50; x++)
		for (int y = -50; y <= +50; y++)
			for (int z = -50; z <= +50; z++)
			{
				bool on = false;
				for (int i = n; i >= 0; i--)
				{
					if (coms[i].x.in(x) && coms[i].y.in(y) && coms[i].z.in(z))
					{
						on = coms[i].on;
						break;
					}
				}
				if (on)
					count++;
			}
	printf("%lld\n", count);	
}

