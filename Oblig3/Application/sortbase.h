#ifndef SORTBASE_H
#define SORTBASE_H

#include <vector>
#include <stdlib.h>
#include <time.h>

enum Algorithm
{
    Selection,
    Insertion,
    Merge,
    Quick
};


class SortBase
{
public:
    SortBase()
    {
        srand(time(NULL));
    }

    template <typename T>
    void Sort(std::vector<T>& data, Algorithm algorithm)
    {
        switch (algorithm) {
        case Selection:
            SelectionSort(data);
            break;
        case Insertion:
            InsertionSort(data);
            break;
        case Merge:
            MergeSort(data);
            break;
        case Quick:
        {
            int low = 0;
            int high = data.size() - 1;
            QuickSort(data, low, high);
            break;
        }
        default:
            break;
        }
    }

    template <typename T>
    std::vector<T> generateRandomData(int length)
    {
        std::vector<T> randomData;
        randomData.reserve(length);

        for(int i = 0; i < length; ++i)
        {
            randomData.push_back(rand() % 100 + 1);
        }

        return randomData;
    }

private:
    template <typename T>
    void MergeSort(std::vector<T>& data)
    {
        unsigned int i, j, k, lower1, lower2, size, upper1, upper2;
        std::vector<T> hjelp;
        hjelp.reserve(data.size());
        size = 1;
        while (size < data.size())
        {
               lower1 = 0;
               k = 0;
               while (lower1+size < data.size())
               {
                  upper1 = lower1+size-1;
                  lower2 = upper1+1;
                  upper2 = (lower2+size-1 < data.size()) ? lower2+size-1 : data.size()-1;
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
    void InsertionSort(std::vector<T>& data)
    {
        int key, j;
        for(unsigned int i = 0; i < data.size(); ++i)
        {
            key = data[i];
            j = i - 1;
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
    void SelectionSort(std::vector<T>& data)
    {
        int min;

        for(unsigned int i = 0; i < data.size() - 1; ++i)
        {
            min = i;
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

};

#endif // SORTBASE_H
