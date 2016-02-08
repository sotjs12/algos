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
		for (idx = 0; idx < 20; ++idx) 
			cout << arr[idx] << " ";
		cout << endl;
		cout << "수행시간 : " << (end - begin) << endl;
	}
	void swap(int &a,int &b) {
		temp = a;
		a = b;
		b = temp;
	}
	/*
		선택정렬 n-1 번의 스왑만 발생, 스왑수가 적고 우선순위 큐로 비교량을 줄일수있음
		이상적인 우선순위큐를 구현한다면 nlogn  속도
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
		삽입정렬으로 어느정도 정렬이 된 배열에 극악의 속도
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
		퀵소트이지만 이미 정렬된 배열에 대해서는 n^2 시간이걸리고 스텍오버플로우란 신선한 경험도 하게해줌
		파티션 하는 부분을 보게되면 정렬된 배열에대해 우직하게 n! 번씩 탐색하고 스왑을해버림...
		분할정복이라기 보단 확률에 의존하는 정렬임.
	*/
	void do_quick_sort(int* arr, int size) {
		begin = clock();
		quick_sort(arr, 0, size - 1);
		end = clock();
		print(arr, size);
	}
	void quick_sort(int* arr, int l, int h) {
		if (h - l > 0) {
			idx = l;
			sidx = h;
			while (1) {
				while (arr[++idx] < arr[l]);
				while (arr[--sidx] > arr[l]);
				if (idx >= sidx)break;
				swap(arr[idx], arr[sidx]);
			}
			swap(arr[sidx], arr[l]);
			quick_sort(arr, l, sidx - 1);
			quick_sort(arr, sidx + 1, h);
		}
	}
};