// CII 4204
// 2008 Dhaka: Chemical Plant
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
#define NE 200005
struct EDGEIN {
	int a, b, sst, sct, dst, dct;
	void get() {
		scanf("%d%d%d%d%d%d", &a, &b, &sst, &sct, &dst, &dct);
	}
};
 
struct TIME {
	int pt, ti;
	TIME() {
	}
	TIME(int pt, int ti) :
		pt(pt), ti(ti) {
	}
	bool operator <(const TIME &t) const {
		if (pt != t.pt) return pt < t.pt;
		return ti < t.ti;
	}
	bool operator ==(const TIME &t) const {
		return pt == t.pt && ti == t.ti;
	}
};
 
struct EDGE {
	int b, w, next;
};
int G[NE], tot, n, m, S, W, T, ct, dest;
EDGEIN EIN[NE];
TIME TE[NE];
EDGE E[NE];
void addedge(int a, int b, int w) {
	EDGE e = { b, w, G[a] };
	E[tot] = e;
	G[a] = tot++;
}
void read() {
	int ct = 0, i;
	scanf("%d%d\n", &S, &T);
	for (i = 0; i < m; i++) {
		EIN[i].get();
		TE[ct++] = TIME(EIN[i].b, EIN[i].dct);
		if (EIN[i].dct > T) i--, m--;
	}
	TE[ct++] = TIME(1, 0);
	TE[ct++] = TIME(S, T);
 
	sort(TE, TE + ct);
	ct = unique(TE, TE + ct) - TE;
	tot = 0;
	memset(G, -1, sizeof(G));
	for (i = 0; i < m; i++) {
		TIME *p1 = upper_bound(TE, TE + ct, TIME(EIN[i].a, EIN[i].sst));
		TIME *p2 = lower_bound(TE, TE + ct, TIME(EIN[i].b, EIN[i].dct));
		if (p1 == TE) continue;
		p1--;
		if (p1->pt != EIN[i].a) continue;
		addedge(p1 - TE, p2 - TE, EIN[i].sct - p1->ti + EIN[i].dct - EIN[i].dst);
	}
	for (i = 1; i < ct; i++) {
		if (TE[i].pt != TE[i - 1].pt) continue;
		addedge(i - 1, i, TE[i].ti - TE[i - 1].ti);
	}
	dest = lower_bound(TE, TE + ct, TIME(S, T)) - TE;
}
int dist[NE];
struct NODE {
	int b, w;
	NODE() {
	}
	NODE(int b, int w) :
		b(b), w(w) {
	}
	bool operator <(const NODE &n) const {
		return w > n.w;
	}
};
int dij() {
	int i;
	priority_queue<NODE> Q;
	memset(dist, -1, sizeof(dist));
	dist[0] = 0;
	Q.push(NODE(0, 0));
	while (!Q.empty()) {
		NODE top = Q.top();
		Q.pop();
		if (top.b == dest) return top.w;
		for (i = G[top.b]; ~i; i = E[i].next) {
			if (dist[E[i].b] == -1 || dist[E[i].b] > top.w + E[i].w) if (top.w + E[i].w <= W) {
				dist[E[i].b] = top.w + E[i].w;
				Q.push(NODE(E[i].b, top.w + E[i].w));
			}
		}
	}
	return W;
}
int solve() {
	read();
	return W - dij();
}
int main() {
	int ca = 1;
	while (scanf("%d%d%d\n", &n, &m, &W) && n)
		printf("Plant %d: %d\n", ca++, solve());
	return 0;
}
