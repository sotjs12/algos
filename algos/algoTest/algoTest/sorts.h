#pragma once
#include <iostream>
#include <time.h>
using namespace std;

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
		int sidx2;
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
	*/
};