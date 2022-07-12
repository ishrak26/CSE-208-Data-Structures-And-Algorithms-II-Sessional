#include<bits/stdc++.h>
#include "fibonacci_heap.h"

using namespace std;

int main() {
    Fibonacci_heap<int> fib;
//    cout << fib.empty() << '\n';
//    cout << fib.getTotNodes() << '\n';
//    cout << fib.getMin() << '\n';
//    cout << '\n';

//    fib.insert(45);

//    cout << fib.empty() << '\n';
//    cout << fib.getTotNodes() << '\n';
//    cout << fib.getMin() << '\n';
//    cout << fib.getMinKey() << '\n';
//    cout << '\n';

//    fib.insert(12);

//    cout << fib.empty() << '\n';
//    cout << fib.getTotNodes() << '\n';
//    cout << fib.getMin() << '\n';
//    cout << fib.getMinKey() << '\n';
//    cout << '\n';

//    fib.insert(35);

//    cout << fib.empty() << '\n';
//    cout << fib.getTotNodes() << '\n';
//    cout << fib.getMin() << '\n';
//    cout << fib.getMinKey() << '\n';
//    cout << '\n';

//    cout << "tree is \n";
//    fib.printTree(fib.getMin());
//    cout << "tree printed\n";
//
//    cout << fib.extractMinKey() << '\n';
//
//    cout << "tree is \n";
//    fib.printTree(fib.getMin());
//    cout << "tree printed\n";

//    cout << fib.empty() << '\n';
//    cout << fib.getTotNodes() << '\n';
//    cout << fib.getMin() << '\n';
//    cout << fib.getMinKey() << '\n';
//    cout << '\n';

//    cout << fib.extractMinKey() << '\n';
//
//    cout << "tree is \n";
//    fib.printTree(fib.getMin());
//    cout << "tree printed\n";

//    cout << fib.empty() << '\n';
//    cout << fib.getTotNodes() << '\n';
//    cout << fib.getMin() << '\n';
//    cout << fib.getMinKey() << '\n';
//    cout << '\n';

//    cout << fib.extractMinKey() << '\n';
//
//    cout << "tree is \n";
//    fib.printTree(fib.getMin());
//    cout << "tree printed\n";

//    cout << fib.empty() << '\n';
//    cout << fib.getTotNodes() << '\n';
//    cout << fib.getMin() << '\n';
//    cout << '\n';

    vector<int> v{23, 7, 21, 3, 18, 52, 38, 39, 41, 17, 30, 24, 26, 46, 35};
    map<int, int> m;

    for (int x : v) {
        int id = fib.insert(x);
        m[x] = id;
    }

//    cout << "tree is \n";
//    fib.printTree(fib.getMin());

    fib.decreaseKey(m[3], 2);
    m[2] = m[3];
    m[3] = 0;

    cout << "min key is " << fib.extractMinKey() << '\n';

//    cout << "tree is \n";
//    fib.printTree(fib.getMin());

    cout << "min key is " << fib.extractMinKey() << '\n';

//    cout << "tree is \n";
//    fib.printTree(fib.getMin());

//    cout << fib.getTotNodes() << '\n';

//    cout << fib.getMinKey() << '\n';

    cout << "min key is " << fib.extractMinKey() << '\n';


//    cout << "tree is \n";
//    fib.printTree(fib.getMin());

    fib.decreaseKey(m[41], 25);
    m[25] = m[41];
    m[41] = 0;

//    cout << "tree is \n";
//    fib.printTree(fib.getMin());

    cout << "min key is " << fib.extractMinKey() << '\n';
//    cout << "tree is \n";
//    fib.printTree(fib.getMin());

    cout << "min key is " << fib.extractMinKey() << '\n';
//    cout << "tree is \n";
//    fib.printTree(fib.getMin());

    cout << "min key is " << fib.extractMinKey() << '\n';
//    cout << "tree is \n";
//    fib.printTree(fib.getMin());

    cout << "min key is " << fib.extractMinKey() << '\n';
//    cout << "tree is \n";
//    fib.printTree(fib.getMin());

    cout << "min key is " << fib.extractMinKey() << '\n';
//    cout << "tree is \n";
//    fib.printTree(fib.getMin());

    cout << "min key is " << fib.extractMinKey() << '\n';
//    cout << "tree is \n";
//    fib.printTree(fib.getMin());

    cout << "min key is " << fib.extractMinKey() << '\n';
//    cout << "tree is \n";
//    fib.printTree(fib.getMin());

    cout << "min key is " << fib.extractMinKey() << '\n';
//    cout << "tree is \n";
//    fib.printTree(fib.getMin());

    cout << "min key is " << fib.extractMinKey() << '\n';
//    cout << "tree is \n";
//    fib.printTree(fib.getMin());

    cout << "min key is " << fib.extractMinKey() << '\n';
//    cout << "tree is \n";
//    fib.printTree(fib.getMin());

    cout << "min key is " << fib.extractMinKey() << '\n';
//    cout << "tree is \n";
//    fib.printTree(fib.getMin());

//    cout << "total nodes " << fib.getTotNodes() << '\n';

    fib.decreaseKey(m[52], 12);
    m[12] = m[52];
    m[52] = 0;

//    cout << "total nodes " << fib.getTotNodes() << '\n';

//    cout << "min key is " << fib.extractMinKey() << '\n';

//    cout << "tree is \n";
//    fib.printTree(fib.getMin());

//    cout << fib.empty() << ' ' << fib.getTotNodes() << '\n';

    return 0;
}

