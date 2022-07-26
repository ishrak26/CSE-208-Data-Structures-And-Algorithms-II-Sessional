#include<bits/stdc++.h>

using namespace std;

template <typename E>
class RedBlackTree {
    class Node {
        E key;
        Node *parent;
        Node *left;
        Node *right;
        int color; // -1: undefined, 0: black, 1: red
        int subtree_sz; // subtree size with this node as the root (root included)

    public:
        Node() {
            parent = left = right = nullptr;
            color = 0; // color of sentinel is black
            subtree_sz = 0;
        }

        Node(E key) {
            this->key = key;
            parent = nullptr;
            left = new Node; // sentinel
            right = new Node; // sentinel
            left->setParent(this);
            right->setParent(this);
            color = 1; // new node will always be colored red initially
            subtree_sz = 1;
        }

        // setters
        void setKey(E key) {
            this->key = key;
        }

        void setParent(Node *parent) {
            this->parent = parent;
        }

        void setLeft(Node *left) {
            this->left = left;
        }

        void setRight(Node *right) {
            this->right = right;
        }

        void setColor(int color) {
            this->color = color;
        }

        void setSubtree_sz(int subtree_sz) {
            this->subtree_sz = subtree_sz;
        }

        // getters
        E getKey() {
            return this->key;
        }

        Node* getParent() {
            return this->parent;
        }

        Node* getLeft() {
            return this->left;
        }

        Node* getRight() {
            return this->right;
        }

        int getColor() {
            return this->color;
        }

        int getSubtree_sz() {
            return this->subtree_sz;
        }

        bool isLeaf() {
            return (left==nullptr && right==nullptr);
        }
    };

    void left_rotate(Node *x) {
        assert(!x->isLeaf()));
        Node *y = x->getRight();
        assert(!y->isLeaf());

        int alpha = 0, beta = 0, gamma = 0;
        alpha = x->getLeft()->getSubtree_sz();
        beta = y->getLeft()->getSubtree_sz();
        gamma = y->getRight()->getSubtree_sz();
        assert(x->getSubtree_sz() == alpha + y->getSubtree_sz() + 1);
        assert(y->getSubtree_sz() == beta + gamma + 1);

        // y's left will now be x's right
        x->setRight(y->getLeft());

        x->getRight()->setParent(x);

        // x's parent will now be y's parent
        y->setParent(x->getParent());
        if (x->getParent() == nullptr) {
            // x was the root
            root = y;
        }
        else if (x == x->getParent()->getLeft()) {
            // x was the left child of its parent
            x->getParent()->setLeft(y);
        }
        else {
            // x was the right child of its parent
            x->getParent()->setRight(y);
        }

        // x will now be the left child of y
        y->setLeft(x);
        x->setParent(y);

