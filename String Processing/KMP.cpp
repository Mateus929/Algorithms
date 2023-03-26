#include <bits/stdc++.h>

using namespace std;

void pi_function(string &str, vector<int> &pi) {
    int n = str.size();
    pi.assign(n, 0);
    for(int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while(j > 0 && str[i] != str[j]) {
            j = pi[j - 1];
        }
        pi[i] = (str[j] == str[i] ? j + 1 : 0);
    }
}

void KMP(string &s, string &t, vector<int> &ans) {
    // the vector ans contains indexes i for which s[i...i+|t|-1] = t.
    string str = t + "*" + s;
    vector<int> pi;
    pi_function(str, pi);
    for(int i = t.size() + 1; i < str.size(); i++) {
        if(pi[i] == t.size()) {
            ans.push_back(i - 2 * t.size());
        }
    }
}

int main() {
    int T;
    cin >> T;
    while(T--) {
        string s, t;
        cin >> s >> t;
        vector<int> ans;
        KMP(s, t, ans);
        if(ans.size() == 0) cout << "Not Found\n";
        else {
            cout << ans.size() << "\n";
            for(int u : ans) cout << u + 1 << " ";
            cout << "\n";
        }
    }

}
