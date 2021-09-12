
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
    return 0;
}