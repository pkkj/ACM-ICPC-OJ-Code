// 2008 Aizu: Common Polynomial
// ACM-ICPC Live Archive 4165
#include <cstdio>
#include <cstring>
#include <stack>
#include <cmath>
#include <algorithm>
using namespace std;
#define N 10000
#define DEG 15
 
int gcd(int m, int n) {
	int r;
	if (m < 0) m = -m;
	if (n < 0) n = -n;
	while (n > 0) {
		r = m % n;
		m = n;
		n = r;
	}
	return m;
}
int lcm(int a, int b) {
	if (a == 0 || b == 0) return 0;
	return a / gcd(a, b) * b;
}
// Frac class
struct FRAC {
	int z, m;
	FRAC() {
		z = 0, m = 1;
	}
	FRAC(int x) {
		z = x, m = 1;
	}
	FRAC(int z, int m) :
		z(z), m(m) {
	}
	void print() {
		if (z < 0 && m < 0) z = -z, m = -m;
		printf("(%d/%d)", z, m);
	}
	bool iszero() {
		return z == 0;
	}
};
FRAC operator +(const FRAC &a, const FRAC &b) {
	FRAC ans;
	int g;
	ans.m = a.m * b.m;
	ans.z = a.z * b.m + b.z * a.m;
	g = gcd(ans.m, ans.z);
	ans.m /= g, ans.z /= g;
	return ans;
}
FRAC operator -(const FRAC &a, const FRAC &b) {
	FRAC ans;
	int g;
	ans.m = a.m * b.m;
	ans.z = a.z * b.m - b.z * a.m;
	g = gcd(ans.m, ans.z);
	ans.m /= g, ans.z /= g;
	return ans;
}
 
FRAC operator *(const FRAC &a, const FRAC &b) {
	FRAC ans;
	int g;
	ans.m = a.m * b.m, ans.z = a.z * b.z;
	g = gcd(ans.m, ans.z);
	ans.m /= g, ans.z /= g;
	return ans;
}
FRAC operator /(const FRAC &a, const FRAC &b) {
	FRAC tmp = FRAC(b.m, b.z);
	return a * tmp;
}
// End of frac class
struct POLY {
	FRAC xi[DEG];
	int l;
	POLY() {
		for (int i = 0; i < DEG; i++)
			xi[i] = FRAC();
		l = 0;
	}
	void print() {
		int st = 1, i, g, lc, pool[20];
		lc = xi[l].m;
		for (i = l - 1; i >= 0; i--)
			lc = lcm(lc, abs(xi[i].m));
		for (i = l; i >= 0; i--)
			pool[i] = xi[i].z * lc / xi[i].m;
		if (l == 0) pool[0] = 1;
		else {
			g = abs(pool[l]);
			for (i = l - 1; i >= 0; i--)
				g = gcd(g, abs(pool[i]));
			if (pool[l] < 0) g = -g;
			for (i = 0; i <= l; i++)
				pool[i] /= g;
		}
		while (xi[l].iszero() && l > 0)
			l--;
		if (l == 0) {
			printf("%d\n", pool[0]);
			return;
		}
		for (i = l; i >= 0; i--) {
			if (pool[i] == 0) continue;
			if (st) {
				if (i == l && pool[i] < 0) printf("-");
				st = 0;
			} else if (i > 0 || (i == 0 && pool[0] != 0)) printf("%c", pool[i] >= 0 ? '+' : '-');
			if ((i >= 1 && abs(pool[i]) != 1) || i == 0) printf("%d", abs(pool[i]));
			if (i) printf("x");
			if (i > 1) printf("^%d", i);
		}
		printf("\n");
	}
	void debug() {
		printf("debug %d:", l);
		for (int i = l; i >= 0; i--) {
			xi[i].print();
		}
		printf("\n");
	}
	FRAC &operator[](int i) {
		return xi[i];
	}
	bool iszero() {
		return l == 0 && xi[0].iszero();
	}
};
POLY operator *(const POLY &p1, const POLY &p2) {
	POLY ans = POLY();
	ans.l = p1.l + p2.l;
	for (int i = 0; i <= p1.l; i++)
		for (int j = 0; j <= p2.l; j++) {
			ans[i + j] = ans[i + j] + p1.xi[i] * p2.xi[j];
		}
	return ans;
}
POLY operator +(const POLY &p1, const POLY &p2) {
	POLY ans = POLY();
	ans.l = max(p1.l, p2.l);
	for (int i = 0; i <= ans.l; i++)
		ans[i] = p1.xi[i] + p2.xi[i];
	return ans;
}
POLY operator -(const POLY &p1, const POLY &p2) {
	POLY ans = POLY();
	ans.l = max(p1.l, p2.l);
	for (int i = 0; i <= ans.l; i++)
		ans[i] = p1.xi[i] - p2.xi[i];
	return ans;
}
 
