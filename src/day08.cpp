#include <stdio.h>

void swap(int &x, int &y)
{
	int h = x;
	x = y;
	y = h;
}

class Permutations
{
public:
	Permutations(int val_n) : n(val_n), _more(true)
	{
		a = new int[n];
		for (int i = 0; i < n; i++)
			a[i] = i;
	}
	~Permutations()
	{
		delete []a;
	}
	bool more() { return _more; }
	void next()
	{
		_more = false;
		for (int i = n-2; i >= 0; i--)
			if (a[i] < a[i+1])
			{
				_more = true;
				for (int j = n-1; j > i; j--)
					if (a[j] > a[i])
					{
						swap(a[j], a[i]);
						break;
					}
				i++;
				for (int j = n-1; j > i; j--, i++)
					swap(a[j], a[i]);
				break;
			}
	}
	inline int operator[](int i) { return a[i]; }
private:
	int n;
	int *a;
	bool _more;
};



#define Va (1 << 0)
#define Vb (1 << 1)
#define Vc (1 << 2)
#define Vd (1 << 3)
#define Ve (1 << 4)
#define Vf (1 << 5)
#define Vg (1 << 6)


int digits[10] = {
  /* 0 */ Va + Vb + Vc +      Ve + Vf + Vg,
  /* 1 */           Vc +           Vf, 
  /* 2 */ Va +      Vc + Vd + Ve +      Vg,
  /* 3 */ Va +      Vc + Vd +      Vf + Vg,
  /* 4 */      Vb + Vc + Vd +      Vf,
  /* 5 */ Va + Vb +      Vd +      Vf + Vg,
  /* 6 */ Va + Vb +      Vd + Ve + Vf + Vg,
  /* 7 */ Va +      Vc +           Vf,
  /* 8 */ Va + Vb + Vc + Vd + Ve + Vf + Vg,
  /* 9 */ Va + Vb + Vc + Vd +      Vf + Vg,
};

const char* dd[10] = { "abcefg", "cf", "acdeg", "acdfg", "bcdf", "abdfg", "abdefg", "acf","abcdefg", "abcdfg" };

void print(int v)
{
	for (int i = 0; i < 7; i++)
		if (v & (1 << i))
			printf("%c", i + 'a');
	printf(" ");
}

int main(int argc, char *argv[])
{

	for (int i = 0; i < 10; i++)
	{
		digits[i] = 0;
		const char *s = dd[i];
		for (;'a' <= *s && *s <= 'g'; s++)
			digits[i] |= (1 << (*s - 'a'));
	}
		
	char buffer[300];
	
	int count[10];
	for (int i = 0; i < 10; i++)
		count[i] = 0;
		
	long sum = 0;
	
	while (fgets(buffer, 300, stdin))
	{
		printf("%s", buffer);

		int sample[20];
		int nr_s = 0;
		
		char *s = buffer;
		while ('a' <= *s && *s <= 'g')
		{
			sample[nr_s] = 0;
			for (;'a' <= *s && *s <= 'g'; s++)
				sample[nr_s] |= (1 << (*s - 'a'));
			print(sample[nr_s]);
			nr_s++;
			if (*s == ' ')
				s++;
		}
		if (*s == '|')
			s += 2;
		
		printf("| ");
		
		int values[20];
		int nr_v = 0;
		
		while ('a' <= *s && *s <= 'g')
		{
			values[nr_v] = 0;
			for (;'a' <= *s && *s <= 'g'; s++)
				values[nr_v] |= (1 << (*s - 'a'));
			print(values[nr_v]);
			nr_v++;
			if (*s == ' ')
				s++;
		}
		//printf("\n");
		
		for (Permutations perms(7); perms.more(); perms.next())
		{
			bool match = true;
			for (int i = 0; i < nr_s; i++)
			{
				bool has_matching = false;
				for (int d = 0; d < 10; d++)
				{
					bool correct = true;
					for (int s = 0; s < 7; s++)
						if (((digits[d] >> s) & 1) != ((sample[i] >> perms[s]) & 1))
						{
							correct = false;
							break;
						}
					if (correct)
					{
						has_matching = true;
						break;
					}
				}
				if (!has_matching)
				{
					match = false;
					break;
				}
			}
			
			if (match)
			{
				printf("Found ");
				
				int v = 0;
				
				for (int i = 0; i < nr_v; i++)
				{
					//printf("%d:", i);
					bool found = false;
					for (int d = 0; d < 10; d++)
					{
						bool correct = true;
						for (int s = 0; s < 7; s++)
							if (((digits[d] >> s) & 1) != ((values[i] >> perms[s]) & 1))
							{
								correct = false;
								break;
							}
						if (correct)
						{
							v = 10 * v + d;
							found = true;
							printf("%d", d);
							count[d]++;
							break;
						}
					}
					if (!found)
						printf("!");
				}
				sum += v;
				break;
			}
			//printf("--\n");
		}
		printf("\n\n");
		//break;
	}
	
	for (int i = 0; i < 10; i++)
		printf("%d: %d\n", i, count[i]);
	printf("%d %ld\n", count[1] + count[4] + count[7] + count[8], sum);
}