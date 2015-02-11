// 2009 Southwestern Europe: Trick or Treat
// ACM-ICPC Live Archive 4504
// POJ 3873
#include <cstdio>
#include <cmath>
using namespace std;

const int N = 50005;
const double INF = 1e30;

int n;
double x[N], y[N];

double check(double xm, double &low, double &high){
    double farDis = -1, farX;
    for (int i = 0; i < n; i++){
        double d = (x[i] - xm) * (x[i] - xm) + y[i] * y[i];
        if (d > farDis)
            farDis = d, farX = x[i];
    }
    xm < farX ? low = xm : high = xm;
    return farDis;
}

int main(){
    while (scanf("%d", &n) && n){
        double d, low, high;
        low = INF; high = -INF;
        for (int i = 0; i < n; i++){
            scanf("%lf%lf", &x[i], &y[i]);
            low = x[i] < low ? x[i] : low;
            high = x[i] > high ? x[i] : high;
        }
        do{
            d = check((high + low) / 2.0, low, high);
        } while (high - low > 1e-6);
        printf("%.6lf %.6lf\n", high, sqrt(d));
    }
    return 0;
}
