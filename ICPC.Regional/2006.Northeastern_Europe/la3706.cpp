// 2006 Northeastern Europe: Exchange
// ACM-ICPC Live Archive 3706

#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

#define INF 99999
#define N 10005
#define BUY 1
#define SELL 0
int buysum[INF + 1], sellsum[INF + 1], tot;
struct NODE {
	int price, size;
	bool op, active;
	void get(bool type) {
		scanf("%d%d", &size, &price);
		op = type, active = 1;
	}
};
NODE nl[N];
class CMP1 {
public:
	bool operator ()(const int &i, const int &j) {
		if (nl[i].price != nl[j].price)
			return nl[i].price < nl[j].price;
		return i > j;
	}
};

class CMP2 {
public:
	bool operator ()(const int &i, const int &j) {
		if (nl[i].price != nl[j].price)
			return nl[i].price > nl[j].price;
		return i > j;
	}
};

typedef priority_queue<int, vector<int>, CMP1> QBUY;
typedef priority_queue<int, vector<int>, CMP2> QSELL;

void cancel() {
	int idx;
	scanf("%d", &idx);
	if (nl[idx].active) {
		nl[idx].active = 0;
		if (nl[idx].op == BUY)
			buysum[nl[idx].price] -= nl[idx].size;
		else
			sellsum[nl[idx].price] -= nl[idx].size;
	}
}

void sell(QBUY &Qbuy, QSELL &Qsell) {
	NODE pt;
	pt.get(SELL);
	while (pt.size > 0 && !Qbuy.empty()) {
		int top = Qbuy.top();
		if (!nl[top].active)
			Qbuy.pop();
		else if (pt.price > nl[top].price)
			break;
		else {
			int delta = min(nl[top].size, pt.size);
			nl[top].size -= delta, pt.size -= delta;
			buysum[nl[top].price] -= delta;
			printf("TRADE %d %d\n", delta, nl[top].price);
			nl[top].active = nl[top].size > 0;
		}
	}
	pt.active = pt.size > 0;
	sellsum[pt.price] += pt.size;
	nl[tot] = pt;
	Qsell.push(tot);
}

void buy(QBUY &Qbuy, QSELL &Qsell) {
	NODE pt;
	pt.get(BUY);
	while (pt.size > 0 && !Qsell.empty()) {
		int top = Qsell.top();
		if (!nl[top].active)
			Qsell.pop();
		else if (pt.price < nl[top].price)
			break;
		else {
			int delta = min(nl[top].size, pt.size);
			nl[top].size -= delta, pt.size -= delta;
			sellsum[nl[top].price] -= delta;
			printf("TRADE %d %d\n", delta, nl[top].price);
			nl[top].active = nl[top].size > 0;
		}
	}
	pt.active = pt.size > 0;
	buysum[pt.price] += pt.size;
	nl[tot] = pt;
	Qbuy.push(tot);
}

int main() {
	int T, begin = 1;
	while (scanf("%d", &T) != EOF) {
		if (begin)
			begin = 0;
		else
			printf("\n");
		QBUY Qbuy;
		QSELL Qsell;
		char cmd[10];
		memset(buysum, 0, sizeof(buysum));
		memset(sellsum, 0, sizeof(sellsum));
		for (tot = 1; tot <= T; tot++) {
			scanf("%s", cmd);
			if (cmd[0] == 'B')
				buy(Qbuy, Qsell);
			else if (cmd[0] == 'S')
				sell(Qbuy, Qsell);
			else if (cmd[0] == 'C')
				cancel();
			int bidsize = 0, bidprice = 0, asksize = 0, askprice = INF;
			while (!Qbuy.empty()) {
				if (nl[Qbuy.top()].active == 0)
					Qbuy.pop();
				else {
					bidprice = nl[Qbuy.top()].price;
					bidsize = buysum[bidprice];
					break;
				}
			}
			while (!Qsell.empty()) {
				if (nl[Qsell.top()].active == 0)
					Qsell.pop();
				else {
					askprice = nl[Qsell.top()].price;
					asksize = sellsum[askprice];
					break;
				}
			}
			printf("QUOTE %d %d - %d %d\n", bidsize, bidprice, asksize, askprice);
		}
	}
	return 0;
}
