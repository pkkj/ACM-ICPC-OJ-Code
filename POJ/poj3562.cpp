// POJ 3562
// Northeastern Europe 2005, Western Subregion: “Roman” corridor
#include <cstdio>
#include <cstring>
#define N 20000
#define NA 7
 
struct NODE {
	int next[NA], min, v;
};
NODE TREE[N];
int rton[200];
struct ITEM {
	char ro[3];
	int x;
};
 
ITEM rol[13];
int id;
void init_node(int p) {
	memset(TREE[p].next, -1, sizeof(TREE[p].next));
	TREE[p].min = 5000, TREE[p].v = -1;
}
void init() {
	char str[] = "IVXLCDM";
	for (int i = 0; i < 7; i++)
		rton[(int) str[i]] = i;
	strcpy(rol[0].ro, "M"), rol[0].x = 1000;
	strcpy(rol[1].ro, "CM"), rol[1].x = 900;
	strcpy(rol[2].ro, "D"), rol[2].x = 500;
	strcpy(rol[3].ro, "CD"), rol[3].x = 400;
	strcpy(rol[4].ro, "C"), rol[4].x = 100;
	strcpy(rol[5].ro, "XC"), rol[5].x = 90;
	strcpy(rol[6].ro, "L"), rol[6].x = 50;
	strcpy(rol[7].ro, "XL"), rol[7].x = 40;
	strcpy(rol[8].ro, "X"), rol[8].x = 10;
	strcpy(rol[9].ro, "IX"), rol[9].x = 9;
	strcpy(rol[10].ro, "V"), rol[10].x = 5;
	strcpy(rol[11].ro, "IV"), rol[11].x = 4;
	strcpy(rol[12].ro, "I"), rol[12].x = 1;
 
	id = 1;
	init_node(1);
}
void number_to_roman(int x, char *ans) {
	ans[0] = 0;
	while (x) {
		int i;
		for (i = 0; i < 13; i++)
			if (x >= rol[i].x) break;
		strcat(ans, rol[i].ro);
		x -= rol[i].x;
	}
}
 
void insert(char *str, int wid) {
	int x = 1, i = 0, y;
	while (str[i]) {
		y = rton[(int) str[i]];
		if (TREE[x].next[y] == -1) {
			TREE[x].next[y] = ++id;
			init_node(id);
		}
		x = TREE[x].next[y];
		TREE[x].min = TREE[x].min < wid ? TREE[x].min : wid;
		i++;
	}
	TREE[x].v = wid;
}
 
void pre() {
	char roman[20];
	for (int i = 1; i <= 4000; i++) {
		number_to_roman(i, roman);
		insert(roman, i);
	}
}
#define M 16
int map[M][M];
bool v[M][M];
int ans, n, m;
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, -1, 0, 1 };
void dfs(int id, int x, int y, int dep) {
	int i;
	if (id == -1 || dep > 20) return;
	if (TREE[id].min > ans) return;
	if (y == m - 1) {
		ans = TREE[id].v;
		return;
	}
	for (i = 0; i < 4; i++) {
		int nx, ny;
		nx = x + dx[i], ny = y + dy[i];
		if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
		if(v[nx][ny])continue;
		v[nx][ny] = 1;
		dfs(TREE[id].next[map[nx][ny]], nx, ny, dep + 1);
		v[nx][ny] = 0;
	}
}
int main() {
	init();
	pre();
	int i, j;
	scanf("%d%d", &n, &m);
	for (i = 0; i < n; i++) {
		getchar();
		for (j = 0; j < m; j++)
			map[i][j] = rton[(int)getchar()];
	}
	ans = 5000;
	for (i = 0; i < n; i++) {
		memset(v, 0, sizeof(v));
		v[i][0]=1;
		dfs(TREE[1].next[map[i][0]], i, 0, 0);
	}
	if (ans == 5000) puts("NO");
	else {
		char roman[20];
		number_to_roman(ans, roman);
		puts(roman);
	}
	return 0;
}
