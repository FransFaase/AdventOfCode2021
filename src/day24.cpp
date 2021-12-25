#include <stdio.h>
#include <string.h>

int get_nr(char *s)
{
	int v = 0;
	bool min = *s == '-' ? *s++ == '-' : false;
	while ('0' <= *s && *s <= '9')
		v = 10 * v + *s++ - '0';
	return min ? -v : v;
}

long calculate(long a, long b, long c, long d, long e, long f, long g, long h, long i, long j, long k, long l, long m, long n)
{
#ifndef GEN_PROGRAM
#include "program.h"
#endif
}

#define CONST '0'

#define MAX_LONG 100000000L
#define MIN_LONG -100000000L

bool input_value(char r) { return 'a' <= r && r <= 'n'; }

struct Range
{
	bool infinite;
	long min;
	long max;
	Range() : infinite(true) {}
	void add(long v)
	{
		if (infinite)
		{
			max = min = v;
			infinite = false;
		}
		else
		{
			if (v < min) min = v;
			else if (v > max) max = v;
		}
	}
	void print()
	{
		if (!infinite && min < max) { printf("[%ld..%ld]", min, max); }
	}
};

bool nonOverlapping(Range &l, Range &r)
{
	return !l.infinite && !r.infinite && (r.max < l.min || l.max < r.min);
}

struct Expr
{
	char type;
	long value;
	Range range;
	
	Expr *l;
	Expr *r;
	Expr(char t) : type(t), value(0), l(0), r(0)
	{
		if ('a' <= t && t <= 'n')
		{
			range.add(9);
			range.add(1);
		}
	}
	Expr(char t, long v) : type(t), value(v), l(0), r(0) { range.add(v); }
	Expr(char o, Expr *_l, Expr *_r) : type(o), value(0), l(_l), r(_r)
	{
		switch(o)
		{
			case '+':
				if (!l->range.infinite && !r->range.infinite)
				{
					range.add(l->range.max + r->range.max);
					range.add(l->range.min + r->range.min);
				}
				break;
			case '*':
				if (!l->range.infinite && !r->range.infinite)
				{
					range.add(l->range.max * r->range.max);
					range.add(l->range.min * r->range.min);
					range.add(l->range.max * r->range.min);
					range.add(l->range.min * r->range.max);
				}
				break;
			case '/':
				if (!l->range.infinite && !r->range.infinite)
				{
					if (l->range.min > 0 && r->range.min > 0)
					{
						range.add(l->range.max / l->range.min);
						range.add(l->range.min / l->range.max);
					}
				}
				break;
			case '%':
				if (!r->range.infinite && r->range.min > 0)
				{
					
					range.add(r->range.max - 1);
					range.add(0);
				}
				break;
			case '=':
				range.add(1);
				range.add(0);
				break;
		}				
	}
	void print()
	{
		if (type == CONST)
			printf("%ld", value);
		else 
		{
			if ('a' <= type && type <= 'z')
				printf("%c", type);
			else
			{
				printf("(");
				l->print();
				if (type == '=')
					printf(" == ");
				else			
					printf(" %c ", type);
				r->print();
				printf(")");
			}
		}
		range.print();
	}
};

Expr *const_expr(long value)
{
	return new Expr(CONST, value);
}

Expr *input_var(char v)
{
	return new Expr(v);
}

Expr *add_expr(Expr *l, Expr *r)
{
	if (l == 0) return r;
	if (r == 0) return l;
	if (l->type == CONST && r->type == CONST) return const_expr(l->value + r->value);
	if (l->type == CONST && l->value == 0) return r;
	if (r->type == CONST && r->value == 0) return l;
	if (r->type == CONST && l->type == '+' && l->r->type == CONST)
	{
		int v = r->value + l->r->value;
		return v == 0 ? l->l : new Expr('+', l->l, const_expr(v));
	}
	return new Expr('+', l, r);
}

Expr *mul_expr(Expr *l, Expr *r)
{
	if (l->type == CONST && r->type == CONST)
		return const_expr(l->value * r->value);
	else if (l->type == CONST && l->value == 0)
		return const_expr(0);
	else if (l->type == CONST && l->value == 1)
		return r;
	else if (r->type == CONST && r->value == 0)
		return r;
	else if (r->type == CONST && r->value == 1)
		return l;
	else
		return new Expr('*', l, r);
}
		
Expr *div_expr(Expr *l, Expr *r)
{
	if (l->type == CONST && r->type == CONST)
		return const_expr(l->value / r->value);
	else if (r->type == CONST && r->value == 1)
		return l;
	else
		return new Expr('/', l, r);
}

