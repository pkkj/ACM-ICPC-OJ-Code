// 2007 Japan Domestic: Dr. Podboq or: How We Became Asymmetric
// POJ 3330
// Aizu OJ 1152
#include <cstring>
#include <cstdio>
#include <set>
#include <algorithm>
#include <string>
using namespace std;
#define N 130
struct TREE {
	int left[N], right[N], counter;
	double sym[N];
	TREE() {
		memset(left, -1, sizeof(left));
		memset(right, -1, sizeof(right));
		counter = 1;
	}
};
char s[1000];
TREE t;
int parse(int node, int left, int right, string &shape, set<string> &shapes) {
	int in = 0;
	if (right - left == 0 && s[left] == 'x') {
		t.sym[node] = 0;
		shape = "x";
		shapes.insert(shape);
		return 1;
	}
	for (int i = left; i <= right; i++) {
		if (s[i] == '(')
			in++;
		if (s[i] == ')')
			in--;
		if (s[i] == ' ' && in == 1) {
			string shapeL, shapeR;
			set<string> shapesL, shapesR;

			int leftChild = t.counter++;
			int rightChild = t.counter++;
			int leftChildCount = parse(leftChild, left + 1, i - 1, shapeL,
					shapesL);
			int rightChildCount = parse(rightChild, i + 1, right - 1, shapeR,
					shapesR);
			if (leftChildCount >= rightChildCount) {
				t.left[node] = leftChild;
				t.right[node] = rightChild;
				shape = "(" + shapeL + " " + shapeR + ")";
			} else {
				t.right[node] = leftChild;
				t.left[node] = rightChild;
				shape = "(" + shapeR + " " + shapeL + ")";
			}
			set<string> intersect;
			set_intersection(shapesL.begin(), shapesL.end(), shapesR.begin(),
					shapesR.end(), std::inserter(intersect, intersect.begin()));
			shapes = shapesL;
			shapes.insert(shapesR.begin(), shapesR.end());
			t.sym[node] = (double) intersect.size() / shapes.size();
			shapes.insert(shape);
			return leftChildCount + rightChildCount;
		}
	}
}

#define LEFT_STRONG 2
#define RIGHT_STRONG 1
#define SAME 0
int compare(int n1, int n2) {
	if (t.sym[n1] < t.sym[n2])
		return LEFT_STRONG;
	if (t.sym[n1] > t.sym[n2])
		return RIGHT_STRONG;
	if (t.sym[n1] == 0 || t.sym[n2] == 0)
		return SAME;
	int l1 = t.left[n1], r1 = t.right[n1];
	int l2 = t.left[n2], r2 = t.right[n2];
	int strong1, weak1, strong2, weak2;
	if (compare(l1, r1) == LEFT_STRONG)
		strong1 = l1, weak1 = r1;
	else
		strong1 = r1, weak1 = l1;
	if (compare(l2, r2) == LEFT_STRONG)
		strong2 = l2, weak2 = r2;
	else
		strong2 = r2, weak2 = l2;
	int resultOfStrong = compare(strong1, strong2);
	if (resultOfStrong)
		return resultOfStrong;
	int resultOfWeak = compare(weak1, weak2);
	if (resultOfWeak)
		return resultOfWeak;
	return SAME;
}

string rotate(int node, bool isLeft) {
	if (t.left[node] == -1)
		return "x";
	int cmpResult = compare(t.left[node], t.right[node]);
	if (cmpResult == LEFT_STRONG && !isLeft
			|| cmpResult == RIGHT_STRONG && isLeft) {
		swap(t.left[node], t.right[node]);
	}
	string left = rotate(t.left[node], true);
	string right = rotate(t.right[node], false);
	return "(" + left + " " + right + ")";
}

int main() {
	while (gets(s) && s[0] != '0') {
		t = TREE();
		string shape;
		set<string> shapes;
		parse(0, 0, strlen(s) - 1, shape, shapes);
		string ans = rotate(0, 1);
		printf("%s\n", ans.c_str());
	}
	return 0;
}
