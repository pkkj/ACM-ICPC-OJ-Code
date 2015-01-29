// 2005 Tokyo: Organize Your Train
// CII 3402
#include <cstdio>
#include <cstring>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;
#define NL 41
#define NR 5

#define WEST 0
#define EAST 1

#define FORWARD 0
#define BACK 1
class RAIL {
public:
	char data[NL];
	char head, tail, sz;
	RAIL() {
	}
	RAIL(char *cmd) {
		head = tail = NL / 2, sz = 0;
		if (cmd[0] == '-')
			return;
		for (int i = 0; cmd[i]; i++)
			data[tail++] = cmd[i], sz++;
	}
	bool operator ==(const RAIL &x) const {
		int i, j;
		if (x.sz != sz)
			return false;
		for (i = head, j = x.head; i < tail; i++, j++)
			if (data[i] != x.data[j])
				return false;
		return true;
	}
	bool operator !=(const RAIL &x) const {
		int i, j;
		if (x.sz != sz)
			return true;
		for (i = head, j = x.head; i < tail; i++, j++)
			if (data[i] != x.data[j])
				return true;
		return false;
	}
	bool operator <(const RAIL &x) const {
		int i, j;
		if (sz != x.sz)
			return sz < x.sz;
		for (i = head, j = x.head; i < tail; i++, j++)
			if (data[i] != x.data[j])
				return data[i] < x.data[j];
		return false;
	}

	void intoW(char ch) {
		data[--head] = ch, sz++;
	}
	void intoE(char ch) {
		data[tail++] = ch, sz++;
	}
	char fromW() {
		sz--;
		char ret = data[head++];
		return ret;
	}
	char fromE() {
		sz--;
		char ret = data[tail - 1];
		tail--;
		return ret;
	}
};

class STATION {
public:
	char sz;
	RAIL list[NR];
	bool operator ==(const STATION &x) const {
		if (x.sz != sz)
			return false;
		for (int i = 0; i < sz; i++)
			if (list[i] != x.list[i])
				return false;
		return true;
	}
	bool operator !=(const STATION &x) const {
		if (x.sz != sz)
			return true;
		for (int i = 0; i < sz; i++)
			if (list[i] != x.list[i])
				return true;
		return false;
	}
	bool operator <(const STATION &x) const {
		int i, j;
		for (i = j = 0; i < sz; i++, j++)
			if (list[i] != x.list[j])
				return list[i] < x.list[j];
		return false;
	}
};

STATION getnext(STATION x, int d, int s, int sd, int t, int td) {
	int nd, i;
	if (sd == WEST) {
		if (td == WEST)
			for (i = 0; i < d; i++)
				x.list[t].intoW(x.list[s].fromW());
		else
			for (i = 0; i < d; i++)
				x.list[t].intoE(x.list[s].fromW());
	} else {
		nd = x.list[s].sz - d;
		if (td == EAST)
			for (i = 0; i < nd; i++)
				x.list[t].intoE(x.list[s].fromE());
		else
			for (i = 0; i < nd; i++)
				x.list[t].intoW(x.list[s].fromE());
	}
	return x;
}

map<STATION, int> FS, BS;
bool layout[NR][2][NR][2];
int nx, nrail;
STATION begin, end;
int bfs(STATION src, map<STATION, int> &D, int mode) {
	STATION u, v;
	queue<STATION> Q;
	Q.push(src);
	D[src] = 0;
	if (mode == FORWARD && BS.find(src) != BS.end())
		return BS[src]; //Take it out
	while (!Q.empty()) {
		u = Q.front(), Q.pop();
		int dist = D[u];
		if (mode == BACK && dist >= 3)
			return 0;
		for (int s = 0; s < nrail; s++)
			for (int d = 0; d < u.list[s].sz; d++)
				for (int sd = 0; sd < 2; sd++)
					for (int t = 0; t < nrail; t++)
						for (int td = 0; td < 2; td++) {
							if (layout[s][sd][t][td] == 0)
								continue;
							v = getnext(u, d, s, sd, t, td);
							if (D.find(v) == D.end()) {
								D[v] = dist + 1;
								if (mode == FORWARD)
									if (BS.find(v) != BS.end())
										return dist + BS[v] + 1;
								Q.push(v);
							}
						}
	}
	return -1;
}

int solve() {
	int i, s, sd, t, td;
	char cmd1[3], cmd2[3], cmd[NL];
	memset(layout, 0, sizeof(layout));
	for (i = 0; i < nx; i++) {
		scanf("%s %s", cmd1, cmd2);
		s = cmd1[0] - '0', sd = (cmd1[1] == 'W') ? WEST : EAST;
		t = cmd2[0] - '0', td = (cmd2[1] == 'W') ? WEST : EAST;
		layout[s][sd][t][td] = layout[t][td][s][sd] = 1;
	}
	begin.sz = end.sz = nrail;
	for (i = 0; i < nrail; i++) {
		scanf("%s", cmd);
		begin.list[i] = RAIL(cmd);
	}
	for (i = 0; i < nrail; i++) {
		scanf("%s", cmd);
		end.list[i] = RAIL(cmd);
	}
	FS = map<STATION, int>();
	BS = map<STATION, int>();

	bfs(end, BS, BACK);
	return bfs(begin, FS, FORWARD);
}
int main() {
	while (scanf("%d%d", &nrail, &nx) && nrail)
		printf("%d\n", solve());
	return 0;
}

