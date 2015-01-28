// 2008 Northwestern Europe: White Water Rafting
// ACM-ICPC Live Archive 4293
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
#define PRECISION 1e-8
#define PI 3.14159265358979323846
#define DATATYPE double
#define N 105
 
inline double double_fix(double x) {
    return (fabs(x) < PRECISION) ? 0 : x;
}
inline int sgn(double x) {
    return (x < -PRECISION) ? -1 : x > PRECISION;
} 
inline DATATYPE sqr(DATATYPE x) {
    return x * x;
}
 
struct POINT {
    DATATYPE x, y;
 
    POINT(DATATYPE x, DATATYPE y) :
    x(x), y(y) {
    }
 
    POINT() :
    x(0), y(0) {
    }
 
    void print() {
        printf("(x:%.2lf y:%.2lf)\n", x, y);
    }
 
    void get() {
        scanf("%lf%lf", &x, &y);
    }
};
typedef POINT VECTOR;
 
struct LINE_EQ {
    double a, b, c;
};

struct LINE {
    POINT p1, p2;
 
    LINE(POINT x, POINT y) :
    p1(x), p2(y) {
    }
 
    LINE() :
    p1(0, 0), p2(0, 0) {
    }
};
 
VECTOR make_vec(const POINT &ps, const POINT &pe) {
    return VECTOR(pe.x - ps.x, pe.y - ps.y);
}
 
double dotdet(double x1, double y1, double x2, double y2) {
    return x1 * x2 + y1 * y2;
}
 
double dotdet(const VECTOR &v1, const VECTOR &v2) {
    return v1.x * v2.x + v1.y * v2.y;
}
 
double dis(const POINT &p1, const POINT &p2) {
    return sqrt(sqr(p1.x - p2.x) + sqr(p1.y - p2.y));
}
 
POINT nearest_point_to_line(POINT p, const LINE &line) {
    POINT ans;
    double a, b, t;
    a = line.p2.x - line.p1.x;
    b = line.p2.y - line.p1.y;
    t = ((p.x - line.p1.x) * a + (p.y - line.p1.y) * b) / (a * a + b * b);
    ans.x = line.p1.x + a * t;
    ans.y = line.p1.y + b * t;
    return ans;
}
 
POINT nearest_point_to_seg(const POINT &p, const LINE &line) {
    POINT a = line.p1, b = line.p2;
    if (sgn(dotdet(make_vec(a, b), make_vec(p, b))) <= 0) return b;
    if (sgn(dotdet(make_vec(a, b), make_vec(a, p))) <= 0) return a;
    return nearest_point_to_line(p, line);
}
 
POINT pl1[N], pl2[N];
 
void solve() {
    int n1, n2, i, j;
    scanf("%d", &n1);
    for (i = 0; i < n1; i++) {
        pl1[i].get();
    }
    scanf("%d", &n2);
    for (i = 0; i < n2; i++) {
 
        pl2[i].get();
    }
    pl1[n1] = pl1[0];
    pl2[n2] = pl2[0];
    double ans = 1e100;
    for (i = 0; i < n1; i++) {
        for (j = 0; j < n2; j++) {
            LINE ll;
            POINT pp;
            ll.p1 = pl1[i], ll.p2 = pl1[i + 1];
            pp = nearest_point_to_seg(pl2[j], ll);
            ans = min(ans, dis(pp, pl2[j]));
 
            pp = nearest_point_to_seg(pl2[j + 1], ll);
            ans = min(ans, dis(pp, pl2[j + 1]));
 
            ll.p1 = pl2[j], ll.p2 = pl2[j + 1];
            pp = nearest_point_to_seg(pl1[i], ll);
            ans = min(ans, dis(pp, pl1[i]));
 
            pp = nearest_point_to_seg(pl1[i + 1], ll);
            ans = min(ans, dis(pp, pl1[i + 1]));
        }
    }
    printf("%.9lf\n", ans/2);
}
 
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}