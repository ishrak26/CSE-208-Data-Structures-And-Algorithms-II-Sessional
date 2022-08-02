#include<bits/stdc++.h>
#include "word_generator.h"
#include "hash_functions.h"
#include "separate_chaining.h"
#include "open_addressing.h"

using namespace std;

#define ld long double

struct Report {
    char type;
    ld alpha;
    ld time_before_del;
    ld time_after_del;
    ld probe_before_del;
    ld probe_after_del;

    Report() {

    }

    Report(char type, ld alpha, ld time_before_del, ld time_after_del, ld probe_before_del=-1, ld probe_after_del=-1) {
        this->type = type;
        this->alpha = alpha;
        this->time_before_del = time_before_del;
        this->time_after_del = time_after_del;
        this->probe_before_del = probe_before_del;
        this->probe_after_del = probe_after_del;
    }
};

vector<Report> reports;

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
    int probe_sum_lp, probe_sum_qp, probe_sum_dh;
    probe_sum_lp = probe_sum_qp = probe_sum_dh = 0;
    for (int i = 0; i < p; i++) {
        int idx = rand() % n;
        idx = inserted_idx[idx];
        chrono::steady_clock::time_point begin = chrono::steady_clock::now();
        bool srch = sc.search(words[idx]);
        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        assert(srch);
        ld tot_time_sc = chrono::duration_cast<chrono::nanoseconds> (end - begin).count();
        sum_sc += tot_time_sc;


        pair<bool, int> srch2;

        begin = chrono::steady_clock::now();
        srch2 = lp.search(words[idx]);
        srch = srch2.first;
        end = chrono::steady_clock::now();
        assert(srch);
        ld tot_time_lp = chrono::duration_cast<chrono::nanoseconds> (end - begin).count();
        sum_lp += tot_time_lp;
        probe_sum_lp += srch2.second;

        begin = chrono::steady_clock::now();
        srch2 = qp.search(words[idx]);
        srch = srch2.first;
        end = chrono::steady_clock::now();
        assert(srch);
        ld tot_time_qp = chrono::duration_cast<chrono::nanoseconds> (end - begin).count();
        sum_qp += tot_time_qp;
        probe_sum_qp += srch2.second;

        begin = chrono::steady_clock::now();
        srch2 = dh.search(words[idx]);
        srch = srch2.first;
        end = chrono::steady_clock::now();
        assert(srch);
        ld tot_time_dh = chrono::duration_cast<chrono::nanoseconds> (end - begin).count();
        sum_dh += tot_time_dh;
        probe_sum_dh += srch2.second;
    }
    ld avg_time_sc = sum_sc / p;
    ld avg_time_lp = sum_lp / p;
    ld avg_time_qp = sum_qp / p;
    ld avg_time_dh = sum_dh / p;
    cerr << "time\n";
    cerr << avg_time_sc << " ns\n";
    cerr << avg_time_lp << " ns\n";
    cerr << avg_time_qp << " ns\n";
    cerr << avg_time_dh << " ns\n";
    cerr << '\n';

    ld avg_probe_lp = probe_sum_lp / (ld)p;
    ld avg_probe_qp = probe_sum_qp / (ld)p;
    ld avg_probe_dh = probe_sum_dh / (ld)p;
    cerr << "probes\n";
    cerr << avg_probe_lp << '\n';
    cerr << avg_probe_qp << '\n';
    cerr << avg_probe_dh << '\n';



    // delete
    random_shuffle(inserted_idx.begin(), inserted_idx.end());
    for (int i = 0; i < p; i++) {
        int idx = inserted_idx[i];
        bool del = sc.deleteKey(words[idx]);
        assert(del);
        del = lp.deleteKey(words[idx]);
        assert(del);
        del = qp.deleteKey(words[idx]);
        assert(del);
        del = dh.deleteKey(words[idx]);
        assert(del);
    }
    // search again
    // search from the deleted elements first
    sum_sc = sum_lp = sum_qp = sum_dh = 0.0;
    probe_sum_lp = probe_sum_qp = probe_sum_dh = 0;
    for (int i = 0; i < p/2; i++) {
        int idx = rand() % p;
        idx = inserted_idx[idx];
        chrono::steady_clock::time_point begin = chrono::steady_clock::now();
//        cerr << "before sc search\n";
        bool srch = sc.search(words[idx]);
//        cerr << "sc search ok\n";
        chrono::steady_clock::time_point end = chrono::steady_clock::now();
//        assert(!srch);
        ld tot_time_sc = chrono::duration_cast<chrono::nanoseconds> (end - begin).count();
        sum_sc += tot_time_sc;


        pair<bool, int> srch2;

        begin = chrono::steady_clock::now();
        srch2 = lp.search(words[idx]);
//        cerr << "lp search ok\n";
        srch = srch2.first;
        end = chrono::steady_clock::now();
        assert(!srch);
        ld tot_time_lp = chrono::duration_cast<chrono::nanoseconds> (end - begin).count();
        sum_lp += tot_time_lp;
        probe_sum_lp += srch2.second;

        begin = chrono::steady_clock::now();
        srch2 = qp.search(words[idx]);
//        cerr << "qp search ok\n";
        srch = srch2.first;
        end = chrono::steady_clock::now();
        assert(!srch);
        ld tot_time_qp = chrono::duration_cast<chrono::nanoseconds> (end - begin).count();
        sum_qp += tot_time_qp;
        probe_sum_qp += srch2.second;

        begin = chrono::steady_clock::now();
        srch2 = dh.search(words[idx]);
//        cerr << "dh search ok\n";
        srch = srch2.first;
        end = chrono::steady_clock::now();
        assert(!srch);
        ld tot_time_dh = chrono::duration_cast<chrono::nanoseconds> (end - begin).count();
        sum_dh += tot_time_dh;
        probe_sum_dh += srch2.second;
    }
