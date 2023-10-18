#include<bits/stdc++.h>


using namespace std;

vector<int> g[100001],rg[100001],comp[100001],indx(100001);
vector<bool> used(100001,false);
stack<int> q;

void DFS(int v){
    used[v]=true;
    for(int u: g[v])
        if(!used[u])
            DFS(u);
    q.push(v);
}

void dfs(int v,int ind){
    used[v]=true;
    comp[ind].push_back(v);
    indx[v]=ind;
    for(int u:rg[v])
        if(!used[u])
            dfs(u,ind);
}

void SCC(int n,int m){
    for(int v=1;v<=n;v++)
        if(!used[v])
            DFS(v);
    int cnt=0;
    fill(used.begin(),used.end(),false);
    while(!q.empty()){
        int v=q.top();
        q.pop();
        if(!used[v]){
            cnt++;
            dfs(v,cnt);
        }

    }
    for(int i=1;i<=cnt;i++){
        cout << i << ": ";
        for(int u: comp[i])
            cout << u << " ";
        cout << endl;
    }
}

int main(){
    int n,m;
    cin >> n >> m;
    for(int i=1;i<=m;i++){
        int v,u;
        cin >> v >> u;
        g[v].push_back(u);
        rg[u].push_back(v);
    }
    SCC(n,m);
}
