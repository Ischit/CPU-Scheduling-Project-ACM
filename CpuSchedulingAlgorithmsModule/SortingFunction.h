#ifndef COMPARE_FUNCTION_H
#define COMPARE_FUNCTION_H

#include "./Process.h"
#include <vector>
#include <algorithm> 
using namespace std;

bool compare_by_return_time(const Process& a, const Process& b) {
    return a.getReturnTime() < b.getReturnTime();
}

void quick_sort_by_return_time(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), compare_by_return_time);
}

void merge(vector<Process>& arr, int left, int mid, int right) {
    int fIdx = left;
    int rIdx = mid + 1;
    int sIdx = left;

    vector<Process> sortArr(arr.size());

    while (fIdx <= mid && rIdx <= right) {
        if (arr[fIdx].getArriveTime() <= arr[rIdx].getArriveTime()) sortArr[sIdx++] = arr[fIdx++];
        else sortArr[sIdx++] = arr[rIdx++];
    }

    while (fIdx <= mid) sortArr[sIdx++] = arr[fIdx++];
    while (rIdx <= right) sortArr[sIdx++] = arr[rIdx++];
    
    for (int i = left; i <= right; i++) arr[i] = sortArr[i];
}

void merge_sort_by_arrive_time(vector<Process>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort_by_arrive_time(arr, left, mid);
        merge_sort_by_arrive_time(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

#endif
