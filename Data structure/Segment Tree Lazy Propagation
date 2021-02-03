#include<bits/stdc++.h>
#define ll long long

using namespace std;

vector<int> t(400001),lazy(400001);

void build(vector<int> &a,int v,int tl,int tr){
    if(tl==tr){
        t[v]=a[tl];
        lazy[v]=0;
    }
    else{
        int tm=(tl+tr)/2;
        build(a,v*2,tl,tm);
        build(a,v*2+1,tm+1,tr);
        lazy[v]=0;
        t[v]=t[v*2]+t[v*2+1];
    }
}
void upd(int v,int x,int tl,int tr){
    t[v]+=x*(tr-tl+1);
    lazy[v]+=x;
}
void push(int v,int tl,int tr){
    if(lazy[v]==0)
        return;
    int tm=(tl+tr)/2;
    upd(v*2,lazy[v],tl,tm);
    upd(v*2+1,lazy[v],tm+1,tr);
    lazy[v]=0;
}
int get(int v,int tl,int tr,int l,int r){
    if(tl==l && r==tr)
        return t[v];
    push(v,tl,tr);
    int tm=(tl+tr)/2;
    if(r<=tm)
        return get(v*2,tl,tm,l,r);
    if(l>tm)
        return get(v*2+1,tm+1,tr,l,r);
    return get(v*2,tl,tm,l,tm) +
           get(v*2+1,tm+1,tr,tm+1,r);
}

void update(int v,int tl,int tr,int l,int r,int x){
    if(tl==l && r==tr){
        upd(v,x,tl,tr);
        return;
    }
    push(v,tl,tr);
    int tm=(tl+tr)/2;
    if(r<=tm)
        update(v*2,tl,tm,l,r,x);
    if(l>tm)
        update(v*2+1,tm+1,tr,l,r,x);
    if(l<=tm && tm<r){
        update(v*2,tl,tm,l,tm,x);
        update(v*2+1,tm+1,tr,tm+1,r,x);
    }
    t[v]=t[v*2]+t[v*2+1];
}

int main(){
    int n;
    cin >> n;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++)
        cin >> a[i];
    build(a,1,1,n);
    int Q;
    cin >>  Q;
    while(Q--){
        char c;
        cin >> c;
        if(c=='u'){
            int l,r,pos;
            cin >> l >> r >> pos;
            update(1,1,n,l,r,pos);
        }
        else{
            int l,r;
            cin >> l >> r;
            cout << get(1,1,n,l,r) << endl;
        }
    }
}
