#include<bits/stdc++.h>
#include "word_generator.h"
#include "hash_functions.h"
#include "separate_chaining.h"
#include "open_addressing.h"

using namespace std;

#define ld long double

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

void generate_report(ld alpha) {
    int n = m * alpha;
    SeparateChaining sc(m);
    OpenAddressing lp(m, 'L'), qp(m, 'Q'), dh(m, 'D');

    // insert n words into the hash table
    vector<int> inserted_idx;

    random_shuffle(words.begin(), words.end());

    for (int i = 0; i < n; ) {
        bool ins = sc.insert(words[i], i+1);

        if (ins) {
            // successful insertion
            ins = lp.insert(words[i], i+1);
//            cerr << "lp insert ok\n";
            assert(ins);
            ins = qp.insert(words[i], i+1);
//            cerr << "qp insert ok\n";
            assert(ins);

            ins = dh.insert(words[i], i+1);
//            cerr << "dh insert ok\n";
            assert(ins);
            inserted_idx.push_back(i);
            i++;
//            cerr << "insert ok\n";
        }
        else {
//            cerr << "duplicate\n";
        }
    }
    assert(inserted_idx.size() == n);
    int p = n/10;
    // search p words
    ld sum_sc, sum_lp, sum_qp, sum_dh;
    sum_sc = sum_lp = sum_qp = sum_dh = 0.0;
    for (int i = 0; i < p; i++) {
        int idx = rand() % n;
        idx = inserted_idx[idx];
        chrono::steady_clock::time_point begin = chrono::steady_clock::now();
        bool srch = sc.search(words[idx]);
        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        assert(srch);
        ld tot_time_sc = chrono::duration_cast<chrono::nanoseconds> (end - begin).count();
        sum_sc += tot_time_sc;

        begin = chrono::steady_clock::now();
        srch = lp.search(words[idx]);
        end = chrono::steady_clock::now();
        assert(srch);
        ld tot_time_lp = chrono::duration_cast<chrono::nanoseconds> (end - begin).count();
        sum_lp += tot_time_lp;

        begin = chrono::steady_clock::now();
        srch = qp.search(words[idx]);
        end = chrono::steady_clock::now();
        assert(srch);
        ld tot_time_qp = chrono::duration_cast<chrono::nanoseconds> (end - begin).count();
        sum_qp += tot_time_qp;

        begin = chrono::steady_clock::now();
        srch = dh.search(words[idx]);
        end = chrono::steady_clock::now();
        assert(srch);
        ld tot_time_dh = chrono::duration_cast<chrono::nanoseconds> (end - begin).count();
        sum_dh += tot_time_dh;
    }
    ld avg_time_sc = sum_sc / p;
    ld avg_time_lp = sum_lp / p;
    ld avg_time_qp = sum_qp / p;
    ld avg_time_dh = sum_dh / p;
    cerr << avg_time_sc << " ns\n";
    cerr << avg_time_lp << " ns\n";
    cerr << avg_time_qp << " ns\n";
    cerr << avg_time_dh << " ns\n";
    cerr << '\n';
}

int main() {
    generate_all_words();

//    cin >> m;

    m = 100003;
//    test_hash_functions();

    for (ld i = 0.4; i <= 0.91; i = i+0.1) {
        generate_report(i);
    }

    return 0;
}
