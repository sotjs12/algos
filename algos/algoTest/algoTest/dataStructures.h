#pragma once
#include <iostream>
using namespace std;

/*
	Heap 귀찮아서 두가지모드 우겨넣어놨는데 한가지 타입으로만 사용해야함.. 
	heap 를 공유해서 어쩔수없음... 따로두기는 또 싫음
*/
class HeapNode {
public:
	int data;
	HeapNode() {}
	HeapNode(int d) {
		data = d;
	}
};
class Heap {
private:
	HeapNode** heap = NULL;
	int capacity = 2;
	int curIdx=0;
	bool compare_heap(HeapNode* n1, HeapNode* n2) {	//밑에 구현도 왼쪽이 더클때 true에 맞췄으므로.. 이거계속유지해야함 NULL 값도안됨
		if (n1->data >= n2->data)return true;	//왼쪽이 더크면 return true
		else return false;	//오른쪽이 더크면 return false
	}
	int get_parentPos(int cur) {
		return (cur - 1) / 2;
	}
	void heap_swap(int a, int b) {
		HeapNode* temp = heap[a];
		heap[a] = heap[b];
		heap[b] = temp;
	}
public:
	Heap() {
		heap = new HeapNode*[capacity];
	}
	void insert_heap(int data) {
		HeapNode* h = new HeapNode(data);
		int cur = curIdx;
		int p = get_parentPos(cur);
		if (curIdx == capacity) {
			capacity *= 2;
			HeapNode** temp = new HeapNode*[capacity];
			for (int i = 0; i < curIdx; ++i)
				temp[i] = heap[i];
			delete []heap;
			heap = temp;
		}
		heap[curIdx++] = h;
		while (cur > 0 && compare_heap(heap[p],heap[cur])){ //새위치는 자기 parent 보다 커야함 아니면 뤂뤂
			heap_swap(p, cur);
			cur = p;
			p = get_parentPos(cur);
		}
	}
	HeapNode* get_top() {
		return heap[0];
	}
	void pop_heap() {
		int cur = 0,left =1,right =2;
		delete heap[0];
		heap[0] = heap[--curIdx];
		heap[curIdx] = NULL;
		while (1) {
			if (heap[left] == NULL || left > curIdx)break;
			if (heap[right] == NULL || left > curIdx) {
				if (compare_heap(heap[left], heap[cur]))break;
				else {
					heap_swap(cur, left);
					cur = left;
					left = cur * 2 + 1;
					right = left + 1;
					continue;
				}
			}				
			if (compare_heap(heap[left], heap[right])) {	//왼쪽이 더 클때 오른쪽녀석과 다시비교
				if (compare_heap(heap[right], heap[cur]))break;
				else {
					heap_swap(cur,right);
					cur = right;
					left = cur * 2 + 1;
					right = left + 1;
				}
			}
			else {	//오른쪽 녀석이 더 크면 왼쪽이랑 다시비교
				if (compare_heap(heap[left], heap[cur]))break;
				else {
					heap_swap(cur, left);
					cur = left;
					left = cur * 2 + 1;
					right = left + 1;
				}
			}
		}
	}
};