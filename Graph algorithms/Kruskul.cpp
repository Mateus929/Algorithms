#include <bits/stdc++.h>

#define ll long long

using namespace std;

class DSU {
private:
    int *sz, *p;
public:
    DSU(int n) {
        sz = new int[n + 1];
        p = new int[n + 1];
        for(int i = 0; i <= n; i++) {
            sz[i] = 1;
            p[i] = i;
        }
    }

    ~DSU() {
        delete[] sz;
        delete[] p;
    }

    int find_set(int v) {
        if(v == p[v]) {
            return v;
        }
        return p[v] = find_set(p[v]);
    }

    void union_set(int v, int u) {
        v = p[v];
        u = p[u];
        if(sz[v] < sz[u]) {
            swap(v, u);
        }
        sz[v] += sz[u];
        p[u] = v;
    }
};

class Kruskal : DSU {
private:
    struct edge {
        int v, u, w;

        edge(int v = 0, int u = 0, int w = 0) : v(v), u(u), w(w) {};
    };

    static bool comp(edge A, edge B) {
        return A.w < B.w;
    }

    vector<edge> edges;
public:
    Kruskal(int n) : DSU(n) {};

    void add(int v, int u, int w) {
        edges.push_back({v, u, w});
    }

    ll mst() {
        sort(edges.begin(), edges.end(), comp);
        ll ans = 0;
        for(edge ej: edges) {
            int v = ej.v, u = ej.u, w = ej.w;
            if(find_set(v) == find_set(u)) {
                continue;
            }
            union_set(v, u);
            ans += (ll) w;
        }
        return ans;
    }
};

int main() {
}
