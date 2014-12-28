// CII 4500
// 2009 Dhaka: Traffic Jam
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define EPS 1e-8
inline int sgn(double x) {
	return (x < -EPS) ? -1 : x > EPS;
}
#define NP 30
struct POINT {
	double x, y;
	POINT() {
	}
	POINT(double x, double y) :
		x(x), y(y) {
	}
	POINT operator +(const POINT & b) {
		return POINT(x + b.x, y + b.y);
	}
	POINT operator -(const POINT & b) {
		return POINT(x - b.x, y - b.y);
	}
	POINT operator /(const double & v) {
		return POINT(x / v, y / v);
	}
	POINT operator *(const double & v) {
		return POINT(x * v, y * v);
	}
	bool operator ==(const POINT &p) {
		return sgn(x - p.x) == 0 && sgn(y - p.y) == 0;
	}
	bool operator !=(const POINT &p) {
		return sgn(x - p.x) != 0 || sgn(y - p.y) != 0;
	}
	double abs() {
		return sqrt(x * x + y * y);
	}
	void get() {
		scanf("%lf%lf", &x, &y);
	}
};
double sqr(double x) {
	return x * x;
}
double dis(const POINT &p1, const POINT &p2) {
	return sqrt(sqr(p1.x - p2.x) + sqr(p1.y - p2.y));
}
inline double cross(POINT &o, POINT &a, POINT &b) {
	return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}
inline double dot(POINT &o, POINT &a, POINT &b) {
	return (a.x - o.x) * (b.x - o.x) + (a.y - o.y) * (b.y - o.y);
}
int between(POINT &o, POINT &a, POINT &b) {
	return sgn(dot(o, a, b)) != 1;
}
POINT rotate(const POINT &p, double sina, double cosa) {
	POINT ret;
	ret.x = p.x * cosa - p.y * sina;
	ret.y = p.x * sina + p.y * cosa;
	return ret;
}
int line_inter(POINT &a, POINT &b, POINT &c, POINT &d, POINT &cp) {
	double u = cross(a, b, c), v = cross(b, a, d);
	if (sgn(u + v)) {
		cp = (c * v + d * u) / (u + v);
		return 1;
	}
	return 0;
}

struct SEGNODE {
	int id;
	double dis;
	SEGNODE() {
	}
	SEGNODE(int id, double dis) :
		id(id), dis(dis) {
	}
	bool operator<(const SEGNODE &node) const {
		return dis < node.dis;
	}
};

// GRAPH SECTION
#define N 10001
#define M 200005

int V[N], D[N];
struct EDGE {
	int a, b, next;
	double w;
};
EDGE E[M];
int G[N], tot;
void addedge(int a, int b, double w) {
	EDGE x = { a, b, G[a], w };
	E[tot] = x;
	G[a] = tot++;
}
void add(int a, int b, double dis) {
	addedge(a, b, dis);
	addedge(b, a, dis);
}

// END OF GRAPH SECTION

int n;
POINT p[NP];
vector<SEGNODE> seglst[NP];
double f;

// DIJSKTRA SECTION
int dest;
double dist[N];
struct NODE {
	int b;
	double w;
	NODE() {
	}
	NODE(int b, double w) :
		b(b), w(w) {
	}
	bool operator <(const NODE &n) const {
		return w > n.w;
	}
};

double dij() {
	int i;
	priority_queue<NODE> Q;
	for (i = 0; i < n; i++)
		dist[i] = 1e50;
	dist[0] = 0;
	Q.push(NODE(0, 0));
	while (!Q.empty()) {
		NODE top = Q.top();
		Q.pop();
		if (top.b == dest) return top.w;
		for (i = G[top.b]; ~i; i = E[i].next) {
			if (dist[E[i].b] > top.w + E[i].w) {
				dist[E[i].b] = top.w + E[i].w;
				Q.push(NODE(E[i].b, top.w + E[i].w));
			}
		}
	}
	return -1;
}
// END OF DIJSKTRA SECTION

double solve() {
	int i, j, cnt;
	double sina, cosa;
	cosa = 1 / f;
	sina = sqrt(1 - sqr(cosa));
	dest = n;
	cnt = ++n;

	for (i = 0; i < n; i++) {
		p[i].get();
		seglst[i].clear();
	}

	// INIT THE GRAPH
	memset(G, -1, sizeof(G));
	tot = 0;

	// FIND THE INTEREST POINTS
	for (i = 0; i < n; i++) {
		// From one point fly to another point
		for (j = 0; j < i; j++)
			add(i, j, dis(p[i], p[j]) * f);
		for (j = 0; j < n - 1; j++) {
			if (i == j || i == j + 1) continue;
			POINT v1 = p[j + 1] - p[j], v2, p1, p2, pit;
			// Direction 1
			v2 = rotate(v1, sina, cosa);
			p1 = p[i], p2 = p[i] + v2;
			if (line_inter(p1, p2, p[j], p[j + 1], pit)) {
				if (between(pit, p[j], p[j + 1])) {
					seglst[j].push_back(SEGNODE(cnt, dis(pit, p[j])));
					add(i, cnt++, dis(p[i], pit) * f);
				}
			}
			// Direction 2
			v2 = rotate(v1, -sina, cosa);
			p1 = p[i], p2 = p[i] + v2;
			if (line_inter(p1, p2, p[j], p[j + 1], pit)) {
				if (between(pit, p[j], p[j + 1])) {
					seglst[j].push_back(SEGNODE(cnt, dis(pit, p[j])));
					add(i, cnt++, dis(p[i], pit) * f);
				}
			}
		}
	}
	for (i = 0; i < n - 1; i++) {
		sort(seglst[i].begin(), seglst[i].end());
		int sz = (int) seglst[i].size();
		if (sz >= 2) for (j = 0; j < sz - 1; j++) {
			addedge(seglst[i][j].id, seglst[i][j + 1].id, seglst[i][j + 1].dis - seglst[i][j].dis);
		}
		if (sz >= 1) {
			addedge(i, seglst[i][0].id, seglst[i][0].dis);
			addedge(seglst[i][sz - 1].id, i + 1, dis(p[i], p[i + 1]) - seglst[i][sz - 1].dis);
		} else {
			addedge(i, i + 1, dis(p[i], p[i + 1]));
		}
	}
	n = cnt;
	return dij();
}

int main() {
	int ca = 1;
	while (scanf("%d%lf", &n, &f) && n) {
		printf("Case %d: %lf\n", ca++, solve());
	}
	return 0;
}

