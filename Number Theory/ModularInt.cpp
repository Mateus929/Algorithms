#include <bits/stdc++.h>

#define ll long long
#define pii pair<int, int>
#define ff first
#define ss second
#define pb push_back
#define new2023 ios_base :: sync_with_stdio(false); cin.tie(0);

using namespace std;

template<int MOD>
class Modular {
private:
    int val;
    static const int mod = MOD;

    Modular inverse(const Modular &A) {
        Modular u = 0, v = 1;
        int a = A.val;
        int b = mod;
        while(a != 0) {
            int t = b / a;
            b -= t * a;
            swap(b, a);
            u -= t * v;
            swap(u, v);
        }
        return (b == 1) ? u : 0;
    }

public:
    explicit operator int() const {
        return val;
    }

    Modular() { val = 0; }

    Modular(ll x) {
        val = x % mod;
        if(val < 0) val += mod;
    }

    friend bool operator==(const Modular &A, const Modular &B) { return A.val == B.val; }

    friend bool operator!=(const Modular &A, const Modular &B) { return A.val != B.val; }

    friend bool operator<(const Modular &A, const Modular &B) { return A.val < B.val; }

    friend bool operator>(const Modular &A, const Modular &B) { return A.val > B.val; }

    Modular &operator+=(const Modular &A) {
        val += A.val;
        val %= mod;
        return *this;
    }

    Modular &operator-=(const Modular &A) {
        val -= A.val;
        if(val < 0) val += mod;
        return *this;
    }

    Modular &operator*=(const Modular &A) {
        val = (int) ((ll) val * A.val % mod);
        return *this;
    }

    Modular &operator/=(const Modular &A) { return *this *= inverse(A); }

    Modular operator-() const { return Modular(-val); }

    Modular &operator++() { return *this += 1; }

    Modular &operator--() { return *this -= 1; }

    friend Modular operator+(Modular A, const Modular &B) { return A += B; }

    friend Modular operator-(Modular A, const Modular &B) { return A -= B; }

    friend Modular operator*(Modular A, const Modular &B) { return A *= B; }

    friend Modular operator/(Modular A, const Modular &B) { return A /= B; }

    friend istream &operator>>(istream &stream, Modular &A) {
        ll x;
        stream >> x;
        A = Modular(x);
        return stream;
    }

    friend ostream &operator<<(ostream &stream, Modular &A) { return stream << A.val; }
};

const int N = 3000000;
const int mod = 1000000007;
const int INF = 1e9;

using Mint = Modular<mod>;


int main() {

}
