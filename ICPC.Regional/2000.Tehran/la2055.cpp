// 2000 Tehran: Color Tunnels
// ACM-ICPC Live Archive 2055
// POJ 1685

#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const int N = 100 + 5;
const double INF = 1e30;
struct POINT{
	double x, y;
	void read(){
		scanf("%lf%lf", &x, &y);
	}
};

int seq[N], color[N];
double dp[N][N][2], len[N];
POINT tunnels[N][2];

double dis(POINT &p1, POINT &p2){
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

void solve(){
	POINT begin, end;
	int ns, nt;
	begin.read(), end.read();
	scanf("%d", &ns);
	for (int i = 0; i < ns; i++)
		scanf("%d", &seq[i]);	

	scanf("%d", &nt);
	for (int i = 0; i < nt; i++){
		tunnels[i][0].read(), tunnels[i][1].read();
		len[i] = dis(tunnels[i][0], tunnels[i][1]);
		scanf("%d", &color[i]);
	}

	for (int i = 0; i < ns; i++){
		for (int j = 0; j < nt; j++){
			dp[i][j][0] = dp[i][j][1] = INF;
			if (seq[i] != color[j])
				continue;

			if (i == 0){
				dp[i][j][0] = dis(begin, tunnels[j][1]) + len[j];
				dp[i][j][1] = dis(begin, tunnels[j][0]) + len[j];
			}
			else{
				for (int k = 0; k < nt; k++){
					dp[i][j][0] = min(dp[i][j][0], dp[i - 1][k][0] + dis(tunnels[k][0], tunnels[j][1]) + len[j]);
					dp[i][j][1] = min(dp[i][j][1], dp[i - 1][k][0] + dis(tunnels[k][0], tunnels[j][0]) + len[j]);

					dp[i][j][0] = min(dp[i][j][0], dp[i - 1][k][1] + dis(tunnels[k][1], tunnels[j][1]) + len[j]);
					dp[i][j][1] = min(dp[i][j][1], dp[i - 1][k][1] + dis(tunnels[k][1], tunnels[j][0]) + len[j]);
				}
			}
		}
	}
	double ans = INF;
	for (int i = 0; i < nt; i++){
		ans = min(ans, dp[ns - 1][i][0] + dis(end, tunnels[i][0]));
		ans = min(ans, dp[ns - 1][i][1] + dis(end, tunnels[i][1]));
	}
	printf("%.3lf\n", ans);
}
int main(){
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}
