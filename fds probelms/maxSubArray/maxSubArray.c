//method 1: Kadane's Algorithm
//time complexity: O(n)
//space complexity: O(1)
int maxSubArray(int* nums, int numsSize) {
    int n = numsSize;   
    int max_sum = nums[0], cur_sum = max_sum;
    for(int i=1;i<n;i++){
        int temp = cur_sum + nums[i];
        cur_sum = (temp > nums[i])? temp:nums[i];
        max_sum = (cur_sum > max_sum)? cur_sum:max_sum;
    }
    return max_sum;
}