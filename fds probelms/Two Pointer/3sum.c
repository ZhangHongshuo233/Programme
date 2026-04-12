/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int cmp(const void* a, const void* b){
    return *(int*)a - *(int*)b;
}

int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    if(numsSize < 3){
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }
    int n = numsSize;
    qsort(nums,n,sizeof(int),cmp);
    int** ans = (int**)malloc(sizeof(int*)*n*n);
    *returnColumnSizes = (int*)malloc(sizeof(int)*n*n);
    int idx = 0;
    for(int i=0;i<n-2;i++){
        int x = nums[i];
        if(i>0 && x == nums[i-1])
            continue;
        if(x + nums[i+1] + nums[i+2] > 0)
            break;
        if( x + nums[n-2] + nums[n-1] < 0)
            continue;
        int j =i + 1, k = n -1;
        while(j<k) {
            int sum = x + nums[j] + nums[k];
            if(sum > 0){
                k--;
            }else if(sum < 0){
                j++;
            }else{
                int* tuple = (int*)malloc(sizeof(int)*3);
                tuple[0] = x;
                tuple[1] = nums[j];
                tuple[2] = nums[k];
                ans[idx] =tuple;
                (*returnColumnSizes)[idx] = 3;
                idx++; 
                j++;
                while(j<k && nums[j] == nums[j-1])
                    j++;
                k--;
                while(j<k && nums[k] == nums[k+1])
                    k--;
            }
        }
    }
    *returnSize = idx;
    return ans;
}