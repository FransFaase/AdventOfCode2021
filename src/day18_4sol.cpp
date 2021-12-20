// This is explained at https://github.com/FransFaase/AdventOfCode2021/blob/main/Day18.md

#include <stdio.h>
#include <string.h>

// This data is taken from https://adventofcode.com/2021/day/18
const char *data[10] = {
    "[[[0,[5,8]],[[1,7],[9,6]]],[[4,[1,2]],[[1,4],2]]]",
    "[[[5,[2,8]],4],[5,[[9,9],0]]]",
    "[6,[[[6,2],[5,6]],[[7,6],[4,7]]]]",
    "[[[6,[0,7]],[0,9]],[4,[9,[9,0]]]]",
    "[[[7,[6,4]],[3,[1,3]]],[[[5,5],1],9]]",
    "[[6,[[7,3],[3,2]]],[[[3,8],[5,7]],4]]",
    "[[[[5,4],[7,7]],8],[[8,3],8]]",
    "[[9,3],[[9,9],[6,[4,9]]]]",
    "[[2,[[7,7],7]],[[5,8],[[9,3],[0,2]]]]",
    "[[[[5,2],5],[8,[3,7]]],[[5,[7,5]],[4,4]]]"
};


// ---- Solution 1: Original solution, using a tree

struct Pair
{
    int n;
    Pair *l;
    Pair *r;
    Pair(int _n) : n(_n), l(0), r(0) {}
    Pair(Pair *_l, Pair *_r) : n(-1), l(_l), r(_r) {}
};

Pair *parse(const char *&s)
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
    for (bool go = true; go;)
    {
        go = false;
        
        // explode
        Pair *prev = 0;
        start(p);
        while (cur != 0 && d < 5)
        {
            prev = cur;
            next();
        }
        if (d == 5)
        {
            go = true;
            Pair *&pp = parent();
            int ln = cur->n;
            next();
            int rn = cur->n;
            if (prev != 0)
                prev->n += ln;
            next();
            if (cur != 0)
                cur->n += rn;
            pp = new Pair(0);
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
        }
    }
    return p;
}

long magnitude(Pair *p)
{
    return p->n == -1 ? 3 * magnitude(p->l) + 2 * magnitude(p->r) : p->n;
}

void solution1(bool trace)
{
    if (trace) printf("Solutions 1:\n");
    const char *s = data[0];
    Pair *sum = parse(s);
    
    for (int i = 1; i < 10; i++)
    {
        s = data[i];
        Pair *p = parse(s);
        
        if (trace) { printf("  "); print(sum); printf("\n+ "); print(p); printf("\n= "); }
        
        sum = add(sum, p);
        
        if (trace) { print(sum); printf("\n\n"); }
    }
    
    printf(trace ? "final result: " : "solution 1: "); print(sum);
    printf(" %ld\n", magnitude(sum));
}

// ---- Solution 2: Using an array 

struct N
{
    int d;
    int n;
};

void parse(const char *s, N *output)
{
    int i = 0;
    int d = 0;
    for (;;s++)
    {
        if (*s == '[')
            d++;
        else if (*s == ']')
            d--;
        else if (*s == ',')
            ;
        else if ('0' <= *s && *s <= '9')
        {
            output[i].d = d;
            output[i].n = *s - '0';
            i++;
        }
        else
            break;
    }
    output[i].d = -1;
}

void print(N *&nodes, int depth)
{
    //printf("%d:", nodes->d);
    if (nodes->d == depth)
    {
        printf("%d", nodes->n);
        nodes++;
    }
    else
    {
        printf("[");
        print(nodes, depth + 1);
        printf(",");
        print(nodes, depth + 1);
        printf("]");
    }
}

void print(const char *s1, N *nodes, const char *s2 = "\n")
{
    printf("%s", s1);
    N *n = nodes;
    print(n, 0);
    printf("%s", s2);
}

long magnitude(N *&nodes, int depth)
{
    long result;
    if (nodes->d == depth)
    {
        result = nodes->n;
        nodes++;
    }
    else
    {
        result = 3 * magnitude(nodes, depth + 1);
        result += 2 * magnitude(nodes, depth + 1);
    }
    return result;
}

long magniute(N *nodes) { N *n = nodes; magnitude(n, 0); }

class It
{
    N *_c;
public:
    int d;
    int n;
    bool more;
    It(N *in) : _c(in) { d = _c->d; n = _c->n; more = d > 0; }
    void next() { _c++; d = _c->d; n = _c->n; more = d > 0; }
};

class Builder
{
    int _f;
    N *_out;
public:
    Builder(N *out) : _out(out), _f(0) {}
    ~Builder() { _out[_f].d = -1; }
    void append(int d, int n)
    {
        _out[_f].d = d;
        _out[_f].n = n;
        _f++;
    }
    void append(It& it) { append(it.d, it.n); }
    void addPrev(int n)
    {
        if (_f > 0)
            _out[_f-1].n += n;
    }
};        

void ass(N *dest, N* src)
{
    Builder builder(dest);
    for (It it(src); it.more; it.next())
        builder.append(it);
}

