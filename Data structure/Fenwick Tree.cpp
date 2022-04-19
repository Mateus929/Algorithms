#include<bits/stdc++.h>
#define ll long long

using namespace std;

const int NMAX=100001;
ll fenwik[NMAX];
int lsb(int indx){
    return indx&-indx;
}
void update(int indx,ll val,int n){
    while(indx<=n){
        fenwik[indx]+=val;
        indx+=lsb(indx);
    }
}
void build(ll a[],int n){
    for(int i=1;i<=n;i++)
        update(i,a[i],n);
}
ll query(int indx){
    ll ans=0;
    while(indx>0){
        ans+=fenwik[indx];
        indx-=lsb(indx);
    }
    return ans;
}
ll query(int l,int r){
    if(l==1)
        return query(r);
    return query(r)-query(l-1);
}

int main(){
    int n,Q;
    cin >> n >> Q;
    ll a[MAXN];
    for(int i=1;i<=n;i++)
        cin >> a[i];
    build(a,n);
    while(Q--){
        char cmd;
        cin >> cmd;
        if(cmd=='u'){
            int pos,val;
            cin >> pos >> val;
            update(pos,val,n);
        }
        if(cmd=='q'){
            int l,r;
            cin >> l >> r;
            cout << query(l,r) << endl;
        }
    }
}
