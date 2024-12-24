/*
 数位dp：统计区间 [a, b] 中的所有整数，每一个数码各出现了多少次。

 
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll dfs(int loc, bool is_limit, bool is_num, string& s, vector<vector<ll>>& dp, int cnt, int dig) {

    if(loc == s.size()) return cnt;

    if(!is_limit && is_num && dp[loc][cnt] >= 0) return dp[loc][cnt];


    ll res = 0;

    if(!is_num) {
        res += dfs(loc+1, 0, 0, s, dp, cnt, dig);
    }


    int up = (is_limit? s[loc] - '0' : 9);

    for(int i = (is_num? 0 : 1); i <= up; i++) {
        if(i == dig)  res = res + dfs(loc+1, (is_limit && i == up), 1, s, dp, cnt + 1, dig);
        else    res = res + dfs(loc+1, (is_limit && i == up), 1, s, dp, cnt, dig);
    }

    if(!is_limit && is_num) dp[loc][cnt] = res;
    
    return res;
}

vector<vector<ll> > dp;
ll ans[10];

void solve(ll l, ll r) {
    memset(ans, 0, sizeof ans);
    dp.resize(12, vector<ll>(128, -1));
    string s_r = to_string(r);
    string s_l = to_string(l-1);

    for(int i = 0; i < 10; i++) {
        dp.assign(12, vector<ll>(128, -1));
        ans[i] = dfs(0, 1, 0, s_r, dp, 0, i);
    }

    for(int i = 0; i < 10; i++) {
        dp.assign(12, vector<ll>(128, -1));
        ans[i] -= dfs(0,1, 0, s_l, dp, 0, i);
    }
}

int main() {
    // int t;
    // cin >> t;
    // while(t--) {
        
    // }
    ll l, r;
    cin >> l >> r;
    solve(l, r);
    for(ll i : ans)    cout << i << " ";
    cout << endl;
}
