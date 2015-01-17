// 2006 Tokyo: Power Calculus
// ACM-ICPC Live Archive 3621
// POJ 3134
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
#define N 1005
#define M 1000
int ans[N];
struct NODE {
	short step, mi, get[15], gz;
	bool operator <(const NODE &n) const {
		return step > n.step;
	}
};
priority_queue<NODE> Q;
 
void precalc() {
	int i;
	NODE st;
	st.gz = 1, st.get[0] = 1;
	st.step = 0, st.mi = 1;
	Q.push(st);
	for (i = 1; i <= M; i++)
		ans[i] = 100000;
	while (!Q.empty()) {
		NODE top = Q.top();
		Q.pop();
		if (top.step < ans[top.mi]) ans[top.mi] = top.step;
		for (i = 0; i < top.gz; i++) {
			NODE nst = top;
			nst.mi += top.get[i];
			if (nst.mi > M) continue;
			nst.step++;
			if (nst.step < ans[nst.mi] && nst.gz < 14) {
				nst.get[nst.gz++] = nst.mi;
				Q.push(nst);
			}
		}
 
		for (i = 0; i < top.gz; i++) {
			NODE nst = top;
			nst.mi -= top.get[i];
			if (nst.mi < 2) continue;
			nst.step++;
			if (nst.step < ans[nst.mi] && nst.gz < 14) {
				nst.get[nst.gz++] = nst.mi;
				Q.push(nst);
			}
		}
	}
}
 
int main() {
	precalc();
	int n;
	while (scanf("%d", &n) && n)
		printf("%d\n", ans[n]);
	return 0;
}