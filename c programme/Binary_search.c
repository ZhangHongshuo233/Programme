int BinarySearchSeqList(SeqList *list, int target) {
    int left = 0, right = list->clen - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2; // 避免直接 (left+right) 溢出
        if (list->head[mid].score == target) {
            return mid; // 返回匹配元素下标
        } else if (list->head[mid].score < target) {
            left = mid + 1; // 目标在右半区
        } else {
            right = mid - 1; // 目标在左半区
        }
    }
    return -1; // 未找到
}