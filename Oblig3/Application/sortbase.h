#ifndef SORTBASE_H
#define SORTBASE_H

#include <mainwindow.h>

#include <algorithm>
#include <conio.h>
#include <ctime>
#include <queue>
#include "BinaryTree/binarytree.h"
#include <stdlib.h>
#include <time.h>

class SortBase
{
public:
    SortBase(MainWindow* window)
    {
        srand(time(NULL));
        window_ = window;
    }

    template <typename T>
    void Sort(std::vector<std::vector<T>> dataSet, Algorithm algorithm)
    {
        for(unsigned int i = 0; i < dataSet.size(); ++i)
        {
            if(dataSet[i].size())
            {
                clock_t startTime, endTime;
                double duration;
                switch (algorithm) {
                case SELECTION:
                    startTime = clock();
                    SelectionSort(dataSet[i]);
                    endTime = clock();
                    duration = (endTime - startTime) / (double)CLOCKS_PER_SEC;
                    times_.push_back(duration);
                    if(i == dataSet.size() -1)
                    {
                        double totalTime = 0.0f;
                        for(auto& duration : times_)
                        {
                            totalTime += duration;
                        }
                        window_->updateTimeTakenList("Selection Sort: ", totalTime);
                        window_->onThreadExit(SELECTION);
                        return;
                    }
                    break;
                case INSERTION:
                    startTime = clock();
                    InsertionSort(dataSet[i]);
                    endTime = clock();
                    duration = (endTime - startTime) / (double)CLOCKS_PER_SEC;
                    times_.push_back(duration);
                    if(i == dataSet.size() -1)
                    {
                        double totalTime = 0.0f;
                        for(auto& duration : times_)
                        {
                            totalTime += duration;
                        }
                        window_->updateTimeTakenList("Insertion Sort: ", totalTime);
                        window_->onThreadExit(INSERTION);
                        return;
                    }
                    break;
                case MERGE:
                    startTime = clock();
                    merge_sort(dataSet[i], 0, dataSet[i].size() - 1);
                    endTime = clock();
                    duration = (endTime - startTime) / (double)CLOCKS_PER_SEC;
                    times_.push_back(duration);
                    if(i == dataSet.size() -1)
                    {
                        double totalTime = 0.0f;
                        for(auto& duration : times_)
                        {
                            totalTime += duration;
                        }
                        window_->updateTimeTakenList("Merge Sort: ", totalTime);
                        window_->onThreadExit(MERGE);
                        return;
                    }
                    break;
                case QUICK:
                {
                    int low = 0;
                    int high = dataSet[i].size() - 1;
                    startTime = clock();
                    QuickSort(dataSet[i], low, high);
                    endTime = clock();
                    duration = (endTime - startTime) / (double)CLOCKS_PER_SEC;
                    times_.push_back(duration);
                    if(i == dataSet.size() -1)
                    {
                        double totalTime = 0.0f;
                        for(auto& duration : times_)
                        {
                            totalTime += duration;
                        }
                        window_->updateTimeTakenList("Quick Sort: ", totalTime);
                        window_->onThreadExit(QUICK);
                        return;
                    }
                    break;
                }
                case STL_SORT:
                    startTime = clock();
                    std::sort(dataSet[i].begin(), dataSet[i].end());
                    endTime = clock();
                    duration = (endTime - startTime) / (double)CLOCKS_PER_SEC;
                    times_.push_back(duration);
                    if(i == dataSet.size() -1)
                    {
                        double totalTime = 0.0f;
                        for(auto& duration : times_)
                        {
                            totalTime += duration;
                        }
                        window_->updateTimeTakenList("std::Sort: ", totalTime);
                        window_->onThreadExit(STL_SORT);
                        return;
                    }
                    break;
                case BINARY_TREE:
                    startTime = clock();
                    BinarySearchTreeSort(dataSet[i]);
                    endTime = clock();
                    duration = (endTime - startTime) / (double)CLOCKS_PER_SEC;
                    times_.push_back(duration);
                    if(i == dataSet.size() -1)
                    {
                        double totalTime = 0.0f;
                        for(auto& duration : times_)
                        {
                            totalTime += duration;
                        }
                        window_->updateTimeTakenList("Binary Search Tree: ", totalTime);
                        window_->onThreadExit(BINARY_TREE);
                        return;
                    }
                    break;
                case STL_HEAP:
                    startTime = clock();
                    HeapSort(dataSet[i]);
                    endTime = clock();
                    duration = (endTime - startTime) / (double)CLOCKS_PER_SEC;
                    times_.push_back(duration);
                    if(i == dataSet.size() -1)
                    {
                        double totalTime = 0.0f;
                        for(auto& duration : times_)
                        {
                            totalTime += duration;
                        }
                        window_->updateTimeTakenList("Heap Sort: ", totalTime);
                        window_->onThreadExit(STL_HEAP);
                        return;
                    }
                    break;
                case BOGO:
                    startTime = clock();
                    BogoSort(dataSet[i]);
                    endTime = clock();
                    duration = (endTime - startTime) / (double)CLOCKS_PER_SEC;
                    times_.push_back(duration);
                    if(i == dataSet.size() -1)
                    {
                        double totalTime = 0.0f;
                        for(auto& duration : times_)
                        {
                            totalTime += duration;
                        }
                        window_->updateTimeTakenList("Bogo Sort: ", totalTime);
                        window_->onThreadExit(BOGO);
                        return;
                    }
                    break;
                default:
                    break;
                }
            }
        }
        window_->onThreadExit(algorithm);
    }

private:
    template<typename T>
    void merge_sort(std::vector<T>& data, int low, int high)
    {
        if (low >= high)
        {
            return;
        }
        else
        {
          int mid = (low + high) / 2;
          merge_sort(data, low, mid);
          merge_sort(data, mid + 1, high);
          merge(data, low, mid, mid + 1, high);
        }
    }

