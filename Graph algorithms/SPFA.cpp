#include<bits/stdc++.h>

#define INF INT_MAX
#define pii pair<int,int>

using namespace std;

vector<pii > g[100001];

bool SPFA(int n, int s) {
    vector<int> d(n + 1, INF), cnt(n + 1, 0);
    vector<bool> inq(n + 1, false);
    queue<int> q;
    d[s] = 0;
    q.push(s);
    inq[s] = true;
    while(!q.empty()) {
        int v = q.front();
        q.pop();
        inq[v] = false;
        for(pii u: g[v]) {
            int to = u.first;
            int len = u.second;
            if(d[v] + len < d[to]) {
                d[to] = d[v] + len;
                if(!inq[to]) {
                    q.push(to);
                    inq[to] = true;
                    cnt[to]++;
                    if(cnt[to] > n)
                        return false;
                }
            }
        }
    }
    return true;
}

int main() {
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        int v, u, w;
        cin >> v >> u >> w;
        g[v].push_back({u, w});
    }
    int s;
    cin >> s;
    if(SPFA(n, s))
        cout << "No";
    else
        cout << "Yes";
}
