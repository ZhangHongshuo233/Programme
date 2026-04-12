class Solution:
    def maxSubArray(self, nums: List[int]) -> int:
        #Leetcode 53. Maximum Subarray
        #method 1: Kadane's Algorithm
        #time complexity: O(n)
        #space complexity: O(1)
        #prerequisite: the array must contain at least one element

        # if not nums:
        #     return 0
        # max_sum = cur_sum = nums[0]
        # for num in nums[1:]:
        #     cur_sum = max(num, cur_sum + num)
        #     max_sum = max(max_sum, cur_sum)
        # return max_sum
    

        #method 2: On-Line Algorithm
        #time complexity: O(n)
        #space complexity: O(1)
        #check if the array is empty
        # if not nums:
        #     return 0
        # #check if the numbers are all negative
        # for num in nums:
        #     if num > 0:
        #         break
        # else:
        #     return max(nums)
        
        # max_sum = cur_sum =0
        # for num in nums:
        #     cur_sum += num
        #     if cur_sum > max_sum:
        #         max_sum = cur_sum
        #     elif cur_sum < 0:   #若cur_sum小于初始值0，则重置cur_sum为0
        #         cur_sum =0
        # return max_sum


    
        #method 3: Divide and Conquer
        #time complexity: O(n log n)
        #space complexity: O(log n)
        def max_crossing_sum(left, mid, right):
            sum_left = float('-inf')  
            sum_temp = 0
            for i in range(mid, left - 1, -1):
                sum_temp += nums[i]
                sum_left = max(sum_left, sum_temp)
            sum_right = float('-inf')
            sum_temp = 0
            for i in range(mid + 1, right + 1):
                sum_temp += nums[i]
                sum_right = max(sum_right, sum_temp)
            return sum_left + sum_right 