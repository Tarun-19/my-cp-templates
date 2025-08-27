#include <bits/stdc++.h>
using namespace std;

// https://leetcode.com/problems/max-stack/

class MaxStack {
private:
    stack<pair<int, int>> sk;
    map<int, vector<int>> pos; // make it stack:)
    int cur;
    
    void stabilize() {
        while(!sk.empty()) {
            int x = sk.top().first;
            int c = sk.top().second;
            
            if(pos.find(x) == pos.end()) { // this can't be merged with pos[x].empty() condition in else-if
                sk.pop();
            } else if(pos[x].back() != c) {
                sk.pop();
                
                if(pos[x].empty()) {
                    pos.erase(x);
                }
            } else {
                break;
            }
        }
    }
    
public:
    MaxStack() {
        cur = 0;
    }
    
    void push(int x) {
        cur++;
        sk.push({x, cur});
        pos[x].push_back(cur);
    }
    
    int pop() {
        if(sk.empty()) return -1;
        
        stabilize();
        
        int x = sk.top().first;
        sk.pop();
        pos[x].pop_back();
        if(pos[x].empty()) {
            pos.erase(x);
        }
        
        return x;
    }
    
    int top() {
        if(sk.empty()) return -1;
        
        stabilize();
        
        return sk.top().first;
    }
    
    int peekMax() {
        if(pos.empty()) return -1;
        
        stabilize();
        return pos.rbegin()->first;
    }
    
    void popMax() {
        if(pos.empty()) return;
        
        int mx = pos.rbegin()->first;
        pos[mx].pop_back();
        if(pos[mx].empty()) {
            pos.erase(mx);
        }
    }
};


int main() {
    MaxStack ms;
    ms.push(5);
    ms.push(1);
    ms.push(5);
    cout<<ms.top()<<endl;
    ms.popMax();
    cout<<ms.top()<<endl;
    cout<<ms.peekMax()<<endl;
    cout<<ms.pop()<<endl;
    cout<<ms.top()<<endl;
    return 0;
}
