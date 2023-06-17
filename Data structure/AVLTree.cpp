#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define ff first
#define ss second
#define pb push_back

using namespace std;

template<typename T>
class BST {
private:
    struct Node {
        T val;
        int height, len = 0;
        Node *left, *right;
        Node(T val = 0) : val(val) {
            left = right = nullptr;
            height = len = 1;
        }
    };
    void deleteDFS(Node *v) {
        if(v == nullptr) return;
        deleteDFS(v -> left);
        deleteDFS(v -> right);
        delete v;
    }
    void updateHeight(Node *node) {
        if(node == nullptr) return;
        int l = 0, r = 0;
        if(node -> left != nullptr) l = node -> left -> height;
        if(node -> right != nullptr) r = node -> right -> height;
        node -> height = max(l, r) + 1;
    }
    void updateLen(Node *node) {
        if(node == nullptr) return;
        int l = 0, r = 0;
        if(node -> left != nullptr) l = node -> left -> len;
        if(node -> right != nullptr) r = node -> right -> len;
        node -> len = l + r + 1;
    }
    int balanceFactor(Node *node) {
        if(node == nullptr) return 0;
        int l = 0, r = 0;
        if(node -> left != nullptr) l = node -> left -> height;
        if(node -> right != nullptr) r = node -> right -> height;
        return l - r;
    }
    Node *rightRotation(Node *x) {
        Node *y = x -> left;
        Node *temp = y -> right;
        // rotate
        y -> right = x;
        x -> left = temp;
        // update heights
        updateHeight(x);
        updateHeight(y);
        // update subtree sizes (len)
        updateLen(x);
        updateLen(y);
        // return a root
        return y;
    }
    Node *leftRotation(Node *x) {
        Node *y = x -> right;
        Node *temp = y -> left;
        // rotate
        y -> left = x;
        x -> right = temp;
        // update heights
        updateHeight(x);
        updateHeight(y);
        // update subtree sizes (len)
        updateLen(x);
        updateLen(y);
        // return a root
        return y;
    }
    Node *successor(Node *node) {
        if(node == nullptr) return node;
        while(node -> left != nullptr) {
            node = node -> left;
        }
        return node;
    }
    Node *insert(Node *node, T val) {
        // Base case
        if(node == nullptr) {
            node = new Node(val);
            return node;
        }
        // recursion
        if(val <= node -> val) {
            node -> left = insert(node -> left, val);
        } else {
            node -> right = insert(node -> right, val);
        }
        // update values
        updateHeight(node);
        updateLen(node);
        // balance
        int factor = balanceFactor(node);
        // case 1 : LL
        if(factor > 1 && val <= node -> left -> val) {
            return rightRotation(node);
        }
        // case 2 : RR
        if(factor < -1 && val > node -> right -> val) {
            return leftRotation(node);
        }
        // case 3 : LR
        if(factor > 1) {
            node -> left = leftRotation(node);
            return rightRotation(node);
        }
        // case 4 : RL
        if(factor < -1) {
            node -> right = rightRotation(node);
            return leftRotation(node);
        }
        // no rotation
        return node;
    }
    Node *remove(Node *node, T val, bool ind = false) {
        if(node == nullptr) return node;
        if(val < node -> val) node -> left = remove(node -> left, val);
        if(node -> val < val) node -> right = remove(node -> right, val);
        if(ind && node -> left != nullptr && node -> val == val) node -> left = remove(node -> left, val);
        else if(node -> val == val) {
            if(node -> left == nullptr || node -> right == nullptr) {
                Node *child = nullptr;
                if(node -> left != nullptr) child = node -> left;
                if(node -> right != nullptr) child = node -> right;
                delete node;
                node = child;
            } else {
                Node *child = successor(node -> right);
                node -> val = child -> val;
                node -> right = remove(node -> right, child -> val, true);
            }
        }
        if(node == nullptr) return node;
        updateLen(node);
        updateHeight(node);
        int factor = balanceFactor(node);
        if(factor > 1 && balanceFactor(root -> left) >= 0) {
            return rightRotation(node);
        }
        if(factor < -1 && balanceFactor(root -> right) <= 0) {
            return leftRotation(node);
        }
        if(factor > 1) {
            node -> left = leftRotation(node);
            return rightRotation(node);
        }
        if(factor < -1) {
            node -> right = rightRotation(node);
            return leftRotation(node);
        }
        return node;
    }
    Node *root;
    int n;
public:
    BST() {
        root = nullptr;
        n = 0;
    };
    ~BST() {
        deleteDFS(root);
    }
    void insert(T val) {
        root = insert(root, val);
        n++;
    }
    void remove(T val) {
        if(!find(val)) return;
        root = remove(root, val);
        n--;
    }
    bool find(T val) {
        Node *cur = root;
        while(cur != nullptr) {
            if(cur -> val == val) return true;
            if(val < cur -> val) {
                cur = cur -> left;
            } else {
                cur = cur -> right;
            }
        }
        return false;
    }
    T findKth(int k) {
        if(n == 0 || k <= 0) {
            return -1;
        }
        Node *cur = root;
        if(root -> len < k) return -1;
        while(cur -> height > 1) {
            if(cur -> left != nullptr) {
                if(k <= cur -> left -> len) {
                    cur = cur -> left;
                    continue;
                }
                k -= cur -> left -> len;
            }
            k--;
            if(k == 0) return cur -> val;
            cur = cur -> right;
        }
        return cur -> val;
    }
    int size() {
        return n;
    }
    bool isEmpty() {
        return (n == 0);
    }
};

const int N = 524289, mod = 998244353, INF = 1e9 + 1; // !!!

int main() {
    BST<int> bt;
    for(int i = 1; i <= 7; i++) {
        int x;
        cin >> x;
        bt.insert(x);
    }
    for(int i = 1; i <= 2; i++) {
        int x;
        cin >> x;
        bt.remove(x);
    }
    cout << bt.findKth(3);
}

// project has bugs and is yet to be completed