//    cerr << "deleted search ok\n";
    // search from the non-deleted elements
    for (int i = 0, rem = p - (p/2); i < rem; i++) {
        int idx = p + rand() % (n-p);
        assert(idx < n);
        idx = inserted_idx[idx];
        chrono::steady_clock::time_point begin = chrono::steady_clock::now();
        bool srch = sc.search(words[idx]);
        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        assert(srch);
        ld tot_time_sc = chrono::duration_cast<chrono::nanoseconds> (end - begin).count();
        sum_sc += tot_time_sc;


        pair<bool, int> srch2;

        begin = chrono::steady_clock::now();
        srch2 = lp.search(words[idx]);
        srch = srch2.first;
        end = chrono::steady_clock::now();
        assert(srch);
        ld tot_time_lp = chrono::duration_cast<chrono::nanoseconds> (end - begin).count();
        sum_lp += tot_time_lp;
        probe_sum_lp += srch2.second;

        begin = chrono::steady_clock::now();
        srch2 = qp.search(words[idx]);
        srch = srch2.first;
        end = chrono::steady_clock::now();
        assert(srch);
        ld tot_time_qp = chrono::duration_cast<chrono::nanoseconds> (end - begin).count();
        sum_qp += tot_time_qp;
        probe_sum_qp += srch2.second;

        begin = chrono::steady_clock::now();
        srch2 = dh.search(words[idx]);
        srch = srch2.first;
        end = chrono::steady_clock::now();
        assert(srch);
        ld tot_time_dh = chrono::duration_cast<chrono::nanoseconds> (end - begin).count();
        sum_dh += tot_time_dh;
        probe_sum_dh += srch2.second;
    }
    cerr << "After deletion\n";
    ld avg_time_sc_del = sum_sc / p;
    ld avg_time_lp_del = sum_lp / p;
    ld avg_time_qp_del = sum_qp / p;
    ld avg_time_dh_del = sum_dh / p;
    cerr << "time\n";
    cerr << avg_time_sc_del << " ns\n";
    cerr << avg_time_lp_del << " ns\n";
    cerr << avg_time_qp_del << " ns\n";
    cerr << avg_time_dh_del << " ns\n";
    cerr << '\n';

    ld avg_probe_lp_del = probe_sum_lp / (ld)p;
    ld avg_probe_qp_del = probe_sum_qp / (ld)p;
    ld avg_probe_dh_del = probe_sum_dh / (ld)p;
    cerr << "probes\n";
    cerr << avg_probe_lp_del << '\n';
    cerr << avg_probe_qp_del << '\n';
    cerr << avg_probe_dh_del << '\n';

    reports.push_back(Report('S', alpha, avg_time_sc, avg_time_sc_del));
    reports.push_back(Report('L', alpha, avg_time_lp, avg_time_lp_del, avg_probe_lp, avg_probe_lp_del));
    reports.push_back(Report('Q', alpha, avg_time_qp, avg_time_qp_del, avg_probe_qp, avg_probe_qp_del));
    reports.push_back(Report('D', alpha, avg_time_dh, avg_time_dh_del, avg_probe_dh, avg_probe_dh_del));
}

