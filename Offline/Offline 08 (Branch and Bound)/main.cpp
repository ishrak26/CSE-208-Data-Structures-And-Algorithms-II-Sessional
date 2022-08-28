#include<bits/stdc++.h>

using namespace std;

int n;

int calc_bound_unfixed(vector<vector<char> > &mat, int fr, int fc) {
    // find for cols
    int ma = 0;
    for (int j = fc; j <= n; j++) {
        int cnt = 0;
        for (int i = fr; i <= n; i++) {
            if (mat[i][j] == 'X') cnt++;
        }
        ma = max(ma, cnt);
    }
    // find for rows
    for (int i = fr; i <= n; i++) {
        int cnt = 0;
        for (int j = fc; j <= n; j++) {
            if (mat[i][j] == 'X') cnt++;
        }
        ma = max(ma, cnt);
    }
    int ret = (ma+1)/2;
    return ret;
}

int calc_bound_fixed(vector<vector<char> > &mat, int fr, int fc) {
    int ma = 0;
    // find for cols
    for (int j = 1; j < fc; j++) {
        // count upwards
        int pos1 = j;
        for (int i = 1; i < j; i++) {
            if (mat[i][j] == 'X') {
                pos1 = i;
                break;
            }
        }
        int cnt1 = j - pos1 + 1;
        // count downwards
        // find the last X inside the fixed region
        int pos2 = j;
        for (int i = j+1; i < fr; i++) {
            if (mat[i][j] == 'X') pos2 = i;
        }
        // find no. of X in unfixed region
        int cnt2 = 0;
        for (int i = max(fr, j+1); i <= n; i++) {
            if (mat[i][j] == 'X') cnt2++;
        }
        int cnt3;
        if (cnt2 == 0) {
            // no need to reorganize the unfixed portion of this col
            cnt3 = pos2 - j + 1;
        }
        else {
            // reorganize the unfixed portion
            // check if the diagonal element itself is inside the fixed region
            if (j < fr) {
                cnt3 = fr - j + cnt2;
            }
            else {
                // diagonal element is in the unfixed portion
                cnt3 = cnt2;
                if (mat[j][j] == 'X') cnt3++;
            }
        }

        int col_bound = max(cnt1, cnt3);
        ma = max(ma, col_bound);
    }
    // find for rows
    for (int i = 1; i < fr; i++) {
        // count leftwards
        int pos1 = i;
        for (int j = 1; j < i; j++) {
            if (mat[i][j] == 'X') {
                pos1 = j;
                break;
            }
        }
        int cnt1 = i - pos1 + 1;
        // count rightwards
        // find the last X inside the fixed region
        int pos2 = i;
        for (int j = i+1; j < fc; j++) {
            if (mat[i][j] == 'X') pos2 = j;
        }
        // find no. of X in unfixed region
        int cnt2 = 0;
        for (int j = max(fc, i+1); j <= n; j++) {
            if (mat[i][j] == 'X') cnt2++;
        }
        int cnt3;
        if (cnt2 == 0) {
            // no need to reorganize the unfixed portion of this row
            cnt3 = pos2 - i + 1;
        }
        else {
            // reorganize the unfixed portion
            // check if the diagonal element itself is inside the fixed region
            if (i < fc) {
                cnt3 = fc - i + cnt2;
            }
            else {
                // diagonal element is in the unfixed portion
                cnt3 = cnt2;
                if (mat[i][i] == 'X') cnt3++;
            }
        }

        int row_bound = max(cnt1, cnt3);
        ma = max(ma, row_bound);
    }
    return ma;
}

int calc_bound(vector<vector<char> > &mat, int fr, int fc) {
    // [1, fr) rows have been fixed
    // [1, fc) cols have been fixed
    int bound_unfixed = calc_bound_unfixed(mat, fr, fc);
    int bound_fixed = calc_bound_fixed(mat, fr, fc);
    int bound = max(bound_unfixed, bound_fixed);
    return bound;
}

// swap c1-th col with c2-th col
void swap_cols(int c1, int c2, vector<vector<char> > &mat) {
    for (int i = 1; i <= n; i++) {
        swap(mat[i][c1], mat[i][c2]);
    }
}

// swap r1-th row with r2-th row
void swap_rows(int r1, int r2, vector<vector<char> > &mat) {
    swap(mat[r1], mat[r2]);
}

bool comp(pair<int, int> a, pair<int, int> b) {
    if (a.first == b.first) return b.second < a.second;
    return a.first < b.first;
}

