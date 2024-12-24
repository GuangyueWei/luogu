/*
  三路快排：可以解决快排中的出现多次重复数据后，导致性能下降的问题；

  思路：使用 left, right 指针标记左区间的右端点 和 右区间的左端点，其中区间 [left, right]为重复元素，且 [0,left] 中的数小于区间中的数，[right, n-1]中的数大于区间数，即区间 [left，right]中的数全局有序

*/

#include <iostream>
#include <vector>
using namespace std;

class solution {

public:
    void t_quick_sort(vector<int>& nums, int left, int right) {
      if (left >= right)  return;
      int piovt = nums[left + rand() % (right - left + 1)];
      int pre = left, i = left, suf = right;
      while (i <= suf) {
        if (nums[i] > piovt)  swap(nums[i], nums[suf--]);
        else if (nums[i] < piovt) swap(nums[pre++], nums[i++]);
        else  i++;
      }

      t_quick_sort(nums, left, pre);
      t_quick_sort(nums, suf+1, right);
    }
    
};

int main() {
    int N;
    cin >> N;
    vector<int> nums(N, 0);
    
    for(int i = 0; i < N; i++) {
        cin >> nums[i];
    }
    
    solution().t_quick_sort(nums, 0, N-1);
    
    for(int i = 0; i < N-1; i++) {
        cout << nums[i] << ' ';
    }
    cout << nums[N-1] <<endl;
    
}
