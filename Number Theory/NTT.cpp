#include <bits/stdc++.h>

#define pii pair<int, int>
#define ll long long

using namespace std;

///// CONSTANTS /////

const int LOGN = 23;
const int N = (1 << LOGN);
const int MOD = 998244353; 
const int G = 3; // Primative root may be used to calc a root of nth unit.

vector<int> rv[LOGN]; // rv[i][j] - bit reverse of j considering length i
vector<int> w[LOGN]; // w[i][j] - root of 2^ith unit ^ j
vector<int> iw[LOGN]; // iw[i][j] - inverse of w[i][j]

int binpow(int a, int n) {
    ll ans = 1;
    while(n != 0) {
        if(n & 1) ans *= a, ans %= MOD;
        a = (1LL * a * a) % MOD;
        n /= 2;
    }
    return ans;
}

void precalc() {
    for(int i = 0; i < LOGN; i++) {
        int ni = (1 << i);
        rv[i].resize(ni);
        w[i].resize(ni);
        iw[i].resize(ni);

        // fill w and iw
        int bw = binpow(G, (MOD - 1) / (1 << i));
        int ibw = binpow(bw, MOD - 2);
        ll cw = 1, icw = 1;

        for(int j = 0; j < ni; j++) {
            w[i][j] = cw;
            iw[i][j] = icw;

            cw *= bw; cw %= MOD; 
            icw *= ibw; icw %= MOD;
        }

        /// fill rv
        if(i == 0) {
            rv[i][0] = 0;
            continue;
        }
        int h = (1 << (i - 1));
        for(int j = 0; j < ni; j++) {
            rv[i][j] = (rv[i - 1][j & (h - 1)] << 1) | (j >= h);
        }
    }
}

void ntt(vector<int> &a, int n = -1, int ln = -1, bool invert = false) {
    if(n == -1) n = a.size();
    if(ln == -1) ln = log2(n);

    for(int i = 0; i < n; i++) {
        int j = rv[ln][i];
        if(j < i) {
            swap(a[i], a[j]);
        }
    }

    
    for(int lg = 1; (1 << lg) <= n; lg++) {
        int len = (1 << lg);
        for(int i = 0; i < n; i += len) {
            for(int j = 0; j < len / 2; j++) {
                int v = a[i + j];
                int c = (invert ? iw[lg][j] : w[lg][j]);
                int u =  (1LL * c * a[i + j + len / 2]) % MOD;
                a[i + j] = (v + u) % MOD;
                a[i + j + len / 2] = (v - u + MOD) % MOD;
            }
        }
    }

    if(invert) {
        int inv_n = binpow(n, MOD - 2);
        for(int &x : a) {
            x = (1LL * x * inv_n) % MOD;
        }
    }
}



vector<int> multiply(vector<int> A, vector<int> B) {
    int n = 1, ln = 0;
    while(n < A.size() + B.size()) n *= 2, ln++;
    
    vector<int> a(A.begin(), A.end());
    a.resize(n);
    vector<int> b(B.begin(), B.end());
    b.resize(n);

    ntt(a, n, ln);
    ntt(b, n, ln);

    for(int i = 0; i < n; i++) a[i] = (1LL * a[i] * b[i]) % MOD;

    ntt(a, n, ln, true);

    vector<int> answer;
    for(int i = 0; i < n; i++) {
        answer.push_back(a[i]);
    }

    while(!answer.empty() && answer.back() == 0) {
        answer.pop_back();
    }

    return answer;
}

int main() {
    precalc();
    vector<int> A = {1, 2, 3}; // 1 + 2x + 3x^2
    vector<int> B = {4, 5};    // 4 + 5x

    vector<int> C = multiply(A, B);
    for (int x : C) cout << x << " ";
    cout << "\n";
}
