#include <bits/stdc++.h>

using namespace std;

vector<int> ans;
multiset<int> G[100001];

void Euler(int v) {
    while(G[v].size() > 0) {
        int to = (*G[v].begin());
        G[v].erase(G[v].begin());
        G[to].erase(G[to].find(v));
        Euler(to);
    }
    ans.push_back(v);
}

int main() {
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        int v, u;
        cin >> v >> u;
        G[v].insert(u);
        G[u].insert(v);
    }
    int start = 1, odd = 0;
    for(int i = 1; i <= n; i++) {
        if(G[i].size() % 2 == 1) {
            odd++;
            start = i;
        }
    }
    if(odd > 2 || odd == 1) {
        cout << "NO";
        return 0;
    }
    cout << "YES" << endl;
    Euler(start);
    reverse(ans.begin(), ans.end());
    for(int u: ans)
        cout << u << " ";
}
