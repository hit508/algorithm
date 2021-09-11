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

int max(int a, int b)
{
    if (a > b) {
        return a;
    }
    return b;
}

int min(int a, int b, int c)
{
    if (a > b) {
        if (b > c) {
            return c;
        } else {
            return b;
        }
    } else {
        if (a > c) {
            return c;
        } else {
            return a;
        }
    }
}

int longestCommonSubsequence(string text1, string text2) {
    int m = text1.size();
    int n = text2.size();

    vector<vector<int>> dp_table(m + 1, vector<int>(n + 1, 0));

    for (int i = 0; i < m + 1; i++) {
        dp_table[i][0] = 0;
    }
    for (int j = 0; j < n + 1; j++) {
        dp_table[0][j] = 0;
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (text1[i - 1] == text2[j - 1]) {
                dp_table[i][j] = dp_table[i - 1][j - 1] + 1;
            } else {
                dp_table[i][j] = max(dp_table[i][j - 1], dp_table[i - 1][j]);
            }
        }
    }

    return dp_table[m][n];
}

int minDistance(string word1, string word2)
{
    int m = word1.size();
    int n = word2.size();

    vector<vector<int>> dp_table(m + 1, vector<int>(n + 1, 0));

    for (int i = 0; i < m + 1; i++) {
        dp_table[i][0] = i;
    }
    for (int j = 0; j < n + 1; j++) {
        dp_table[0][j] = j;
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (word1[i - 1] == word2[j - 1]) {
                dp_table[i][j] = dp_table[i - 1][j - 1];
            } else {
                dp_table[i][j] = min(dp_table[i - 1][j], dp_table[i][j - 1], dp_table[i - 1][j - 1]) + 1;
            }
        }
    }

    return dp_table[m][n];
}

int longestPalindromeSubseq(string s) {
    int n = s.size();

    vector<vector<int>> dp_table(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        dp_table[i][i] = 1;
    }

    for (int i = n - 2; i >= 0; i--) {
        for (int j = i + 1; j < n; j++) {
            if (s[i] == s[j]) {
                dp_table[i][j] = dp_table[i + 1][j - 1] + 2;
            } else {
                dp_table[i][j] = max(dp_table[i][j  - 1], dp_table[i + 1][j]);
            }
        }
    }

    return dp_table[0][n - 1];

}

vector<vector<int>> m_result;
vector<int> m_sub_result;

void select(vector<int>& candidates, int start, int target)
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
        select(candidates, i, target - candidates[i]);
        m_sub_result.pop_back();
    }
}

vector<vector<int>> combinationSum(vector<int>& candidates, int target)
{
    select(candidates, 0, target);
    return m_result;
}

void dfs(vector<int>& nums, vector<int>& visit, int start, int target)
{
    if (m_sub_result.size() == 4) {
        if (target == 0) {
            m_result.push_back(m_sub_result);
        }
        return;
    }

    for (int itr = start; itr < nums.size(); itr++) {
        if (target < nums[itr]) {
            continue;
        }
        if (visit[itr] == 1) {
            continue;
        }
        m_sub_result.push_back(nums[itr]);
        visit[itr] = 1;
        dfs(nums, visit, itr, target - nums[itr]);
        m_sub_result.pop_back();
        visit[itr] = 0;
    }
}

vector<vector<int>> fourSum(vector<int>& nums, int target)
{
    int left = 0, right = nums.size();

    sort(nums.begin(), nums.end());
    while (left < right) {
        if (nums[left] < target - nums[right - 1]) {
            left++;
        }
    }

    vector<int> visit(nums.size(), 0);
    dfs(nums, visit, 0, target);
    return m_result;
}

vector<vector<string>> result;

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


int dp(vector<int>& coins, int amount)
{
    if (amount <= 0) {
        return 0;
    }
    int maxNum = amount + 1;
    for(int i = 0; i < coins.size(); i++) {
        if (amount < coins[i]) {
            continue;
        }
        int res = 1 + dp(coins, amount - coins[i]);
        if (res < maxNum) {
           maxNum = res;
        }
    }
    return maxNum;
}

int coinChange(vector<int> coins, int amount)
{
    vector<int> dpTable;
    for(int i = 0; i < amount + 1; i++) {
        dpTable.push_back(amount + 1);
    }

    return dp(coins, amount);
}

