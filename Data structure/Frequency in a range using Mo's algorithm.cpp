#include<bits/stdc++.h>

using namespace std;
int block;

struct Query {
    int l, r, indx;

    Query(int l, int r, int indx) : l(l), r(r), indx(indx) {};

    Query() { l = r = indx = 0; }
};

bool comp(Query a, Query b) {
    int A = (a.l - 1) / block, B = (b.l - 1) / block;
    if(A == B)
        return (a.r < b.r);
    return (a.l < b.l);
}

int a[300005], freq[300005], cnt[300005], ans[300005];
int mo_ans = 0, mo_left = 0, mo_right = 0;

void add(int v) {
    int x = a[v];
    cnt[freq[x]]--;
    freq[x]++;
    cnt[freq[x]]++;
    if(freq[x] > mo_ans)
        mo_ans = freq[x];
}

void del(int v) {
    int x = a[v];
    cnt[freq[x]]--;
    freq[x]--;
    cnt[freq[x]]++;
    if(cnt[mo_ans] == 0)
        mo_ans--;
}

void update(int l, int r) {
    while(l > mo_left) {
        del(mo_left);
        mo_left++;
    }
    while(mo_left > l) {
        mo_left--;
        add(mo_left);
    }
    while(r > mo_right) {
        mo_right++;
        add(mo_right);
    }
    while(mo_right > r) {
        del(mo_right);
        mo_right--;
    }
}

int main() {
    vector<Query> mo_list;
    int n;
    cin >> n;
    block = sqrt(n);
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    int Q;
    cin >> Q;
    for(int i = 1; i <= Q; i++) {
        int l, r;
        cin >> l >> r;
        mo_list.push_back({l, r, i});
    }
    sort(mo_list.begin(), mo_list.end(), comp);
    for(Query q: mo_list) {
        update(q.l, q.r);
        ans[q.indx] = mo_ans;
    }
    for(int i = 1; i <= Q; i++)
        cout << ans[i] << endl;
}
