#include <bits/stdc++.h>
#define INF INT_MAX

using namespace std;

int d[1001][1001];

void Fill_INF(int n){
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
           if(i==j)
              d[i][j]=0;
           else
              d[i][j]=INF;

}

void Floyd_Warshall(int n){
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
           for(int j=1;j<=n;j++)
              if(d[i][k]<INF && d[k][j]<INF)
                 d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
}
int main(){
    int n,m;
    cin >> n >> m;
    Fill_INF(n);
    for(int i=1;i<=m;i++){
        int v,u,w;
        cin >> v >> u >> w;
        d[v][u]=w;
    }

    Floyd_Warshall(n);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)
            if(d[i][j]<INF)
                cout << d[i][j] << " ";
            else
                cout << -1 << " ";
        cout << endl;
    }
}
