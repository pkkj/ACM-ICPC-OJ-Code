// 2002 Kaohsiung: Rooted Trees Isomorphism
// POJ 1343
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

#define TREES 155
#define N 105

vector<int> tree[N];
int cntTree, n;
int deg[N];

string toString(int nid){
	if (tree[nid].size() == 0)
		return "()";

	vector<string> children;
	for (int i = 0; i < tree[nid].size(); i++)
		children.push_back(toString(tree[nid][i]));
	
	sort(children.begin(), children.end());

	string cur = "";
	for (int i = 0; i < children.size(); i++)
		cur += children[i];
	return "(" + cur + ")";
}

string treeStr[TREES];
int main() {
	scanf("%d%d", &cntTree, &n);
	for (int i = 0; i < cntTree; i++){
		for (int j = 0; j < n; j++)
			tree[j].clear();
		
		memset(deg, 0, sizeof(deg));
		for (int j = 0; j < n - 1; j++){
			int a, b;
			scanf("%d%d", &a, &b);
			tree[a - 1].push_back(b - 1);
			deg[b - 1]++;
		}

		int root = -1;
		for (int j = 0; j < n && root == -1;j++)
			if (!deg[j])
				root = j;

		treeStr[i]= toString(root);
	}
	bool vis[TREES];
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i < cntTree; i++){
		if (vis[i])continue;
		printf("%d", i + 1);
		for (int j = i + 1; j < cntTree; j++){
			if (treeStr[i] == treeStr[j]){
				vis[j] = true;
				printf(" = %d", j + 1);
			}
		}
		printf(" ;\n");
	}
	return 0;
}