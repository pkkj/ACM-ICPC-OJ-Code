// 2009 Northwestern Europe: Common Subexpression Elimination
// ACM-ICPC Live Archive 4610
#include <cstdio>
#include <string>
#include <cstring>
#include <map>
using namespace std;
#define N 50005

struct NODE{
	string s;
	int left, right, num;
	NODE() :s(""), left(-1), right(-1) {}
};

struct KEY{
	int left, right, code;
	KEY(int code, int left, int right) :code(code), left(left), right(right){}
	bool operator<(const KEY &other) const{
		if (left != other.left) return left < other.left;
		if (right != other.right) return right < other.right;
		return code < other.code;
	}
};

map<KEY, int> hashTable;
NODE nodes[N];
int sidx, seq, tot;
bool duplicated[N];
char input[N * 10];

int encode(string s){
	int code = 0;
	for (size_t i = 0; i < s.length(); i++){
		code *= 26;
		code += s[i] - 'a' + 1;
	}
	return code;
}
void insert (KEY &key, int nodeIdx){
	if (hashTable.find(key) == hashTable.end()){
		hashTable[key] = nodes[nodeIdx].num;
	}
	else{
		nodes[nodeIdx].num = hashTable[key];
		duplicated[nodeIdx] = true;
		seq--;
	}
}
int construct(){
	int nodeIdx = tot++;
	nodes[nodeIdx] = NODE();
	nodes[nodeIdx].num = ++seq;
	
	while ('a' <= input[sidx] && input[sidx] <= 'z')
		nodes[nodeIdx].s += input[sidx++];
	
	if (input[sidx] == '('){
		sidx++;
		nodes[nodeIdx].left = construct();
		sidx++;
		nodes[nodeIdx].right = construct();
		sidx++;
		KEY key = KEY(encode(nodes[nodeIdx].s), nodes[nodes[nodeIdx].left].num, nodes[nodes[nodeIdx].right].num);
		insert(key, nodeIdx);
	}
	else {
		KEY key = KEY(encode(nodes[nodeIdx].s), -1, -1);
		insert(key, nodeIdx);
	}
	return nodeIdx;
}

void output(int idx){
	if (duplicated[idx]) printf("%d", nodes[idx].num);
	else{
		printf("%s", nodes[idx].s.c_str());
		if (nodes[idx].left != -1){
			printf("(");
			output(nodes[idx].left);
			printf(",");
			output(nodes[idx].right);
			printf(")");
		}
	}
}

int main(){
	int T;
	scanf("%d", &T);
	while (T--){
		scanf("%s", input);
		sidx = tot = seq = 0;
		memset(duplicated, 0, sizeof(duplicated));
		hashTable.clear();
		construct();
		output(0);
		printf("\n");
	}
	return 0;
}