#include<bits/stdc++.h>
#define ll long long

using namespace std;

ll gcd(ll a,ll b,ll &u,ll &v){
    if(a==0){
        u=0;
        v=1;
        return b;
    }
    ll u1,v1;
    ll d=gcd(b%a,a,u1,v1);
    v=u1;
    u=v1-(b/a)*u1;
    return d;
}

ll inverse(ll x,ll m){
    ll u,v;
    ll d=gcd(x,m,u,v);
    if(d!=1)
        return -1;
    while(u<0)
        u+=m;
    return (u%m);
}

int main(){
    ll x,p;
    cin >> x >> p;
    cout << inverse(x,p);
}
