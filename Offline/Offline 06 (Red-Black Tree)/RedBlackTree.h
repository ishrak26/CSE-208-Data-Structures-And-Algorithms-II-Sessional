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
            color = -1;
            subtree_sz = 0;
        }

        Node(E key) {
            this->key = key;
            parent = left = right = nullptr;
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
        void getKey() {
            return this->key;
        }

        void getParent() {
            return this->parent;
        }

        void getLeft() {
            return this->left;
        }

        void getRight() {
            return this->right;
        }

        void getColor() {
            return this->color;
        }

        void getSubtree_sz() {
            return this->subtree_sz;
        }
    };

    void left_rotate(Node *x) {
        assert(x != nullptr);
        Node *y = x->getRight();
        assert(y != nullptr);
        x->setRight(y->getLeft());

        // y's left will now be x's right
        if (x->getRight() != nullptr) {
            x->getRight()->setParent(x);
        }
        y->setParent(x->getParent());

        // x's parent will now be y's parent
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
    }

    void right_rotate(Node *y) {
        assert(y != nullptr);
        Node *x = y->getLeft();
        assert(x != nullptr);

        // x's right will now be y's left
        y->setLeft(x->getRight());
        if (y->getLeft() != nullptr) {
            y->getLeft()->setParent(y);
        }

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
         if (node == nullptr) {
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
        if (node == nullptr) {
            return node;
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
        if (node == nullptr) return 0;
        if (node->getKey() >= key) {
            // all nodes less than key reside to the left of this node
            return find_less_help(node->getLeft(), key);
        }
        return node->getSubtree_sz() + find_less_help(node->getRight(), key);
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
        return root == null;
    }

    bool search(E key) {
        Node *node = find_node_by_key(key, root);
        return !(node == nullptr);
    }

    int find_less_nodes(E key) {
        return find_less_help(root, key);
    }

};
