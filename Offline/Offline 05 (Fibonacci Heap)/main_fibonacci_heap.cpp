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

    for (int x : v) {
        fib.insert(x);
    }

//    cout << "tree is \n";
//    fib.printTree(fib.getMin());

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

    cout << "min key is " << fib.extractMinKey() << '\n';
    cout << "tree is \n";
    fib.printTree(fib.getMin());

    cout << fib.empty() << ' ' << fib.getTotNodes() << '\n';

    return 0;
}

