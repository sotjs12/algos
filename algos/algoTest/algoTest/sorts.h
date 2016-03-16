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
		우선순위큐를 어떻게 구현했느냐에따라 속도가 차이많이남.
		우선순위큐 자료구조 특성상 배열1개만 사용하면 되고, size_t 개만큼의 배열을 담을수있다.
		입력 및 삭제에 logn 속도가 나온다. 완전이진트리라 저 속도가 보장됨
		힙 구성할때 nlogn 그리고 이를 다시 꺼낼때 nlogn 의 시간복잡도를 갖는다.
		우선순위큐 라이브러리를 쓰면 젤 구현하기 쉬운 소팅방법.
		아그럼 그냥 stl sort를 쓰겠구나..
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
		radix sort 기수정렬
		이건 내가짰다기보단 거의 배꼈음... 위키에 너무잘나와있어서 멍때리고 보고쳐버림
		시간복잡도 n 이란 매지컬한 성능을 보이는 정렬. 그러나 양의 정수에 한에서만 가능.
		1의자리부터 10의자리까지(int 라고 가정함) 각 자리에대해서 작은순서로 나열함.
		누적합을 이용하여 subArr 에 들어갈 자리를 확보함으로써 비교연산 및 교환을 하지않는다.
		소팅중에 이해하기 가장 난해한 소팅임. 머리속에잘안그려짐
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
			for (int j = 1; j < 10; ++j) count[j] = count[j] + count[j - 1];//누적합
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