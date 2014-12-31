// CII 4609
// 2009 Northwestern Europe: An Industrial Spy
#include <cstdio>
#include <cstring>
#include <cmath>
#include <set>
#include <algorithm>
using namespace std;
#define N 10

const int maxsz = 10000000;
const int maxsz2 = maxsz / 2;
const int maxsqrt = sqrt(double(maxsz)) / 2;

char a[maxsz / 16 + 2];

inline int isPrime(int n) {
	return ((n & 1) || (2 == n)) && (a[(n) >> 4] & (1 << (((n) >> 1) & 7)));
}
void sieve() {
	memset(a, 255, sizeof a);
	a[0] = 0xFE;
	for (int i = 1; i < maxsqrt; i++)
		if (a[i >> 3] & (1 << (i & 7)))
			for (int j = i + i + i + 1; j < maxsz2; j += i + i + 1)
				a[j >> 3] &= ~(1 << (j & 7));
}

int solve() {
	char digits[N];
	set<int> possiblity;;
	scanf("%s", digits);
	int len = strlen(digits);
	int count = 1 << len;
	for (int bit = 1; bit < count; bit++) {
		int subsetLength = 0;
		int subset[N];
		for (int i = 0; i < len; i++) {
			if (bit & (1 << i)) {
				subset[subsetLength++] = digits[i] - '0';
			}
		}
		sort(subset, subset + subsetLength);
		do {
			int number = 0;
			for (int i = subsetLength - 1, pos = 1; i >= 0; i--, pos *= 10) {
				number += subset[i] * pos;
			}
			if (isPrime(number))
				possiblity.insert(number);
		} while (next_permutation(subset, subset + subsetLength));
	}
	return possiblity.size();
}
int main() {
	sieve(); // Calculate the prime number
	int T;
	scanf("%d", &T);
	while (T--)
		printf("%d\n", solve());
	return 0;
}

