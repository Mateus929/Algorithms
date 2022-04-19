#include<bits/stdc++.h>
using namespace std;

int t[1001],a[1000000],len;

void build(int n){
    for(int i=0;i<len;i++)
        for(int j=i*len;j<min((i+1)*len,n);j++)
            t[i]+=a[j];
}

int get(int n,int l,int r){
    int ans=0;
    while(l<=r){
        if(l%len!=0 || l+len-1>r){
            ans+=a[l];
            l++;
        }
        else{
            ans+=t[l/len];
            l+=len;
        }
    }
    return ans;
}

void update(int n,int pos,int val){
    t[pos/len]+=(val-a[pos]);
    a[pos]=val;
}

int main(){
    int n,Q;
    cin >> n;
    for(int i=0;i<n;i++)
        cin >> a[i];
    len=sqrt(n);
    if(len*len<n)
        len++;
    build(n);
    cin >> Q;
    while(Q--){
        char id;
        cin >> id;
        if(id=='u'){
            int val,pos;
            cin >> pos >> val;
            update(n,pos-1,val);
        }
        else{
            int l,r;
            cin >> l >> r;
            cout << get(n,l-1,r-1) << endl;
        }
    }
}
