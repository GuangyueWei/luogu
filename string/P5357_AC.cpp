/* 
AC 状态机：求解字符串的多匹配问题，给出多个模式串 和 一个匹配串，找出给模式串在匹配串中出现的次数；
    AC 状态机：以 Trie 的结构为基础，结合 KMP 的思想建立的自动机，用于解决多模式匹配任务。(本质：Trie上的自动机)
    步骤： 
	1. 基础的 Trie 结构，将所有的模式串构成一棵 Trie；
	2. KMP 细想，对 Trie 树上的所有节点构造失配指针。

 	失配指针的构造：fail指针表示，状态定义 fail(u) = v，表示状态 u 的fail指针指向另一状态 v， 其中 u，v 都是自动机上的状态，且 v 是 u 的最长后缀；
	
	转移函数：trans(p, c) = u：表示状态 p 加上一个字符 c 可以转变为状态 u，对于在 Trie 中，即节点 p 通过加上一个字符 c 可以到达 节点 u；
	
	失配指针与转移函数之间的关系为：当前节点为 u（状态），父节点为 p，通过字符 c 转移过来，即Trie(p, c) = u，那么有： 
        
	1. 如果Tire(fail(p), c)存在，那么 fail(u) = Trie(fail(p), c)
        2. 如果 Trie(fail(p), c)不存在，继续找到Trie(fail(fail(p)), c)，重复判断过程，一直跳 fail 指针到根节点，如果依然不存在， fail指针指向根节点

*/

#include <bits/stdc++.h>
using namespace std;

const int inf = -(2e5 + 5);
// 构造字典图 与 fail指针，并使用 topo 排序进行优化
class AC {
    
    // 结构定义
    struct Node {
        
        Node* fail;
        vector<Node*> children;
        
        int idx;
        int cnt;
        int in_degree; // fail 的入度，该节点是否是其余节点的 fail 节点 
        bool seen; // 是否被访问过

        Node() {
            fail = nullptr;
            children.resize(26);
            
            idx = -1;
            cnt = 0;
            in_degree = 0;
            seen = false;
        }

        Node(Node* node) {
            fail = node;
            children.resize(26);
            
            idx = -1;
            cnt = 0;
            in_degree = 0;
            seen = false;
        }
    };
    Node* head;
    int n;
    vector<int> ret;

    void insert(string& s, int idx) {
        Node* tmp = head;

        for (char c : s) {
            int d = c - 'a';
            if (tmp->children[d] == nullptr) tmp->children[d] = new Node(head);          
            tmp = tmp->children[d];
        }
        if (tmp->idx == -1)
            tmp->idx = idx;
        else ret[idx] = -(tmp->idx);
    }
    
public:
    AC(vector<string>& words) {
        head = new Node();
        head->fail = head;
        
        n = words.size();
        ret.resize(n+1);
        ret.assign(n+1, inf);

        int idx = 1;
        for (string& word : words) {
            insert(word, idx++);
        }
        
    }

    // 字典图和 fail 指针的构建
    void build() {
        queue<Node*> Q;
        for (int i = 0; i < 26; ++i) {
            if (head->children[i]) Q.push(head->children[i]);
        }

        while (!Q.empty()) {
            Node* cur = Q.front();
            Q.pop();
            for (int i = 0; i < 26; ++i) {
                if (cur->children[i]) {
                    cur->children[i]->fail = cur->fail->children[i] ? cur->fail->children[i] : head;
                    cur->children[i]->fail->in_degree += 1;
                    Q.push(cur->children[i]);
                } else {
                    cur->children[i] = cur->fail->children[i] ? cur->fail->children[i] : head;
                }
            }
        }
    }

    // 匹配
    void query(string& s) {
        Node* cur = head;

        for (char c : s) {
            int d = c - 'a';
            cur = cur->children[d] ? cur->children[d] : head;

            cur->cnt += 1;
        }

    }

