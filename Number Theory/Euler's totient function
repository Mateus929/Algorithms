#include<bits/stdc++.h>
#define ll long long
using namespace std;

ll phi(ll n){
    ll ans=n;
    for(ll i=2;i*i<=n;i++){
        if(n%i==0)
            ans-=ans/i;
        while(n%i==0)
            n/=i;
    }
    return (n>1) ? ans-ans/n : ans;
}

int main(){
    int T;
    cin >> T;
    while(T--){
        ll n;
        cin >> n;
        cout << phi(n) << "\n";
    }
}
