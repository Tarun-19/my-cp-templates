// https://algo.monster/liteproblems/588

#include <bits/stdc++.h>
using namespace std;

class Util {
public:
    static vector<string> split(string &s) {
        vector<string> res;

        stringstream ss(s);
        string word;
        while (getline(ss, word, '/')) {
            if (!word.empty())
                    res.push_back(word);
        }
        return res;
    }
};

struct TreeNode {
    unordered_map<string, string> files; // name, content
    unordered_map<string, TreeNode*> directories;
};

class Trie {
public:
    Trie() {
        root = new TreeNode();
    }

    void insertDirectory(vector<string> &path) {
        TreeNode* cur = root;

        for (int i = 0; i < path.size(); i++) {
            if (cur->directories.find(path[i]) == cur->directories.end()) {
                cur->directories[path[i]] = new TreeNode();
            }
            cur = cur->directories[path[i]];
        }
    }

    void insertFile(vector<string> &path, string &content) {
        TreeNode* cur = root;

        for (int i = 0; i < path.size()-1; i++) {
            if (cur->directories.find(path[i]) == cur->directories.end()) {
                cur->directories[path[i]] = new TreeNode();
            }
            cur = cur->directories[path[i]];
        }
        cur->files[path.back()] += content;
    }

    string readFile(vector<string> &path) {
        TreeNode* cur = root;

        for (int i = 0; i < path.size()-1; i++) {
            if (cur->directories.find(path[i]) == cur->directories.end()) {
                cur->directories[path[i]] = new TreeNode();
            }
            cur = cur->directories[path[i]];
        }
        return cur->files[path.back()];
    }

    vector<string> readPath(vector<string> &path) {
        TreeNode* cur = root;

        for (int i = 0; i < path.size(); i++) {
            if (cur->directories.find(path[i]) == cur->directories.end()) {
                cur->directories[path[i]] = new TreeNode();
            }
            cur = cur->directories[path[i]];
        }

        vector<string> ans;
        for (auto it: cur->files) {
            ans.push_back(it.first);
        }
        for (auto it: cur->directories) {
            ans.push_back(it.first);
        }
        sort(ans.begin(), ans.end());
        return ans;
    }
private:
    TreeNode* root;
};

class FileSystem {
public:
    FileSystem() {
        trie = new Trie();
    }

    vector<string> ls(string path) {
        vector<string> p = Util::split(path);
        return trie->readPath(p);
    }

    void mkdir(string path) {
        vector<string> p = Util::split(path);
        trie->insertDirectory(p);
    }

    void addContentToFile(string filePath, string content) {
        vector<string> p = Util::split(filePath);
        trie->insertFile(p, content);
    }

    string readContentFromFile(string filePath) {
        vector<string> p = Util::split(filePath);
        return trie->readFile(p);
    }

private:
    Trie* trie;
};

int main() {
    FileSystem* fs = new FileSystem();
    assert(fs->ls("/") == vector<string>{});

    fs->mkdir("/a/b/c");
    fs->addContentToFile("/a/b/c/d", "hello");
    assert(fs->ls("/") == vector<string>{"a"});
    assert(fs->readContentFromFile("/a/b/c/d") == "hello");


    FileSystem* fs2 = new FileSystem();
    fs2->mkdir("/a/b/c");
    fs2->addContentToFile("/a/b/file.txt", "hello");

    // IMP: assert is defined as a macro that takes one argument. if comma is used, use extra parenthesis:)
    // assert(fs2->ls("/a/b") == vector<string>{"c", "file.txt"}); // compilation error
    assert((fs2->ls("/a/b") == vector<string>{"c", "file.txt"})); // working due to extra outer parenthesis
    assert(fs2->readContentFromFile("/a/b/file.txt") == "hello");

    return 0;
}
