#include<bits/stdc++.h>
#include "RedBlackTree.h"

using namespace std;

int main() {
    RedBlackTree<int> rb;

//    rb.print_tree();
//    cerr << rb.size() << ' ' << rb.empty() << '\n';

    rb.insert(3);
    rb.print_tree();



    rb.insert(5);
    rb.print_tree();

    rb.insert(4);
    rb.print_tree();

    rb.insert(1);
    rb.print_tree();

    rb.insert(2);
    rb.print_tree();

//    rb.print_in_order();

//    cerr << rb.size() << ' ' << rb.empty() << '\n';
//    /// ok up to now
//
//    cerr << rb.search(3) << ' ' << rb.search(-1) << ' ' << rb.search(7) << '\n'; // ok
//    cerr << rb.find_less_nodes(3) << ' ' << rb.find_less_nodes(6) << ' ' << rb.find_less_nodes(1) << ' ' << rb.find_less_nodes(0) << '\n'; // ok

//    rb.deleteNode(4);
//    rb.print_tree();

    rb.deleteNode(2);
    rb.print_tree();

    rb.deleteNode(3);
    rb.print_tree();

    rb.deleteNode(4);
    rb.print_tree();

    rb.deleteNode(5);
    rb.print_tree();

    rb.deleteNode(1);
    rb.print_tree();

    rb.insert(28);
    rb.insert(30);
    rb.insert(35);
    rb.insert(38);
    rb.insert(39);
    rb.insert(41);
    rb.insert(47);
    rb.print_tree();

    rb.deleteNode(28);
    rb.print_tree();

    return 0;
}
