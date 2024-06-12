#include<bits/stdc++.h>

using namespace std;

int st[100001][20];

void build(vector<int> &a) {
    int n = a.size() - 1;
    for(int j = 0; j < 20; j++)
        for(int i = 1; i <= n; i++)
            if(j == 0)
                st[i][j] = a[i];
            else if(i + (1 << (j - 1)) <= n)
                st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
}

int get(int l, int r) {
    int b = log2(r - l + 1);
    return min(st[l][b], st[r - (1 << b) + 1][b]);
}

int main() {
    int n, Q;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    build(a);
    cin >> Q;
    while(Q--) {
        int l, r;
        cin >> l >> r;
        cout << get(l, r) << endl;
    }
}