        // handle subtree sizes
        x->setSubtree_sz(alpha + beta + 1);
        y->setSubtree_sz(x->getSubtree_sz() + gamma + 1);
    }

    void right_rotate(Node *y) {
        assert(!y->isLeaf());
        Node *x = y->getLeft();
        assert(!x->isLeaf());

        int alpha = 0, beta = 0, gamma = 0;
        alpha = x->getLeft()->getSubtree_sz();
        beta = x->getRight()->getSubtree_sz();
        gamma = y->getRight()->getSubtree_sz();

        assert(x->getSubtree_sz() == alpha + beta + 1);
        assert(y->getSubtree_sz() == x->getSubtree_sz() + gamma + 1);

        // x's right will now be y's left
        y->setLeft(x->getRight());

        y->getLeft()->setParent(y);

        // y's parent will now be x's parent
        x->setParent(y->getParent());
        if (y->getParent() == nullptr) {
            // y was the root
            root = x;
        }
        else if (y == y->getParent()->getLeft()) {
            // y was the left child
            y->getParent()->setLeft(x);
        }
        else {
            // y was the right child
            y->getParent()->setRight(x);
        }

        // y will now be the right child of x
        x->setRight(y);
        y->setParent(x);

        // handle subtree_sizes
        y->setSubtree_sz(beta + gamma + 1);
        x->setSubtree_sz(alpha + y->getSubtree_sz() + 1);
    }

    // called by the destructor
    void deallocate_nodes(Node *node) {
        if (node == nullptr) return;
        deallocate_nodes(node->getLeft());
        deallocate_nodes(node->getRight());
        delete node;
    }

    // returns the parent of the node where this key can be inserted
    Node *find_node_position(E key, Node *node, Node *parent) {
         if (node->isLeaf()) {
            return parent;
         }
         if (key < node->getKey()) {
            // move to the left subtree
            return find_node_position(key, node->getLeft(), node);
         }
         // move to the right subtree
         return find_node_position(key, node->getRight(), node);
    }

    // returns the node having its key exactly equal to key
    // else returns null
    Node *find_node_by_key(E key, Node *node) {
        if (node->isLeaf()) {
            return nullptr;
        }
        if (key == node->getKey()) {
            return node;
        }
        else if (key < node->getKey()) {
            // move to the left subtree
            return find_node_by_key(key, node->getLeft());
        }
        // move to the right subtree
        return find_node_by_key(key, node->getRight());
    }

    int find_less_help(Node *node, E key) {
        if (node->isLeaf()) return 0;
        if (node->getKey() >= key) {
            // all nodes less than key reside to the left of this node
            return find_less_help(node->getLeft(), key);
        }
        return 1 + node->getLeft()->getSubtree_sz() + find_less_help(node->getRight(), key);
//        return node->getSubtree_sz() + find_less_help(node->getRight(), key);
    }

    void fixup_insert(Node *z) {
        assert(z != nullptr && z->getParent() != nullptr);
        while (z->getParent() != nullptr && z->getParent()->getColor() == 1) {
            // z is not a leaf, since z is a red node

            assert(z->getParent()->getParent() != nullptr);
            // if z's parent is the root, it would be black, not red
            // so z's parent is not the root
            // so z's grandparent must exist

            if (z->getParent() == z->getParent()->getParent()->getLeft()) {
                // z's parent is a left child
                Node *y = z->getParent()->getParent()->getRight(); // uncle of z
                if (y != nullptr && y->getColor() == 1) {
                    // uncle is red
                    z->getParent()->setColor(0);
                    y->setColor(0);
                    z->getParent()->getParent()->setColor(1);
                    z = z->getParent()->getParent();
                }
                else {
                    // uncle is black
                    if (z == z->getParent()->getRight()) {
                        // z is the right child
                        z = z->getParent();
                        left_rotate(z);
                    }
                    z->getParent()->setColor(0);
                    z->getParent()->getParent()->setColor(1);
                    right_rotate(z->getParent()->getParent());
                }
            }
            else {
                // z's parent is a right child
                Node *y = z->getParent()->getParent()->getLeft(); // uncle of z
                if (y != nullptr && y->getColor() == 1) {
                    // uncle is red
                    z->getParent()->setColor(0);
                    y->setColor(0);
                    z->getParent()->getParent()->setColor(1);
                    z = z->getParent()->getParent();
                }
                else {
                    // uncle is black
                    // null implies sentinel i.e. black node
                    if (z == z->getParent()->getLeft()) {
                        // z is the left child
                        z = z->getParent();
                        right_rotate(z);
                    }
                    z->getParent()->setColor(0);
                    z->getParent()->getParent()->setColor(1);
                    left_rotate(z->getParent()->getParent());
                }
            }
        }
        root->setColor(0);
    }

    Node* find_predecessor(Node *node) {
        assert(node != nullptr && !node->isLeaf() && !node->getLeft()->isLeaf());
        // this function is called only when left subtree of node is not empty

        Node *y = node->getLeft();
        Node *x = y->getRight();
        while (!x->isLeaf()) {
            y = x;
            x = x->getRight();
        }
        return y;
    }

    Node* find_successor(Node *node) {
        assert(node != nullptr && !node->isLeaf() && !node->getRight()->isLeaf());
        // this function is called only when right subtree of node is not empty

        Node *y = node->getRight();
        Node *x = y->getLeft();
        while (!x->isLeaf()) {
            y = x;
            x = x->getLeft();
        }
        return y;
    }

    Node *root;

public:
    RedBlackTree() {
        root = nullptr;
    }

    ~RedBlackTree() {
        if (empty()) return;
        deallocate_nodes(root);
    }

    int size() {
        if (empty()) return 0;
        return root->getSubtree_sz();
    }

    bool empty() {
        return root==nullptr;
    }

    bool search(E key) {
        Node *node = find_node_by_key(key, root);
        return !(node == nullptr);
    }

    int find_less_nodes(E key) {
        return find_less_help(root, key);
    }

    void insert(E key) {
        Node *z = new Node(key);
        Node *y = nullptr;
        Node *x = root;
        while (!x->isLeaf()) {
            y = x;
            if (key < x->getKey()) {
                x = x->getLeft();
            }
            else {
                x = x->getRight();
            }
        }

        // x is now the position at which z will be inserted
        // y will be the parent
        z->setParent(y);
        if (y == nullptr) {
            root = z;
        }
        else if (key < y->getKey()) {
            // z will be left of y

            assert(y->getLeft()->isLeaf());
            delete y->getLeft();
            y->setLeft(z);
        }
        else {
            // z will be right of y

            assert(y->getRight()->isLeaf());
            delete y->getRight();
            y->setRight(z);
        }

        // update the subtree size of all ancestors
        Node *t = y;
        while (t != nullptr) {
            t->setSubtree_sz(t->getLeft()->getSubtree_sz() + t->getRight()->getSubtree_sz() + 1);
            t = t->getParent();
        }

        if (root == z) {
            z->setColor(0); // root color is black
            // z's subtree_sz is already 1
            return;
        }

        fixup_insert(z);
    }

};
