#include<bits/stdc++.h>

using namespace std;

class Node {
    string key;
    int val;
public:
    Node() {
        key = "";
        val = -1;
    }

    Node(string key, int val) {
        this->key = key;
        this->val = val;
    }

    void setKey(string key) {
        this->key = key;
    }

    void setVal(int val) {
        this->val = val;
    }

    string getKey() {
        return key;
    }

    string getVal() {
        return val;
    }
};
