#include <iostream>
#include <vector>

template<typename T>
void merge_sort(std::vector<T>& a);
template<typename T>
void merge_sort(std::vector<T>& a, int low, int high);
template<typename T>
void merge_final(std::vector<T>& a, int left_low, int left_high, int right_low, int right_high);
template<typename T>
void print(std::vector<T>& a);

int main()
{
    std::vector<int> data1 = {8, 3, 2, 7, 6, 1, 9, 5, 4};
    std::vector<char> data2 = {'h', 'r', 'n', 'a', 'z', 'y', 'w', 'k', 'l'};

    merge_sort(data1);
    merge_sort(data2);

    print(data1);
    print(data2);

    return 0;
}

template<typename T>
void merge_sort(std::vector<T>& a)
{
    merge_sort(a, 0, a.size() - 1);
}

template<typename T>
void merge_sort(std::vector<T>& a, int low, int high)
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
void merge_final(std::vector<T>& a, int left_low, int left_high, int right_low, int right_high)
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

template<typename T>
void print(std::vector<T> &a)
{
    for(auto& data : a)
    {
        std::cout << data << " ";
    }

    std::cout << std::endl;
}
