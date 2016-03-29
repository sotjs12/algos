#pragma once
#include <iostream>
#include <time.h>
#include "dataStructures.h"
using namespace std;

//count bit
int SWAR(unsigned int i)
{
	i = i - ((i >> 1) & 0x55555555);
	i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
	return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}
int bc(int x) {
	int ret = 0;
	while (x > 0) {
		++ret;
		x &= x - 1;
	}
	return ret;
}
/////count bit
class sorts {
private:
	int idx,sidx,min,temp;
	clock_t begin, end;
public:
	void print(int* arr,int size) {
		for (idx = 0; idx < size; ++idx)
			cout << arr[idx] << " ";
		cout << endl;
		cout << "����ð� : " << (end - begin) << endl;
	}
	void swap(int &a,int &b) {
		temp = a;
		a = b;
		b = temp;
	}
	/*
		�������� n-1 ���� ���Ҹ� �߻�, ���Ҽ��� ���� �켱���� ť�� �񱳷��� ���ϼ�����
		�̻����� �켱����ť�� �����Ѵٸ� nlogn  �ӵ�
	*/


	void selection_sort(int* arr,int size) {
		begin = clock();
		for (idx = 0; idx < size; ++idx) {
			min = idx;
			for (sidx = idx + 1; sidx < size; ++sidx) 
				if (arr[sidx] < arr[min])
					min = sidx;
			swap(arr[idx], arr[min]);
		}
		end = clock();
		print(arr,size);
	}

	/*
		������������ ������� ������ �� �迭�� �ؾ��� �ӵ�
	*/
	void insertion_sort(int* arr, int size) {
		begin = clock();
		for (idx = 1; idx < size; ++idx) {
			sidx = idx;
			while (sidx > 0 && (arr[sidx] < arr[sidx - 1])) {
				swap(arr[sidx], arr[sidx - 1]);
				--sidx;
			}
		}
		end = clock();
		print(arr, size);
	}
	/*
  h		����Ʈ������ �̹� ���ĵ� �迭�� ���ؼ��� n^2 �ð��̰ɸ��� ���ؿ����÷ο�� �ż��� ���赵 �ϰ�����
		��Ƽ�� �ϴ� �κ��� ���ԵǸ� ���ĵ� �迭������ �����ϰ� n! ���� Ž���ϰ� �������ع���...
		���������̶�� ���� Ȯ���� �����ϴ� ������.
	*/
	void do_quick_sort(int* arr, int size) {
		begin = clock();
		quick_sort(arr, 0, size - 1);
		end = clock();
		print(arr, size);
	}
	void quick_sort(int* arr, int l, int h) {
		if (h - l > 0) {
			int left = l;
			int right = h;
			while (left <= right) {
				while (arr[left] <= arr[l] && left < right) ++left;
				while (arr[right] > arr[l] && left <= right) --right;
				if (left < right)swap(arr[left], arr[right]);
				else break;
			}
			swap(arr[right], arr[l]);
			quick_sort(arr, l, right - 1);
			quick_sort(arr, right + 1, h);
		}
	}

	/*
		merge sort �ε� nlogn �ӵ��� ����Ǵµ�
		���ҿ� logn �ӵ� ��ġ�°� n���� ������
		�ٵ� ������ �����ٴ°� ������ �Ȱ�
		���� ��쿡���� swapȽ���� ���������־ �׷��Ͱ���...
	*/
	void merge(int* arr,int l,int h,int mid) {
		idx = 0;
		int left = l;
		int right = mid + 1;
		int *sub = new int[h - l + 1];

		while (left <= mid && right <= h)
			if (arr[left] < arr[right])	sub[idx++] = arr[left++];
			else sub[idx++] = arr[right++];
		while (left <= mid) sub[idx++] = arr[left++];
		while (right <= h) sub[idx++] = arr[right++];
		for (idx = l, sidx = 0; idx <= h;)arr[idx++] = sub[sidx++];
		delete sub;
	}
	void merge_sort(int* arr, int l, int h) {
		int mid = (l + h)/ 2;
		if (h - l <= 0)return;
		merge_sort(arr, l, mid);
		merge_sort(arr, mid + 1, h);
		merge(arr, l, h, mid);
	}

	/*
		Shell ����
		�������� �߸𸣰���
		���� �õ��� �����̶�µ� ���� 4�� for���� ��������
		�ð����⵵ ����� ��ƴ�
	*/
	void shell_sort(int* arr, int size) {
		begin = clock();
		int jump = size;
		while (jump > 1){
			jump = jump / 3 + 1;
			for (idx = 0; idx < jump; ++idx){
				for (sidx = idx; sidx < size; sidx = sidx + jump) {
					while (sidx > 0 && (arr[sidx] < arr[sidx - 1])) {
						swap(arr[sidx], arr[sidx - 1]);
						--sidx;
					}
				}
			}			
		}		
		end = clock();
		print(arr, size);
	}

	/*
		heap ����
		�켱����ť�� ��� �����ߴ��Ŀ����� �ӵ��� ���̸��̳�.
		�켱����ť �ڷᱸ�� Ư���� �迭1���� ����ϸ� �ǰ�, size_t ����ŭ�� �迭�� �������ִ�.
		�Է� �� ������ logn �ӵ��� ���´�. ��������Ʈ���� �� �ӵ��� �����
		�� �����Ҷ� nlogn �׸��� �̸� �ٽ� ������ nlogn �� �ð����⵵�� ���´�.
		�켱����ť ���̺귯���� ���� �� �����ϱ� ���� ���ù��.
		�Ʊ׷� �׳� stl sort�� ���ڱ���..
	*/
	void heap_sort(int* arr, int size) {
		begin = clock();
		Heap h;
		HeapNode* n;
		int i = 0;
		for (i = 0; i < size; ++i) {
			h.insert_heap(arr[i]);
		}
		i = 0;
		while ( (n = h.get_top()) != NULL) {
			arr[i++] = n->data;
			h.pop_heap();
		}
		end = clock();
		print(arr, size);
	}

	/*
		radix sort �������
		�̰� ����®�ٱ⺸�� ���� �貼��... ��Ű�� �ʹ��߳����־ �۶����� �����Ĺ���
		�ð����⵵ n �̶� �������� ������ ���̴� ����. �׷��� ���� ������ �ѿ����� ����.
		1���ڸ����� 10���ڸ�����(int ��� ������) �� �ڸ������ؼ� ���������� ������.
		�������� �̿��Ͽ� subArr �� �� �ڸ��� Ȯ�������ν� �񱳿��� �� ��ȯ�� �����ʴ´�.
		�����߿� �����ϱ� ���� ������ ������. �Ӹ��ӿ��߾ȱ׷���
	*/
	void radix_sort(int* arr, int size) {
		begin = clock();
		int* subArr = new int[size];
		int count[10];
		int n;
		int idx;
		for (int i = 0; i < 10; ++i) {
			for (int j = 0; j < 10; ++j) count[j] = 0;
			n = (int)pow(10, i);
			for (int j = 0; j < size; ++j) {
				idx = (arr[j] / n) % 10;
				count[idx]++;
			}
			for (int j = 1; j < 10; ++j) count[j] = count[j] + count[j - 1];//������
			for (int j = size - 1; j >= 0; --j, --count[idx]) {
				idx = (arr[j] / n) % 10;
				subArr[count[idx] - 1] = arr[j];
			}
			for (int j = 0; j < size; ++j)arr[j] = subArr[j];
		}
		end = clock();
		print(arr, size);
	}
};