int maxArea(int* height, int heightSize) {
    //time complexity: O(n)
    //space complexity: O(1)
    int ans =0;
    int n = heightSize;
    int left = 0, right = n - 1;
    while(left < right){
        int area = (right - left)* ((height[left]<height[right])?height[left]:height[right]);
        ans = (ans < area)? area:ans;
        if(height[left] < height[right]){
            left++;
        }else{
            right--;
        }
    }
    return ans;
    
}