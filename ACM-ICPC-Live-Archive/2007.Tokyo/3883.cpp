// 2007 Tokyo: Prime Gap
// ACM-ICPC Live Archive 3883
// POJ 3518
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
#define MAX_N 1299719+10
bool primes[MAX_N];
int solve(int n) {
	int gap = 0, i;
	if (primes[n])
		return 0;
	for (i = n + 1; !primes[i]; i++)
		gap++;
	for (i = n - 1; !primes[i]; i--)
		gap++;
	return gap + 2;
}

int main() {
	int n;
	memset(primes, 0, sizeof(primes));
	for (int i = 2; i <= MAX_N / 2; i++)
		primes[i] = true;

	for (int i = 2; i < MAX_N; i++) {
		if (primes[i]) {
			for (int j = 2; i * j < MAX_N; j++)
				primes[i * j] = false;
		}
	}

	while (scanf("%d", &n) && n)
		printf("%d\n", solve(n));

	return 0;
}