Expr *mod_expr(Expr *l, Expr *r)
{
	if (l->type == CONST && r->type == CONST)
		return const_expr(l->value % r->value);
	else if (r->type == CONST && !l->range.infinite && l->range.max < r->value && l->range.min >= 0)
		return l;
	else
		return new Expr('%', l, r);
}

Expr *eql_expr(Expr *l, Expr *r)
{
	printf("[ "); l->print(); printf(" != "); r->print(); printf(" ]");
	if (l->type == CONST && r->type == CONST)
		return const_expr(l->value == r->value);
	else if (input_value(l->type) && l->type == r->type)
	{
		return const_expr(1);
	}
	else if (nonOverlapping(l->range, r->range))
		return const_expr(0);
	else if (   l->type == '+' && r->type == '+'
	         && input_value(l->l->type) && l->l->type == r->l->type
	         && l->r->type == CONST && r->r->type == CONST)
		return const_expr(l->r->value == r->r->value);
	return new Expr('=', l, r);
}

struct Expr26
{
	Expr *d[26];
	Expr26() { for (int i = 0; i < 26; i++) d[i] = 0; }
	Expr26(long v) { d[0] = new Expr(v); for (int i = 1; i < 26; i++) d[i] = 0; }
	bool is(long v) { return d[1] == 0 && (d[0] == 0 ? v == 0 : (d[0]->type == CONST && d[0]->value == v)); }
	Expr* first() { return d[1] != 0 ? 0 : d[0] == 0 ? const_expr(0) : d[0]; } 
	void print()
	{
		if (d[0] == 0)
			printf("0");
		else
		{
			bool b = false;
			for (int i = 25; i >= 0; i--)
				if (d[i] != 0)
				{
					if (b) printf("_");
					d[i]->print();
					b = true;
				}
		}
	}
};

Expr26 *const_expr26(long value)
{
	Expr26 *e = new Expr26;
	e->d[0] = new Expr(CONST, value);
	return e;
}

Expr26 *input_var26(char v)
{
	Expr26 *e = new Expr26;
	e->d[0] = new Expr(v);
	return e;
}

Expr26 *add_expr(Expr26 *l26, Expr26 *r26)
{
	//printf("ADD26 "); l26->print(); printf(" WITH "); r26->print(); printf("\n");
	Expr26 *e = new Expr26;
	for (int i = 0; i < 26; i++)
	{
		Expr *l = l26->d[i];
		Expr *r = r26->d[i];
		if (l == 0 && r == 0)
			break;
		//printf("ADD "); l->print(); printf(" WITH "); r->print(); printf("\n");
		e->d[i] = add_expr(l, r);
	}
	return e;
}

Expr26 *mul_expr(Expr26 *l, Expr26 *r)
{
	if (l->is(0) || r->is(0))
	{
		Expr26 *e = new Expr26;
		e->d[0] = const_expr(0);
		return e;
	}
	if (l->is(1))
		return r;
	if (r->is(1))
		return l;
	if (l->is(26))
	{
		Expr26 *e = new Expr26;
		e->d[0] = const_expr(0);
		for (int i = 0; i < 26 && r->d[0] != 0; i++)
			e->d[i+1] = r->d[i];
		return e;
	}
	if (r->is(26))
	{
		Expr26 *e = new Expr26;
		e->d[0] = const_expr(0);
		for (int i = 0; i < 26 && l->d[0] != 0; i++)
			e->d[i+1] = l->d[i];
		return e;
	}
	Expr26 *e = new Expr26;
	for (int i = 0; i < 26 && l->d[i] != 0; i++)
		for (int j = 0; i + j < 26 && r->d[i] != 0; i++)
		{
			if (e->d[i+j] == 0)
				e->d[i+j] = mul_expr(l->d[i], r->d[i]);
			else
				e->d[i+j] = add_expr(e->d[i+j], mul_expr(l->d[i], r->d[i]));
		}
	return e;
}

bool isConst(Expr26 *e)
{
	for (int i = 0; e->d[i] != 0; i++)
		if (e->d[i]->type != CONST)
			return false;
	return true;
}
		
Expr26 *div_expr(Expr26 *l, Expr26 *r)
{
	if (r->is(26))
	{
		Expr26 *e = new Expr26;
		for (int i = 0; i < 26 && l->d[i+1] != 0; i++)
			e->d[i] = l->d[i+1];
		if (e->d[0] == 0) e->d[0] = const_expr(0);
		return e;
	}
	if (r->is(1))
		return l;
	Expr *fl = l->first();
	Expr *fr = r->first();
	if (fl != 0 && fr != 0)
	{
		Expr26 *e = new Expr26;
		e->d[0] = div_expr(fl, fr);
		return e;
	}
	printf("DIV ERROR");
	return const_expr26(0);
}

