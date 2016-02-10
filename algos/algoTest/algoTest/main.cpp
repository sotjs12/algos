#include "WERTYU.h"
#include "doublets.h"
#include "eatMan.h"
#include "permutation.h"
#include "island.h"
#include "knightsTour.h"
#include "miro.h"
#include "Virus.h"
#include "sorts.h"
#include "dataStructures.h"

void main() {
	/*
	sorts s;
	int arr[] = { 45, 39, 98, 15, 52, 44, 33, 28, 40, 38, 77, 68, 11, 43 };
	s.shell_sort(arr, 14);*/
	Heap h;
	h.insert_arrType(10);
	h.insert_arrType(1);
	h.insert_arrType(4);
	h.insert_arrType(2);
	h.insert_arrType(9);
	h.insert_arrType(7);
	h.insert_arrType(3);
	cout << h.get_top()->data << endl;
	h.pop_arrType();
	cout << h.get_top()->data << endl;
	h.pop_arrType();
	cout << h.get_top()->data << endl;
	h.pop_arrType();
	cout << h.get_top()->data << endl;
	h.pop_arrType();
	cout << h.get_top()->data << endl;
	h.pop_arrType();
	cout << h.get_top()->data << endl;
	h.pop_arrType();
	cout << h.get_top()->data << endl;
	h.pop_arrType();
}