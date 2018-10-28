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
    void Sort(std::vector<T*> data, Algorithm algorithm)
    {
        if(data.size())
        {
            clock_t startTime, endTime;
            double duration;
            switch (algorithm) {
            case SELECTION:
                startTime = clock();
                SelectionSort(data);
                endTime = clock();
                duration = (endTime - startTime) / (double)CLOCKS_PER_SEC;
                window_->updateTimeTakenList("Selection Sort: ", duration);
                break;
            case INSERTION:
                startTime = clock();
                InsertionSort(data);
                endTime = clock();
                duration = (endTime - startTime) / (double)CLOCKS_PER_SEC;
                window_->updateTimeTakenList("Insertion Sort: ", duration);
                break;
            case MERGE:
                startTime = clock();
                MergeSort(data);
                endTime = clock();
                duration = (endTime - startTime) / (double)CLOCKS_PER_SEC;
                window_->updateTimeTakenList("Merge Sort: ", duration);
                break;
            case QUICK:
            {
                int low = 0;
                int high = data.size() - 1;
                startTime = clock();
                QuickSort(data, low, high);
                endTime = clock();
                duration = (endTime - startTime) / (double)CLOCKS_PER_SEC;
                window_->updateTimeTakenList("Quick Sort: ", duration);
                break;
            }
            case STL:
                startTime = clock();
                std::sort(data.begin(), data.end());
                endTime = clock();
                duration = (endTime - startTime) / (double)CLOCKS_PER_SEC;
                window_->updateTimeTakenList("std::Sort: ", duration);
                break;
            case BINARY_TREE:
                startTime = clock();
                BinarySearchTreeSort(data);
                endTime = clock();
                duration = (endTime - startTime) / (double)CLOCKS_PER_SEC;
                window_->updateTimeTakenList("Binary Search Tree Sort: ", duration);
                break;
            case HEAP:
                startTime = clock();
                HeapSort(data);
                endTime = clock();
                duration = (endTime - startTime) / (double)CLOCKS_PER_SEC;
                window_->updateTimeTakenList("Heap Sort: ", duration);
                break;
            default:
                break;
            }
        }

        window_->onThreadExit(std::this_thread::get_id(), algorithm);
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
        auto root = new ADS101::btree<int>(*data[0]);
        for(unsigned int i = 0; i < data.size(); ++i)
        {
            root->insert(*data[i]);
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
    std::mutex mutex_;
};

#endif // SORTBASE_H
