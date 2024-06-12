#include<bits/stdc++.h>

#define ll long long

using namespace std;

vector<ll> h(100001), rh(100001), pw(100001);

void POW(int n, int p) {
    pw[0] = 1;
    for(int i = 1; i < n; i++)
        pw[i] = pw[i - 1] * p;
}

void Hash(string &st) {
    int n = st.size();
    h[0] = st[0] - 'a';
    for(int i = 1; i < n; i++)
        h[i] = h[i - 1] + (st[i] - 'a') * pw[i];
    rh[n - 1] = st[n - 1] - 'a';
    for(int i = n - 2; i >= 0; i--)
        rh[i] = rh[i + 1] + (st[i] - 'a') * pw[n - i - 1];
}

bool IsPal(int n, int l, int r) {
    int f, b;
    if(l == 0)
        f = h[r];
    else
        f = h[r] - h[l - 1];
    if(r == n - 1)
        b = rh[l];
    else
        b = rh[l] - rh[r + 1];
    if(f * pw[n - 1 - r] == b * pw[l])
        return true;
    return false;
}

int main() {
    string st;
    cin >> st;
    int n = st.size();
    POW(n, 29);
    Hash(st);
    int Q;
    cin >> Q;
    while(Q--) {
        int l, r;
        cin >> l >> r;
        if(IsPal(n, l, r))
            cout << "YES";
        else
            cout << "NO";
        cout << endl;
    }
}
