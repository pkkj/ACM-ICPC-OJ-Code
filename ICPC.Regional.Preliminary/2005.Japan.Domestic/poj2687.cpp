// 2005 Japan Domestic: Earth Observation with a Mobile Robot Team
// POJ 2687
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
using namespace std;
#define N 1005
#define EPS 1e-6
inline int sgn(double x) {
	return (x < -EPS) ? -1 : x > EPS;
}

struct POINT {
	double x, y, t;
	POINT() {}
	POINT(double t, double x, double y) : t(t), x(x), y(y) {}
};
struct EVENT {
	int a, b, type;
	double time;
	EVENT() {}
	EVENT(int a, int b, int type, double time) : a(a), b(b), type(type), time(time) {}
	bool operator <(const EVENT &other) const {
		if (sgn(other.time - time) == 0)
			return type < other.type;
		return time < other.time;
	}
};
const int IN = 0;
const int OUT = 1;

double sqr(double x) {
	return x * x;
}
double dis(POINT &a, POINT &b) {
	return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}
int n, t, r;
char names[N][10];
vector<POINT> movement[N];
vector<EVENT> events;

// Get the hitting time if robot 1 and robot 2 meet each other during [preTime and curTime]. And update their locations at curTime.
void gethitAndUpdateTime(int r1, int r2, POINT &loc1, POINT &loc2, POINT &v1, POINT &v2, double preTime,
		double curTime) {
	double a = sqr(v1.x - v2.x) + sqr(v1.y - v2.y);
	double b = 2 * (loc1.x - loc2.x) * (v1.x - v2.x) + 2 * (loc1.y - loc2.y) * (v1.y - v2.y);
	double c = sqr(loc1.x - loc2.x) + sqr(loc1.y - loc2.y) - sqr(r);
	double t1 = (-b - sqrt(b * b - 4 * a * c)) / 2 / a;
	double t2 = (-b + sqrt(b * b - 4 * a * c)) / 2 / a;
	if (0 < t1 && t1 < curTime - preTime)
		events.push_back(EVENT(r1, r2, IN, preTime + t1)); // In event
	if (0 < t2 && t2 < curTime - preTime)
		events.push_back(EVENT(r1, r2, OUT, preTime + t2)); // Out event

	double deltaT = curTime - preTime;
	loc1.x = loc1.x + v1.x * deltaT;
	loc2.x = loc2.x + v2.x * deltaT;
	loc1.y = loc1.y + v1.y * deltaT;
	loc2.y = loc2.y + v2.y * deltaT;
}

void processEvent(int r1, int r2) {
	double preTime = 0, curTime;
	POINT loc1 = movement[r1][0], loc2 = movement[r2][0];
	for (int p1 = 1, p2 = 1; p1 < movement[r1].size() || p2 < movement[r2].size();) {
		POINT v1 = movement[r1][p1], v2 = movement[r2][p2];
		if (movement[r1][p1].t == movement[r2][p2].t) {
			curTime = movement[r2][p2].t;
			p1++, p2++;
		} else if (movement[r1][p1].t > movement[r2][p2].t)
			curTime = movement[r2][p2++].t;
		else
			curTime = movement[r1][p1++].t;

		gethitAndUpdateTime(r1, r2, loc1, loc2, v1, v2, preTime, curTime);
		preTime = curTime;
	}
}

bool touch[N][N], has[N], vis[N];
void dfs(int root) {
	vis[root] = has[root] = true;
	for (int i = 0; i < n; i++)
		if (!vis[i] && touch[root][i])
			dfs(i);
}

void solve() {
	memset(touch, 0, sizeof(touch));
	memset(has, 0, sizeof(has));

	// Find out which robots are connected at the beginning
	has[0] = true;
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			if (dis(movement[i][0], movement[j][0]) <= r)
				touch[i][j] = touch[j][i] = true;

	memset(vis, 0, sizeof(vis));
	dfs(0);

	// Find out all the intersecting events between any pair of robots
	for (int r1 = 0; r1 < n; r1++)
		for (int r2 = r1 + 1; r2 < n; r2++)
			processEvent(r1, r2);

	// Sort all the events in chronological order
	sort(events.begin(), events.end());

	// Simulate the intersecting events and data tranfer between robots
	for (int i = 0; i < events.size(); i++) {
		int a = events[i].a, b = events[i].b;
		if (events[i].type == IN) {
			touch[a][b] = touch[b][a] = true;
			if (has[a] || has[b]) {
				memset(vis, 0, sizeof(vis));
				has[a] ? dfs(a) : dfs(b); // DFS to find out all the connected robots holding the data
			}
		} else if (events[i].type == OUT) {
			touch[a][b] = touch[b][a] = false;
		}
	}
	vector<string> ans;
	for (int i = 0; i < n; i++)
		if (has[i])
			ans.push_back(string(names[i]));
	sort(ans.begin(), ans.end());
	for (size_t i = 0; i < ans.size(); i++)
		printf("%s\n", ans[i].c_str());
}
int main() {
	while (scanf("%d%d%d", &n, &t, &r) && n) {
		events.clear();
		for (int i = 0; i < n; i++) {
			scanf("%s", names[i]);
			movement[i].clear();
			for (;;) {
				double pt, px, py;
				scanf("%lf%lf%lf", &pt, &px, &py);
				movement[i].push_back(POINT(pt, px, py));
				if (pt == t)
					break;
			}
		}
		solve();
	}
}

