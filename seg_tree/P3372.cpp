/*
  线段树：区间求和问题（带懒惰标记）

*/

#include <bits/stdc++.h>
using namespace std;

const int SIZE = 1e5+5;

long long sum[4 * SIZE];
long long lazy[4 * SIZE]; // lazy 标记
int nums[SIZE];

void build(int l, int r, int p){
    if(l == r){
        sum[p] = nums[l];
        return;
    }
    int mid = l + ((r - l) >> 1);
    build(l, mid, p << 1);
    build(mid+1, r, (p<<1) + 1);
    sum[p] = sum[p<<1] + sum[(p<<1) + 1];
}

long long get_sum(int l, int r, int p, int L, int R){
    if(L <= l && r <= R) {
        return sum[p];
    }
    int mid = l + ((r - l) >> 1);
    if(lazy[p]) {
        sum[p<<1] += (mid - l + 1) * lazy[p];
        sum[(p<<1) + 1] += (r - mid) * lazy[p];
        lazy[p<<1] += lazy[p];
        lazy[(p<<1) + 1] += lazy[p];
        lazy[p] = 0;
    }
    long long t_sum = 0;
    if(L <= mid)  t_sum += get_sum(l, mid, p<<1, L, R);
    if(R > mid) t_sum += get_sum(mid+1, r, (p<<1)+1, L, R);
    return t_sum;

}

void update(int l, int r, int p, int L, int R, int val) {
    if(L <= l && r <= R) {
        sum[p] += (r - l + 1) * val;
        lazy[p] += val;
        return;
    }
    int mid = l + ((r - l) >> 1);
    // update
    if(lazy[p] && l != r) {
        sum[p<<1] += (mid - l + 1) * lazy[p];
        sum[(p<<1) + 1] += (r - mid) * lazy[p];
        lazy[p<<1] += lazy[p];
        lazy[(p<<1) + 1] += lazy[p];
        lazy[p] = 0;
    }

    if(L <= mid)    update(l, mid, p<<1, L, R, val);
    if(R > mid) update(mid+1, r, (p<<1) + 1, L, R, val);
    sum[p] = sum[p<<1] + sum[(p<<1) + 1];
}

int main() {
    int n, m;
    cin >> n >> m;
    
    for(int i = 1; i <=n; i++)  cin >> nums[i];
    memset(sum, 0, sizeof(sum));
    build(1, n, 1);
    memset(lazy, 0, sizeof(lazy));

    int label, x, y, val;
    while(m--) {
        cin >> label;
        switch (label)
        {
        case 1:
            cin >> x >> y >> val;
            update(1, n, 1, x, y, val);
            break;
        case 2:
            cin >> x >> y;
            cout << get_sum(1, n, 1, x, y) << endl;
            break;
        default:
            break;
        }
    }



}

