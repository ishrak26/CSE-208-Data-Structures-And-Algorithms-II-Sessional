#include <bits/stdc++.h>
#include<unistd.h>

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

        Node(Node *node) {
            key = node->getKey();
            parent = node->getParent();
            child = node->getChild();
            left = node->getLeft();
            right = node->getRight();
            degree = node->getDegree();
            mark = node->getMark();
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
    };

    Node *min;
    int tot_nodes;

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
//            cerr << tmp->getKey() << ' ';
//            sleep(1);
            tmp = tmp->getRight();
            cnt++;
        } while (tmp != min);
//        cerr << '\n';
//        cerr << "cnt is " << cnt << '\n';

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
//                cerr << tot_nodes << ' ' << deg << ' ' << d << '\n';
                assert(d <= deg);
            }
            arr[d] = x;
        }

//        cerr << "aux array: ";
//        for (int i = 0; i <= deg; i++) {
//            if (arr[i] == nullptr) cerr << -1 << ' ';
//            else cerr << arr[i]->getKey() << ' ';
//        }
//        cerr << '\n';

        // build the new root list from arr
        min = nullptr;
        for (int i = 0; i <= deg; i++) {
            if (arr[i] != nullptr) {
                Node *node = new Node(arr[i]);
                if (min == nullptr) {
                    // root list hasn't been created yet
                    node->setParent(nullptr);
                    node->setLeft(node);
                    node->setRight(node);
                    min = node;
                }
                else {
                    // insert new_node into the root list
                    node->setParent(nullptr);
                    insertNode(min, node);
                    if (node->getKey() < min->getKey()) {
                        min = node;
                    }
                }
            }
        }
        delete[] arr;
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
//        cerr << "ret is " << ret << '\n';

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

//            tmp = min;
//            do {
//                cerr << tmp->getKey() << ' ';
//                sleep(1);
//                tmp = tmp->getRight();
//            } while (tmp != min);
//            cerr << '\n';

        }
        // remove the minimum
        min = removeNodeFromList(min);
        tot_nodes--;
//        cerr << min->getKey() << '\n';

        if (min != nullptr) {
            consolidate();
//            cerr << "consolidation done\n";
        }

        return ret;
    }

    void printTree(Node *x) {
        if (x == nullptr) return;
        cerr << "root is " << x->getKey() << '\n';
        cerr << "rootlist is ";
        Node *tmp = x;
        do {
//            cerr << tmp->getKey() << ' ';
            cerr << tmp->getKey() << ',' << tmp->getDegree() << ' ';
            tmp = tmp->getRight();
        } while (tmp != x);
        cerr << "\n\n";

        tmp = x;
        do {
            printTree(tmp->getChild());
            tmp = tmp->getRight();
        } while (tmp != x);
    }
};

