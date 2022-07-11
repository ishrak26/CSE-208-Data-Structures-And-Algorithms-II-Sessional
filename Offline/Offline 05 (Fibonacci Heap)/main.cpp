#include<bits/stdc++.h>
#include "fibonacci_heap.h"

using namespace std;

int main() {
    Fibonacci_heap<int> fib;
    cout << fib.empty() << '\n';
    cout << fib.getTotNodes() << '\n';
    cout << fib.getMin() << '\n';

    fib.insert(45);

    cout << fib.empty() << '\n';
    cout << fib.getTotNodes() << '\n';
    cout << fib.getMin() << '\n';
    cout << fib.getMinKey() << '\n';

    fib.insert(12);

    cout << fib.empty() << '\n';
    cout << fib.getTotNodes() << '\n';
    cout << fib.getMin() << '\n';
    cout << fib.getMinKey() << '\n';

    fib.insert(35);

    cout << fib.empty() << '\n';
    cout << fib.getTotNodes() << '\n';
    cout << fib.getMin() << '\n';
    cout << fib.getMinKey() << '\n';

    return 0;
}
