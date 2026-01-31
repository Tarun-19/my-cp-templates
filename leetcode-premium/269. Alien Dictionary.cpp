// https://neetcode.io/problems/foreign-dictionary/question

class Solution {
public:
    string foreignDictionary(vector<string>& words) {
        unordered_map<char, set<char>> adj;
        unordered_map<char, int> inDeg;

        for (auto &w : words)
        for (char c : w)
            inDeg[c] = 0; // external loop required as graph creation will have break statement

        for(int i = 1; i < words.size(); i++) {
            int x = min(words[i-1].size(), words[i].size());

            if(words[i-1].size() > x and isPrefixOf(words[i], words[i-1])) { // w1.substr(0, w2.size()) == w2
                return ""; // "abc" < "ab" is invalid
            }

            for(int j = 0; j < x; j++) {
                if(words[i-1][j] == words[i][j])
                    continue;
                
                if(adj[words[i-1][j]].find(words[i][j]) != adj[words[i-1][j]].end())
                    break; // imp
                
                adj[words[i-1][j]].insert(words[i][j]);
                inDeg[words[i][j]]++; // not for duplicates:)
                break; // imp
            }
        }

        int totDistinctChars = inDeg.size();

        queue<char> q;
        for(auto &[ch, deg]: inDeg) {
            if(deg == 0)
                q.push(ch);
        }

        string ans;

        while(!q.empty()) {
            char cur = q.front();
            q.pop();

            ans.push_back(cur);

            for(auto child: adj[cur]) {
                inDeg[child]--;
                if(inDeg[child] == 0) {
                    q.push(child);
                }
            }
        }

        return ans.size()==totDistinctChars? ans : "";
    }
private:
    bool isPrefixOf(string &s, string &str) {
        int n = str.size();
        int m = s.size();

        if(n < m)
            return false;
        
        int j = 0;
        while(j < m) {
            if(str[j] != s[j])
                return false;
            j++;
        }
        return true;
    }
};
