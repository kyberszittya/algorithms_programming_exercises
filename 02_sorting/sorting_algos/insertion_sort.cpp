//
// Created by keret on 2026. 02. 15..
//

#include "sort_algorithms.h"

template<typename T>
void InsertionSort<T>::sort(std::vector<T> &arr)
{
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        T key = arr[i];
        int j = i - 1;

        /* Move elements of arr[0..i-1], that are
           greater than key, to one position ahead
           of their current position */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

template class InsertionSort<int>;