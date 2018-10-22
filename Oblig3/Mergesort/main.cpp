#include <iostream>

void merge_sort(int a[], int low, int high);
void merge(int a[], int left_low, int left_high, int right_low, int right_high);

int main()
{
    const int size = 9;
    int data[size] = {8, 3, 2, 7, 6, 1, 9, 5, 4};

    merge_sort(data, 0, size-1);

    for(int i = 0; i < size; ++i)
        std::cout << data[i] << " ";

    std::cout << std::endl;
    return 0;
}

void merge_sort(int a[], int low, int high)
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
      merge(a, low, mid, mid + 1, high);
    }
}

void merge(int a[], int left_low, int left_high, int right_low, int right_high)
{
    int length = right_high - left_low + 1;
    int temp[length];
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
}
