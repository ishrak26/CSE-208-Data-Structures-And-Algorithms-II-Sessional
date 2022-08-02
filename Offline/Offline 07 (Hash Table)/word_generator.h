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

// generate a list of unique words
void generate_all_words() {
    map<string, bool> m;
    for (int i = 0; i < WORD_NO; ) {
        string word = generate_word();
        if (m[word] == false) {
            words.push_back(word);
            m[word] = true;
            i++;
        }

//        cerr << word << '\n';
    }
}
