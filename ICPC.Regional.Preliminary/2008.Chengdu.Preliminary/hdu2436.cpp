// 2008 Chengdu Preliminary: Collision Detection
// HDU 2436

#include <cstdio>
#include <algorithm>
using namespace std;

int ks;
int x, y, z;
int cx, cy, cz, r;
int xt, yt, zt;
int minX, maxX, minY, maxY, minZ, maxZ;

void in() {
	scanf("%d%d%d", &xt, &yt, &zt);
	minX = maxX = xt;
	minY = maxY = yt;
	minZ = maxZ = zt;
	for (int j = 0; j < 7; ++j) {
		scanf("%d%d%d", &xt, &yt, &zt);
		minX = min(minX, xt);
		maxX = max(maxX, xt);
		minY = min(minY, yt);
		maxY = max(maxY, yt);
		minZ = min(minZ, zt);
		maxZ = max(maxZ, zt);
	}
	scanf("%d%d%d%d", &cx, &cy, &cz, &r);
}

void getxyz() {
	x = cx, y = cy, z = cz;

	if (x < minX)
		x = minX;
	else if (x > maxX)
		x = maxX;

	if (y < minY)
		y = minY;
	else if (y > maxY)
		y = maxY;

	if (z < minZ)
		z = minZ;
	else if (z > maxZ)
		z = maxZ;
}

long long getdis() {
	return (long long) (x - cx) * (x - cx) + (long long) (y - cy) * (y - cy) + (long long) (z - cz) * (z - cz);
}

int main() {
	scanf("%d", &ks);
	for (int i = 0; i < ks; ++i) {
		in();
		getxyz();
		if ((long long) r * r >= getdis())
			printf("Yes\n");
		else
			printf("No\n");
	}
	return 0;
}
