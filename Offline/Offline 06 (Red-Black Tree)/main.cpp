#include<bits/stdc++.h>
#include "RedBlackTree.h"

using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    RedBlackTree<int> rb;
    int n;
    cin >> n;
    cout << n << '\n';
    while (n--) {
        int e, x;
        cin >> e >> x;
        int r = -1;
        if (e == 0) {
            // terminate program with x
            if (rb.search(x)) {
                rb.deleteNode(x);
                r = 1;
            }
            else {
                // no program with x
                r = 0;
            }
        }
        else if (e == 1) {
            // initiate program with x
            if (rb.search(x)) {
                // already a program with x
                r = 0;
            }
            else {
                rb.insert(x);
                r = 1;
            }
        }
        else if (e == 2) {
            // search program with x
            if (rb.search(x)) {
                r = 1;
            }
            else {
                r = 0;
            }
        }
        else {
            // find programs less than x
            r = rb.find_less_nodes(x);
        }
        cout << e << ' ' << x << ' ' << r << '\n';
    }

    return 0;
}
