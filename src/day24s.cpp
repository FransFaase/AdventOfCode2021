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
		if (!infinite && min < max) { printf("/*%ld..%ld*/", min, max); }
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
		//range.print();
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
	//printf("[ "); l->print(); printf(" != "); r->print(); printf(" ]");
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

int calculate(long *input)
{
#ifndef GEN_PROGRAM
#include "program.h"
	if (z == 0) return 14;
	//printf("z = %ld\n", z);
	return 13;
#endif
}


int main(int argc, char *argv[])
{
#ifdef GEN_PROGRAM
	Expr *expr[26];
	
	for (int i = 0; i < 26; i++)
		expr[i] = 0;;
	for (int i = 0; i < 14; i++)
	{
		//	printf("\tlong %c = *inp++;\n", 'a' + i);
		expr[i] = input_var('a' + i);
	}
	
	bool assign[300];
	for (int i = 0; i < 300; i++) assign[i] = false;
	assign[7] = true;
	assign[17] = true;
	assign[25] = true;
	assign[35] = true;
	assign[43] = true;
	assign[53] = true;
	assign[61] = true;
	assign[71] = true;
	assign[79] = true;
	assign[89] = true;
	assign[97] = true;
	assign[107] = true;
	assign[115] = true;
	assign[125] = true;
	assign[133] = true;
	assign[143] = true;
	assign[151] = true;
	assign[161] = true;
	assign[169] = true;
	assign[179] = true;
	assign[187] = true;
	assign[197] = true;
	assign[205] = true;
	assign[215] = true;
	assign[223] = true;
	assign[233] = true;
	assign[241] = true;
	
	// Some assumptions:
	/*
	expr['f'-'a'] = expr['e'-'a'];
	expr['g'-'a'] = add_expr(expr['h'-'a'], const_expr(4));
	expr['i'-'a'] = add_expr(expr['d'-'a'], const_expr(-1));
	expr['k'-'a'] = add_expr(expr['j'-'a'], const_expr(7));
	expr['l'-'a'] = add_expr(expr['c'-'a'], const_expr(-6));
	expr['m'-'a'] = add_expr(expr['b'-'a'], const_expr(-6));
	//expr['n'-'a'] = add_expr(expr['m'-'a'], const_expr26(5));
	*/
	
	for (int i = 22; i < 26; i++)
	{
		printf("\tlong long %c = 0;\n", 'a' + i);
		expr[i] = const_expr(0);
		//expr[i] = input_var('a' + i);
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
	int varnr = 0;
	for (int i = 0; i < n; i++)
	{
		char *s = buffer[i];

		/*
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
		*/
		
		//printf("  //%4d %-15s  ", i, s);
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
						Expr *re = new Expr(r);
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
			Expr *l = expr[a];
			Expr *r = ('w' <= s[6] && s[6] <= 'z')
					? expr[s[6] - 'a']
					: const_expr(get_nr(s + 6));
			if (strncmp(s, "add ", 4) == 0) expr[a] = add_expr(l, r);
			if (strncmp(s, "mul ", 4) == 0) expr[a] = mul_expr(l, r);
			if (strncmp(s, "div ", 4) == 0) expr[a] = div_expr(l, r);
			if (strncmp(s, "mod ", 4) == 0) expr[a] = mod_expr(l, r);
			if (strncmp(s, "eql ", 4) == 0) expr[a] = eql_expr(l, r);
		}
		//printf("// ");

		printf("\t/*%3d %-10s */ ", i, s);
		if (strncmp(s, "inp ", 4) == 0)
		{
			printf("%c = *input++; ", s[4]);
			expr[s[4]-'a'] = input_var(s[4]);
		}
		else
		if (assign[i])
		{
			printf("%c = ", s[4]); expr[s[4]-'a']->print(); printf("; ");
			if (s[4] == 'x')
			{
				printf("if (x != 1) return %d; ", varnr++);
				expr[s[4]-'a'] = const_expr(1);
			}
			else
				expr[s[4]-'a'] = input_var(s[4]);
		}
		printf("// ");
		for (int j = 22; j < 26; j++)
		{
			printf(" %c=", 'a' + j);
			expr[j]->print();
			//expr[i]->range.print();
		}
		printf("\n");
	}
	printf("\tz = ");
	expr['z'-'a']->print();
	printf(";\n");
	return 0;
#endif
/*
	input['g'-'a'] = input['h'-'a'] + 4;
	input['d'-'a'] = input['i'-'a'] + 1;
	input['k'-'a'] = input['j'-'a'] + 7;
	input['c'-'a'] = input['l'-'a'] + 6;
	input['b'-'a'] = input['m'-'a'] + 6;
	input['n'-'a'] = input['m'-'a'] + 5;

	input[7] = input[6] - 4;
	input[8] = input[3] - 1;
	input[10] = input[9] + 7;
	input[11] = input[2] - 6 ;
	input[12] = input[1] - 6;
	printf("%ld\n", calculate(input));
*/
	
	long input[14];
	long values[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	long *start[14];
	long *stop[14];
	long offset[14];
	for (int i = 0; i < 14; i++)
	{
		start[i] = values + 9;
		stop[i] = values + 1;
		offset[i] = 0;
	}
	/*
	start[ 7] = stop[ 7] = input +  6; offset[ 7] = -4;  stop[6] = values + 1 - offset[ 7];
	start[ 8] = stop[ 8] = input +  3; offset[ 8] = -1;  stop[3] = values + 1 - offset[ 8];
	start[10] = stop[10] = input +  9; offset[10] =  7; start[9] = values + 1 + offset[10];
	start[11] = stop[11] = input +  2; offset[11] = -6;  stop[2] = values + 1 - offset[11];
	start[12] = stop[12] = input +  1; offset[12] = -6;  stop[1] = values + 1 - offset[12];
	*/
/*	abcdefghijklmn
    01234567890123
              1111 	
	input[7] = input[6] - 4;
	input[8] = input[3] - 1;
	input[10] = input[9] + 7;
	input[11] = input[2] - 6;
	input[12] = input[1] - 6;
	input[13] = input[12] + 5;

*/

	for (int i = 0; i < 14; i++)
		input[i] = *start[i] + offset[i];
	{
		for (int i = 0; i < 14; i++)
			printf("%ld", input[i]);
		printf("\n");
	}			

	for (;;)
	{
		int c = calculate(input);
		if (c == 14)
		{
			break;
		}
	//	int err = c;
	//	int save[14];
	//	for (int i = 0; i < 14; i++)
	//		save[i] = input[i];
		for (; c >= 0; c--)
		{
			if (input[c] > *stop[c] + offset[c])
				break;
		}
		if (c == -1)
			break;
		input[c]--;
		int low = c;
		for (c++; c < 14; c++)
			input[c] = *start[c] + offset[c];
		/*
		if (false)
		{
			for (int i = 0; i < 14; i++)
				input[i] = save[i];
			for (int i = 0; i < 14; i++)
				printf("%ld", input[i]);
			printf(" = %d %d\n", low, err);
			c = err;
			
			for (; c >= 0; c--)
			{
				printf(" %d:%ld > %ld\n", c, input[c], *stop[c]);
				if (input[c] > *stop[c] + offset[c])
					break;
			}
			input[c]--;
			for (int i = 0; i <= c; i++)
				printf("%ld", input[i]);
			printf("\n");
			printf("c = %d\n", c);
			for (c++; c < 14; c++)
			{
				input[c] = *start[c] + offset[c];
				printf(" %d: %ld\n", c, input[c]);
			} 
			for (int i = 0; i < 14; i++)
				printf("%ld", input[i]);
			printf("\n\n");
		}
		*/			

		/*			
			c = 0;
		}
		*/
	}
	for (int i = 0; i < 14; i++)
		printf("%ld", input[i]);
	printf("\n");
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