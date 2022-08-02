#include<bits/stdc++.h>
#include "word_generator.h"
#include "hash_functions.h"

using namespace std;

int m;

void test_hash_functions() {
    // pick 100 words randomly from words
    set<int> s1, s2;
    for (int i = 0; i < 100; i++) {
        int idx = rand() % WORD_NO;
        int h1 = hash_func1(words[idx], m);
        int h2 = hash_func2(words[idx], m);
        s1.insert(h1);
        s2.insert(h2);
    }
    cout << s1.size() << ' ' << s2.size() << '\n'; // 100 100
}

int main() {
    generate_all_words();

    cin >> m;

//    test_hash_functions();



    return 0;
}
