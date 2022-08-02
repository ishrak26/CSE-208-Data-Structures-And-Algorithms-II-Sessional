#include<bits/stdc++.h>
#include "hash_functions.h"
#include "node.h"

using namespace std;

class SeparateChaining {
    class hashTableNode {
    public:
        Node *node;
        hashTableNode *prev;
        hashTableNode *next;

        hashTableNode() {
            node = prev = next = nullptr;
        }

        hashTableNode(string key, int val, hashTableNode *prev, hashTableNode *next) {
            node = new Node(key, val);
            this->prev = prev;
            this->next = next;

        }

        ~hashTableNode() {
            if (node != nullptr) {
                delete node;
            }
        }
    };

    int m;
    hashTableNode **hashTable; // array of doubly linked list

    void init() {
        hashTable = new hashTableNode*[m];
        for (int i = 0; i < m; i++) {
            hashTable[i] = nullptr;
        }
    }

    // returns (h, true) if found
    // else returns false
    pair<int, bool> searchHelp(string key) {
        int h = hash_func1(key, m);
        assert(h >= 0 && h < m);
        hashTableNode *tmp = hashTable[h];
        bool found = false;
        while (tmp != nullptr) {
            string str = tmp->node->getKey();
            if (key.compare(str) == 0) {
                // matched
                found = true;
                break;
            }
            tmp = tmp->next;
        }
        return make_pair(h, found);
    }

    hashTableNode *deleteHelp(string key) {
        int h = hash_func1(key, m);
        assert(h >= 0 && h < m);
        hashTableNode *tmp = hashTable[h];
        bool found = false;
        while (tmp != nullptr) {
            string str = tmp->node->getKey();
            if (key.compare(str) == 0) {
                // matched
                return tmp;
            }
            tmp = tmp->next;
        }
        return nullptr;
    }

public:
    SeparateChaining() {
        m = 1e5+3;
        init();
    }

    SeparateChaining(int m) {
        this->m = m;
        init();
    }

    ~SeparateChaining() {

    }

    // returns false if the value already existed in the hash table
    bool insert(string key, int val) {
        pair<int, bool> match = searchHelp(key);
        if (match.second == true) {
            // this string already exists
            // no need to insert again
            return false;
        }
        int idx = match.first;
        // insert at idx
        hashTableNode *prev = nullptr;
        hashTableNode *next = hashTable[h]==nullptr ? nullptr : hashTable[h];
        hashTableNode *x = new hashTableNode(key, val, prev, next);
        hashTable[h].prev = x;
        hashTable[h] = x;
        return true;
    }

    bool search(string key) {
        pair<int, bool> match = searchHelp(key);
        if (match.second == true) {
            // this string exists
            return true;
        }
        return false;
    }

    // returns true upon successful deletion
    bool delete(string key) {
        hashTableNode *x = deleteHelp(key);
        if (key == nullptr) {
            // nothing to delete
            return false;
        }
        if (x.prev != nullptr) x.prev.next = x.next;
        if (x.next != nullptr) x.next.prev = x.prev;
        delete x;
        return true;
    }
};
