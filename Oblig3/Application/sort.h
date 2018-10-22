#ifndef SORT_H
#define SORT_H

#include <vector>

class Sort
{
public:
    Sort();

    template<typename T>
    void Merge(std::vector<T>& vectorToSort);

private:
    template<typename T>
    void merge_sort(std::vector<T>& a, int low, int high);
    template<typename T>
    void merge_final(std::vector<T>& a, int left_low, int left_high, int right_low, int right_high);

    template<typename T>
    void print(std::vector<T>& a);

};

#endif // SORT_H
