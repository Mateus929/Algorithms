#include<bits/stdc++.h>
using namespace std;

vector<int> g[100001];
int tin[100001],tout[100001],A[100001][20],deph[100001];
int timer=0;
void DFS(int v,int e=-1){
    for(int j=0;j<20;j++)
        if(j==0)
            A[v][j]=max(e,0);
        else
            if(A[v][j-1]!=0)
                A[v][j]=A[A[v][j-1]][j-1];
    deph[v]=(e!=-1) ? deph[e]+1 : 1;
    tin[v]=++timer;
    for(int u: g[v])
        if(u!=e)
            DFS(u,v);
    tout[v]=++timer;
}
bool IsAncestor(int v,int u){
    return (tin[v]<=tin[u] && tout[u]<=tout[v]);
}
int LCA(int v,int u){
    if(deph[u]<deph[v])
        swap(v,u);
    if(IsAncestor(v,u))
        return v;
    for(int i=19;i>=0;i--){
        if(A[v][i]==0)
            continue;
        int k=A[v][i];
        if(!IsAncestor(k,u))
            v=k;
    }
    return A[v][0];
}
int main(){
    int n;
    cin >> n;
    for(int i=1;i<n;i++){
        int v,u;
        cin >> v >> u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    DFS(1);
    int Q;
    cin >> Q;
    while(Q--){
        int v,u;
        cin >> v >> u;
        cout << LCA(v,u) << endl;
    }
}
