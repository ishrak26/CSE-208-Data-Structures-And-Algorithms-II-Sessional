#include <bits/stdc++.h>

using namespace std;

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

    public:
        Node() {
            parent = child = right = left = nullptr;
            degree = 0;
            mark = false;
        }

        Node(const E key) {
            this->key = key;
            parent = child = nullptr;
            right = left = this;
            degree = 0;
            mark = false;
        }

        ~Node() {

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

        E getKey() {
            return key;
        }

        Node *getLeft() {
            return left;
        }

        Node *getRight() {
            return right;
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
    };

    Node *min;
    int tot_nodes;

    // concatenate b to a
    void concatLists(Node *a, Node *b) {
        assert(a->getLeft() != nullptr && a->getRight() != nullptr);
        assert(b->getLeft() != nullptr && b->getRight() != nullptr);
        a->getLeft()->setRight(b);
        b->getLeft()->setRight(a);
        a->setLeft(b->getLeft());
        b->setLeft(a->getLeft());
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
        Node *w = min;
        do {
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
        } while (w != min);

        // build the new root list from arr
        min = nullptr;
        for (int i = 0; i <= deg; i++) {
            if (arr[i] != nullptr) {
                if (min == nullptr) {
                    // root list hasn't been created yet
                    min = arr[i];
                }
                else {
                    // insert arr[i] into the root list
                    insertNode(min, arr[i]);
                    if (arr[i]->getKey() < min->getKey()) {
                        min = arr[i];
                    }
                }
            }
        }
    }

public:
    Fibonacci_heap() {
        min = nullptr;
        tot_nodes = 0;
    }

    // Union
    Fibonacci_heap(Fibonacci_heap *h1, Fibonacci_heap *h2) {
        // to be implemented
        if (h1.empty()) {
            if (h2.empty()) {
                Fibonacci_heap();
            }
            else {
                 ;
            }
        }
    }

    ~Fibonacci_heap() {

    }

    int getTotNodes() {
        return tot_nodes;
    }

    Node *getMin() {
        return min;
    }

    E getMinKey() {
        assert(min != nullptr);
        return min->getKey();
    }

    bool empty() {
        return min==nullptr;
    }

    void insert(const E key) {
        Node *node = new Node(key);
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

            // concatenate the children to root list
            concatLists(min, x);

            // remove the minimum
            min = removeNodeFromList(min);

            if (min != nullptr) {
                consolidate();
                cerr << "consolidation done\n";
            }
        }
        else {
            // remove the minimum
            min = removeNodeFromList(min);

            if (min != nullptr) {
                // traverse through the root list to set the new minimum
                Node *tmp = min;
                Node *finish = tmp;
                do {
                    if (tmp->getKey() < min->getKey()) {
                        min = tmp;
                    }
                    tmp = tmp->getRight();
                } while (tmp != finish);
            }
        }
        tot_nodes--;

        return ret;
    }

    void printList(Node *x) {
        Node *tmp = x;
        do {
            cerr << tmp->getKey() << ' ';
            tmp = tmp->getRight();
        } while (tmp != x);
        cerr << '\n';
    }
};

