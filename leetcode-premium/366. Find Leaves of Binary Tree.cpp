// https://algo.monster/liteproblems/366
#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node *left, *right;
    Node(int val) : val(val), left(nullptr), right(nullptr) { }
};

vector<vector<int>> ans;

int dfs(Node* root) {
    if(!root) return 0;
    
    int l = dfs(root->left);
    int r = dfs(root->right);
    int h = max(l, r);
    
    while(ans.size() < h+1)
        ans.push_back({});
    
    ans[h].push_back(root->val);
    return h+1;
}

vector<vector<int>> findLeaves(Node* root) {
    dfs(root);
    return ans;
}


int main() {
	Node* root = new Node(1);
	root->left = new Node(2);
	root->right = new Node(3);
	root->left->left = new Node(4);
	root->left->right = new Node(5);
	
	vector<vector<int>> ans = findLeaves(root);
	for(auto it: ans) {
	    for(auto i: it) cout << i << " ";
	    cout << endl;
	}
}
