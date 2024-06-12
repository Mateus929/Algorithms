// works but remove function calls left and right rotations incorrectly without it gives run time error
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
        int height = 0, cnt = 0, len = 0;
        Node *left, *right;

        Node(T val = 0) : val(val) {
            left = right = nullptr;
            height = len = cnt = 1;
        }
    };

    void deleteDFS(Node *v) {
        if(v == nullptr) return;
        deleteDFS(v->left);
        deleteDFS(v->right);
        delete v;
    }

    void updateHeight(Node *node) {
        if(node == nullptr) return;
        int l = 0, r = 0;
        if(node->left != nullptr) l = node->left->height;
        if(node->right != nullptr) r = node->right->height;
        node->height = max(l, r) + 1;
    }

    void updateLen(Node *node) {
        if(node == nullptr) return;
        int l = 0, r = 0;
        if(node->left != nullptr) l = node->left->len;
        if(node->right != nullptr) r = node->right->len;
        node->len = l + r + node->cnt;
    }

    int balanceFactor(Node *node) {
        if(node == nullptr) return 0;
        int l = 0, r = 0;
        if(node->left != nullptr) l = node->left->height;
        if(node->right != nullptr) r = node->right->height;
        return l - r;
    }

    Node *rightRotation(Node *x) {
        Node *y = x->left;
        if(y == nullptr) {
            return x;
        }
        Node *temp = y->right;
        // rotate
        y->right = x;
        x->left = temp;
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
        Node *y = x->right;
        if(y == nullptr) {
            return x;
        }
        Node *temp = y->left;
        // rotate
        y->left = x;
        x->right = temp;
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
        while(node->left != nullptr) {
            node = node->left;
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
        if(val == node->val) {
            node->cnt++;
        }
        if(val < node->val) {
            node->left = insert(node->left, val);
        }
        if(val > node->val) {
            node->right = insert(node->right, val);
        }
        // update values
        updateHeight(node);
        updateLen(node);
        // balance
        int factor = balanceFactor(node);
        // case 1 : LL
        if(factor > 1 && val < node->left->val) {
            return rightRotation(node);
        }
        // case 2 : RR
        if(factor < -1 && val > node->right->val) {
            return leftRotation(node);
        }
        // case 3 : LR
        if(factor > 1) {
            node->left = leftRotation(node->left);
            return rightRotation(node);
        }
        // case 4 : RL
        if(factor < -1) {
            node->right = rightRotation(node->right);
            return leftRotation(node);
        }
        // no rotation
        return node;
    }

    Node *remove(Node *node, T val) {
        if(node == nullptr) return node;
        if(val < node->val) node->left = remove(node->left, val);
        if(node->val < val) node->right = remove(node->right, val);
        if(node->val == val) {
            node->cnt--;
            if(node->cnt == 0) {
                if(node->left == nullptr || node->right == nullptr) {
                    Node *child = nullptr;
                    if(node->left != nullptr) child = node->left;
                    if(node->right != nullptr) child = node->right;
                    Node *temp = node;
                    node = child;
                    delete temp;
                }else {
                    Node *child = successor(node->right);
                    node->val = child->val;
                    node->cnt = child->cnt;
                    child->cnt = 1;
                    node->right = remove(node->right, child->val);
                }
            }
        }
        if(node == nullptr) return node;
        updateLen(node);
        updateHeight(node);
        int factor = balanceFactor(node);
        if(factor > 1 && balanceFactor(root->left) >= 0) {
            return rightRotation(node);
        }
        if(factor < -1 && balanceFactor(root->right) <= 0) {
            return leftRotation(node);
        }
        if(factor > 1 && balanceFactor(root->left) < 0) {
            node->left = leftRotation(node->left);
            return rightRotation(node);
        }
        if(factor < -1 && balanceFactor(root->right) > 0) {
            node->right = rightRotation(node->right);
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
        n++;
        root = insert(root, val);
    }

    void remove(T val) {
        if(find(val) == 0) return;
        n--;
        if(n == 0) {
            root = nullptr;
            return;
        }
        root = remove(root, val);
    }

    int find(T val) {
        if(n == 0) return 0;
        Node *cur = root;
        while(cur != nullptr) {
            if(cur->val == val) {
                return cur->cnt;
            }
            if(val < cur->val) {
                cur = cur->left;
            }else {
                cur = cur->right;
            }
        }
        return 0;
    }

    T findKth(int k) {
        if(n == 0 || k <= 0) {
            return -1;
        }
        Node *cur = root;
        if(root->len < k) return -1;
        while(cur->height > 1) {
            if(cur->left != nullptr) {
                if(k <= cur->left->len) {
                    cur = cur->left;
                    continue;
                }
                k -= cur->left->len;
            }
            k -= cur->cnt;
            if(k <= 0) return cur->val;
            cur = cur->right;
        }
        return cur->val;
    }

    int size() {
        return n;
    }

    bool isEmpty() {
        return (n == 0);
    }
};

multiset<int> st;

int find_kth(int k) {
    for(int u: st) {
        k--;
        if(k == 0) return u;
    }
    return -1;
}

void print() {
    cout << "Printing multiset...\n";
    for(int u: st) cout << u << " ";
    cout << "\n....";
}

int main() {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    BST<int> bt;
    bt.insert(3);
    bt.remove(3);
    int Q;
    cin >> Q;
    int cnt = 0;
    for(int i = 1; i <= Q; i++) {
        int x = rng() % 10;
        int ind = rng() % 2;
        if(ind == 0) {
            bt.insert(x);
            st.insert(x);
        }else {
            multiset<int>::iterator it = st.find(x);
            bool isIn = bt.find(x);
            if(isIn && it == st.end()) {
                cout << "Step " << i << ": The element wasn't erased";
                return 0;
            }
            if(it != st.end()) {
                if(!isIn) {
                    cout << "Step " << i << ": The element was erased for no reason";
                    return 0;
                }
                st.erase(it);
            }
            bt.remove(x);
            if(isIn) cnt++;
            if(bt.find(x) != st.count(x)) {
                cout << "Step " << i << ": didn't count elements correctly!\n";
                return 0;
            }
        }
        if(bt.size() != st.size()) {
            cout << "Step " << i << ": Sizes dont match! ";
            cout << "Error is " << bt.size() - st.size() << "\n";
            return 0;
        }
        int n = st.size();
        if(n == 0) continue;
        int k = rng() % n;
        k++;
        if(bt.findKth(k) != find_kth(k)) {
            cout << "Step " << i << ": " << k << "th element didn't match!\n";
            return 0;
        }
    }
    cout << "Everything is fine!\n";
    cout << "Number of elements removal = " << cnt;
}
