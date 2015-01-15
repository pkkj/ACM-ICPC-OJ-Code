// 2005 Japan: Mobile Computing
// CII 3403
// POJ 2743
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

#define N 15
int stones[N], s, childCnt;
double r, ans, mostLeft, mostRight, pos[N];

struct TREE {
	int left[N], right[N], count[N], size;
	queue<int> next;
	TREE() : size(1) {
		memset(left, -1, sizeof(left));
		memset(right, -1, sizeof(right));
	}
};

void findRange(TREE &t, int node, double parentPos) {
	if (t.left[node] == -1 && t.right[node] == -1)
		mostRight = max(mostRight, parentPos), mostLeft = min(mostLeft, parentPos);
	else {
		findRange(t, t.left[node], parentPos - pos[node]);
		findRange(t, t.right[node], parentPos + (1 - pos[node]));
	}
}

int calcWeight(TREE &t, int node) {
	if (t.left[node] == -1 && t.right[node] == -1)
		return stones[childCnt++];
	else {
		int weightLeft = calcWeight(t, t.left[node]);
		int weightRight = calcWeight(t, t.right[node]);
		pos[node] = (double) weightRight / (double) (weightLeft + weightRight);
		return weightLeft + weightRight;
	}
}
void compute(TREE &t) {
	do {
		childCnt = 0;
		calcWeight(t, 0);
		mostLeft = 1e20, mostRight = -1e20;
		findRange(t, 0, 0.0);
		double width = mostRight - mostLeft;
		if (width <= r && width > ans)
			ans = width;
	} while (next_permutation(stones, stones + s));
}

void addChild(TREE &t, bool goLeft, int cur, int num) {
	int child = t.size++;
	goLeft ? t.left[cur] = child : t.right[cur] = child;
	t.count[child] = num;
	if (num > 1)
		t.next.push(child);
}

void construct(TREE t) {
	if (t.next.empty()) {
		compute(t);
		return;
	}

	int cur = t.next.front();
	t.next.pop();

	// A small optimization. At the root we can mirror the tree. So this might reduce some searching
	int maxCount = t.count[cur];
	if (cur == 0)
		maxCount = maxCount / 2 + 1;
	for (int i = 1; i < maxCount; i++) {
		TREE newT = t;
		addChild(newT, true, cur, i);
		addChild(newT, false, cur, t.count[cur] - i);
		construct(newT);
	}
}
void solve() {
	ans = -1;
	scanf("%lf%d", &r, &s);
	for (int i = 0; i < s; i++)
		scanf("%d", &stones[i]);
	sort(stones, stones + s);
	TREE t;
	t.count[0] = s;
	t.next.push(0);
	construct(t);
	if (s == 1)
		ans = 0;
	ans < 0 ? printf("-1\n") : printf("%.10lf\n", ans);
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
}

