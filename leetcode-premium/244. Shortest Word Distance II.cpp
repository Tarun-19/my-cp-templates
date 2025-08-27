#include <bits/stdc++.h>
using namespace std;

// https://leetcode.ca/all/244.html
vector<string> words = {"practice", "makes", "perfect", "coding", "makes"};
string word1 = "coding", word2 = "practice";

int solve() {
    unordered_map<string, vector<int>> v;
    
    int pos = 0;
    for(auto it: words) {
        v[it].push_back(pos++); // duplicates in words list :)
    }
    
    // two-pointer approach to find min dif in sorted array
    // https://www.geeksforgeeks.org/dsa/smallest-difference-pair-values-two-unsorted-arrays/
    
    int n = v[word1].size();
    int m = v[word2].size();
    int i = 0, j = 0, ans = 1e9;
    while(i < n and j < m) {
        ans = min(ans, abs(v[word1][i]-v[word2][j]));
        if(v[word1][i] < v[word2][j])
            i++;
        else
            j++;
    }
    return ans;
}


int main() {
    cout << solve();
    return 0;
}
