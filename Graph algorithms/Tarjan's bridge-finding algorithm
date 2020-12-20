#include<bits/stdc++.h>


using namespace std;

vector<int> g[100001],tin(100001),low(100001);
vector<pair<int,int>> bridges;
vector<bool> used(100001,false);
int cnt=0;

void Tarjan(int v,int e=-1){
    used[v]=true;
    tin[v]=low[v]=cnt++;
    for(int u: g[v]){
        if(e==u)
            continue;
        if(used[u])
            low[v]=min(low[v],tin[u]);
        else{
            Tarjan(u,v);
            low[v]=min(low[v],low[u]);
            if(low[u]>tin[v])
                bridges.push_back({v,u});
        }
    }
}

int main(){
    int n,m;
    cin >> n >> m;
    for(int i=1;i<=m;i++){
        int v,u;
        cin >> v >> u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    for(int i=1;i<=n;i++)
        if(!used[i])
            Tarjan(i);
    cout << bridges.size() << endl;
    for(pair<int,int> u:bridges)
        cout << u.first << " " << u.second << endl;
}
