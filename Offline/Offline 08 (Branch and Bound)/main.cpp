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
                cnt3 = cnt2 + 1;
            }
        }

        int col_bound = max(cnt1, cnt3);
        ma = max(ma, col_bound);
//        cerr << "col " << j << ' ' << col_bound << ' ' << cnt1 << ' ' << cnt3 << '\n';
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
                cnt3 = cnt2 + 1;
            }
        }

        int row_bound = max(cnt1, cnt3);
        ma = max(ma, row_bound);
//        cerr << "row " << i << ' ' << row_bound << ' ' << cnt1 << ' ' << cnt3 << '\n';
    }

//    for (int i = 1; i < fr; i++) {
//        // count leftward
//        int pos1 = i;
//        for (int j = 1; j < i; j++) {
//            if (mat[i][j] == 'X') {
//                pos1 = j;
//                break;
//            }
//        }
//        int cnt1 = i - pos1 + 1;
//        // count rightward
//        int cnt2 = 1;
//        for (int j = i+1; j <= n; j++) {
//            if (mat[i][j] == 'X') cnt2++;
//        }
//        int row_bound = max(cnt1, cnt2);
//        ma = max(ma, row_bound);
//        cerr << "row " << i << ' ' << row_bound << ' ' << cnt1 << ' ' << cnt2 << '\n';
//    }
    return ma;
}

int calc_bound(vector<vector<char> > &mat, int fr, int fc) {
    // [1, fr) rows have been fixed
    // [1, fc) cols have been fixed
    int bound_unfixed = calc_bound_unfixed(mat, fr, fc);
//    cerr << bound_unfixed << '\n';
    int bound_fixed = calc_bound_fixed(mat, fr, fc);
//    cerr << bound_fixed << '\n';
    int bound = max(bound_unfixed, bound_fixed);
    return bound;
}

int main() {
    cin >> n;
    vector<vector<char> > mat(n+1, vector<char> (n+1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> mat[i][j];
        }
    }
    // bound calculation test
    int fr, fc;
    cin >> fr >> fc;
    int bound = calc_bound(mat, fr, fc);
    cout << bound << '\n';
    return 0;
}
