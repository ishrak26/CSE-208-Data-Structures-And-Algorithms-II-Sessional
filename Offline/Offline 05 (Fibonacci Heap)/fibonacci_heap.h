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

        E getKey() {
            return key;
        }

        Node *getLeft() {
            return left;
        }

        Node *getRight() {
            return right;
        }
    };

    Node *min;
    int tot_nodes;

    // concatenate b to a
    void concat_lists(Node *a, Node *b) {
        assert(a->left != nullptr && a->right != nullptr);
        assert(b->left != nullptr && b->right != nullptr);
        a->getLeft()->setRight(b);
        b->getLeft()->setRight(a);
        a->setLeft(b->getLeft());
        b->setLeft(a->getLeft());
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
            node->setLeft(min->getLeft());
            min->getLeft()->setRight(node);
            node->setRight(min);
            min->setLeft(node);
            if (key < min->getKey()) {
                min = node;
            }
        }
        tot_nodes++;
    }
};