void add(N *n1, N *n2, N* r)
{
    // Add
    {
        Builder builder(r);
        for (It it1(n1); it1.more; it1.next())
            builder.append(it1.d + 1, it1.n);
        for (It it2(n2); it2.more; it2.next())
            builder.append(it2.d + 1, it2.n);
    }
    
    for (bool go = true; go;)
    {
        go = false;
        
        // explodes
        N nr[100];
        {
            Builder bnr(nr);
            int c = 0;
            for (It it(r); it.more; it.next())
            {
                if (it.d < 5)
                {
                    bnr.append(it.d, it.n + c);
                    c = 0;
                }
                else
                {
                    go = true;
                    bnr.addPrev(it.n + c);
                    bnr.append(it.d - 1, 0);
                    it.next();
                    c = it.n;
                }
            }
        }

        // split
        bool split = false;
        {
            Builder bnr(r);
            It it(nr);
    
            for (; it.more; it.next())
            {
                if (!split && it.n > 9)
                {
                    int v1 = it.n / 2;
                    int v2 = it.n - v1;
                    bnr.append(it.d + 1, v1);
                    bnr.append(it.d + 1, v2);
                    go = true;
                    split = true;
                }
                else
                {
                    bnr.append(it);
                }
            }
        }
    }
}

void solution2(bool trace)
{
    if (trace) printf("\nSolution 2:\n");

    N numbers[10][100];
    int nr = 0;

    for (int i = 0; i < 10; i++)
    {
        parse(data[i], numbers[nr]);
        nr++;
    }

    N *num;
    N sum[100];
    ass(sum, numbers[0]);
    for (int i = 1; i < nr; i++)
    {
        if (trace) { print("  ", sum); print("+ ", numbers[i]); }

        N result[100];
        add(sum, numbers[i], result);

        if (trace) { print("= ", result); printf("\n"); }
        
        ass(sum, result);
    }
    
    print(trace ? "final result: " : "Solution 2: ", sum, "");
    N *s = sum;
    printf(" %ld\n", magnitude(s, 0));
}

// ---- Solution 3: Using a double linked list 

struct L
{
    L *prev;
    L *next;
    int d;
    int n;
    L(int _d, int _n) : d(_d), n(_n), prev(0), next(0) {}
    void append(L *l)
    {
        if (next != 0)
        {
            next->prev = l;
            l->next = next;
        }
        l->prev = this;
        next = l;
    }
};

L *parseL(const char *s)
{
    L* result = 0;
    L* last;
    
    int i = 0;
    int d = 0;
    for (;;s++)
    {
        if (*s == '[')
            d++;
        else if (*s == ']')
            d--;
        else if (*s == ',')
            ;
        else if ('0' <= *s && *s <= '9')
        {
            L* cur = new L(d, *s - '0');
            if (result == 0)
                result = cur;
            else
                last->append(cur);
            last = cur;
        }
        else
            break;
    }
    return result;
}

void print(L *&nodes, int depth)
{
    //printf("%d:", nodes->d);
    if (nodes->d == depth)
    {
        printf("%d", nodes->n);
        nodes = nodes->next;
    }
    else
    {
        printf("[");
        print(nodes, depth + 1);
        printf(",");
        print(nodes, depth + 1);
        printf("]");
    }
}

void print(const char *s1, L *nodes, const char *s2 = "\n")
{
    printf("%s", s1);
    L *n = nodes;
    print(n, 0);
    printf("%s", s2);
}

long magnitude(L *&nodes, int depth)
{
    long result;
    if (nodes->d == depth)
    {
        result = nodes->n;
        nodes = nodes->next;
    }
    else
    {
        result = 3 * magnitude(nodes, depth + 1);
        result += 2 * magnitude(nodes, depth + 1);
    }
    return result;
}

long magniute(L *nodes) { L *n = nodes; magnitude(n, 0); }

L* add(L *n1, L *n2)
{
    // Add
    {
        L *last = n1;
        while (last->next != 0)
            last = last->next;
        last->append(n2);
    }
    L *sum = n1;
    for (L* l = sum; l != 0; l = l->next)
        l->d++;
    
    // explodes
    for (L* l = sum; l != 0; l = l->next)
    {
        if (l->d == 5)
        {
            L* other = l->next;
            if (other->d != 5) { printf("ERROR\n"); return 0; }
            
            L* prev = l->prev;
            if (prev != 0)
                prev->n += l->n;
            
            L* next = other->next;
            if (next != 0)
                next->n += other->n;
            other->d--;
            other->n = 0;
            
            other->prev = prev;
            if (prev != 0)
                prev->next = other;
            if (l == sum)
                sum = other;
            l = other;
        }
    }
    
    for (L* l = sum; l != 0; )
    {
        if (l->n < 10)
            l = l->next;
        else
        {
            int n1 = l->n / 2;
            int n2 = l->n - n1;
            int d = l->d;
            if (d == 4)
            {
                if (l->prev != 0)
                    l->prev->n += n1;
                if (l->next != 0)
                    l->next->n += n2;
                l->n = 0;
                l = l->prev != 0 ? l->prev : l->next;
            }
            else
            {
                l->d++;
                l->n = n1;
                l->append(new L(d+1, n2));
            }
        }
    }
    return sum;
}

