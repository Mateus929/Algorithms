#include<bits/stdc++.h>

using namespace std;

struct point {
    int x, y;

    point(int x, int y) : x(x), y(y) {};

    point() { x = y = 0; }
};

double area(vector<point> &a) {
    double ans = 0;
    for(int i = 0; i < a.size(); i++) {
        point p = (i) ? a[i - 1] : a.back();
        point q = a[i];
        ans += (p.x - q.x) * (p.y + q.y);
    }
    return abs(ans) / 2;
}

int main() {
    int n;
    cin >> n;
    vector<point> a;
    for(int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        a.push_back({x, y});
    }
    cout << fixed << setprecision(6) << area(a);
}
