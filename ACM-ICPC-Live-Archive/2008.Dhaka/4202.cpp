// CII 4202
// 2008 Dhaka: Schedule of a Married Man
#include <cstdio>
int main() {
	int T, h1, m1, h2, m2, ca = 1;
	int t1, t2, t3, t4;
	scanf("%d", &T);
	while (T--) {
		scanf("%d:%d %d:%d", &h1, &m1, &h2, &m2);
		t1 = h1 * 60 + m1;
		t2 = h2 * 60 + m2;
		scanf("%d:%d %d:%d", &h1, &m1, &h2, &m2);
		t3 = h1 * 60 + m1;
		t4 = h2 * 60 + m2;
 
		printf("Case %d: ", ca++);
		if (t1 > t4 || t2 < t3) printf("Hits Meeting\n");
		else printf("Mrs Meeting\n");
	}
}
