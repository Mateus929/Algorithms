#include <bits/stdc++.h>

using namespace std;

template<typename T>
class Fenwick {
private:
    int n;
    T *fenwick;

    int lsb(int x) {
        return x & -x;
    }

public:
    Fenwick(int n = 0) : n(n) {
        fenwick = new T[n + 1];
        fill(fenwick, fenwick + n + 1, 0);
    }

    ~Fenwick() {
        delete[] fenwick;
    }

    void update(int indx, T val) {
        while(indx <= n) {
            fenwick[indx] += val;
            indx += lsb(indx);
        }
    }

    T query(int indx) {
        T ans = 0;
        while(indx > 0) {
            ans += fenwick[indx];
            indx -= lsb(indx);
        }
        return ans;
    }

    T query(int l, int r) {
        return (l == 1 ? query(r) : query(r) - query(l - 1));
    }
};

int main() {
}
