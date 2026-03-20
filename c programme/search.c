int seqSearch_Iterative(int* arr, int n, int key){
    //parameters:arr:the array to be searched
    //           n:the size of the array
    //           key:the value to be searched
    //hypothesis:the array is sorted 
    //return value:the index of the key in the array if found, otherwise -1

    //First:deal with invalid parameters(include null pointer and negative size)
    if(arr == NULL || n <= 0){
        return -1;
    }

    //iterative search：using for loop to traverse the array and compare each element with the key
    for(int i=0;i<n;i++){
        //if the current element is equal to the key, return its index i
        if(arr[i] == key){
            return i;
        }
    }
    return -1;
}


int seqSearch_Recursive(int* arr, int n, int key){
    //parameters:arr:the array to be searched
    //           n:the size of the array
    //           key:the value to be searched
    //hypothesis:the array is sorted
    //return value:the index of the key in the array if found, otherwise -1

    //deal with invalid parameters(include null pointer and negative size)
    if(arr == NULL || n <= 0){
        return -1;
    }

    //recursive search
    //base case:if the first element of the array is equal to the key, return 0
    if(arr[0] == key){
        return 0;
    }

    //recursive case:search the rest of the array by calling the function itself (for each time with the pointer arr to the next element and the size reduced by 1)
    int result = seqSearch_Recursive(arr+1, n-1, key);

    //if the case is that:result is -1, that means the key is not found in the rest of the array, so return -1; 
    //otherwise,that means there exists a certain index i in the rest of the array such that arr[i] == key, so we need to return the index of the key in the original array 
    //if the key is found in the rest of the array at the index result, then the index of the key in the former array is result + 1, because we have skipped the first element of the array in the recursive call
    return (result == -1) ? -1 : result + 1;
}


int binSearch_Iterative(int* arr, int n, int key){
    //parameters:arr:the array to be searched
    //           n:the size of the array
    //           key:the value to be searched
    //hypothesis:the array is sorted
    //return value:the index of the key in the array if found, otherwise -1

    //deal with invalid parameters(include null pointer and negative size)
    if(arr == NULL || n <= 0){
        return -1;
    }

    //iterative search：using while loop to maintain two pointers (left and right) that represent the current search range in the array
    int left = 0;
    int right = n - 1;

    while(left <= right){
        //calculate the middle index of the current search range
        int mid = left + (right - left) / 2;
        //we don't use (left + right) / 2 to avoid potential overflow because the int type has a limited range, 
        //and if left and right are both large enough, their sum may exceed the maximum value of int, causing overflow.
        //By using left + (right - left) / 2, we can avoid this problem because we are calculating the difference between right and left first, which will be less likely to cause overflow as long as right is greater than or equal to left.
        
        //if the middle element is equal to the key, return its index mid
        if(arr[mid] == key){
            return mid;
        }
        //if the middle element is less than the key, that means the key can only be found in the right half of the current search range, so we need to move the left pointer to mid + 1
        else if(arr[mid] < key){
            left = mid + 1;
        }
        //if the middle element is greater than the key, that means the key can only be found in the left half of the current search range, so we need to move the right pointer to mid - 1
        else{
            right = mid - 1;
        }
    }
    //if the while loop ends, that means the left pointer has moved past the right pointer
    //indicating  that the key is not found in the array, so we return -1
    return -1;
}



//To implement the recursive version of binary search, we need use a helper function 
int binSearch_Recursive_helper(int* arr, int left, int right, int key){
    //parameters:arr:the array to be searched
    //           left:the left boundary of the search range
    //           right:the right boundary of the search range
    //           key:the value to be searched
    //hypothesis:the array is sorted
    //return value:the index of the key in the array if found, otherwise -1

    //deal with invalid parameters(include null pointer and invalid search range)
    if(arr == NULL || left > right){
        return -1;
    }

    //recursive search
    //calculate the middle index of the current search range
    int mid = left + (right - left) / 2;
    //the same reason for using left + (right - left) / 2 instead of (left + right) / 2 as mentioned in the iterative version

    //base case:if the middle element is equal to the key, return its index mid
    if(arr[mid] == key){
        return mid;
    }

    //recursive case:
    //if the middle element is less than the key, that means the key can only be found in the right half of the current search range, so we need to search the right half by calling the function itself with the left pointer moved to mid + 1
    if(arr[mid] < key){
        return binSearch_Recursive_helper(arr, mid + 1, right, key);
    }

    //if the middle element is greater than the key, that means the key can only be found in the left half of the current search range, so we need to search the left half by calling the function itself with the right pointer moved to mid - 1
    else{
        return binSearch_Recursive_helper(arr, left, mid - 1, key);
    }
}
int binSearch_Recursive(int* arr, int n, int key) {
    //parameters:arr:the array to be searched
    //           n:the size of the array
    //           key:the value to be searched
    //hypothesis:the array is sorted
    //return value:the index of the key in the array if found, otherwise -1

    //deal with invalid parameters(include null pointer and negative size)
    if(arr == NULL || n <= 0){
        return -1;
    }

    //call the helper function(left initialized as 0 and right initialized as n-1) to perform the recursive search
    return binSearch_Recursive_helper(arr, 0, n-1, key);
}

