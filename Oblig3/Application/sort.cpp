#include "sort.h"
#include <QDebug>

Sort::Sort()
{

}

template<typename T>
void Sort::Merge(std::vector<T> &vectorToSort)
{
    merge_sort(vectorToSort, 0, vectorToSort.size() - 1);
}

template<typename T>
void Sort::merge_sort(std::vector<T>& a, int low, int high)
{
    if (low >= high)
    {
        return;
    }
    else
    {
      int mid = (low + high) / 2;
      merge_sort(a, low, mid);
      merge_sort(a, mid + 1, high);
      merge_final(a, low, mid, mid + 1, high);
    }
}

template<typename T>
void Sort::merge_final(std::vector<T>& a, int left_low, int left_high, int right_low, int right_high)
{
    int length = right_high - left_low + 1;
    int temp[a.size()];
    int left = left_low;
    int right = right_low;
    for (int i = 0; i < length; ++i) {
        if (left > left_high)
            temp[i] = a[right++];
        else if (right > right_high)
            temp[i] = a[left++];
        else if (a[left] <= a[right])
            temp[i] = a[left++];
        else
            temp[i] = a[right++];
    }

    for (int i=0; i< length; ++i)
        a[left_low++] = temp[i];

    print(a);
}

template<typename T>
void Sort::print(std::vector<T> &a)
{
    for(auto& data : a)
        qDebug() << data << " ";
}
