#pragma once
#include <iostream>
using namespace std;

/*
	Heap �����Ƽ� �ΰ������ ��ܳ־���µ� �Ѱ��� Ÿ�����θ� ����ؾ���.. 
	heap �� �����ؼ� ��¿������... ���εα�� �� ����
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
	bool compare_heap(HeapNode* n1, HeapNode* n2) {	//�ؿ� ������ ������ ��Ŭ�� true�� �������Ƿ�.. �̰Ű�������ؾ��� NULL �����ȵ�
		if (n1->data >= n2->data)return true;	//������ ��ũ�� return true
		else return false;	//�������� ��ũ�� return false
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
		while (cur > 0 && compare_heap(heap[p],heap[cur])){ //����ġ�� �ڱ� parent ���� Ŀ���� �ƴϸ� ����
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
			if (compare_heap(heap[left], heap[right])) {	//������ �� Ŭ�� �����ʳ༮�� �ٽú�
				if (compare_heap(heap[right], heap[cur]))break;
				else {
					heap_swap(cur,right);
					cur = right;
					left = cur * 2 + 1;
					right = left + 1;
				}
			}
			else {	//������ �༮�� �� ũ�� �����̶� �ٽú�
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