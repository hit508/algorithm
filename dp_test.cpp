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

int main(int argc, char** argv)
{
    return 0;
}