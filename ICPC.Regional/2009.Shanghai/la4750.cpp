// 2009 Shanghai: Heroes Arrangement
// ACM-ICPC Live Archive 4750
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
#define N 50
#define EPS 1e-8
#define DIS 1e4
inline int sgn(double x) {
	return (x < -EPS) ? -1 : x > EPS;
}

struct POINT {
	double x, y, z;
	POINT() :
			x(0), y(0), z(0) {
	}
	POINT(double x, double y, double z) :
			x(x), y(y), z(z) {
	}
	void input() {
		scanf("%lf%lf%lf", &x, &y, &z);
	}
	double norm() {
		return sqrt(x * x + y * y + z * z);
	}
	POINT toLen(double d) {
		double m = norm();
		return POINT(x * d / m, y * d / m, z * d / m);
	}
};
POINT operator-(const POINT &a, const POINT &b) {
	return POINT(a.x - b.x, a.y - b.y, a.z - b.z);
}

POINT cross(const POINT &a, const POINT &b) {
	return POINT(a.y * b.z - b.y * a.z, -a.x * b.z + b.x * a.z, a.x * b.y - b.x * a.y);
}

double dot(const POINT &a, const POINT &b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

int segment_cross_plane(const POINT &s1, const POINT &s2, const POINT &p1, const POINT &p2, const POINT &p3) {
	POINT nvec = cross(p2 - p1, p3 - p1);
	return sgn(dot(nvec, s2 - p1) * dot(nvec, s1 - p1));
}

bool segment_cross_triangle(const POINT &s1, const POINT &s2, const POINT &p1, const POINT &p2, const POINT &p3) {
	return segment_cross_plane(s1, s2, p1, p2, p3) < 0 && segment_cross_plane(p1, p2, s1, s2, p3) < 0
			&& segment_cross_plane(p1, p3, s1, s2, p2) < 0 && segment_cross_plane(p2, p3, s1, s2, p1) < 0;
}

bool dot_inside_triangle(const POINT &p, const POINT &p1, const POINT &p2, const POINT &p3) {
	return sgn(cross(p2 - p1, p3 - p1).norm() - cross(p1 - p, p2 - p).norm() - cross(p1 - p, p3 - p).norm() - cross(p2 - p, p3 - p).norm())
			== 0;
}

int g[N][N], n;
POINT triangle[N][4];
bool conflict(int u, int v) {
	if (segment_cross_triangle(POINT(), triangle[u][0].toLen(DIS), triangle[v][0], triangle[v][1], triangle[v][2]))
		return true;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (segment_cross_triangle(triangle[u][i], triangle[u][i + 1], POINT(), triangle[v][j].toLen(DIS),
					triangle[v][j + 1].toLen(DIS)))
				return true;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (dot_inside_triangle(triangle[u][i], POINT(), triangle[v][j].toLen(DIS), triangle[v][j + 1].toLen(DIS)))
				return true;

	return false;
}

// MaxClique
int dp[N], best;
int dfs(int n, int* u, int size) {
	int i, j, vn, v[N];
	if (n) {
		if (size + dp[u[0]] <= best)
			return 0;
		for (i = 0; i < n + size - best && i < n; i++) {
			for (j = i + 1, vn = 0; j < n; ++j)
				if (g[u[i]][u[j]])
					v[vn++] = u[j];
			if (dfs(vn, v, size + 1))
				return 1;
		}
	} else if (size > best) {
		best = size;
		return 1;
	}
	return 0;
}

int maxclique() {
	int i, j, vn, v[N];
	best = 0;
	for (dp[i = n - 1] = 0; i >= 0; --i) {
		for (vn = 0, j = i + 1; j < n; ++j)
			if (g[i][j])
				v[vn++] = j;
		dfs(vn, v, 1);
		dp[i] = best;
	}
	return best;
}

// End of MaxClique
int solve() {
	int i, j;
	scanf("%d", &n);
	for (i = 0; i < n; i++)
		for (j = 0; j < 3; j++) {
			triangle[i][j].input();
			triangle[i][3] = triangle[i][0];
		}

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++)
			g[i][j] = 1;
		g[i][i] = 0;
	}
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++) {
			if (!g[i][j])
				continue;
			if (conflict(i, j))
				g[i][j] = g[j][i] = 0;
		}
	return maxclique();
}

int main() {
	int T;
	scanf("%d", &T);
	for (int ca = 1; ca <= T; ca++)
		printf("Case #%d: %d\n", ca, solve());
	return 0;
}
