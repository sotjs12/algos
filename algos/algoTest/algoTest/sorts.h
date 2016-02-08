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
		����Ʈ������ �̹� ���ĵ� �迭�� ���ؼ��� n^2 �ð��̰ɸ��� ���ؿ����÷ο�� �ż��� ���赵 �ϰ�����
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