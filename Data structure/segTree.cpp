#include <bits/stdc++.h>
using namespace std;

template<typename T>
class segTree {
private:
    int n;
    T *t, *lazy;
    // To modify segTree, just modify comb and upd.
    // lazy[v] stores 0 initialy, in case of update change it.
    T comb(T a, T b) {
        return a + b;
    }
    void upd(int v, int tl, int tr, T x) {
        t[v] += x * (tr - tl + 1);
        lazy[v] += x;
    }
    void push(int v, int tl, int tr) {
        if(lazy[v] == 0 || tl == tr) {
            return;
        }
        int tm = (tl + tr) / 2;
        upd(v * 2, tl, tm, lazy[v]);
        upd(v * 2 + 1, tm + 1, tr, lazy[v]);
        lazy[v] = 0;
    }
    void build(int v, int tl, int tr, T a[]) {
        if(tl == tr) {
            t[v] = a[tl];
            lazy[v] = 0;
        } else {
            int tm = (tl + tr) / 2;
            build(v * 2, tl, tm, a);
            build(v * 2 + 1, tm + 1, tr, a);
            t[v] = comb(t[v * 2], t[v * 2 + 1]);
            lazy[v] = 0;
        }
    }
    T query(int v, int tl, int tr, int l, int r) {
        if(tl == l && tr == r) {
            return t[v];
        }
        push(v, tl, tr);
        int tm = (tl + tr) / 2;
        if(r <= tm) {
            return query(v * 2, tl, tm, l, r);
        }
        if(tm < l) {
            return query(v * 2 + 1, tm + 1, tr, l, r);
        }
        return comb(query(v * 2, tl, tm, l, tm),
                    query(v * 2 + 1, tm + 1, tr, tm + 1, r));
    }
    void update(int v, int tl, int tr, int l, int r, T val) {
        if(tl == l && tr == r) {
            upd(v, tl, tr, val);
            return;
        }
        push(v, tl, tr);
        int tm = (tl + tr) / 2;
        if(r <= tm) {
            update(v * 2, tl, tm, l, r, val);
        }
        if(tm < l) {
            update(v * 2 + 1, tm + 1, tr, l, r, val);
        }
        if(l <= tm && tm < r) {
            update(v * 2, tl, tm, l, tm, val),
            update(v * 2 + 1, tm + 1, tr, tm + 1, r, val);
        }
        t[v] = comb(t[v * 2], t[v * 2 + 1]);
    }
public:
    segTree(int n) : n(n) {
        t = new T [4 * n];
        lazy = new T [4 * n];
        for(int i = 0; i < 4 * n; i++) {
            t[i] = lazy[i] = 0;
        }
    }
    segTree(int n, T a[]) : n(n) {
        t = new T [4 * n];
        lazy = new T [4 * n];
        build(1, 1, n, a);
    }
    ~segTree() {
        delete[] t;
        delete[] lazy;
    }
    T query(int l, int r) {
        return query(1, 1, n, l, r);
    }
    void update(int pos, T val) {
        update(1, 1, n, pos, pos, val);
    }
    void update(int l, int r, T val) {
        update(1, 1, n, l, r, val);
    }
};


int main() {
}