int main() {
    generate_all_words();

//    cin >> m;

    m = 100003;
//    test_hash_functions();

    for (ld i = 0.4; i <= 0.91; i = i+0.1) {
        generate_report(i);
    }

    int sz = reports.size();

    // performance of separate chaining in various load factors
    freopen("separate_chaining_all_load_factors.csv", "w", stdout);
    cout << "Load factor,Avg search time before deletion, Avg search time after deletion\n";
    for (int i = 0; i < sz; i++) {
        if (reports[i].type != 'S') continue;
        cout << reports[i].alpha << ',' << reports[i].time_before_del << ',' << reports[i].time_after_del << '\n';
    }

    // performance of linear probing in various load factors
    freopen("linear_probing_all_load_factors.csv", "w", stdout);
    cout << "Load factor,Avg search time before deletion,Avg number of probes before deletion,Avg search time after deletion,Avg number of probes after deletion\n";
    for (int i = 0; i < sz; i++) {
        if (reports[i].type != 'L') continue;
        cout << reports[i].alpha << ',' << reports[i].time_before_del << ',' << reports[i].probe_before_del << ',';
        cout << reports[i].time_after_del << ',' << reports[i].probe_after_del << '\n';
    }

    // performance of quadratic probing in various load factors
    freopen("quadratic_probing_all_load_factors.csv", "w", stdout);
    cout << "Load factor,Avg search time before deletion,Avg number of probes before deletion,Avg search time after deletion,Avg number of probes after deletion\n";
    for (int i = 0; i < sz; i++) {
        if (reports[i].type != 'Q') continue;
        cout << reports[i].alpha << ',' << reports[i].time_before_del << ',' << reports[i].probe_before_del << ',';
        cout << reports[i].time_after_del << ',' << reports[i].probe_after_del << '\n';
    }

    // performance of double hashing in various load factors
    freopen("double_hashing_all_load_factors.csv", "w", stdout);
    cout << "Load factor,Avg search time before deletion,Avg number of probes before deletion,Avg search time after deletion,Avg number of probes after deletion\n";
    for (int i = 0; i < sz; i++) {
        if (reports[i].type != 'D') continue;
        cout << reports[i].alpha << ',' << reports[i].time_before_del << ',' << reports[i].probe_before_del << ',';
        cout << reports[i].time_after_del << ',' << reports[i].probe_after_del << '\n';
    }

    // performance of various collision resolution methods in all load factors
    ld eps = 1e-6;
    for (ld i = 0.4; i <= 0.91; i = i+0.1) {
        string lf = to_string(i).substr(0, to_string(i).find(".") + 2);
        string filename = "all_performance_in_load_factor " + lf + ".csv";
        char fn[500];
        strncpy(fn, filename.c_str(), sizeof(fn));
        freopen(fn, "w", stdout);
        cout << "Method,Avg search time before deletion,Avg number of probes before deletion,Avg search time after deletion,Avg number of probes after deletion\n";
        for (int j = 0; j < sz; j++) {
            if (abs(i - reports[j].alpha) < eps) {
                if (reports[j].type == 'S') {
                    cout << "Separate Chaining";
                }
                else if (reports[j].type == 'L') {
                    cout << "Linear Probing";
                }
                else if (reports[j].type == 'Q') {
                    cout << "Quadratic Probing";
                }
                else {
                    cout << "Double Hashing";
                }
                cout << ',' << reports[j].time_before_del;
                if (reports[j].type == 'S') cout << ",N/A";
                else cout << ',' << reports[j].probe_before_del;
                cout << ',' << reports[j].time_after_del;
                if (reports[j].type == 'S') cout << ",N/A";
                else cout << ',' << reports[j].probe_after_del;
                cout << '\n';
            }
        }
    }

    return 0;
}
