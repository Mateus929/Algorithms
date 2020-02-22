#include <bits/stdc++.h>

using namespace std;

vector<int> ans,deg(100001);
queue <int> G[100001];

void Euler(int v){
    while(!G[v].empty()){
        int to=G[v].front();
        G[v].pop();
        Euler(to);
    }
    ans.push_back(v);
}

int main(){
    int n,m;
    cin >> n >> m;
    for(int i=1;i<=m;i++){
        int v,u;
        cin >> v >> u;
        G[v].push(u);
        deg[v]++;
        deg[u]--;
    }
    int start=1,odd=0;
    for(int i=1;i<=n;i++){
        if(deg[i]!=0)
        {
            odd++;
            if(deg[i]>0)
                start=i;
        }
    }
    if(odd>2 || odd==1){
        cout << "NO";
        return 0;
    }
    cout << "YES" << endl;
    Euler(start);
    reverse(ans.begin(),ans.end());
    for(int u : ans)
        cout << u << " ";
}
