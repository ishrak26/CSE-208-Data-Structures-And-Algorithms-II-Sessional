#include <bits/stdc++.h>

using namespace std;

#define FASTIO               \
    ios::sync_with_stdio(0); \
    cin.tie(0)
#define PB push_back

#define SZ 100005

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<pii> vp;
typedef vector<pll> vpll;

// const ld PI = acos(-1.0);
// const ll MOD = 1000000007;
const ll INF = 1LL<<60;

template <typename E>
class Fibonacci_heap {
    class Node {
        E key;
        Node *parent;
        Node *child;
        Node *right;
        Node *left;
        int degree;
        bool mark;
        int id;

    public:
        Node() {
            parent = child = right = left = nullptr;
            degree = 0;
            mark = false;
            id = -1;
        }

        Node(const E key) {
            this->key = key;
            parent = child = nullptr;
            right = left = this;
            degree = 0;
            mark = false;
            id = -1;
        }

        Node(Node *node) {
            key = node->getKey();
            parent = node->getParent();
            child = node->getChild();
            left = node->getLeft();
            right = node->getRight();
            degree = node->getDegree();
            mark = node->getMark();
            id = node->getID();
        }

        ~Node() {

        }

        void setKey(E key) {
            this->key = key;
        }

        void setLeft(Node *left) {
            this->left = left;
        }

        void setRight(Node *right) {
            this->right = right;
        }

        void setParent(Node *parent) {
            this->parent = parent;
        }

        void setChild(Node *child) {
            this->child = child;
        }

        void setDegree(int degree) {
            this->degree = degree;
        }

        void setMark(bool mark) {
            this->mark = mark;
        }

        void setID(int id) {
            this->id = id;
        }

        E getKey() {
            return key;
        }

        Node *getLeft() {
            return left;
        }

        Node *getRight() {
            return right;
        }

        Node *getParent() {
            return parent;
        }

        Node *getChild() {
            return child;
        }

        int getDegree() {
            return degree;
        }

        bool getMark() {
            return mark;
        }

        int getID() {
            return id;
        }
    };

    Node *min;
    int tot_nodes;
    vector<Node*> node_ids;
    stack<int> freelist; // node id's currently free

    // concatenate b to a
    void concatLists(Node *a, Node *b) {
        assert(a->getLeft() != nullptr && a->getRight() != nullptr);
        assert(b->getLeft() != nullptr && b->getRight() != nullptr);
        a->getLeft()->setRight(b);
        b->getLeft()->setRight(a);
        Node *tmp = a->getLeft();
        a->setLeft(b->getLeft());
        b->setLeft(tmp);
    }

    // returns the right node of x
    Node *removeNodeFromList(Node *x) {
        assert(x != nullptr);
        Node *ret = x->getRight();
        if (ret == x) {
            ret = nullptr; // x has no sibling
        }
        x->getLeft()->setRight(x->getRight());
        x->getRight()->setLeft(x->getLeft());
        delete x;
        return ret;
    }

    int calc_ceil_log2(int n) {
        int bits = sizeof(int) * 8;
        int i;
        for (i = bits-1; i >= 0; i--) {
            if (n & (1<<i)) break;
        }
        if (__builtin_popcount(n) == 1) return i;
        return i+1;
    }

    // insert node y to x's list
    void insertNode(Node *x, Node *y) {
        assert(x != nullptr && y != nullptr);
        y->setRight(x);
        y->setLeft(x->getLeft());
        y->getLeft()->setRight(y);
        x->setLeft(y);
    }

    // make y a child of x
    // both were initially in the root list
    void consolidateLink(Node *x, Node *y) {
        // remove y from the root list
        y->getLeft()->setRight(y->getRight());
        y->getRight()->setLeft(y->getLeft());

        y->setRight(y);
        y->setLeft(y);
        y->setParent(x);
        y->setMark(false);

        x->setDegree(x->getDegree() + 1);
        if (x->getChild() == nullptr) {
            // x previously had no child
            x->setChild(y);
        }
        else {
            // insert y in the children list of x
            insertNode(x->getChild(), y);
            x->setChild(y);
        }
    }

    void consolidate() {
        int deg = calc_ceil_log2(tot_nodes);
        Node **arr = new Node*[deg+1];
        for (int i = 0; i <= deg; i++) {
            arr[i] = nullptr;
        }
        assert(!empty()); // min != nullptr

        // count the length of the rootlist
        int cnt = 0;
        Node *tmp = min;
        do {
            tmp = tmp->getRight();
            cnt++;
        } while (tmp != min);

        Node *w = min;
        for (int i = 0; i < cnt; i++) {
            Node *x = w;
            w = w->getRight();
            int d = x->getDegree();
            assert(d <= deg);
            while (arr[d] != nullptr) {
                Node *y = arr[d];
                if (x->getKey() > y->getKey()) {
                    swap(x, y);
                }
                consolidateLink(x, y);
                arr[d] = nullptr;
                d++;
                assert(d <= deg);
            }
            arr[d] = x;
        }

        // build the new root list from arr
        min = nullptr;
        for (int i = 0; i <= deg; i++) {
            if (arr[i] != nullptr) {
                Node *node = arr[i];

                if (min == nullptr) {
                    // root list hasn't been created yet
//                    node->setParent(nullptr);
                    assert(node->getParent() == nullptr);
                    node->setLeft(node);
                    node->setRight(node);
                    min = node;
                }
                else {
                    // insert new_node into the root list
//                    node->setParent(nullptr);
                    assert(node->getParent() == nullptr);
                    insertNode(min, node);
                    if (node->getKey() < min->getKey()) {
                        min = node;
                    }
                }
            }
        }
        delete[] arr;
    }