POLY operator%(const POLY &p1, const POLY &p2) {
	POLY ans = POLY(), remain = POLY();
	int i, j, k, top;
	top = p1.l;
	ans.l = p1.l - p2.l;
	for (i = 0; i <= p1.l; i++)
		remain[i] = p1.xi[i];
	for (i = p1.l - p2.l; i >= 0; i--, top--) {
		FRAC x = remain.xi[top] / p2.xi[p2.l];
		//printf("%.3lf ", x);
		for (j = top, k = p2.l; k >= 0; k--, j--) {
			remain[j] = remain[j] - (x * p2.xi[k]);
		}
	}
	remain.l = 13;
	while (remain[remain.l].iszero() && remain.l > 0)
		remain.l--;
	return remain;
}
POLY gcd(POLY m, POLY n) {
	POLY r;
	while (!n.iszero()) {
		r = m % n;
		m = n;
		n = r;
	}
	return m;
}
char s1[N], s2[N];
 
int pow(int x, int e) {
	int ans = 1;
	if (e == 0) return 1;
	for (int i = 1; i <= e; i++)
		ans *= x;
	return ans;
}
bool isdigit(char ch) {
	return ch >= '0' && ch <= '9';
}
POLY readsingle(char *s, int &pos) {
	char num[6], ss[100];
	int a = 0, b = 0, i, len = 0, j;
	int xpos = -1, mpos = -1;
	POLY ret = POLY();
	for (i = pos;; i++) {
		if (s[i] == '(' || s[i] == ')' || s[i] == '+' || (s[i] == '-' && i != pos) || s[i] == 0) break;
		ss[len++] = s[i];
	}
	ss[len] = 0;
	pos = i;
	for (i = 0; i < len; i++) {
		if (ss[i] == 'x') xpos = i;
		if (ss[i] == '^') mpos = i;
	}
 
	// I. ax^b
	if (xpos != -1 && mpos != -1) {
		if (xpos == 0) a = 1;
		else {
			for (j = 0, i = 0; i < xpos; i++)
				num[j++] = ss[i];
			num[j] = 0;
			sscanf(num, "%d", &a);
		}
		for (j = 0, i = mpos + 1; i < len; i++)
			num[j++] = ss[i];
		num[j] = 0;
		sscanf(num, "%d", &b);
	}
	// II. a^b
	if (xpos == -1 && mpos != -1) {
		for (j = 0, i = 0; i < mpos; i++)
			num[j++] = ss[i];
		num[j] = 0;
		sscanf(num, "%d", &a);
		for (j = 0, i = mpos + 1; i < len; i++)
			num[j++] = ss[i];
		num[j] = 0;
		sscanf(num, "%d", &b);
		a = pow(a, b);
		b = 0;
	}
	// III ax
	if (xpos != -1 && mpos == -1) {
		if (xpos == 0) a = 1;
		else if (xpos == 1 && ss[0] == '-') a = -1;
		else {
			for (j = 0, i = 0; i < xpos; i++)
				num[j++] = ss[i];
			num[j] = 0;
			sscanf(num, "%d", &a);
		}
		b = 1;
	}
	// IV a or -
	if (xpos == -1 && mpos == -1) {
		if (len == 1 && ss[0] == '-') a = -1;
		else sscanf(ss, "%d", &a);
		b = 0;
	}
	ret[b] = a;
	ret.l = b;
	return ret;
}
struct LNODE {
	POLY p;
	char op;
	int mi;
};
 
