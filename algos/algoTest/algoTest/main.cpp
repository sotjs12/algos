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
#include "backjoon.h"
#include "waterBottle.h"

#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

vector<int> a[200002];

int main()
{
	priority_queue<int> pq;
	long long r = 0;
	int i, j, n;
	cin >> n;
	while (n--)
	{
		cin >> i >> j;
		a[i].push_back(j);
	}
	for (i = 200000; i; i--)
	{
		for (j = 0; j < a[i].size(); j++) {
			cout << a[i][j] << endl;
			pq.push(a[i][j]);
		}
		if (!pq.empty())
		{
			r += pq.top();
			pq.pop();
		}
	}
	printf("%lld", r);
}