// Given a sorted array of distinct integers and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.
// You must write an algorithm with O(log n) runtime complexity.

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        for (int i = 0; i < nums.size(); i++) {
        // 分别处理如下三种情况
        // 目标值在数组所有元素之前
        // 目标值等于数组中某一个元素
        // 目标值插入数组中的位置
            if (nums[i] >= target) { // 一旦发现大于或者等于target的num[i]，那么i就是我们要的结果
                return i;
            }
        }
        // 目标值在数组所有元素之后的情况
        return nums.size(); // 如果target是最大的，或者 nums为空，则返回nums的长度
    }
};
// 用find不行，因为find找不到的话会返回nums.size()的index
// 用lower_bound
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        vector<int>::iterator beg, end, lowerBound;
        beg = nums.begin();
        end = nums.end();
        lowerBound = lower_bound(beg, end, target);
        int index = distance(beg, lowerBound);  // 举例在一个升序的容器里，若是全部元素都大于i则，upp和low都返回begin。都小于i则返回end(越界了)
        return index;
    }

    // int searchInsert(vector<int>& nums, int target) {
    //     return lower_bound(nums.begin(), nums.end(), target) - nums.begin();
    // }
};


// 面试题里给出的数组是有序数组，都可以想一想是否可以使用二分法。
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int n = nums.size();
        int left = 0;
        int right = n - 1; // 定义target在左闭右闭的区间里，[left, right]
        while (left <= right) { // 当left==right，区间[left, right]依然有效
            int middle = left + ((right - left) / 2);// 防止溢出 等同于(left + right)/2
            if (nums[middle] > target) {
                right = middle - 1; // target 在左区间，所以[left, middle - 1]
            } else if (nums[middle] < target) {
                left = middle + 1; // target 在右区间，所以[middle + 1, right]
            } else { // nums[middle] == target
                return middle;
            }
        }
        // 分别处理如下四种情况
        // 目标值在数组所有元素之前  [0, -1]
        // 目标值等于数组中某一个元素  return middle;
        // 目标值插入数组中的位置 [left, right]，return  right + 1
        // 目标值在数组所有元素之后的情况 [left, right]， return right + 1
        return right + 1;
    }
};