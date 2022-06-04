#include<iostream>
#include<vector>
#include<string>

using namespace std;

#define SZ 3

int count_player(vector<string> &board, char player) {
    int cnt = 0;
    for (int i = 0; i < SZ; i++) {
        for (int j = 0; j < SZ; j++) {
            if (board[i][j] == player) cnt++;
        }
    }
    return cnt;
}

bool check_winner_hor(vector<string> &board, char player) {
    for (int i = 0; i < SZ; i++) {
        int sum = 0;
        for (int j = 0; j < SZ; j++) {
            if (board[i][j] == player) sum++;
        }
        if (sum == SZ) return true;
    }
    return false;
}

bool check_winner_ver(vector<string> &board, char player) {
    for (int j = 0; j < SZ; j++) {
        int sum = 0;
        for (int i = 0; i < SZ; i++) {
            if (board[i][j] == player) sum++;
        }
        if (sum == SZ) return true;
    }
    return false;
}

bool check_winner_diagonal(vector<string> &board, char player) {
    // principal diagonal
    int sum = 0;
    for (int i = 0; i < SZ; i++) {
        if (board[i][i] == player) sum++;
    }
    if (sum == SZ) return true;
    // secondary diagonal
    sum = 0;
    for (int i = 0; i < SZ; i++) {
        if (board[i][SZ-1-i] == player) sum++;
    }
    return (sum==SZ);
}

bool check_winner(vector<string> &board, char player) {
    if (check_winner_hor(board, player) || check_winner_ver(board, player) || check_winner_diagonal(board, player)) {
        return true;
    }
    return false;
}

bool check_any_move_left(vector<string> &board) {
    for (int i = 0; i < SZ; i++) {
        for (int j = 0; j < SZ; j++) {
            if (board[i][j] == '_') return true;
        }
    }
    return false;
}

int solve() {
    vector<string> board(SZ);
    for (int i = 0; i < SZ; i++) cin >> board[i];
    // count X and O
    int X = count_player(board, 'X');
    int O = count_player(board, 'O');
    if (X == O || X == O+1) {
        // may be a reachable state
        bool winX = check_winner(board, 'X');
        bool winO = check_winner(board, 'O');
        bool moveLeft = check_any_move_left(board);
        if (X == O) {
            // X cannot win
            if (winX) {
                // there is a O move even after X won
                // unreachable
                return 3;
            }
            // check if O wins
            if (winO) {
                // O won in the last move
                return 1;
            }
            if (moveLeft) {
                return 2;
            }
            // draw
            return 1;
        }
        else {
            // O cannot win
            if (winO) {
                // there is a X move even after O won
                return 3;
            }
            // check if X won in the last move
            if (winX) {
                return 1;
            }
            if (moveLeft) {
                return 2;
            }
            // draw
            return 1;
        }
    }
    else {
        // unreachable
        return 3;
    }
}

int main() {
    int tt;
    cin >> tt;
    while (tt--) {
        int ans = solve();
        cout << ans << '\n';
    }
    return 0;
}
