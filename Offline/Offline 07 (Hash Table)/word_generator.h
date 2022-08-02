#include<bits/stdc++.h>

using namespace std;

#define WORD_NO 100000
#define WORD_LEN 7

vector<string> words;

string generate_word() {
    int lo = 'a';
    int hi = 'z';
    int range = hi-lo+1;
    string ret;
    for (int i = 0; i < WORD_LEN; i++) {
        char c = rand() % range + lo;
        assert(c >= lo && c <= hi);
        ret.push_back(c);
    }
    return ret;
}

void generate_all_words() {
    for (int i = 0; i < WORD_NO; i++) {
        string word = generate_word();
        words.push_back(word);
//        cerr << word << '\n';
    }
}