int check_branching(int fr, int fc, vector<vector<char> > &mat, int max_bound) {
    if (fr == fc) {
        if (fr == n) {
            // all done
            return 1;
        }
        // swap cols
        vector<vector<char> > ini_mat = mat;
        vector<pair<int, int> > branches;
        for (int j = 0; fc+j <= n; j++) {
            swap_cols(fc, fc+j, mat);
            int bound = calc_bound(mat, fr, fc+1);
            branches.push_back({bound, j});
//            cerr << "col " << fr << " " << fc << " " << j << " " << bound << '\n';
            // restore
//            swap_cols(fc, fc+j, fr, mat);
        }
        sort(branches.begin(), branches.end(), comp);
        for (pair<int, int> p : branches) {
            if (p.first > max_bound) {
                return 0;
            }
            mat = ini_mat;
            for (int j = 0; j <= p.second; j++) {
                swap_cols(fc, fc+j, mat);
            }
            int ret = check_branching(fr, fc+1, mat, max_bound);
            // restore
//            swap_cols(fc, fc+p.second, fr, mat);
            if (ret == 1) {
                return ret;
            }
        }
        return 0;
    }
    // swap rows
    vector<vector<char> > ini_mat = mat;
    vector<pair<int, int> > branches;
    for (int i = 0; fr+i <= n; i++) {
        swap_rows(fr, fr+i, mat);
        int bound = calc_bound(mat, fr+1, fc);
        branches.push_back({bound, i});
//        cerr << "row " << fr << " " << fc << " " << i << " " << bound << '\n';
        // restore
//        swap_rows(fr, fr+i, fc, mat);
    }
    sort(branches.begin(), branches.end(), comp);
    for (pair<int, int> p : branches) {
        if (p.first > max_bound) {
            return 0;
        }
        mat = ini_mat;
        for (int i = 0; i <= p.second; i++) {
            swap_rows(fr, fr+i, mat);
        }
        int ret = check_branching(fr+1, fc, mat, max_bound);
        // restore
//        swap_rows(fr, fr+p.second, fc, mat);
        if (ret == 1) {
            return ret;
        }
    }
    return 0;
}

int find_final_matrix(int fr, int fc, vector<vector<char> > &mat, int bound) {
    if (fr == fc) {
        if (fr == n) {
            // all done
            return 1;
        }
        // swap cols
        vector<vector<char> > ini_mat = mat;
        vector<pair<int, int> > branches;
        for (int j = 0; fc+j <= n; j++) {
            swap_cols(fc, fc+j, mat);
            int bound = calc_bound(mat, fr, fc+1);
            branches.push_back({bound, j});
            // restore
//            swap_cols(fc, fc+j, fr, mat);
        }
        sort(branches.begin(), branches.end(), comp);
        for (pair<int, int> p : branches) {
            if (p.first > bound) {
                return 0;
            }
            mat = ini_mat;
            for (int j = 0; j <= p.second; j++) {
                swap_cols(fc, fc+j, mat);
            }
            int ret = find_final_matrix(fr, fc+1, mat, bound);
            if (ret == 1) {
                return ret;
            }
            // restore
//            swap_cols(fc, fc+p.second, fr, mat);
        }
        return 0;
    }
    // swap rows
    vector<vector<char> > ini_mat = mat;
    vector<pair<int, int> > branches;
    for (int i = 0; fr+i <= n; i++) {
        swap_rows(fr, fr+i, mat);
        int bound = calc_bound(mat, fr+1, fc);
        branches.push_back({bound, i});
        // restore
//        swap_rows(fr, fr+i, fc, mat);
    }
    sort(branches.begin(), branches.end(), comp);
    for (pair<int, int> p : branches) {
        if (p.first > bound) {
            return 0;
        }
        mat = ini_mat;
        for (int i = 0; i <= p.second; i++) {
            swap_rows(fr, fr+i, mat);
        }
        int ret = find_final_matrix(fr+1, fc, mat, bound);
        if (ret == 1) {
            return ret;
        }
        // restore
//        swap_rows(fr, fr+p.second, fc, mat);
    }
    return 0;
}

int main() {
    cin >> n;
    vector<vector<char> > mat(n+1, vector<char> (n+1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> mat[i][j];
        }
    }
    vector<vector<char> > ini_mat = mat;
    // run a binary search on the decision problem
    int lo = 1, hi = n, mid;
    while (hi - lo > 2) {
        mid = (lo+hi)/2;
        int check = check_branching(1, 1, mat, mid);
//        cerr << "mid: " << mid << ", check: " << check << '\n';
        if (check == 1) {
            hi = mid;
        }
        else {
            lo = mid+1;
        }
        mat = ini_mat;
    }
    for (int mid = lo; mid <= hi; mid++) {
        int check = check_branching(1, 1, mat, mid);
        if (check == 1) {
            mat = ini_mat;
            int ans = find_final_matrix(1, 1, mat, mid);
            assert(ans == 1);
            cout << mid << '\n';
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    cout << mat[i][j];
                }
                cout << '\n';
            }
            return 0;
        }
        mat = ini_mat;
    }
    assert(false);
    return 0;
}

/*
4
XOOX
OOXO
XOOX
OXXX
*/
