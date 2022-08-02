#include<bits/stdc++.h>
#include "hash_functions.h"
#include "node.h"

using namespace std;

class OpenAddressing {
    int m;
    Node **hashTable; // array of nodes
    char type;
    vector<bool> deleted;

    void init() {
        hashTable = new Node*[m];
        deleted.assign(m, false);
        for (int i = 0; i < m; i++) {
            hashTable[i] = nullptr;
        }
    }

    int hash_func(string key, ll i) {
        if (type == 'L') {
            // linear probing
            return (hash_func1(key, m) + i) % m;
        }
        if (type == 'Q') {
            // quadratic probing
            const ll c1 = 1LL;
            const ll c2 = 1LL;
            ll sum = 0LL;
            sum = (sum + hash_func1(key, m)) % m;
            sum = (sum + c1 * i) % m;
            sum = (sum + c2 * i * i) % m;
            return (int)sum;
        }
        assert(type == 'D');
        // double hashing
        ll sum = 0LL;
        sum = (sum + i * hash_func2(key, m)) % m;
        sum = (sum + hash_func1(key, m)) % m;
        return (int)sum;
    }

public:
    OpenAddressing() {
        m = 1e5+3;
        type = 'd';
        init();
    }

    OpenAddressing(int m, char type) {
        this->m = m;
        this->type = type;
        init();
    }

    ~OpenAddressing() {

    }

    // returns false if the value already existed in the hash table
    bool insert(string key, int val) {
        if (search(key)) {
            // key already exists in the table
            // no need to insert again
            return false;
        }
        int j;
        for (int i = 0; i < m; i++) {
            j = hash_func(key, i);
            if (hashTable[j] == nullptr || deleted[j]) {
                hashTable[j] = new Node(key, val);
                if (deleted[j]) deleted[j] = false;
                return true;
            }
        }
//        cerr << "key is " << key << '\n';
//        cerr << "type is " << type << '\n';
        assert(false);
    }

    bool search(string key) {
        for (int i = 0; i < m; i++) {
            int j = hash_func(key, i);
            if (hashTable[j] == nullptr) {
                return false;
            }
            if (key.compare(hashTable[j]->getKey()) == 0) {
                return true;
            }
        }
        return false;
    }

    // returns true upon successful deletion
    bool deleteKey(string key) {
        for (int i = 0; i < m; i++) {
            int j = hash_func(key, i);
            if (hashTable[j] == nullptr) {
                // key doesn't exist
                return false;
            }
            if (key.compare(hashTable[j]->getKey()) == 0) {
                // delete this key
                delete hashTable[j];
                hashTable[j] = nullptr;
                deleted[j] = true;
                return true;
            }
        }
        return false;
    }
};

