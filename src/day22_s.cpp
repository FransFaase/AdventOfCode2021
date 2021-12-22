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

int minv(long a, long b) { return a < b ? a : b; }
int maxv(long a, long b) { return a > b ? a : b; }

struct Range
{
	long min;
	long max;
	Range() : min(100000), max(-1000000) {}
	Range(int _min, int _max) : min(_min), max(_max) {}
	long overlap(Range &o) { return maxv(0, minv(max, o.max) - maxv(min, o.min) + 1); }
	void join(Range &other)
	{
		if (other.min < min) min = other.min;
		if (other.max > max) max = other.max;
	}
	void intersect(Range &other)
	{
		if (other.min > min) min = other.min;
		if (other.max < max) max = other.max;
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
	long overlap(Range &ox, Range &oy, Range &oz) { return x.overlap(ox) * y.overlap(oy) * z.overlap(oz); }
};

Command coms[500];
int n = 0;

long long countIn(Range &xr, Range &yr, Range zr, int i)
{
	long long o = 0;
	while (i >= 0 && (o = coms[i].overlap(xr, yr, zr)) == 0)
		i--;
	if (o == 0)
		return 0;

	long long result = coms[i].on ? o : 0;
	result += countIn(xr, yr, zr, i-1);
	Range nxr = xr; nxr.intersect(coms[i].x);
	Range nyr = yr; nyr.intersect(coms[i].y);
	Range nzr = zr; nzr.intersect(coms[i].z);
	result -= countIn(nxr, nyr, nzr, i-1);
	return result;
}

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
		n++;
	}
	
	Range rx1(-50, 50);
	Range ry1(-50, 50);
	Range rz1(-50, 50);
	long long r1 = countIn(rx1, ry1, rz1, n-1);
	printf("%lld\n", r1);

	long long r2 = countIn(rx, ry, rz, n-1);
	printf("%lld\n", r2);
	
}

