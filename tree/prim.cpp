/*
  prim: 最小生成树算法，通过向连通图中加入最小的一条边（边的节点为从标记到未标记），构建最小生成树。

  思路：构建一个 seen 数组标记节点是否加入连通图，使用优先队列保存边，每次取出最小的边，判断后加入到连通图中，进行标记。

*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> edges(n+1);
    for (int i = 0; i < m; ++i) {
        int x, y, w;
        cin >> x >> y >> w;
        edges[x].emplace_back(y, w);
        edges[y].emplace_back(x, w);
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> Q;
    vector<int> seen(n+1, 0);
    Q.push({0, 1});

    int ret = 0;
    while (!Q.empty()) {
        auto [w, node] = Q.top();
        Q.pop();
        if (seen[node]) continue;
        ret += w;
        seen[node] = 1;
        for (auto next : edges[node]) {
            if (seen[next.first]) continue;
            Q.push({next.second, next.first});
        }

    }

    for (int i = 1; i <= n; ++i) {
        if (seen[i] == 0) {
            cout << "orz" << endl;
            return 0;
        }
    }

    cout << ret << endl;
}
