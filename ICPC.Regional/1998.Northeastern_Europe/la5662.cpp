// 1998 Northeastern Europe: Defragment
// ACM-ICPC Live Archive 5662

#include <cstdio>
#include <cstring>
#include <utility>
using namespace std;

int const N = 10000;
int mem[N + 5];
pair<int, int> stack[N];

void move(int a, int b, int &empty){
	printf("%d %d\n", a, b);
	mem[b] = mem[a];
	mem[a] = 0;
	empty = a;
}

void solve(){
	int n, k, id = 1, m, pos, empty = -1;
	bool moved = false;

	scanf("%d%d", &n, &k);
	memset(mem, 0, sizeof(mem));

	for (int i = 0; i < k; i++){
		scanf("%d", &m);
		for (int j = 0; j < m; j++){
			scanf("%d", &pos);
			mem[pos] = id++;
		}
	}

	for (int i = 1; i <= n && empty == -1; i++)
		if (mem[i] == 0)
			empty = i;

	for (int i = 1; i <= n; i++){
		if (mem[i] == 0 || mem[i] == i) continue;

		moved = true;
		int cur = i, begin = i, top = 0;
		do{
			stack[top++] = make_pair(cur, mem[cur]);
			cur = mem[cur];
		} while (mem[cur] != 0 && cur != begin);

		if (cur == begin){
			// Detect a loop, move the current element to empty position. Then it becomes a chain.
			move(cur, empty, empty);
		}
		else{
			// Detect a chain, sort its elements.
			while (top--) move(stack[top].first, stack[top].second, empty);
		}
	}

	if (!moved)
		printf("No optimization needed\n");
}

int main(){
	int T;
	scanf("%d", &T);
	for (int ca = 0; ca < T; ca++){
		if (ca) printf("\n");
		solve();
	}
}