    template<typename T>
    void merge(std::vector<T>& data, int left_low, int left_high, int right_low, int right_high)
    {
        int length = right_high - left_low + 1;
        int temp[length];
        int left = left_low;
        int right = right_low;
        for (int i = 0; i < length; ++i) {
            if (left > left_high)
                temp[i] = data[right++];
            else if (right > right_high)
                temp[i] = data[left++];
            else if (data[left] <= data[right])
                temp[i] = data[left++];
            else
                temp[i] = data[right++];
        }

        for (int i=0; i< length; ++i)
            data[left_low++] = temp[i];
    }

    template <typename T>
    void InsertionSort(std::vector<T>& data)
    {
        for(unsigned int i = 0; i < data.size(); ++i)
        {
            int key = data[i];
            int j = i - 1;
            while (j >= 0 && data[j] > key)
            {
                data[j+1] = data[j];
                j = j - 1;
            }
            data[j+1] = key;
        }
    }

    template <typename T>
    void swap(T* data1, T* data2)
    {
        auto temp = *data1;
        *data1 = *data2;
        *data2 = temp;
    }

    template <typename T>
    void SelectionSort(std::vector<T>& data)
    {
        for(unsigned int i = 0; i < data.size() - 1; ++i)
        {
            int min = i;
            for(unsigned int j = i + 1; j < data.size(); ++j)
            {
                if(data[j] < data[min])
                {
                    min = j;
                }
            }

            swap(&data[min], &data[i]);
        }
    }

    template <typename T>
    void QuickSort(std::vector<T>& data, int low, int high)
    {
        if(low < high)
        {
            int pi = partition(data, low, high);

            QuickSort(data, low,  pi - 1);
            QuickSort(data, pi + 1, high);
        }
    }

    template <typename T>
    int partition(std::vector<T>& data, int low,int high)
    {
        int pivot = data[high];
        int i = low - 1;

        for(int j = low; j < high; ++j)
        {
            if(data[j] <= pivot)
            {
                i++;
                swap(&data[i], &data[j]);
            }
        }
        swap(&data[i + 1], &data[high]);
        return i + 1;
    }

    template <typename T>
    void BinarySearchTreeSort(std::vector<T>& data)
    {
        auto root = ADS101::btree<int>(data[0]);
        for(unsigned int i = 0; i < data.size(); ++i)
        {
            root.insert(data[i]);
        }
    }

    template <typename T>
    void HeapSort(std::vector<T>& data)
    {
        std::priority_queue<T, std::vector<T>, std::greater<T>> heap;
        for(unsigned int i = 0; i < data.size(); ++i)
        {
            heap.push(data[i]);
        }
    }

    template <typename T>
    void BogoSort(std::vector<T>& data)
    {
        while(!isSorted(data, data.size()))
        {
            shuffle(data);
        }
    }

    template <typename T>
    bool isSorted(std::vector<T>& data, unsigned int n)
    {
        while(--n > 0)
        {
            if(data[n-1] < data[n-2])
            {
                return false;
            }
        }

        return true;
    }

    template <typename T>
    void shuffle(std::vector<T>& data)
    {
        for(unsigned int i = 0; i < data.size(); ++i)
        {
            swap(&data[i], &data[rand()%data.size()]);
        }
    }

    MainWindow* window_;
    std::vector<double> times_;
};

#endif // SORTBASE_H
