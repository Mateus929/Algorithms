#include<bits/stdc++.h>


using namespace std;

string lcs(string &a, string &b) {
    int n = a.size(), m = b.size();
    int dp[n + 1][m + 1];
    for(int i = 0; i <= n; i++)
        for(int j = 0; j <= m; j++) {
            if(i == 0 || j == 0) {
                dp[i][j] = 0;
                continue;
            }
            if(a[i - 1] == b[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    int indx = dp[n][m];
    string st(indx, ' ');
    int l = n, r = m;
    while(l > 0 && r > 0) {
        if(a[l - 1] == b[r - 1]) {
            st[indx - 1] = a[l - 1];
            l--;
            r--;
            indx--;
            continue;
        }
        if(dp[l - 1][r] > dp[l][r - 1])
            l--;
        else
            r--;
    }
    return st;
}

int main() {
    int T;
    cin >> T;
    while(T--) {
        string a, b;
        cin >> a >> b;
        cout << lcs(a, b) << endl;;
    }
}
