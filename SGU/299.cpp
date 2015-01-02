// SGU 299 Triangle
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
 
#define MAX_L 300
#define BASE 1000
#define N 1005
struct BIGINT {
	int d[MAX_L], len;
	BIGINT() {
		memset(d, 0, sizeof(d));
		len = 0;
	}
	BIGINT operator =(const char * str) {
		int i, j, k, len = strlen(str);
		int mul[] = { 1, 10, 100 };
		memset(d, 0, sizeof(d));
		if (len == 1 && str[0] == '0') {
			d[this->len = 0] = 0;
			return *this;
		}
		for (k = -1, j = 0, i = len - 1; i >= 0; i--, j++) {
			if (j % 3 == 0) k++;
			d[k] += (str[i] - '0') * mul[j % 3];
		}
		this->len = k + 1;
		return *this;
	}
	void print() {
		int i;
		if (len == 0) {
			printf("0");
			return;
		}
		printf("%d", d[len - 1]);
		for (i = len - 2; i >= 0; i--) {
			if (d[i] >= 100) printf("%d", d[i]);
			else if (d[i] >= 10) printf("0%d", d[i]);
			else printf("00%d", d[i]);
		}
	}
};
 
bool operator <(const BIGINT &n1, const BIGINT &n2) {
	if (n1.len != n2.len) return n1.len < n2.len;
	for (int i = n1.len - 1; i >= 0; i--)
		if (n1.d[i] != n2.d[i]) return n1.d[i] < n2.d[i];
	return false;
}
BIGINT bigint_add(const BIGINT &a, const BIGINT &b);
char cmd[1000];
BIGINT list[N];
int main() {
	int n, i;
	scanf("%d\n", &n);
	for (i = 0; i < n; i++) {
		gets(cmd);
		list[i] = cmd;
	}
	sort(list, list + n);
	for (i = 2; i < n; i++) {
		if (list[i] < bigint_add(list[i - 1], list[i - 2])) {
			list[i - 2].print();
			printf(" ");
			list[i - 1].print();
			printf(" ");
			list[i].print();
			printf("\n");
			return 0;
		}
	}
	puts("0 0 0");
	return 0;
}
 
BIGINT bigint_add(const BIGINT &a, const BIGINT &b) {
	BIGINT r, pb, ps;
	int i;
	if (a.len > b.len) pb = a, ps = b;
	else pb = b, ps = a;
	for (i = 0; i < pb.len; i++) {
		r.d[i] = r.d[i] + pb.d[i] + ps.d[i];
		if (r.d[i] >= BASE) {
			r.d[i + 1]++;
			r.d[i] %= BASE;
		}
	}
	r.len = pb.len + 2;
	while (!r.d[r.len - 1])
		r.len--;
	return r;
}