Expr26 *mod_expr(Expr26 *l, Expr26 *r)
{
	if (r->is(26))
	{
		Expr26 *e = new Expr26;
		e->d[0] = l->d[0];
		if (e->d[0] == 0) e->d[0] = const_expr(0);
		return e;
	}
	Expr *fl = l->first();
	Expr *fr = r->first();
	if (fl != 0 && fr != 0)
	{
		Expr26 *e = new Expr26;
		e->d[0] = mod_expr(fl, fr);
		return e;
	}
	printf("MOD ERROR");
	return const_expr26(0);
}

Expr26 *eql_expr(Expr26 *l, Expr26 *r)
{
	Expr *fl = l->first();
	Expr *fr = r->first();
	if (fl != 0 && fr != 0)
	{
		Expr26 *e = new Expr26;
		e->d[0] = eql_expr(fl, fr);
		return e;
	}
	printf("EQL ERROR");
	return const_expr26(0);
}

int main(int argc, char *argv[])
{
#ifdef GEN_PROGRAM
	Expr26 *expr[26];
	
	for (int i = 0; i < 26; i++)
		expr[i] = 0;;
	for (int i = 0; i < 14; i++)
	{
		//	printf("\tlong %c = *inp++;\n", 'a' + i);
		expr[i] = input_var26('a' + i);
	}
	
	// Some assumptions:
	expr['f'-'a'] = expr['e'-'a'];
	expr['g'-'a'] = add_expr(expr['h'-'a'], const_expr26(4));
	expr['i'-'a'] = add_expr(expr['d'-'a'], const_expr26(-1));
	expr['k'-'a'] = add_expr(expr['j'-'a'], const_expr26(7));
	expr['l'-'a'] = add_expr(expr['c'-'a'], const_expr26(-6));
	expr['m'-'a'] = add_expr(expr['b'-'a'], const_expr26(-6));
	//expr['n'-'a'] = add_expr(expr['m'-'a'], const_expr26(5));
	
	for (int i = 22; i < 26; i++)
	{
		printf("\tlong %c = 0;\n", 'a' + i);
		//expr[i] = const_expr26(0);
		expr[i] = input_var26('a' + i);
	}
	
	char buffer[300][20];
	int n = 0;
	while (fgets(buffer[n], 19, stdin))
	{
		for (char *s = buffer[n]; *s != '\0'; s++)
			if (*s == '\r' || *s == '\n')
				*s = '\0';
		n++;
	}
	
	int nr_lines = 0;
	char input_reg = 0;
	for (int i = 234; i < n; i++)
	{
		char *s = buffer[i];

		char code[30];
		if (strncmp(s, "inp ", 4) == 0)
			sprintf(code, "= %c;", 'a' + input_reg);
		else
		{
			if ('w' <= s[6] && s[6] <= 'z')
			{
				if (strncmp(s, "add ", 4) == 0) sprintf(code, "+= %c;", s[6]);
				if (strncmp(s, "mul ", 4) == 0) sprintf(code, "*= %c;", s[6]);
				if (strncmp(s, "div ", 4) == 0) sprintf(code, "/= %c;", s[6]);
				if (strncmp(s, "mod ", 4) == 0) sprintf(code, "%%= %c;", s[6]);
				if (strncmp(s, "eql ", 4) == 0) sprintf(code, "= %c == %c;", s[4], s[6]);
			}
			else
			{
				int v = get_nr(s + 6);
				if (strncmp(s, "add ", 4) == 0) sprintf(code, "+= %d;", v);
				if (strncmp(s, "mul ", 4) == 0) sprintf(code, "*= %d;", v);
				if (strncmp(s, "div ", 4) == 0) sprintf(code, "/= %d;", v);
				if (strncmp(s, "mod ", 4) == 0) sprintf(code, "%%= %d;", v);
				if (strncmp(s, "eql ", 4) == 0) sprintf(code, "= %c == %d;", s[4], v);
			}
		}
		printf("\t%c %-10s", s[4], code);
		
		printf("  //%4d %-15s  ", i, s);
		//printf("  printf(\"%-10s  %c = %%ld\\n\", %c); //", s, s[4], s[4]); 
		//if (++nr_lines > 40)
		//	break;
		if (strncmp(s, "inp ", 4) == 0)
		{
			char reg = s[4];
			/*
			if (input_reg > 0)
			{
				for (char r = 'w'; r <= 'z'; r++)
					if (r != reg && isConst(expr[r-'a']))
					{
						printf("\t%c = ", r);
						expr[r-'a']->print();
						printf(";");
						Expr26 *re = new Expr26(r);
						//re->range = expr[r-'a']->range;
						expr[r-'a'] = re;
						printf("\n");
					}
			}
			printf("\t%c = %c;\n", reg, 'a' + input_reg);
			*/
			expr[reg-'a'] = expr[input_reg++];
		}
		else
		{
			int a = s[4] - 'a';
			Expr26 *l = expr[a];
			Expr26 *r = ('w' <= s[6] && s[6] <= 'z')
					? expr[s[6] - 'a']
					: const_expr26(get_nr(s + 6));
			if (strncmp(s, "add ", 4) == 0) expr[a] = add_expr(l, r);
			if (strncmp(s, "mul ", 4) == 0) expr[a] = mul_expr(l, r);
			if (strncmp(s, "div ", 4) == 0) expr[a] = div_expr(l, r);
			if (strncmp(s, "mod ", 4) == 0) expr[a] = mod_expr(l, r);
			if (strncmp(s, "eql ", 4) == 0) expr[a] = eql_expr(l, r);
		}
		//printf("// ");

		// Some more fixes
		for (int j = 22; j < 26; j++)
		{
			printf(" %c=", 'a' + j);
			expr[j]->print();
			//expr[i]->range.print();
		}
		if (i == 240)
			expr['x'-'a'] = const_expr26(1);
		printf("\n");
	}
	printf("\treturn z; //");
	expr['z'-'a']->print();
	printf(";\n");
	return 0;
#endif
	
	int input[14];
	for (int i = 0; i < 14; i++)
		input[i] = 1;
/*		
	input['g'-'a'] = input['h'-'a'] + 4;
	input['d'-'a'] = input['i'-'a'] + 1;
	input['k'-'a'] = input['j'-'a'] + 7;
	input['c'-'a'] = input['l'-'a'] + 6;
	input['b'-'a'] = input['m'-'a'] + 6;
	input['n'-'a'] = input['m'-'a'] + 5;
	printf("%ld\n", calculate(input));
*/

	{
		long a = 1;
		long b = 1;
		long c = 1;
		long d = 1;
		long e = 1;
		long f = 1;
		long g = 1;
		long h = 1;
		long i = 1;
		long j = 1;
		long k = 1;
		long l = 1;
		long m = 1;
		long n = 1;
		g = h + 4;
		d = i + 1;
		k = j + 7;	
		c = l + 6;
		b = m + 6;
		n = m + 5;
		printf("%ld\n", calculate(a,b,c,d,e,f,g,h,i,j,k,l,m,n));
	}	
	/*
	int input[14];
	for (int i = 0; i < 14; i++)
		input[i] = 9;
	long c = 0;
	for (;;)
	{
		if (calculate(input) == 0)
		{
			break;
		}
		
		int i = 13;
		for (; i >= 0; i--)
		{
			if (input[i] > 2)
			{
				input[i]--;
				break;
			}
			input[i] = 9;
		}
		if (i == -1)
			break;
		if (++c > 1000000)
		{
			printf("checking ");
			for (int i = 0; i < 14; i++)
				printf("%d", input[i]);
			printf("\n");
			c = 0;
		}
	}
	for (int i = 0; i < 14; i++)
		printf("%d", input[i]);
	printf("\n");
	*/
}

