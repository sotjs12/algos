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
  h		퀵소트이지만 이미 정렬된 배열에 대해서는 n^2 시간이걸리고 스텍오버플로우란 신선한 경험도 하게해줌
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
		merge sort 인데 nlogn 속도가 보장되는듯
		분할에 logn 속도 합치는건 n으로 고정됨
		근데 퀵보다 느리다는게 납득이 안감
		퀵은 경우에따라서 swap횟수가 적어질수있어서 그런것같음...
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
		Shell 정렬
		빠른지는 잘모르겠음
		아주 올드한 정렬이라는데 무려 4중 for문이 돌고있음
		시간복잡도 계산이 어렵다
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
		heap 정렬
	*/
};