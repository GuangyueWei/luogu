/*
  字典树：Trie

*/

#include <bits/stdc++.h>
using namespace std;

int record[128];
int idx;

void init() {
    idx = 0;
    
    for (char c = 'a'; c <= 'z'; ++c) {
        record[c] = idx++;
    }
    for (char c = 'A'; c <= 'Z'; ++c) {
        record[c] = idx++;
    }
    for (char c = '0'; c <= '9'; ++c) {
        record[c] = idx++;
    }
}

class Trie {
    struct Node{
        vector<Node*> sons;
        int cnt;

        Node() {
            sons.resize(idx);
            cnt = 0;
        }
    };
    Node* head;

public:
    Trie() {
        head = new Node();
    }

    void add(string& s) {
        Node* tmp = head;
        for (char c : s) {
            int d = record[c];
            if (tmp->sons[d] == nullptr) tmp->sons[d] = new Node();
            tmp = tmp->sons[d];
            tmp->cnt++;
        }
    }

    int query(string& s) {
        Node* tmp = head;

        for (char c : s) {
            int d = record[c];
            if (tmp->sons[d] == nullptr) return 0;
            tmp = tmp->sons[d];
        }

        return tmp->cnt;
    }

};


int main() {
    init();
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        Trie* trie = new Trie();
        for (int i = 0; i < n; ++i) {
            string s;
            cin >> s;
            trie->add(s);
        }

        for (int i = 0; i < q; ++i) {
            string s;
            cin >> s;
            cout << trie->query(s) << endl;
        }
        delete trie;
    }
}
