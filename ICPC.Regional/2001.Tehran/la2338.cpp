// 2001 Tehran: Parencodings
// ACM-ICPC Live Archive 2338
// POJ 1068

#include <cstdio>
#define MAX 30
int arr[MAX], n, T;

void solve(){
	int num;
	printf("1");
	if (n == 1)
		return;
	for (int i = 1; i <= n; i++)
		arr[i]--;
	for (int i = 2; i <= n; i++){
		int pos, num = 1;
		for (pos = i; pos > 1; pos--){
			if (arr[pos] == arr[pos - 1])
				num++;
			else
				break;
		}
		for (int j = pos; j <= n; j++)
			arr[j]--;
		printf(" %d", num);
	}
	printf("\n");
}

int main(){
	scanf("%d", &T);
	while (T--){
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			scanf("%d", &arr[i]);
		solve();
	}
	return 0;
}