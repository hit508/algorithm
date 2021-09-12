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

int main(int argc, char** argv)
{
    return 0;
}