void solution3(bool trace)
{
    if (trace) printf("\nSolution 3:\n");

    L *numbers[10];
    int nr = 0;

    for (int i = 0; i < 10; i++)
    {
        numbers[i] = parseL(data[i]);
        nr++;
    }

    L* sum = numbers[0];
    for (int i = 1; i < nr; i++)
    {
        if (trace) { print("  ", sum); print("+ ", numbers[i]); }

        sum = add(sum, numbers[i]);

        if (trace) { print("= ", sum); printf("\n"); }
    }
    
    print(trace ? "final result: " : "Solution 3: ", sum, "");
    L *s = sum;
    printf(" %ld\n", magnitude(s, 0));
}

// ---- Solution 4: Limited binary tree

struct LBT
{
    int v[32];
    
    LBT() { clear(); }
    void clear() { for (int i = 1; i < 32; i++) v[i] = -1; }
};

void parseLBT(const char *&s, int *v, int d)
{
    if (*s == '[')
    {
        s++;
        parseLBT(s, v - d, d/2);
        s++;
        parseLBT(s, v + d, d/2);
        s++;
    }
    else
    {
        *v = *s++ - '0';
    }
}

void printLBT(int *v, int d)
{
    if (*v == -1)
    {
        printf("[");
        printLBT(v - d, d/2);
        printf(",");
        printLBT(v + d, d/2);
        printf("]");
    }
    else
        printf("%d", *v);
}

void print(const char *p, LBT &lbt, const char *n = "\n") { printf("%s", p); printLBT(lbt.v + 16, 8); printf("%s", n); }

void add(LBT &l, LBT &r, LBT &sum)
{
    // Have to temporary use a double depth tree
    int isum[64];
    isum[32] = -1;
    for (int i = 1; i < 32; i++)
    {
        isum[i] = l.v[i];
        isum[32 + i] = r.v[i];
    }
    
    for (int i = 0; i < 64; i++)
    {
        if ((i & 3) == 1 && isum[i] != -1)
        {
            for (int j = i-1; j > 0; j--)
                if (isum[j] != -1)
                {
                    isum[j] += isum[i];
                    break;
                }
            isum[i++] = -1;
            isum[i++] = 0;
            for (int j = i+1; j < 64; j++)
                if (isum[j] != -1)
                {
                    isum[j] += isum[i];
                    break;
                }
            isum[i] = -1;
        }
    }
    
    // Now shrink it again
    sum.clear();
    for (int i = 1; i < 32; i++)
    {
        sum.v[i] = isum[2*i];
    }

    for (int i = 1; i < 32;)
    {
        if (sum.v[i] < 10)
            i++;
        else
        {
            int n1 = sum.v[i] / 2;
            int n2 = sum.v[i] - n1;
            if ((i & 1) == 1)
            {
                int p_i;
                for (p_i = i - 1; p_i > 0; p_i--)
                    if (sum.v[p_i] != -1)
                    {
                        sum.v[p_i] += n1;
                        break;
                    }
                int n_i;
                for (n_i = i + 1; n_i < 32; n_i++)
                    if (sum.v[n_i] != -1)
                    {
                        sum.v[n_i] += n2;
                        break;
                    }
                sum.v[i] = 0;
                i = p_i > 0 ? p_i : n_i;
            }
            else
            {
                sum.v[i] = -1;
                int o = 1;
                if ((i & 3) == 0)
                    o = 2;
                else if ((i & 7) == 0)
                    o = 4;
                else if ((i & 15) == 0)
                    o = 8;
                //printf("o = %d\n", o);
                sum.v[i] = -1;
                sum.v[i - o] = n1;
                sum.v[i + o] = n2;
                i -= o;
            }
        }
    }
}

long magnitude(int *v, int d)
{
    return *v == -1 ? 3 * magnitude(v - d, d/2) + 2 * magnitude(v + d, d/2) : *v;
}

void solution4(bool trace)
{
    if (trace) printf("\nSolution 4:\n");

    LBT numbers[10];
    int nr = 0;

    for (int i = 0; i < 10; i++)
    {
        parseLBT(data[i], numbers[i].v + 16, 8);
        nr++;
    }

    LBT sum = numbers[0];
    for (int i = 1; i < nr; i++)
    {
        if (trace) { print("  ", sum); print("+ ", numbers[i]); }

        LBT result;
        add(sum, numbers[i], result);
        sum = result;

        if (trace) { print("= ", sum); printf("\n"); }
    }
    
    print(trace ? "final result: " : "Solution 4: ", sum, "");
    printf(" %ld\n", magnitude(sum.v + 16, 8));
}

// -------------------------

int main(int argc, char *argv[])
{
    bool trace = argc == 2 && strcmp(argv[1], "-t") == 0;
    solution1(trace);
    solution2(trace);
    solution3(trace);
    solution4(trace);
}