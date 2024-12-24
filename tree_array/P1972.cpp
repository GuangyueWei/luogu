/*
  P1972: HH 的项链
    给定一个数组，并给出多组询问，求解询问区间中的数据的种类；

  树状数组求解：可以对询问进行排序，对左端点从左到右进行排序，在查询过程中，对小于左端点的数据种类减少，然后再次查询。

*/

#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int nums[N];
unordered_map<int, int> seen; // 记录出现值的位置，离散化
int n, m;
vector<int> queries[N]; // 数据询问


// 树状数组
class TG{
    int n;
    vector<int> record;
public:
    TG(int size) {
        n = size + 1;
        record.resize(n);
        record.assign(n, 0);
    }
    
    int lowbit(int x) {
        return x & (-x);
    }

    void add(int x, int val) {
        while (x <= n) {
            record[x] += val;
            x += lowbit(x);
        }
    }

    int query(int l, int r) {
        int x = r;
        int ret_r = 0;
        while (x) {
            ret_r += record[x];
            x -= lowbit(x);
        }

        x = l - 1;
        int ret_l = 0;
        while (x) {
            ret_l += record[x];
            x -= lowbit(x);
        }

        return ret_r - ret_l;
    }
};

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> nums[i];
    }

    TG Tg(n);

    cin >> m;
    vector<int> ans(m+1, 0);
    for (int i = 1; i <= m; ++i) {
        int x, y;
        cin >> x >> y;
        queries[i] = {x, y, i};
    }

    sort(queries + 1, queries + 1 + m, [](const vector<int>& q1, const vector<int>& q2){
        return q1[1] < q2[1];
    });

    
    int prev = 1;
    for (int i = 1; i <= m; ++i) {
        for (int j = prev; j <= queries[i][1]; ++j) {
            if (seen.count(nums[j])) {
                int x = seen[nums[j]];
                Tg.add(x, -1);
            }
            seen[nums[j]] = j;
            Tg.add(j, 1);
        }
        prev = queries[i][1];
        ans[queries[i][2]] = Tg.query(queries[i][0], queries[i][1]);
    }

    for (int i = 1; i <= m; ++i) {
        cout << ans[i] << endl;
    }
}

