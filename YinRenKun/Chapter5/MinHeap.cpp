//
// Created by steve on 18-10-19.
//

#include <iostream>
#include "../Chapter3/PriorQueue.cpp"

#define DefaultSize 10
using namespace std;

template<typename E>
class MinHeap : public PriorQueue<E> {
public:
    MinHeap(int sz = DefaultSize);

    MinHeap(E arr[], int n);

    ~MinHeap() { delete (heap); }

    bool Insert(const E &x);

    bool RemoveMin(E &x);

    bool IsEmpty() const { return currentSize == 0; }

    bool IsFull() const { return currentSize == maxHeapSize; }

    void MakeEmpty() { currentSize = 0; }

private:
    E *heap;
    int currentSize;
    int maxHeapSize;

    //从start到m下滑成为最小堆
    void siftDown(int start, int m);

    //从start到0上滑成为最小堆
    void siftUp(int start);
};

template<typename E>
MinHeap<E>::MinHeap(int sz) {
    maxHeapSize = DefaultSize < sz ? sz : DefaultSize;
    heap = new E[maxHeapSize];
    if (!heap)cerr << "堆存储分配失败！" << endl;
    currentSize = 0;
}

template<typename E>
MinHeap<E>::MinHeap(E *arr, int n) {
    maxHeapSize = DefaultSize < n ? n : DefaultSize;
    heap = new E[maxHeapSize];
    if (!heap)cerr << "堆存储分配失败！" << endl;
    currentSize = n;
    for (int i = 0; i < n; ++i) heap[i] = arr[i];

    int currentPos = (currentSize - 2) / 2;
    //从下向上逐步调整
    while (currentPos >= 0) {
        //局部自上向下下滑调整
        siftDown(currentPos, currentSize - 1);
        //再向前换一个分支结点
        currentPos--;
    }
}

template<typename E>
void MinHeap<E>::siftDown(int start, int m) {
    int i = start, j = i * 2 + 1;//j是i的左子女
    E temp = heap[i];
    while (j <= m) {//检查是否到最后位置
        //让j指向i的较小子女
        if (j < m && heap[j] < heap[j + 1])j++;
        //如果i比子女小或者等，则已经完成最小堆生成
        if (temp <= heap[j]) break;
        else {
            //否则较小子女上移，i指向被移动的子女索引，j再指向新的i的左子女
            heap[i] = heap[j];
            i = j;
            j = 2 * i + 1;
        }
    }
    //while循环结束时，i为指向temp应该存放的位置
    heap[i] = temp;
}