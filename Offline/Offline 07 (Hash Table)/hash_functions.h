#include<bits/stdc++.h>

using namespace std;

#define ll long long

#pragma once

// polynomial rolling function
int hash_func1(string &s, ll m) {
    const ll p = 31; // for lowercase letters
    ll hash_val = 0LL;
    ll p_pow = 1LL;
    for (int i = 0, len = s.length(); i < len; i++) {
        // for lowercase letters only
        hash_val = (hash_val + (s[i] - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    assert(hash_val <= INT_MAX);
    return int(hash_val);
}

// 5-bit cycle shift
int hash_func2(string &s, int m) {
    int hash_val = 0;
    for (int i = 0, len = s.length(); i < len; i++) {
        hash_val = (hash_val << 5) | (hash_val >> 27);
        hash_val += s[i];
        hash_val %= m;
    }
    if (hash_val == 0) hash_val = m-1;
    return hash_val;
}
