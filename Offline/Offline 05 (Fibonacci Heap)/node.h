template <typename E>
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
