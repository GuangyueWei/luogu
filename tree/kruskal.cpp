/*
  kruskal：最小生成树算法，通过加入最小的不构成圈的边，生成一棵树；（加边）
  
  思路：通过并查集判断是否成圈来加入边

*/

#include <bits/stdc++.h>
using namespace std;


int main() {
    int n, m;
    cin >> n >> m;
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> Q;
    for (int i = 0; i < m; ++i) {
        int x, y, w;
        cin >> x >> y >> w;
        Q.push({w, x, y});
    }
    vector<int> pa(n+1, 0);
    iota(pa.begin(), pa.end(), 0);
    
    int ret = 0;

    auto find = [&](auto&& find, int x)->int {
        return (x == pa[x] ? x : pa[x] = find(find, pa[x]));
    };

    auto merge = [&](auto&& merge, int x, int y, int w) ->void {
        int pa_x = find(find, x), pa_y = find(find, y);
        if (pa_x == pa_y)   return;
        ret += w;
        pa[pa_y] = pa_x;
    };

 
    while (!Q.empty()) {
        auto [w, x, y] = Q.top();
        Q.pop();
        int pa_x = find(find, x), pa_y = find(find, y);
        if (pa_x == pa_y)   continue;
        ret += w;
        pa[pa_y] = pa_x;
    }

    int pa_ = find(find, 1);
    for (int i = 1; i <= n; ++i) {
        if (pa_ != find(find, i)) {
            cout << "orz" << endl;
            return 0;
        }
    }

    cout << ret << endl;

}

