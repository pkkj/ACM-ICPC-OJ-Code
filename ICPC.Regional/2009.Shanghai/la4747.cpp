// 2009 Shanghai: Exciting Time
// ACM-ICPC Live Archive 4747
#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
#include <stack>
#include <algorithm>
#include <set>
using namespace std;

#define W 30005
const int INF = 1 << 20;
struct SHAPE{
	int w, h;
	SHAPE(){}
	SHAPE(int h, int w) :h(h), w(w){}
};

char shape[7][4][4][5] = {
	{
		{ "XXXX" }, {
			"X",
			"X",
			"X",
			"X",
		}
	}, {
		{
			"X..",
			"XXX",
		}, {
			"XX",
			"X.",
			"X.",
		}, {
			"XXX",
			"..X",
		}, {
			".X",
			".X",
			"XX",
		},
	}, {
		{
			"..X",
			"XXX",
		}, {
			"X.",
			"X.",
			"XX",
		}, {
			"XXX",
			"X..",
		}, {
			"XX",
			".X",
			".X",
		},
	}, {
		{
			"XX",
			"XX",
		}
	}, {
		{
			".XX",
			"XX.",
		}, {
			"X.",
			"XX",
			".X",
		}
	}, {
		{
			".X.",
			"XXX",
		}, {
			"X.",
			"XX",
			"X.",
		}, {
			"XXX",
			".X.",
		}, {
			".X",
			"XX",
			".X",
		},
	}, {
		{
			"XX.",
			".XX",
		}, {
			".X",
			"XX",
			"X.",
		}
	}
};

SHAPE shapeMeta[7][4] = {
	{ SHAPE(1, 4), SHAPE(4, 1) },
	{ SHAPE(2, 3), SHAPE(3, 2), SHAPE(2, 3), SHAPE(3, 2) },
	{ SHAPE(2, 3), SHAPE(3, 2), SHAPE(2, 3), SHAPE(3, 2) },
	{ SHAPE(2, 2) },
	{ SHAPE(2, 3), SHAPE(3, 2) },
	{ SHAPE(2, 3), SHAPE(3, 2), SHAPE(2, 3), SHAPE(3, 2) },
	{ SHAPE(2, 3), SHAPE(3, 2) },
};

int heightAdjust[7][4][4] = {
	{ { 1, 1, 1, 1 }, { 1 } },
	{ { 1, 1, 1 }, { 1, -1 }, { 0, 0, 1 }, { 1, 1 } },
	{ { 1, 1, 1 }, { 1, 1 }, { 1, 0, 0 }, { -1, 1 } },
	{ { 1, 1 } },
	{ { 1, 1, 0 }, { 0, 1 } },
	{ { 1, 1, 1 }, { 1, 0 }, { 0, 1, 0 }, { 0, 1 } },
	{ { 0, 1, 1 }, { 1, 0 } },
};

int widthInfo[7][4][4] = {
	{ { 4 }, { 1, 1, 1, 1 } },
	{ { 1, 3 }, { 2, 1, 1 }, { 3, 1 }, { 1, 1, 2 } },
	{ { 1, 3 }, { 1, 1, 2 }, { 3, 1 }, { 2, 1, 1 } },
	{ { 2, 2 } },
	{ { 2, 2 }, { 1, 2, 1 } },
	{ { 1, 3 }, { 1, 2, 1 }, { 3, 1 }, { 1, 2, 1 } },
	{ { 2, 2 }, { 1, 2, 1 } },
};

char shapeMap[200];
int w, upper[W * 4], lower[W * 4], rows[W * 4];
stack<int> cols[W];
vector<int> clearedRow;
int score[] = { 0, 100, 250, 400, 1000 };

void initShapeMap() {
	shapeMap['I'] = 0, shapeMap['J'] = 1, shapeMap['L'] = 2;
	shapeMap['O'] = 3, shapeMap['S'] = 4, shapeMap['T'] = 5, shapeMap['Z'] = 6;
}

int getHeight(int cur, int gap){
	if (gap > 0){
		for (int i = 0; i < gap; i++)
			cur = upper[cur];
	}
	else if (gap < 0){
		for (int i = 0; i < -gap; i++)
			cur = lower[cur];
	}
	return cur;
}

int fall(char type, int left, int degree){
	int toBeRemoved[4], targetRows[4], toBeRemovedCnt = 0;
	degree /= 90;
	if (type == 'I' || type == 'S' || type == 'Z')
		degree %= 2;
	else if (type == 'O')
		degree /= 4;

	type = shapeMap[type];

	// Find the height
	int height = -1;
	for (int i = 0; i < shapeMeta[type][degree].w; i++){
		int newHeight = getHeight(cols[left + i].top(), heightAdjust[type][degree][i]);
		height = max(height, newHeight);
	}
	for (int h = shapeMeta[type][degree].h - 1; h >= 0; h--)
		targetRows[shapeMeta[type][degree].h - h - 1] = getHeight(height, h);
	
	// Insert the tetromino
	for (int i = 0; i < shapeMeta[type][degree].w; i++){
		for (int j = shapeMeta[type][degree].h - 1; j >= 0; j--){
			if (shape[type][degree][j][i] == 'X'){
				cols[left + i].push(targetRows[j]);
			}
		}
	}

	// Update rows
	for (int i = 0; i < shapeMeta[type][degree].h; i++){
		rows[targetRows[i]] += widthInfo[type][degree][i];
		if (rows[targetRows[i]] == w)
			toBeRemoved[toBeRemovedCnt++] = targetRows[i];
	}

	// Clear rows
	for (int i = 0; i < toBeRemovedCnt; i++){
		int removingRow = toBeRemoved[i];
		rows[removingRow] = -1;
		clearedRow.push_back(removingRow);
		upper[lower[removingRow]] = upper[removingRow];
		lower[upper[removingRow]] = lower[removingRow];
	}
	if (toBeRemovedCnt){
		for (int i = 0; i < w; i++){
			while (rows[cols[i].top()] == -1){
				cols[i].pop();
			}
		}
	}
	return score[toBeRemovedCnt];
}


void solve() {
	int n, score = 0, left, degree;
	char type[2];
	scanf("%d%d", &w, &n);
	clearedRow.clear();
	for (int i = 0; i < w; i++){
		while (!cols[i].empty())
			cols[i].pop();
		cols[i].push(0);
	}

	for (int i = 0; i <= (n + 1) * 4; i++){
		upper[i] = i + 1;
		lower[i] = i - 1;
		rows[i] = 0;
	}
	while (n--){
		scanf("%s%d%d", type, &left, &degree);
		score += fall(type[0], left, degree);
	}

	printf("%d\n", score);
	sort(clearedRow.begin(), clearedRow.end());
	for (int i = 0; i < w; i++){
		int height = cols[i].top();
		printf(i == 0 ? "%d" : " %d", height - (lower_bound(clearedRow.begin(), clearedRow.end(), height) - clearedRow.begin()));
	}
	printf("\n");
}

int main() {
	initShapeMap();
	int T, ca = 1;
	scanf("%d", &T);
	while (T--) {
		printf("Case #%d:\n", ca++);
		solve();
	}
}