string NodeInc(const string& Node, int i)
{
    string nextNode = Node;
    if (Node[i] == '9') {
        nextNode[i] = '0';
    } else {
        nextNode[i] = nextNode[i] + 1;
    }
    return nextNode;
}

string NodeDec(const string& Node, int i)
{
    string nextNode = Node;
    if (Node[i] == '0') {
        nextNode[i] = '9';
    } else {
        nextNode[i] = nextNode[i] - 1;
    }
    return nextNode;
}

int OpenLock(vector<string> deadends, string target)
{
    queue<string> NodeList;
    set<string> Visited;

    NodeList.push("0000");
    int step = 0;
    while(!NodeList.empty()) {
        int size = NodeList.size();
        for (int i = 0; i < size; i++) { // 一次访问完成一层
            string node = NodeList.front();
            NodeList.pop();

            int k = 0;
            for (; k < deadends.size(); k++) {
                if (deadends[k] == node) {
                    break;
                }
            }
            if (k <deadends.size())
            {
                continue;
            }

            if (node == target) {
                return step;
            }
    
            for (int j = 0; j < 4; j++) {
                string newNode = NodeInc(node, j);
                if (Visited.find(newNode) == Visited.end()) {
                    NodeList.push(newNode);
                    Visited.insert(newNode);
                }

                newNode = NodeDec(node, j);
                if (Visited.find(newNode) == Visited.end()) {
                    NodeList.push(newNode);
                    Visited.insert(newNode);
                }
            }
        }
        step++;
    }
    return step;
}

string MinWindow(string s, string t)
{
    unordered_map<char, int> need, window;
    for(char i  : t) {
        need[i]++;
    }
    int left = 0;
    int right = 0;

    int valid = 0;
    int start = 0;
    int len = INT32_MAX;

    while(right < s.size()) {
        char c = s[right];
        right++;
        if (need.count(c) > 0) {
            window[c]++; // 加入滑窗
            if (window[c] == need[c]) {
                valid++;
            }
        }
        while(valid == need.size()) {
            if (right -left  < len) {
                start = left;
                len = right - left;
            }
            char d = s[left];
            left++;
            if (need.count(d)) {
                if (window[d] == need[d]) {
                    valid--;
                }
                window[d]--; // 从滑窗删除
            }
        }
    }
    return len == INT32_MAX ? "" : s.substr(start, len);
}

int lengthOfLongestSubstring(string s)
{
    unordered_map<char, int> window;

    int left = 0;
    int right = 0;

    int start = 0;
    int len = 0;

    while (right < s.size()) {
        char c = s[right];
        right++;
        window[c]++;

        if (window[c] < 2) {
            if (right - left > len) {
                start = left;
                len = right - left;
            }
        } else {
            while (window[c] >= 2) {
                if (window[s[left]] > 0) {
                    window[s[left]]--;
                }
                left++;
            }
        }
    }
    return len;
}
bool CheckInclusion(string s, string t)
{
    unordered_map<char, int> need, window;
    for(char i  : t) {
        need[i]++;
    }
    int left = 0;
    int right = 0;

    int valid = 0;

    while(right < s.size()) {
        char c = s[right];
        right++;
        if (need.count(c) > 0) {
            window[c]++; // 加入滑窗
            if (window[c] == need[c]) {
                valid++;
            }
        }
    }
    int start = 0;
    int len = INT32_MAX;
    while(valid == need.size()) {
        if (right -left  < len) {
            start = left;
            len = right - left;
        }
        char d = s[left];
        left++;
        if (need.count(d)) {
            if (window[d] == need[d]) {
                valid--;
            }
            window[d]--; // 从滑窗删除
        }
    }
    string sub = (len == INT32_MAX) ? "" : s.substr(start, len);
    if (sub == "") {
        return false;
    }
    if (sub.size()  != t.size()) {
        return false;
    }
    return true;
}

int main(int argc, char** argv)
{
    // string text1 = "abcde";
    // string text2 = "ace";
    // int num = longestCommonSubsequence(text1, text2);
    vector<int> nums = { 1, 0, -1, 0, -2, 2 };
    vector<vector<int>> r = fourSum(nums, 0);
    printf("num = %d\n", r);
}
