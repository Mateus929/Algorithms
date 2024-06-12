#include<bits/stdc++.h>


using namespace std;

struct trie {
    trie *children[26];
    int cnt = 0;

    trie() {
        for(auto &u: children)
            u = nullptr;
    }
};

void add(trie *root, string &st) {
    trie *cur = root;
    for(char c: st) {
        int indx = c - 'a';
        if(cur->children[indx] == nullptr)
            cur->children[indx] = new trie;
        cur = cur->children[indx];
        cur->cnt++;
    }
}

int get(trie *root, string &st) {
    trie *cur = root;
    for(char c: st) {
        int indx = c - 'a';
        if(cur->children[indx] == nullptr)
            return 0;
        cur = cur->children[indx];
    }
    return cur->cnt;
}

int main() {
    trie *root = new trie;
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        string st;
        cin >> st;
        add(root, st);
    }
    int Q;
    cin >> Q;
    while(Q--) {
        string st;
        cin >> st;
        cout << get(root, st) << endl;
    }
}
