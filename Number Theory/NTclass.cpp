#include <bits/stdc++.h>

using namespace std;


class NumberTheory {
    typedef long long ll;
    inline static ll MOD = LLONG_MAX;
private:
    int *fact, *invfact, *lp;
    bool isFactorialPrepped = false, sievePrepped = false;
    vector<int> primes;
    bool multOverflow(ll a, ll b) {
        // detects if the multiplication overflows.
        if(a == 0 || b == 0) {
            return false;
        }
        ll c = a * b;
        return (c / b != a);
    }

    ll extended_gcd(ll a, ll b, ll &x, ll &y) {
        x = 1;
        y = 0;
        if(b == 0) {
            return a;
        }
        ll n_x = 0, n_y = 1; // value of x and y now.
        ll temp;
        while(b != 0) {
            // b is smaller
            ll q = a / b; // quantity
            a %= b;
            swap(a, b);

            temp = x - n_x * q;
            x = n_x;
            n_x = temp;

            temp = y - n_y * q;
            y = n_y;
            n_y = temp;
        }
        return a;
    }

    bool check_composite(ll x, ll a, ll d, ll s) {
        ll b = binpow(a, d, x);
        if(b == 1 || b == x-1)
            return false;
        for(int i = 1; i < s; i++) {
            b = mult(b, b, x);
            if(b == x - 1)
                return false;
        }
        return true;
    }

public:
    bool setMod(ll mod) {
        if(0 < mod && mod <= LLONG_MAX) {
            MOD = mod;
            return true;
        }
        return false;
    }
    
    ll binpow(ll a, ll n, ll mod = MOD) {
        ll ans = 1;
        while(n > 0) {
            if(n & 1) {
                ans *= a;
                ans %= mod;
            }
            a *= a;
            a %= mod;
            n /= 2;
        }
        return ans;
    }

    ll mult(ll a, ll b, ll mod = MOD) {
        if(multOverflow(a, b)) {
            ll ans = 0;
            while(b > 0) {
                if(b & 1) {
                    ans += a;
                    ans %= mod;
                }
                a += a;
                a %= mod;
                b /= 2;
            }
            return ans;
        }
        return (a * b) % mod;
    }

    ll gcd(ll a, ll b) {
        return (a == 0 || b == 0) ? a + b : gcd(a % b, b);
    }

    ll lcm(ll a, ll b) {
        ll d = gcd(a, b);
        a /= d;
        return a * b;
    }

    ll linear_Diophantine_equation(ll a, ll b, ll &x, ll &y) {
        ll d = extended_gcd(a, b, x, y);
        return d;
    }

    bool linear_Diophantine_equation(ll a, ll b, ll c, ll &x, ll &y) {
        ll d = extended_gcd(a, b, x, y);
        if (c % d) return false;
        ll k = c / d;
        x *= k;
        y *= k;
        return true;
    }

    ll modInverse(ll a, ll mod = MOD) {
        ll x, y;
        ll d = extended_gcd(a, mod, x, y);
        if(d != 1) return -1;
        return (x < 0) ? x + mod : x;
    }

    bool prepFactorials(int n, ll mod = MOD) {
        if(n > 10000000) return false;
        isFactorialPrepped = true;
        fact = new int[n + 1];
        invfact = new int[n + 1];
        fact[0] = 1 % mod;
        for(int i = 1; i <= n; i++) {
            fact[i] = mult(fact[i - 1], i, mod);
        }
        invfact[n] = modInverse(fact[n], mod);
        for(int i = n - 1; i >= 0; i--) {
            invfact[i] = mult(invfact[i + 1], (i + 1), mod);
        }
    }

    ll Binomial_C(ll n, ll k, ll mod = MOD) {
        if(n < k || k < 0) {
            return -1; // Impossible
        }
        if(isFactorialPrepped && n < sizeof(fact) / sizeof(int)) {
            ll ans = fact[n];
            ans = mult(ans, invfact[k]);
            ans = mult(ans, invfact[n - k]);
            return ans;
        }
        if(n >= 100000000) {
            return -1;
            // cannot process due to time error.
        }
        ll ans = 1;
        if(k < n / 2) k = n - k;
        for(int i = k + 1; i <= n; i++) {
            ans *= i;
            ans %= mod;
        }
        for(int i = 2; i <= n - k; i++) {
            ans *= modInverse(i, mod);
        }
        return ans;
    }

    bool sieve(int n) {
        if(n > 10000000) return false;
        lp = new int[n + 1];
        sievePrepped = true;
        lp[0] = 2;
        lp[1] = 0;
        for(int i = 2; i <= n; i++){
            if(lp[i] == 0){
                lp[i] = i;
                primes.push_back(i);
            }
            for(int p : primes) {
                if(p * i > n) break;
                lp[p * i] = p;
            }
        }
    }

    bool IsPrime(ll x) {
        // Miller-Rabin primality test
        if(sievePrepped && x < sizeof(lp) / sizeof(int)) {
            return (lp[x] == x);
        }
        if(x == 2 || x == 151)
            return true;
        if(x == 1 || x % 2 == 0 || x % 151==0)
            return false;
        ll s = 0;
        ll d = x - 1;
        while(d % 2 == 0) {
            s++;
            d /= 2;
        }
        for(ll u : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
            if(u == x)
                return true;
            if(check_composite(x, u, d, s))
                return false;
        }
        return true;
    }

    ll largestPrimeDivisor(ll x) {
        if(sievePrepped && x < sizeof(lp) / sizeof(int)) {
            return (ll)lp[x];
        }
        int d = 1;
        ll last = x;
        if(sievePrepped) {
            for(int p : primes) {
                if(x % p == 0) {
                    last = p;
                }
                while(x % p == 0) {
                    x /= p;
                }
            }
            d = primes.back();
        }
        for(ll i = d + 1; i * i <= x; i++) {
            if(x % i == 0) {
                last = i;
            }
            while(x % i == 0) {
                x /= i;
            }
        }
        return max(last, x);
    }

    void factorize(ll x, vector<pair<ll, int>> factors) {
        if(sievePrepped && x < sizeof(lp) / sizeof(int)) {
            while(x > 1) {
                ll p = lp[x];
                int cnt = 0;
                while (x % p == 0) {
                    x /= p;
                    cnt++;
                }
                factors.push_back({p, cnt});
            }
        } else {
            for(int i = 2; i * i <= x; i++) {
                int cnt = 0;
                while(x % i == 0) {
                    x /= (ll)i;
                    cnt++;
                }
                if(cnt) {
                    factors.push_back({(ll)i, cnt});
                }
            }
            if(x != 1) {
                factors.push_back({x, 1});
            }
        }
    }

    ll numDivisors(ll x) {
        vector<pair<ll, int>> factors;
        ll ans = 1;
        factorize(x, factors);
        for(pair<ll, int> pr : factors) {
            int cnt = pr.second;
            ans *= (cnt + 1);
        }
        return ans;
    }

    ll sumDivisors(ll x, ll mod = MOD) {
        vector<pair<ll, int>> factors;
        ll ans = 1;
        factorize(x, factors);
        for(pair<ll, int> pr : factors) {
            ll p = pr.first % mod;
            int alpha = pr.second;
            if(p == mod) {
                continue;
            }
            ll cur = binpow(p, alpha + 1) - 1;
            if(cur < 0) cur += mod;
            cur *= modInverse(p - 1);
            cur %= mod;
            ans *= cur;
        }
        return ans;
    }

}NT;


int main() {
    int n;
    cin >> n;
    NT.setMod(7);
    cout << NT.modInverse(n);
}
