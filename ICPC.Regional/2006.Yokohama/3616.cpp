// 2006 Yokohama: How I Wonder What You Are!
// POJ 3129
// ACM-ICPC Live Archive 3616
#include <cmath>
#include <cstdio>
#define N 1000

struct POINT {
	double x, y, z, a;
	double abs() {
		return sqrt(x * x + y * y + z * z);
	}
};

int ns, nt;
POINT stars[N], telescopes[N];

int check_visible(int i, int j) {
	double v = stars[i].x * telescopes[j].x + stars[i].y * telescopes[j].y + stars[i].z * telescopes[j].z;
	v = v / stars[i].abs() / telescopes[j].abs();
	if (v < 0)
		return 0;
	return acos(v) < telescopes[j].a;
}

int main() {
	while (scanf("%d", &ns) && ns) {
		int ans = 0;
		for (int i = 0; i < ns; i++)
			scanf("%lf%lf%lf", &stars[i].x, &stars[i].y, &stars[i].z);

		scanf("%d", &nt);
		for (int i = 0; i < nt; i++)
			scanf("%lf%lf%lf%lf", &telescopes[i].x, &telescopes[i].y, &telescopes[i].z, &telescopes[i].a);

		for (int i = 0; i < ns; i++)
			for (int j = 0; j < nt; j++)
				if (check_visible(i, j)) {
					ans++;
					break;
				}
		printf("%d\n", ans);
	}
	return 0;
}
