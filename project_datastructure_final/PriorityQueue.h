#pragma once
#include <vector>
#include <iostream>
using namespace std;
template<class T>
class PriorityQueue
{
    private:
        vector<T> heap;

        void heapify_up(int index) {
            if (index == 0) return;

            int parent = (index - 1) / 2;
            if (heap[parent] < heap[index]) {
                std::swap(heap[parent], heap[index]);
                heapify_up(parent);
            }
        }

        void heapify_down(int index) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;

            int largest = index;
            if (left < heap.size() && heap[left] > heap[largest]) {
                largest = left;
            }

            if (right < heap.size() && heap[right] > heap[largest]) {
                largest = right;
            }

            if (largest != index) {
                std::swap(heap[index], heap[largest]);
                heapify_down(largest);
            }
        }

    public:
        PriorityQueue() {}

        bool empty() const {
            return heap.empty();
        }

        int size() const {
            return heap.size();
        }

        void push(const T& value) {
            heap.push_back(value);
            heapify_up(heap.size() - 1);
        }

        void pop() {
            if (empty()) {
                return;
            }

            heap[0] = heap.back();
            heap.pop_back();

            heapify_down(0);
        }

        T& top() {
            return heap.front();
        }

        const T& top() const {
            return heap.front();
        }
};

