#pragma once

template <typename T>
class MinHeap
{
    T arr[1000];
    int size;

public:
    MinHeap()
    {
        size = 0;
    }
    void insert(T data)
    {
        arr[size] = data;
        int childIndex = size;
        int parentIndex = (childIndex - 1) / 2;
        while (childIndex > 0)
        {
            if (arr[childIndex] < arr[parentIndex])
            {
                T temp = arr[childIndex];
                arr[childIndex] = arr[parentIndex];
                arr[parentIndex] = temp;
                childIndex = parentIndex;
                parentIndex = (childIndex - 1) / 2;
            }
            else
                break;
        }
        size++;
    }
    T remove()
    {
        if (size == 0)
        {
            exit(1);
        }
        T ans = arr[0];
        arr[0] = arr[size - 1];
        size--;
        int parentIndex = 0;
        int leftChildIndex = 2 * parentIndex + 1;
        int rightChildIndex = 2 * parentIndex + 2;
        while (leftChildIndex < size)
        {
            int minIndex = parentIndex;
            if (arr[leftChildIndex] < arr[minIndex])
                minIndex = leftChildIndex;
            if (rightChildIndex < size && arr[rightChildIndex] < arr[minIndex])
                minIndex = rightChildIndex;
            if (minIndex == parentIndex)
                break;
            T temp = arr[minIndex];
            arr[minIndex] = arr[parentIndex];
            arr[parentIndex] = temp;
            parentIndex = minIndex;
            leftChildIndex = 2 * parentIndex + 1;
            rightChildIndex = 2 * parentIndex + 2;
        }
        return ans;
    }
    T getMin()
    {
        if (size == 0)
        {
            exit(1);
        }
        return arr[0];
    }
    int getSize()
    {
        return size;
    }
    bool isEmpty()
    {
        return size == 0;
    }
};