    // result
    vector<int> topo() {
        
        queue<Node*> Q;

        auto dfs = [&](auto&& dfs, Node* cur) -> void{
            if (cur->in_degree == 0) Q.push(cur);
            cur->seen = true;
            for (int i = 0; i < 26; ++i) {
                if (cur->children[i] && cur->children[i]->seen == false) {
                    dfs(dfs, cur->children[i]);
                }
            }
            
        };
        dfs(dfs, head);

        while (!Q.empty()) {
            Node* cur = Q.front();
            Q.pop();
            if (cur->idx != -1) ret[cur->idx] = cur->cnt;
            cur->fail->cnt += cur->cnt;
            cur->fail->in_degree -= 1;
            if (cur->fail->in_degree == 0)  Q.push(cur->fail);
        }

        for (int i = 0; i <= n; ++i) {
            if (ret[i] == inf)  ret[i] = 0;
            else if (ret[i] < 0)    ret[i] = ret[-ret[i]];
        }

        return ret;
    }
};

int main() {
    int n;
    cin >> n;
    vector<string> words(n);

    for (int i = 0; i < n; ++i) {
        cin >> words[i];
    }

    string s;
    cin >> s;

    AC* ac = new AC(words);
    ac->build();
    ac->query(s);
    vector<int> ret = ac->topo();
    for (int i = 1; i <= n; ++i) cout << ret[i] << endl;
    
}


// 模板
/**
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

constexpr int N = 2e5 + 6;
constexpr int LEN = 2e6 + 6;
constexpr int SIZE = 2e5 + 6;

int n;

namespace AC {
struct Node {
  int son[26];  // 子结点
  int ans;      // 匹配计数
  int fail;     // fail 指针
  int du;       // 入度
  int idx;

  void init() {  // 结点初始化
    memset(son, 0, sizeof(son));
    ans = fail = idx = 0;
  }
} tr[SIZE];

int tot;  // 结点总数
int ans[N], pidx;

void init() {
  tot = pidx = 0;
  tr[0].init();
}

void insert(char s[], int &idx) {
  int u = 0;
  for (int i = 1; s[i]; i++) {
    int &son = tr[u].son[s[i] - 'a'];  // 下一个子结点的引用
    if (!son) son = ++tot, tr[son].init();  // 如果没有则插入新结点，并初始化
    u = son;                                // 从下一个结点继续
  }
  // 由于有可能出现相同的模式串，需要将相同的映射到同一个编号
  if (!tr[u].idx) tr[u].idx = ++pidx;  // 第一次出现，新增编号
  idx = tr[u].idx;  // 这个模式串的编号对应这个结点的编号
}

void build() {
  queue<int> q;
  for (int i = 0; i < 26; i++)
    if (tr[0].son[i]) q.push(tr[0].son[i]);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = 0; i < 26; i++) {
      if (tr[u].son[i]) {                               // 存在对应子结点
        tr[tr[u].son[i]].fail = tr[tr[u].fail].son[i];  // 只用跳一次 fail 指针
        tr[tr[tr[u].fail].son[i]].du++;                 // 入度计数
        q.push(tr[u].son[i]);                           // 并加入队列
      } else
        tr[u].son[i] =
            tr[tr[u].fail]
                .son[i];  // 将不存在的字典树的状态链接到了失配指针的对应状态
    }
  }
}

void query(char t[]) {
  int u = 0;
  for (int i = 1; t[i]; i++) {
    u = tr[u].son[t[i] - 'a'];  // 转移
    tr[u].ans++;
  }
}

void topu() {
  queue<int> q;
  for (int i = 0; i <= tot; i++)
    if (tr[i].du == 0) q.push(i);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    ans[tr[u].idx] = tr[u].ans;
    int v = tr[u].fail;
    tr[v].ans += tr[u].ans;
    if (!--tr[v].du) q.push(v);
  }
}
}  // namespace AC

char s[LEN];
int idx[N];

int main() {
  AC::init();
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%s", s + 1);
    AC::insert(s, idx[i]);
    AC::ans[i] = 0;
  }
  AC::build();
  scanf("%s", s + 1);
  AC::query(s);
  AC::topu();
  for (int i = 1; i <= n; i++) {
    printf("%d\n", AC::ans[idx[i]]);
  }
  return 0;
}
*/
