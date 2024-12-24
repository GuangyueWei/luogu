/*
  LCA：最近公共祖先
  给定一棵多根树，求出指定两个点直接最近的公共祖先
  
  输入：
    第一行包含三个正整数 N, M, S，分别表示树的结点个数、询问的个数和树根结点的序号。
  
    接下来 N−1 行每行包含两个正整数 x, y，表示 x 结点和 y 结点之间有一条直接连接的边（数据保证可以构成树）

    接下来 M 行每行包含两个正整数 a,b，表示询问 a 结点和 b 结点的最近公共祖先。
  
  输出：
    输出包含 M 行，每行包含一个正整数，依次为每一个询问的结果。

*/

#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 5; // 节点数量
const int MAX = 21;
vector<int> graph[N];

int f[N][MAX];
int height[N];

int lg[N];

void dfs(int root, int pa, int h) {
    f[root][0] = pa;
    height[root] = h;
    
    for(int i = 1; (1 << i) <= h; ++i) {
        f[root][i] = f[f[root][i-1]][i-1];
    }

    for(int& next : graph[root]) {
        if (next != pa) {
            dfs(next, root, h+1);
        }
    }
}

int LCA(int x, int y) {
    if (height[x] < height[y])  swap(x, y);
    int d = height[x] - height[y];
    int lv = 0;
    while(d) {
        if (d & 1) x = f[x][lv];
        lv++;
        d >>= 1;
    }
    // while(height[x] > height[y])
    //     x = f[x][lg[height[x] - height[y]] - 1];

    if (x == y)  return x;
    else {
        for (int i = lg[height[x]]; i >= 0; --i) {
            if (f[x][i] != f[y][i]) {
                x = f[x][i];
                y = f[y][i];
            }
        }
        return f[x][0];
    }
}

int main() {
    int n, m, s; // 表示节点数目，询问次数，根节点编号
    cin >> n >> m >> s;

    int t = n-1;
    while(t--) {
        int x, y;
        cin >> x >> y;
        graph[x].emplace_back(y);
        graph[y].emplace_back(x);
    }
    lg[0] = 0;
    for (int i = 1; i <= n; ++i)    lg[i] = lg[i-1] + ((1 << lg[i-1]) == i);
    dfs(s, 0, 1);

    while(m--) {
        int x, y;
        cin >> x >> y;
        int ret = LCA(x, y);
        cout << ret << endl;
    }
}
