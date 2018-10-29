#ifndef SORTBASE_H
#define SORTBASE_H

#include <mainwindow.h>

#include <QDebug>
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
        srand(static_cast<unsigned int>(time(nullptr)));
        window_ = window;
    }

    template <typename T>
    void Sort(std::vector<std::vector<T>> dataSet, Algorithm algorithm)
    {
        if(dataSet.size())
        {
            clock_t startTime = 0, endTime = 0;
            double duration;
            std::string s;
            for(unsigned int i = 0; i < dataSet.size(); ++i)
            {
                if(!checkIfStillRunning())
                {
                    window_->onThreadExit(algorithm);
                    return;
                }

                if(dataSet[i].size())
                {

                    switch (algorithm) {
                    case SELECTION:
                        s = "Selection Sort: ";
                        startTime = clock();
                        SelectionSort(dataSet[i]);
                        endTime = clock();
                        break;
                    case INSERTION:
                        s = "Insertion Sort: ";
                        startTime = clock();
                        InsertionSort(dataSet[i]);
                        endTime = clock();
                        break;
                    case MERGE:
                        s = "Merge Sort: ";
                        startTime = clock();
                        merge_sort(dataSet[i], 0, dataSet[i].size() - 1);
                        endTime = clock();
                        break;
                    case QUICK:
                    {
                        s = "Quick Sort: ";
                        int low = 0;
                        int high = dataSet[i].size() - 1;
                        startTime = clock();
                        QuickSort(dataSet[i], low, high);
                        endTime = clock();
                        break;
                    }
                    case STL_SORT:
                        s = "std::Sort: ";
                        startTime = clock();
                        std::sort(dataSet[i].begin(), dataSet[i].end());
                        endTime = clock();
                        break;
                    case BINARY_TREE:
                        s = "Binary Search Tree: ";
                        startTime = clock();
                        BinarySearchTreeSort(dataSet[i]);
                        endTime = clock();
                        break;
                    case STL_HEAP:
                        s = "Heap Sort ";
                        startTime = clock();
                        HeapSort(dataSet[i]);
                        endTime = clock();
                        break;
                    case BOGO:
                        s = "Bogo Sort: ";
                        startTime = clock();
                        BogoSort(dataSet[i]);
                        endTime = clock();
                        break;
                    }
                }

                duration = (endTime - startTime) / static_cast<double>(CLOCKS_PER_SEC);
                times_.push_back(duration);
            }

            double totalTime = 0;
            for(auto& duration : times_)
            {
                totalTime += duration;
            }
            window_->updateTimeTakenList(s, totalTime);
        }
        window_->onThreadExit(algorithm);
    }

private:
    MainWindow* window_;
    std::vector<double> times_;
    std::mutex mutex_;

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
        std::vector<T> temp;
        int length = right_high - left_low + 1;
        int left = left_low;
        int right = right_low;
        for (int i = 0; i < length; ++i) {

        if(!checkIfStillRunning())
            return;

            if (left > left_high)
                temp.push_back(data[right++]);
            else if (right > right_high)
                temp.push_back(data[left++]);
            else if (data[left] <= data[right])
                temp.push_back(data[left++]);
            else
                temp.push_back(data[right++]);
        }
        for (int i = 0; i < length; ++i)
        {
            if(!checkIfStillRunning())
                return;
            data[left_low++] = temp[i];
        }
    }

    template <typename T>
    void InsertionSort(std::vector<T>& data)
    {
        for(unsigned int i = 0; i < data.size(); ++i)
        {
            int key = data[i];
            unsigned int j = i - 1;
            while (j >= 0 && data[j] > key)
            {
                if(!checkIfStillRunning())
                    return;

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
            if(!checkIfStillRunning())
                return;
            unsigned int min = i;
            for(unsigned int j = i + 1; j < data.size(); ++j)
            {
                if(!checkIfStillRunning())
                    return;
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

            if(pi == -1)
                return;

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
            if(!checkIfStillRunning())
                return -1;

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
            if(!checkIfStillRunning())
                return;
            heap.push(data[i]);
        }
    }

    template <typename T>
    void BogoSort(std::vector<T>& data)
    {
        while(!isSorted(data, data.size()))
        {
            if(!checkIfStillRunning())
                return;
            shuffle(data);
        }
    }

    template <typename T>
    bool isSorted(std::vector<T>& data, unsigned int n)
    {
        while(--n > 0)
        {
            if(!checkIfStillRunning())
                return true;

            if(data[n] < data[n-1])
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
            if(!checkIfStillRunning())
                return;
            swap(&data[i], &data[rand()%data.size()]);
        }
    }

    bool checkIfStillRunning()
    {
        std::lock_guard<std::mutex> lock(mutex_);

        return window_->getIsSorting();
    }
};

#endif // SORTBASE_H
