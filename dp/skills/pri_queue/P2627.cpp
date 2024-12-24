/*
  P2627：给一个长度为 n 的数组，选择不能连续超过 k 的数，使得和最大；
  
  dp问题：状态定义：f[i][0]：表示当前位置不选的最大和，f[i][1]：表示当前位置选的最大和；
	  状态转移：f[i][0] = max(f[i-1][0], f[i-1][1]), f[i][1] = max{f[j][0] + sum(nums[l]), 其中 l 所在区间为[j+1, i]，且 j 在区间[i-k, i]}，该算法的时间复杂度为O(n^2)
	  优化：能不能再 O(1) 的时间下得到 max{f[j][0] + sum(nums[l]), 其中 l 所在区间为[j+1, i]，且 j 在区间[i-k, i]}，可以维护一个前缀和数组，然后计算 f[j][0] - pre_sum[j+1] 的值，然后将其
使用优先队列进行维护，然后每次取出top，使用pre_sum[i+1] + f[j][0] - pre_sum[j+1]即为区间[i-k, i]的最大值；（并维护一个下标，判断下标j是否在区间 [i-k, i] 之间，如果在直接跳过；
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    int n, k;
    cin >> n >> k;
    vector<int> nums(n);
    vector<ll> pre_sum(n+1);

    for(int i = 0; i < n; ++i) {
        cin >> nums[i];
        pre_sum[i+1] = pre_sum[i] + nums[i];
    }
    
    priority_queue<pair<ll, int>> Q;
    vector<vector<ll>> f(n, vector<ll>(2, 0));
    // init
    f[0][0] = 0;
    f[0][1] = pre_sum[1];
    Q.push({f[0][0] - pre_sum[1], 0});

    for(int i = 1; i < n; ++i) {
        f[i][0] = max(f[i-1][0], f[i-1][1]);
        if(i < k)   f[i][1] = f[i-1][1] + nums[i];
        else {
            f[i][1] = 0;
            while(!Q.empty()) {
                auto& [val, loc] = Q.top();
                if(loc < i - k) Q.pop();
                else    { f[i][1] = pre_sum[i+1] + val; break; }
            }
        }
        Q.push({f[i][0] - pre_sum[i+1], i});

    }

    ll res = max(f[n-1][0], f[n-1][1]);
    cout << res << endl;

    return 0;
    
}
