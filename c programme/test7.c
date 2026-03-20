int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    int left=0,right=numsSize-1;
    while(left<right){
        if(nums[left]+nums[right]<target){
            left++;
        }else if(nums[left]+nums[right]>target){
            right--;
        }else{
            int* ans=(int*)malloc(sizeof(int)*2);
            ans[0]=left;
            ans[1]=right;
            *returnSize=2;
            return ans;
        }
    }
    *returnSize=0;
    return NULL;
}