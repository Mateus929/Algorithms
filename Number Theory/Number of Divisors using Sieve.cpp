#include <bits/stdc++.h>

using namespace std;

const int N = 1000000;

int lp[N + 1];
/// lp[x] = Largest Prime Factor of x

void sieve() {
    for(int i = 2; i <= N; i++) {
        if(!lp[i]) {
            for(int j = i; j <= N; j += i)
                lp[j] = i;
        }
    }
}

int d(int n) {
    int ans = 1;
    while(n > 1) {
        int prime = lp[n], cnt = 0;
        while(n % prime == 0) {
            n /= prime;
            cnt++;
        }
        ans *= (cnt + 1);
    }
    return ans;
}

int main() {
    int T;
    cin >> T;
    sieve();
    while(T--) {
        int n;
        cin >> n;
        cout << d(n) << "\n";
    }
}
