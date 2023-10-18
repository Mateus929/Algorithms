#include<bits/stdc++.h>
#define ll long long
using namespace std;

ll mult(ll a,ll b,ll m){
    if(b==1)
        return a;
    ll k=mult(a,b/2,m)%m;
    if(b%2==0)
        return (2*k)%m;
    return (2*k+a)%m;
}

ll binpower(ll a,ll n,ll mod){
    if(n==0)
        return 1;
    ll b=binpower(a,n/2,mod);
    b=mult(b,b,mod);
    return (n%2) ? mult(a,b,mod) : b;
}

bool check_composite(ll x,ll a,ll d,ll s){
    ll b=binpower(a,d,x);
    if(b==1 || b==x-1)
        return false;
    for(int i=1;i<s;i++){
        b=mult(b,b,x);
        if(b==x-1)
            return false;
    }
    return true;
}

bool IsPrime(ll x){
    if(x==2 || x==151)
        return true;
    if(x==1 || x%2==0 || x%151==0)
        return false;
    ll s=0;
    ll d=x-1;
    while(d%2==0){
        s++;
        d/=2;
    }
    for(ll u : {2,3,5,7,11,13,17,19,23,29,31,37}){
        if(u==x)
            return true;
        if(check_composite(x,u,d,s))
            return false;
    }
    return true;
}

int main(){
    int T;
    cin >> T;
    while(T--){
        ll x;
        cin >> x;
        if(IsPrime(x))
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}
