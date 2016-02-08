#include "WERTYU.h"
#include "doublets.h"
#include "eatMan.h"
#include "permutation.h"
#include "island.h"
#include "knightsTour.h"
#include "miro.h"
#include "Virus.h"
#include "sorts.h"

void main() {
	int size = 10000;
	int* arr = new int[size];
	for (int i = 0; i < size; i++) {
		arr[i] = rand();
	}
	sorts s;
	s.selection_sort(arr, size);
	s.insertion_sort(arr, size);
	for (int i = 0; i < size; i++) {
		arr[i] = rand();
	}
	s.do_quick_sort(arr, size);
}