    void cut(Node *x, Node *y) {
        assert(x->getParent() == y);
        // x may not be a direct child of y
        // instead, x can be a sibling of the direct child of y

        // remove x from the child list of y
        if (y->getDegree() == 1) {
            // x is the only child
            y->setChild(nullptr);
            y->setDegree(0);
        }
        else {
            // x has siblings
            assert(y->getDegree() > 1);
            y->setDegree(y->getDegree() - 1);

            if (x == y->getChild()) {
                // x is the direct child of y
                y->setChild(x->getRight());
                y->getChild()->setLeft(x->getLeft());
                x->getLeft()->setRight(y->getChild());
            }
            else {
                // x is a sibling of the direct child of y
                x->getLeft()->setRight(x->getRight());
                x->getRight()->setLeft(x->getLeft());
            }
        }

        // add x to root list
        x->setParent(nullptr);
        insertNode(min, x);
        x->setMark(false);
    }

    void cascadingCut(Node *y) {
        assert(y != nullptr);
        Node *z = y->getParent();
        if (z != nullptr) {
            if (y->getMark() == false) {
                y->setMark(true);
            }
            else {
                cut(y, z);
                cascadingCut(z);
            }
        }
    }

    void deallocateNode(Node *root, int len) {
        // root is a node belonging to a circular doubly linked list
        // list size is len

        if (root == nullptr) {
            assert(len == 0);
            return;
        }

        for (int i = 0; i < len-1; i++) {
            deallocateNode(root->getChild(), root->getDegree());
            root->getLeft()->setRight(root->getRight());
            root->getRight()->setLeft(root->getLeft());
            Node *tmp = root;
            root = root->getRight();
            delete tmp;
        }
        // delete the last node of the linked list
        assert(root != nullptr && root->getRight() == root && root->getLeft() == root);
        deallocateNode(root->getChild(), root->getDegree());
        delete root;
    }

public:
    Fibonacci_heap() {
        min = nullptr;
        tot_nodes = 0;
    }

    ~Fibonacci_heap() {
        // find the length of the root list
        if (empty()) return;
        int cnt = 0;
        Node *tmp = min;
        do {
            tmp = tmp->getRight();
            cnt++;
        } while (tmp != min);

        deallocateNode(min, cnt);
    }

    int size() {
        return tot_nodes;
    }

    E getMinKey() {
        assert(min != nullptr);
        return min->getKey();
    }

    bool empty() {
        if (tot_nodes == 0) {
            assert(min == nullptr);
            return true;
        }
        return false;
    }

    int insert(const E key) {
        Node *node = new Node(key);

        int idx = -1;
        if (!freelist.empty()) {
            idx = freelist.top();
            freelist.pop();
            assert(idx < node_ids.size() && node_ids[idx] == nullptr);
            node_ids[idx] = node;
        }
        else {
            idx = node_ids.size();
            node_ids.push_back(node);
        }
        node->setID(idx);

        if (empty()) {
            min = node;
        }
        else {
            // insert node to the left of min
            insertNode(min, node);
            if (key < min->getKey()) {
                min = node;
            }
        }
        tot_nodes++;
        return idx;
    }

    E extractMinKey() {
        E ret = getMinKey();

        Node *x = min->getChild();
        if (x != nullptr) {
            // set the parent of each children to null
            Node *tmp = x;
            do {
                x->setParent(nullptr);
                x = x->getRight();
            } while (x != tmp);
            min->setDegree(0);
            min->setChild(nullptr);

            // concatenate the children to root list
            concatLists(min, x);
        }
        // remove the minimum
        int idx = min->getID();
        node_ids[idx] = nullptr;
        freelist.push(idx);
        min = removeNodeFromList(min);
        tot_nodes--;

        if (min != nullptr) {
            consolidate();
        }

        return ret;
    }

    void decreaseKey(int id, E key) {
        assert(id < node_ids.size());
        Node *x = node_ids[id];
        assert(x != nullptr);
        assert(key <= x->getKey());
        if (key == x->getKey()) return;
        x->setKey(key);
        Node *y = x->getParent();
        if (y != nullptr && x->getKey() < y->getKey()) {
            cut(x, y);
            cascadingCut(y);
        }
        if (x->getKey() < min->getKey()) {
            min = x;
        }
    }
};

int n, m;
vector<vector<pair<int, ll>>> G;
vll dis;

void dijkstra(int src) {
    dis[src] = 0;
    Fibonacci_heap<pair<ll, int> > pq;
    vi ids(n+1, -1);
    for (int i = 1; i <= n; i++) {
        ids[i] = pq.insert({dis[i], i});
    }

    while (!pq.empty()) {
        pair<ll, int> p = pq.extractMinKey();
        int u = p.second;
        for (pii v : G[u]) {
            if (dis[u] + v.second < dis[v.first]) {
                dis[v.first] = dis[u] + v.second;
                pq.decreaseKey(ids[v.first], {dis[v.first], v.first});
            }
        }
    }
}

void solve(int t) {
    cin >> n >> m;
    G.resize(n+1);
    dis.resize(n+1, INF);
    for (int i = 0; i < m; i++) {
        int u, v;
        ll c;
        cin >> u >> v >> c;
        G[u].PB({v, c});
    }
    dijkstra(1);
    for (int i = 1; i <= n; i++) cout << dis[i] << ' ';
    cout << '\n';
}

int main() {
    FASTIO;
    int tc;
    tc = 1;
//    cin >> tc;
    for (int tt = 1; tt <= tc; tt++)
    {
        solve(tt);
    }
    return 0;
}

