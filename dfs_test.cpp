#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

vector<vector<int>> m_result;
vector<int> m_sub_result;

void dfs(vector<int>& candidates, int start, int target)
{
    if (target == 0) {
        m_result.push_back(m_sub_result);
        return;
    }

    int select_num = candidates.size();
    for (int i = start; i < select_num; i++) {
        if (target < candidates[i]) {
            continue;
        }
        m_sub_result.push_back(candidates[i]);
        dfs(candidates, i, target - candidates[i]);
        m_sub_result.pop_back();
    }
}

vector<vector<int>> combinationSum(vector<int>& candidates, int target)
{
    dfs(candidates, 0, target);
    return m_result;
}

bool checkValid(vector<string>& board, int row, int col)
{
    for (int i = 0; i < row; i++) {
        if (board[i][col] == 'Q') {
            return false;
        }
    }
    for (int i = 0; i < col; i++) {
        if (board[row][i] == 'Q') {
            return false;
        }
    }
    for (int i = row - 1, j = col -1; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 'Q') {
            return false;
        }
    }
    for (int i = row - 1, j = col + 1; i >= 0 && j < board.size(); i--, j++) {
        if (board[i][j] == 'Q') {
            return false;
        }
    }
    return true;
}

vector<vector<string>> result;
void BackTrace(vector<string>& board, int row)
{
    if (row == board.size()) {
        result.push_back(board);
        return;
    }

    int colNum = board[row].length();
    for (int col = 0; col < board[row].length(); col++) {
        if (checkValid(board, row, col) != true) {
            continue;
        }
        board[row][col] = 'Q';
        BackTrace(board, row + 1);
        board[row][col] = '.';
    }
}

vector<vector<string>> SloveQueens(int n)
{
    vector<string> board;
    for(int i = 0; i < n; i++) {
        string str = "";
        for(int j = 0; j < n; j++) {
            str += ".";
        }
        board.push_back(str);
    }

    BackTrace(board, 0);
    return result;
}

int main(int argc, char** argv)
{
    return 0;
}