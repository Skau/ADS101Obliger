#ifndef SORTBASE_H
#define SORTBASE_H

#include <vector>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <QVariant>

enum Algorithm
{
    SELECTION,
    INSERTION,
    MERGE,
    QUICK,
    STL,
    BINARY_TREE,
    HEAP
};


class SortBase
{
public:
    SortBase()
    {
        srand(time(NULL));
    }

    template <typename T>
    void Sort(std::vector<T*> data, Algorithm algorithm)
    {
        if(data.size())
        {
            switch (algorithm) {
            case SELECTION:
                SelectionSort(data);
            case INSERTION:
                InsertionSort(data);
            case MERGE:
                MergeSort(data);
            case QUICK:
            {
                int low = 0;
                int high = data.size() - 1;
                QuickSort(data, low, high);
            }
            case STL:
                STLSort(data);
            case BINARY_TREE:
                break;
            case HEAP:
                break;
            default:
                break;
            }
        }
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
   void STLSort(std::vector<T*>& data)
    {
        std::sort(data.begin(), data.end());
    }

};

#endif // SORTBASE_H
