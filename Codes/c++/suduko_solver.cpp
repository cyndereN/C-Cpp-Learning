bool is_valid(vector<vector<int>>& board, int row, int col, int num) {
    // check row
    for (int j = 0; j < 9; j++) {
        if (board[row][j] == num) {
            return false;
        }
    }
    // check column
    for (int i = 0; i < 9; i++) {
        if (board[i][col] == num) {
            return false;
        }
    }
    // check box
    int box_row = row / 3 * 3;
    int box_col = col / 3 * 3;
    for (int i = box_row; i < box_row + 3; i++) {
        for (int j = box_col; j < box_col + 3; j++) {
            if (board[i][j] == num) {
                return false;
            }
        }
    }
    return true;
}

bool solve(vector<vector<int>>& board) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (board[row][col] == 0) {
                for (int num = 1; num <= 9; num++) {
                    if (is_valid(board, row, col, num)) {
                        board[row][col] = num;
                        if (solve(board)) {
                            return true;
                        }
                        board[row][col] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

vector<string> solution(vector<string>& A) {
    vector<vector<int>> board(9, vector<int>(9));
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (A[i][j] == '.') {
                board[i][j] = 0;
            } else {
                board[i][j] = A[i][j] - '0';
            }
        }
    }
    solve(board);
    vector<string> result(9);
    for (int i = 0; i < 9; i++) {
        result[i] = "";
        for (int j = 0; j < 9; j++) {
            result[i] += to_string(board[i][j]);
        }
    }
    return result;
}
