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

bool input_value(char r) { return 'a' <= r && r <= 'n'; }

struct Range
{
	bool infinite;
	long long min;
	long long max;
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
	bool contains(int v) { return infinite || (min <= v && v <= max); }
	void print()
	{
		if (!infinite)
		{
			if (min == max) 
				printf("[%lld]", min);
			else
				printf("[%lld..%lld]", min, max);
		}
			
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
	void print(bool wr = false)
	{
		if (type == CONST)
			printf("%ld", value);
		else 
		{
			if ('a' <= type && type <= 'n')
				printf("input[%d]", type - 'a');
			else if ('w' <= type && type <= 'z')
				printf("%c", type);
			else
			{
				printf("(");
				l->print(wr);
				if (type == '=')
					printf(" == ");
				else			
					printf(" %c ", type);
				r->print(wr);
				printf(")");
			}
		}
		if (wr)
			range.print();
	}
	void print_depth(int depth)
	{
		if (depth == 0)
		{
			printf("???");
			return;
		}
		depth--;
		if (type == CONST)
			printf("%ld", value);
		else 
		{
			if ('a' <= type && type <= 'n')
				printf("input[%d]", type - 'a');
			else if ('w' <= type && type <= 'z')
				printf("%c", type);
			else
			{
				printf("(");
				l->print_depth(depth);
				if (type == '=')
					printf(" == ");
				else			
					printf(" %c ", type);
				r->print_depth(depth);
				printf(")");
			}
		}
		range.print();
	}
	void print_tree(int depth, int max_depth = -1)
	{
		if (max_depth > -1 && depth >= max_depth) return;
		if (type == CONST)
			printf("%*.*s%ld\n", depth, depth, "", value);
		else if ('a' <= type && type <= 'n')
			printf("%*.*sinput[%d]\n", depth, depth, "", type - 'a');
		else
		{
			l->print_tree(depth + 1, max_depth);
			printf("%*.*s%c ", depth, depth, "", type);
			range.print();
			printf("\n");
			r->print_tree(depth + 1, max_depth);
		}
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
	if (l->type == CONST && r->type == CONST)
		return const_expr(l->value == r->value);
	else if (input_value(l->type) && l->type == r->type)
		return const_expr(1);
	else if (nonOverlapping(l->range, r->range))
		return const_expr(0);
	else if (l->type == '+' && r->type == '+'
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
	void print(bool wr = false)
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
					d[i]->print(wr);
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
	Expr26 *e = new Expr26;
	for (int i = 0; i < 26; i++)
	{
		Expr *l = l26->d[i];
		Expr *r = r26->d[i];
		if (l == 0 && r == 0)
			break;
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
		for (int j = 0; i + j < 26 && r->d[j] != 0; j++)
			{
				if (e->d[i+j] == 0)
					e->d[i+j] = mul_expr(l->d[i], r->d[j]);
				else
					e->d[i+j] = add_expr(e->d[i+j], mul_expr(l->d[i], r->d[j]));
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
		for (int i = 0; i + 1 < 26 && l->d[i+1] != 0; i++)
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

struct
{
	int i1;
	int i2;
	int offset;
} rules[7];
int nr_rules = 0;

void should_be_equal_zero(Expr *e, int depth)
{
	printf("%*.*sShould be zero: ", depth, depth, "");
	e->print_depth(2);
	if (e->type == '*' && !e->l->range.contains(0))
	{
		printf(": Left unequal to zero => right should be zero\n");
		e = e->r;
	}
	else
	{
		printf("\nUNRESOLVED %c  ", e->type);
		e->print_tree(0, 4);
		printf("\n");
		return;
	}
	printf("%*.*sShould be zero: ", depth, depth, "");
	e->print_depth(2);
	if (e->type == '=' && e->r->type == CONST && e->r->value == 0)
	{
		printf(": Compare with zero => left should be unequal zero\n");
		e = e->l;
	}
	else
	{
		printf("\nUNRESOLVED %c  ", e->type);
		e->print_tree(0, 4);
		printf("\n");
		return;
	}
	printf("%*.*sShould be unequal zero: ", depth, depth, "");
	e->print_depth(2);
	printf("  ");
	int i;
	if (e->type == '=' && input_value(e->r->type))
	{
		i = e->r->type - 'a';
		printf("right should be in range input[%d]\n", i);
		e = e->l;
	}
	else
	{
		printf("\nUNRESOLVED %c\n", e->type);
		e->print_tree(0, 4);
		printf("\n");
		return;
	}
	printf("%*.*sShould be range with input[%d]: ", depth, depth, "", i);
	e->print_depth(2);
	printf("  ");
	long offset = 0;
	if (e->type == '+' && e->r->type == CONST)
	{
		printf("right is const, subtract offset\n");
		offset = e->r->value;
		e = e->l;
	}
	else
		printf("\n");
	printf("%*.*sShould be range with input[%d] + %ld: ", depth, depth, "", i, offset);
	e->print_depth(2);
	if (input_value(e->type))
	{
		printf("\n%*.*sCONCLUSION: input[%d] == input[%d] + %ld\n", depth, depth, "", i, e->type - 'a', offset);
		rules[nr_rules].i1 = i;
		rules[nr_rules].i2 = e->type - 'a';
		rules[nr_rules].offset = offset;
		nr_rules++;
		return;
	}
	
	for (;;)
	{
		if (e->type == '+'
		    && e->r->type == '*'
		    && e->r->range.contains(0)
		    && e->l->type == '*'
		        && e->l->r->range.contains(1)
		        && e->l->r->type == '+'
		        && e->l->r->l->type == '*'
		              && e->l->r->l->l->type == CONST
		              && e->l->r->l->l->value == 25)
	    {
	    	should_be_equal_zero(e->r, depth + 4);
			e = e->l->l;
		}
	    else if (e->type == '*')
	    {
			e = e->l;
		}
		else
			break;
	}
	if (e->type == '+'
        && input_value(e->l->type)
        && e->r->type == CONST)
    {
		printf("%*.*sCONCLUSION: input[%d] == input[%d] + %ld\n", depth, depth, "", i, e->l->type - 'a', e->r->value + offset);
		rules[nr_rules].i1 = i;
		rules[nr_rules].i2 = e->l->type - 'a';
		rules[nr_rules].offset = e->r->value + offset;
		nr_rules++;
	}
}



int main(int argc, char *argv[])
{
	Expr26 *expr[26];
	
	for (int i = 0; i < 26; i++)
		expr[i] = 0;;
	for (int i = 0; i < 14; i++)
	{
		expr[i] = input_var26('a' + i);
	}
	
	for (int i = 22; i < 26; i++)
	{
		expr[i] = const_expr26(0);
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
	
	char input_reg = 0;
	for (int i = 0; i < n; i++)
	{
		char *s = buffer[i];
		printf("%-10s  ", s);

		if (strncmp(s, "inp ", 4) == 0)
		{
			char reg = s[4];
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
		printf("%c = ", s[4]); expr[s[4]-'a']->print(true); printf(";\n");
	}
	printf("\n");
	
	Expr *e = expr['z'-'a']->first();
	if (e == 0)
	{
		printf("Unknown(Expr26):\n");
		return 0;	
	}
	should_be_equal_zero(e, 0);
	printf("\n");
	
	// Answer puzzle 1;
	int sol[14];
	for (int i = 0; i < nr_rules; i++)
	{
		if (rules[i].offset < 0)
		{
			sol[rules[i].i1] = 9 + rules[i].offset;
			sol[rules[i].i2] = 9;
		}
		else
		{
			sol[rules[i].i1] = 9;
			sol[rules[i].i2] = 9 - rules[i].offset;
		}
	}
	for (int i = 0; i < 14; i++)
		printf("%d", sol[i]);

	printf("\n");
	for (int i = 0; i < nr_rules; i++)
	{
		if (rules[i].offset < 0)
		{
			sol[rules[i].i1] = 1;
			sol[rules[i].i2] = 1 - rules[i].offset;
		}
		else
		{
			sol[rules[i].i1] = 1 + rules[i].offset;
			sol[rules[i].i2] = 1;
		}
	}
	for (int i = 0; i < 14; i++)
		printf("%d", sol[i]);
	printf("\n");
}	

	