/*
struct Range
{
	bool infinite;
	long min;
	long max;
	Range() : infinite(true) {}
	void add(long v)
	{
		if (infinite)
		{
			max = min = v;
			infinite = false;
		}
		else
		{
			if (v < min) min = v;
			else if (v > max) max = v;
		}
	}
	void print()
	{
		if (!infinite && min < max) { printf("[%ld..%ld]", min, max); }
	}
};

bool nonOverlapping(Range &l, Range &r)
{
	return !l.infinite && !r.infinite && (r.max < l.min || l.max < r.min);
}



*/

/*  DUMB algorithm
	char buffer[20];
	while (fgets(buffer, 19, stdin))
	{
		
		char *s = buffer;
		if (strncmp(s, "inp ", 4) == 0)
		{
			printf("\t%c = *inp++;", s[4]);
		}
		else
		{
			printf("\t%c ", s[4]);
			if (strncmp(s, "add ", 4) == 0) printf("+= ");
			if (strncmp(s, "mul ", 4) == 0) printf("*= ");
			if (strncmp(s, "div ", 4) == 0) printf("/= ");
			if (strncmp(s, "mod ", 4) == 0) printf("%%= ");
			if (strncmp(s, "eql ", 4) == 0) printf("= %c == ", s[4]);
			if ('w' <= s[6] && s[6] <= 'z')
				printf("%c;", s[6]);
			else
				printf("%d;", get_nr(s + 6));
		}
		printf(" // %s", buffer);
	}
*/		