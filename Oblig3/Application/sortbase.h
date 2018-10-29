#ifndef SORTBASE_H
#define SORTBASE_H

#include <mainwindow.h>

#include <algorithm>
#include <conio.h>
#include <ctime>
#include <queue>
#include "BinaryTree/binarytree.h"

class SortBase
{
public:
    SortBase(MainWindow* window)
    {
        window_ = window;
    }

    template <typename T>
    void Sort(std::vector<std::vector<T*>> dataSet, Algorithm algorithm)
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
                    MergeSort(dataSet[i]);
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
                default:
                    break;
                }
            }
        }

        window_->onThreadExit(algorithm);
    }

private:
    template <typename T>
    void MergeSort(std::vector<T*>& data)
    {
        std::vector<T*> hjelp;
        hjelp.reserve(data.size());
        unsigned int size = 1;
        while (size < data.size())
        {
               unsigned int i, j;
               unsigned int lower1 = 0;
               unsigned int k = 0;
               while (lower1+size < data.size())
               {
                  unsigned int upper1 = lower1+size-1;
                  unsigned int lower2 = upper1+1;
                  unsigned int upper2 = (lower2+size-1 < data.size()) ? lower2+size-1 : data.size()-1;
                  for (i=lower1, j=lower2; i<=upper1 && j<=upper2; k++)
                     if (data[i] < data[j])
                        hjelp[k]=data[i++];
                     else
                        hjelp[k] = data[j++];

                  for (; i<=upper1; k++)
                     hjelp[k] = data[i++];
                  for (; j<=upper2; k++)
                     hjelp[k] = data[j++];

                  lower1 = upper2+1;
               } // endwhile

               for (i=lower1; k<data.size(); i++)
                  hjelp[k++] = data[i];
               for (i=0; i<data.size(); i++)
                  data[i] = hjelp[i];

               size = size*2;
           }
    }

    template <typename T>
    void InsertionSort(std::vector<T*>& data)
    {
        for(unsigned int i = 0; i < data.size(); ++i)
        {
            auto key = data[i];
            int j = i - 1;
            while (j >= 0 && data[j] > key)
            {
                data[j+1] =  data[j];
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
    void SelectionSort(std::vector<T*>& data)
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
    void QuickSort(std::vector<T*>& data, int low, int high)
    {
        if(low < high)
        {
            int pi = partition(data, low, high);

            QuickSort(data, low,  pi - 1);
            QuickSort(data, pi + 1, high);
        }
    }

    template <typename T>
    int partition(std::vector<T*>& data, int low,int high)
    {
        auto pivot = data[high];
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
    void BinarySearchTreeSort(std::vector<T*>& data)
    {
        auto root = ADS101::btree<int>(*data[0]);
        for(unsigned int i = 0; i < data.size(); ++i)
        {
            root.insert(*data[i]);
        }
    }

    template <typename T>
    void HeapSort(std::vector<T*>& data)
    {
        std::priority_queue<T*, std::vector<T*>, std::greater<T*>> heap;
        for(unsigned int i = 0; i < data.size(); ++i)
        {
            heap.push(data[i]);
        }
    }

    MainWindow* window_;
    std::vector<double> times_;
};

#endif // SORTBASE_H
