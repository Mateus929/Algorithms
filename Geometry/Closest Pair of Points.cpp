#include<bits/stdc++.h>

#define ll long long
using namespace std;

struct point {
    ll x, y;
    int indx;

    point(ll x, ll y, int indx) : x(x), y(y), indx(indx) {};

    point() {
        x = y = 0;
        indx = 0;
    }
};

bool compx(point a, point b) {
    if(a.x == b.x)
        return a.y < b.y;
    return a.x < b.x;
}

struct compy {
    bool operator()(point a, point b) {
        if(a.y == b.y)
            return a.x < b.x;
        return a.y < b.y;
    }
};

double dist(point a, point b) {
    ll x = (a.x - b.x), y = a.y - b.y;
    return sqrt(x * x + y * y);
}

double closets_pair(vector<point> &points, point &A, point &B) {
    int n = points.size();
    double h = DBL_MAX;
    sort(points.begin(), points.end(), compx);
    multiset<point, compy> st;
    st.insert(points[0]);
    int indx = 0;
    for(int i = 1; i < n; i++) {
        while(indx < i && points[i].x - points[indx].x > h)
            st.erase(points[indx++]);
        for(set<point, compy>::iterator it = st.lower_bound({points[i].x - h, points[i].y - h, 0});
            points[i].y + h >= it->y && it != st.end(); it++) {
            double d = dist(points[i], *it);
            if(h > d) {
                h = d;
                A = *it;
                B = points[i];
            }
        }
        st.insert(points[i]);
    }
    return h;
}

int main() {
    int n;
    cin >> n;
    vector<point> a;
    for(int i = 1; i <= n; i++) {
        ll x, y;
        cin >> x >> y;
        a.push_back({x, y, i});
    }
    point A, B;
    cout << fixed << setprecision(6) << closets_pair(a, A, B) << endl;
    cout << A.indx << " " << B.indx;
}
