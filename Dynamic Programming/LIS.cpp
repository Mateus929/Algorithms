#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int lis(int a[], int n, vector<int> &ans) {
    ans.assign(n, INF);
    for(int i = 0; i < n; i++) {
        int indx = lower_bound(ans.begin(), ans.end(), a[i]) - ans.begin();
        ans[indx] = a[i];
    }
    while(ans.back() == INF) {
        ans.pop_back();
    }
    return ans.size();
}

int main() {
    int n;
    cin >> n;
    int a[n];
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> ans;
    cout << lis(a, n, ans);
};
