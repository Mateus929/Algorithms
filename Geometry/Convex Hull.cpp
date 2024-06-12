#include<bits/stdc++.h>

using namespace std;

struct point {
    int x, y;

    point(int x, int y) : x(x), y(y) {};

    point() { x = y = 0; }
};

bool compx(point a, point b) {
    if(a.x == b.x)
        return a.y < b.y;
    return a.x < b.x;
}

double cross(point a, point b, point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

void Convex_Hull(vector<point> &a, vector<point> &hull) {
    sort(a.begin(), a.end(), compx);
    int k = 0;
    hull.resize(2 * a.size() + 1);
    for(int i = 0; i < a.size(); i++) {
        while(k >= 2 && cross(hull[k - 2], hull[k - 1], a[i]) <= 0) k--;
        hull[k++] = a[i];
    }
    int len = k + 1;
    for(int i = a.size() - 2; i >= 0; i--) {
        while(k >= len && cross(hull[k - 2], hull[k - 1], a[i]) <= 0) k--;
        hull[k++] = a[i];
    }
    hull.resize(k - 1);
}

int main() {
    int n;
    cin >> n;
    vector<point> a, b;
    for(int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        a.push_back({x, y});
    }
    Convex_Hull(a, b);
    for(point k: b) {
        cout << k.x << "," << k.y << " ";
    }
}
