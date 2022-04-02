#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int N=200000;
ll a[N+1],t[4*N];

ll build(int v,int tl,int tr){
    if(tl==tr) return t[v]=a[tl];
    int tm=(tl+tr)/2;
    return t[v]=build(v*2,tl,tm)+build(v*2+1,tm+1,tr);
}

void update(int v,int tl,int tr,int pos,ll val){
    if(tl==tr) t[v]=val,a[tl]=val;
    else{
        int tm=(tl+tr)/2;
        if(pos<=tm) update(v*2,tl,tm,pos,val);
        else update(v*2+1,tm+1,tr,pos,val);
        t[v]=t[v*2]+t[v*2+1];
    }
}

ll query(int v,int tl,int tr,int l,int r){
    if(l<=tl && tr<=r) return t[v];
    if(r<tl || tr<l) return 0;
    int tm=(tl+tr)/2;
    return query(v*2,tl,tm,l,r)+
           query(v*2+1,tm+1,tr,l,r);
}


int main(){
    int n,Q;
    cin >> n >> Q;
    for(int i=1;i<=n;i++) cin >> a[i];
    build(1,1,n);
    while(Q--){
        int cmd,x,y;
        cin >> cmd >> x >> y;
        if(cmd==1) update(1,1,n,x,(ll)y);
        else cout << query(1,1,n,x,y) << "\n";
    }
}