LNODE list[300];
int lst_tot;
void move(char *s) {
	int len = strlen(s);
	for (int i = len - 1; i >= 0; i--)
		s[i + 1] = s[i];
	s[len + 1] = 0;
}
void parse(char *s) {
	int len, i;
	lst_tot = 0;
	if (s[0] == '-') {
		move(s);
		s[0] = '0';
	}
	len = strlen(s);
	for (i = 0; i < len;) {
		if (s[i] == '(' || s[i] == '+' || (s[i] == '-' && i > 0 && s[i - 1] != '(')) {
			if (s[i] == '(') {
				if (lst_tot > 0 && (list[lst_tot - 1].op == ')' || list[lst_tot - 1].op == 'x')) {
					list[lst_tot++].op = '*';
				}
			}
			list[lst_tot].op = s[i];
			i++, lst_tot++;
		} else if (s[i] == ')') {
			list[lst_tot].op = s[i];
			if (s[i + 1] == '^') {
				list[lst_tot].mi = s[i + 2] - '0';
				i += 3;
			} else {
				i++;
				list[lst_tot].mi = 1;
			}
			lst_tot++;
		} else {
			list[lst_tot].op = 'x';
			list[lst_tot].p = readsingle(s, i);
			lst_tot++;
		}
	}
	list[lst_tot].op = 0;
}
 
// Expression Tree
struct NODE {
	int l, r;
	char op;
	POLY p;
	int mi;
	NODE() {
	}
	NODE(int l, int r, char op) :
		l(l), r(r), op(op) {
		mi = 1;
	}
	NODE(int l, int r, char op, POLY p) :
		l(l), r(r), op(op), p(p) {
		mi = 1;
	}
};
NODE T[200];
int tot, pos;
 
int newnode(char op, int l, int r, POLY p) {
	T[tot] = NODE(l, r, op, p);
	return tot++;
}
int newnode(char op, int l, int r) {
	T[tot] = NODE(l, r, op);
	return tot++;
}
int parse_exp();
int parse_factor();
int parse_term();
int parse_factor() {
	if (list[pos].op == '(') {
		pos++;
		int ret = parse_exp();
		T[ret].mi = list[pos].mi;
		pos++;
		return ret;
	}
	int ret = newnode(list[pos].op, -1, -1, list[pos].p);
	pos++;
	return ret;
}
int parse_term() {
	int cur = parse_factor();
	while (list[pos].op == '*' || list[pos].op == '/') {
		char op = list[pos++].op;
		cur = newnode(op, cur, parse_factor());
	}
	return cur;
}
int parse_exp() {
	int cur = parse_term();
	while (list[pos].op == '+' || list[pos].op == '-') {
		char op = list[pos++].op;
		cur = newnode(op, cur, parse_term());
	}
	return cur;
}
POLY dfs(int p) {
	POLY ans, a2;
	if (T[p].op == '+') ans = dfs(T[p].l) + dfs(T[p].r);
	else if (T[p].op == '-') ans = dfs(T[p].l) - dfs(T[p].r);
	else if (T[p].op == '*') ans = dfs(T[p].l) * dfs(T[p].r);
	else if (T[p].op == 'x') ans = T[p].p;
	a2 = ans;
	for (int i = 1; i < T[p].mi; i++)
		ans = ans * a2;
	return ans;
}
// End of expression tree
void solve() {
	POLY p1, p2;
	int root;
	pos = tot = 0;
	memset(list, 0, sizeof(list));
	parse(s1);
	root = parse_exp();
	p1 = dfs(root);
	pos = tot = 0;
	memset(list, 0, sizeof(list));
	parse(s2);
	root = parse_exp();
	p2 = dfs(root);
	POLY ans = gcd(p1, p2);
	ans.print();
}
 
bool read() {
	gets(s1);
	if (s1[0] == '.') return 0;
	gets(s2);
	return 1;
}
int main() {
	while (read())
		solve();
	return 0;
}