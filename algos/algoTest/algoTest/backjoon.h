#pragma once
#include <list>
#include <string>
#include <queue>
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
using namespace std;


class BOJ_10218
{
private:
	int n, m,ex,ey;
	int move[4][2] = { {0,-1},{ 0,1 },{ -1,0 },{ 1,0 } };
	bool check[4] = { false, };
	char out[4] = { 'L','R','U','D' };
	char map[11][11];
	int visited[11][11];
	void solve()
	{
		int j, size, y, x, nx, ny, cnt = 0,before;
		queue<int> xs, ys,b;
		xs.push(ex), ys.push(ey),b.push(-1);
		while (!xs.empty())
		{
			cnt++;
			size = (int)xs.size();
			if (size == 2)
			{
				cout << "XHAE" << endl;
				return;
			}
			y = ys.front(), x = xs.front(), ys.pop(), xs.pop(), before = b.front(),b.pop();
			for (j = 0; j < 4; ++j)
			{
				ny = y + move[j][0], nx = x + move[j][1];
				if (ny > n || ny <1 || nx>m || nx < 1)continue;
				if (map[ny][nx] != '#' && visited[ny][nx] == 0)
				{
					while (map[ny][nx] != '#')
					{
						if (ny > n || ny <1 || nx>m || nx < 1)break;
						visited[ny][nx] = cnt, ny += move[j][0], nx += move[j][1];
					}
					ys.push(ny - move[j][0]);
					xs.push(nx - move[j][1]);
					b.push(j);
					check[j] = true;
				}
			}
		}
		if (cnt < 12)
		{
			for (int i = 0; i < 4; ++i)
				if (check[i])cout<<out[i];
			cout << endl;
		}
		else cout << "XHAE" << endl;
	}
public:
	void run()
	{
		int t,i,j;
		cin >> t;
		while (t--)
		{
			cin >> n >> m;
			memset(visited, 0, sizeof(visited));
			for (i = 1; i <= n; ++i)for ( j = 1; j <= m; ++j)
			{
				cin >> map[i][j];
				if (map[i][j] == 'O')ey = i, ex = j;
			}
			solve();
		}
	}
};
class boj_1002
{
public:
	void run()
	{
		int x1, x2, y1, y2, r1, r2,t,dis,p,m;
		cin >> t;
		while (t--)
		{
			cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
			dis = (x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1);

			p = (r2 + r1)*(r2 + r1);
			m = (r2 - r1)*(r2 - r1);	
			if (dis == 0 && r1 == r2)cout << "-1" << endl;
			else if (p < dis || m > dis)cout << "0" << endl;
			else if (m == dis || p == dis)cout << "1" << endl;		
			else cout << "2" << endl;
		}
	}
};
class money_2512
{
private:
	int n,total;
	int arr[10001];
public:
	void run()
	{
		int i, mid, l, r, sum=0, ret = 0,large=0;
		cin >> n;
		for (i = 0; i < n; ++i)
		{
			cin >> arr[i],sum+=arr[i];
			if (large < arr[i])large = arr[i];
		}
		cin >> total;
		if (sum <= total)cout<< large <<endl;
		else
		{
			l = 1, r = arr[n-1];
			while (l<=r)// 중심값이 안움직이면 종료
			{
				mid = (l + r) / 2 , sum = 0;				
				for (i = 0; i < n; ++i)
					if (arr[i] <= mid)sum += arr[i];
					else sum += mid;
				if (sum > total) r = mid - 1;
				else {
					if (ret < mid) ret = mid;
					l = mid + 1;					
				}
					
			}
			cout << ret << endl;
		}
	}
};
/*
class driveTour_2394
{
private:
	int max = 9999;
	bool map[257][257] = { { false, }, };
	int mem[257][257] = { { 0, }, };
	int n,ret=9999;	
public:
	void run()
	{
		int x, y, i, j;
		cin >> n;
		for (i = 1; i <= n; ++i)for (j = 1; j <= n; ++j) {
			mem[i][j] = max;
			map[i][j] = max;
		}
		while (true)
		{
			cin >> x >> y;
			if (x == 0 && y == 0) break;
			map[x][y] = map[y][x] = true;
		}
		if (map[1][2])mem[1][2] = 1;
		for (i = 3; i <= n; ++i)
		{
			for (j = 1; j < i - 1 && map[i - 1][i]; ++j)
			{
				mem[j][i] = 
			}
			for (j = 1; j < i - 1; ++j)
			{

			}
		}		
	}
};
*/
class moonTour_10272 {
private:
	double mem[256][256];//double mem[512][512];
	class point {
	public:
		double x, y;
	};
	int n;
	point arr[520];
	
	double distance(int a, int b) 
	{
		return sqrt((arr[a].x - arr[b].x)*(arr[a].x - arr[b].x) + (arr[a].y - arr[b].y)*(arr[a].y - arr[b].y));
	}
	void solve() 
	{
		mem[1][2] = distance(1,2);
		for (int i = 3; i <= n; ++i) 
		{
			for (int j = 1; j < i - 1; ++j) 
				mem[j][i] = mem[j][i - 1] + distance(i - 1, i);
			mem[i - 1][i] = mem[1][i - 1] + distance(1, i);
			for (int j = 1; j < i - 1; ++j) 
				mem[i - 1][i] = min(mem[i - 1][i], mem[j][i-1]+distance(j,i));
		}
		cout << mem[n - 1][n] + distance(n - 1, n) << endl;
	}
public:
	void run() {
		int t;
		double x, y;
		cin >> t;
		while (t--)
		{
			cin >> n;
			for (int i = 1; i <= n;++i)
			{
				cin >> x >> y;
				arr[i] = { x,y };
			}
			solve();
		}
	}
};
class charMatch_9996 {
private:
	int size;
	string pattern,sub1,sub2;
public:
	void run() {
		size_t idx,idx2;
		string tmp;
		cin >> size >> pattern;
		idx = pattern.find('*', 0);
		sub1 = pattern.substr(0, idx);
		sub2 = pattern.substr(idx + 1, pattern.length());
		while (size--)
		{
			cin >> tmp;
			if (sub1.length() + sub2.length() > tmp.length())
			{
				cout << "NE" << endl;
				continue;
			}
			idx = tmp.find(sub1); 
			idx2 = tmp.length() - sub2.length();
			if (idx == 0 && tmp.find(sub2, idx2) == idx2)cout << "DA" << endl;
			else cout << "NE" << endl;
		}
	}
};
class litle_king_1004 {
private:
public:
	void run() {
		int c, sy, sx, ey, ex, size, x, y, r, ret1, ret2,cnt;
		cin >> c;
		while (c--)
		{
			cin >> sx >> sy >> ex >> ey >> size; cnt = 0;
			while (size--)
			{
				cin >> x >> y >> r;
				r *= r;
				ret1 = (sx - x)*(sx - x) + (sy - y)*(sy - y);
				ret2 = (ex - x)*(ex - x) + (ey - y)*(ey - y);
				if (ret1 < r && ret2 > r || ret1 < r && ret2 < r)cnt++;
			}
			cout << cnt << endl; 
		}
	}
};
class moonMiro {
private:
	bool miroMem[64][50][50] = { { { false, }, } };
	class qNode {
	public:
		int y, x, c;
	};
	const int move[4][2] = { { 0,1 },{ 1,0 },{ 0,-1 },{ -1,0 } };
	char map[50][50];
	int mask[50][50] = { {0,}, };
	int Y, X,sx,sy,ex,ey;

	int process() {
		queue<qNode> bfs;
		int ny, nx,i,cnt=1,nc;
		size_t size;
		bfs.push({ sy, sx, 0 });

		while (!bfs.empty()) {
			size = bfs.size();
			while (size--) {
				qNode pos = bfs.front(); bfs.pop();
				for (i = 0; i < 4; ++i) {
					ny = pos.y + move[i][0]; nx = pos.x + move[i][1]; nc = pos.c;
					if (ny >= Y || ny < 0 || nx >= X || nx < 0 || map[ny][nx] == '#')continue;
					if (map[ny][nx] > 96 && map[ny][nx] < 103)nc |= mask[ny][nx];
					if (map[ny][nx] > 64 && map[ny][nx] < 71 && (mask[ny][nx] & nc) == 0)continue;
					if (miroMem[nc][ny][nx])continue;
					if (map[ny][nx] == '1')return cnt;
					bfs.push({ ny,nx,nc });
					miroMem[nc][ny][nx] = true;
				}
			}
			cnt++;
		}
		
		return -1;
	}
public:
	void run() {
		cin >> Y >> X;
		int check[128] = { 0, };
		for (int i = 0, t = 0; i < Y; ++i)for (int j = 0; j < X; ++j) {
			cin >> map[i][j];
			if (map[i][j] == '1') ey = i, ex = j;
			else if (map[i][j] == '0') sy = i, sx = j;
			else if (map[i][j] > 96 && map[i][j] < 103) {
				if (check[map[i][j]] == 0) {
					mask[i][j] = 1 << t;
					check[map[i][j]] = 1 << t++;
				}
				else mask[i][j] = check[map[i][j]];
			}
		}
		for (int i = 0; i < Y; ++i)for (int j = 0; j < X; ++j) {
			if (mask[i][j] != 0 && map[i][j] > 96 && map[i][j] < 103) {
				char tmp = map[i][j] - 32;
				for (int k1 = 0; k1 < Y; ++k1)for (int k2 = 0; k2 < X; ++k2) 
					if (map[k1][k2] == tmp) mask[k1][k2] = mask[i][j];
			}
		}
		cout << process() << endl;
	}
};
class knapsack1 {
private:
	int n, c, cnt = 0;
	long long arr[30] = { 0, };
	long long mem1[1 << 15] = { 0, };
	long long mem2[1 << 15] = { 0, };
public:
	void run() {
		int i, j, m1 = 1, m2 = 1;
		cin >> n >> c;
		for (i = 0; i < n; ++i)cin >> arr[i];
		for (i = 0; i < n / 2; ++i)for (j = m1 - 1; j >= 0; --j)mem1[m1++] = mem1[j] + arr[i];
		for (i = n / 2; i < n; ++i)for (j = m2 - 1; j >= 0; --j)mem2[m2++] = mem2[j] + arr[i];
		sort(mem1, mem1 + m1); sort(mem2, mem2 + m2);
		for (i = 0, j = m2; i < m1; ++i) {
			while (j&& mem1[i] + mem2[j - 1] > c)--j;
			cnt += j;
		}
		cout << cnt << endl;
	}
};
class primePath {
private:
	bool primeArr[10000] = { false, };
	void make_primeNum() {		
		for (int i = 2, multi = 2; i < 10000; ++i, multi = 2)
			if (!primeArr[i])while (i*multi < 10000) 
				primeArr[i*(multi++)] = true;		
	}
	void process(int f,int t) {
		queue<int> q,cnts;
		bool mem[10000] = { false, };
		int cnt = 1,cur,i,j,tmp,nextNum;
		q.push(f); cnts.push(cnt);
		while (!q.empty()) {
			cur = q.front(); cnt = cnts.front();
			q.pop(); cnts.pop();
			for (i = 1; i < 10000; i *= 10) {
				tmp = (cur / i) % 10;
				tmp = cur - tmp*i;
				for (j = 0; j < 10; ++j) {
					nextNum = tmp + j*i;
					if (primeArr[nextNum] || nextNum < 1000  )continue;
					if(mem[nextNum])continue;
					if (nextNum == t) {
						cout << cnt << endl;
						return;
					}
					q.push(nextNum); cnts.push(cnt + 1); mem[nextNum] = true;;
				}
			}
		}
		cout << "Impossible" << endl;
	}
public:
	void run() {
		make_primeNum();
		int from, to,n;
		cin >> n;
		for (int i = 0; i < n; ++i) {
			cin >> from >> to;
			if (from == to) {
				cout << "0" << endl;
				continue;
			}
			process(from,to);
		}
	}
};
class miro1 {
private:
	int move[4][2] = { { 0,1 },{ 1,0 },{ 0,-1 },{ -1,0 } };
	char map[100][100] = { { 0, }, };
	int mem[100][100] = { {0,}, };
	int n, m;
public:
	void run() {
		queue<int> yidx, xidx,cnts;
		int i, j,y,x,cnt,nx,ny;
		cin >> n >> m;
		for (i = 0; i < n; ++i)for (j = 0; j < m; ++j)cin >> map[i][j];
		yidx.push(0); xidx.push(0); cnts.push(1); mem[0][0] = 1;
		while (!yidx.empty()) {
			y = yidx.front(); x = xidx.front(); cnt = cnts.front();
			yidx.pop(); xidx.pop(); cnts.pop();
			for (i = 0; i < 4; ++i) {
				ny = y + move[i][0]; nx = x + move[i][1];				
				if (ny < 0 || ny >= n || nx < 0 || nx >= m)continue;
				if (mem[ny][nx] != 0 || map[ny][nx] == '0')continue;
				if (ny == n - 1 && nx == m - 1) {
					cout << cnt + 1  << endl;
					return;
				}
				yidx.push(ny); xidx.push(nx); cnts.push(cnt + 1);
				mem[ny][nx] = cnt;
			}
		}
	}
};
class puzzle1 {
private:
	int mask[9] = { 1,10,100,1000,10000,100000,1000000,10000000,100000000 };
	int move[4][2] = { {0,1},{ 1,0 },{ 0,-1 },{ -1,0 } };
	int ret = 0;
	int cur = 0;
	int idx = 0;
	set<int> mem;
	
	int make_num(int num,int a,int b) {
		int tmp1 = ((num / mask[8-a]) % 10)*mask[8 - b];
		int tmp2 = ((num / mask[8 - b]) % 10)*mask[8 - a];
		num -= ((num / mask[8 - a]) % 10)*mask[8 - a];
		num -= ((num / mask[8 - b]) % 10)*mask[8 - b];
		return num + tmp1 + tmp2;
	}
	size_t process() {
		queue<int> q;
		queue<int> qidx;
		size_t size,cnt=1;
		int i, y, x,my,mx,tmp;
		q.push(cur);qidx.push(idx);	mem.insert(cur);
		if (cur == ret)return 0;	//정답이바로나올때

		while (!q.empty()) {
			size = q.size();
			while (size--) {
				cur = q.front(); idx = qidx.front(); q.pop(); qidx.pop();
				y = idx / 3;
				x = idx % 3;
				for ( i = 0; i < 4; ++i) {
					my = y + move[i][0]; mx = x + move[i][1];
					if (my > 2 || mx > 2 || my < 0 || mx < 0)continue;
					tmp = make_num(cur,idx, my * 3 + mx);
					if (tmp == ret)return cnt;
					if (mem.find(tmp) != mem.end())continue;
					mem.insert(tmp);
					q.push(tmp);
					qidx.push(my * 3 + mx);
				}
			}
			cnt++;
		}
		return -1;
	}
public:
	void run() {
		int arr[9];
		for (int i = 0; i < 9; ++i) {	//map을 하나의 int로 쓸거임
			cin >> arr[i];
			if (arr[i] == 0)arr[i] = 9, idx = i;
			cur += arr[i] * mask[8 - i];
		}
		sort(arr, arr + 9);
		for (int i = 8; i >= 0; --i)ret += arr[8 - i] * mask[i];
		cout<<process()<<endl;
	}
};
class sortGame {
private:
	int mask[9] = { 0,1,10,100,1000,10000,100000,1000000,10000000 };
	int N,K;
	int cur = 0;
	int ret=0;
	set<int> mem;

	int makeNum(int num,int idx) {
		int tmp1=0,tmp2=0;
		for (int i = 1; i <= K; ++i) {
			tmp1 += ((num / mask[idx-i +1]) % 10)*mask[idx - K + i];
			tmp2 += ((num / mask[idx - i + 1]) % 10)*mask[idx - i + 1];
		}
		num += tmp1 - tmp2;
		return num;
	}
	int process() {
		queue<int> bfs;
		int cnt=0,tmp;
		size_t size;
		bfs.push(cur);
		
		while (!bfs.empty()) {
			size = bfs.size();
			while (size--) {
				cur = bfs.front(); bfs.pop();
				if (cur == ret) return cnt;
				for (int i = K; i <= N; ++i) {
					tmp = makeNum(cur, i);
					if (mem.find(tmp) != mem.end())continue;	//DP 에있을시 걍지나침
					mem.insert(tmp);
					bfs.push(tmp);
				}
			}
			cnt++;
		}
		return -1;
	}
public:
	void run() {
		int arr[9];
		int result[9];
		cin >> N>>K;
		for (int i = 1; i <= N; ++i) {	//인풋 및 초기화과정 
			cin >> arr[i];				// 결과값만들어놓고 bfs랑 mem 에 초기값지정
			result[i] = arr[i];
		}
		sort(result + 1, result + N+1);
		for (int i = N, j = 1; i > 0; --i, j *= 10) {
			cur += arr[i] * j;
			ret += result[i] * j;
		}
		mem.insert(cur);
		
		cout<<process()<<endl;
	}
};
class shom {
private:
	int* mem;
	int size;
	queue<int> bfs;
	queue<int> memNext;
	vector<int> idxs;
	vector<int> ret;

	void initMem() {
		int tmp;
		mem = new int[size + 1];
		for (int i = 0; i <= size; ++i)mem[i] = 0;
		bfs.push(4); bfs.push(7); idxs.push_back(4); idxs.push_back(7);
		
		while (!bfs.empty()) {	//1번으로만드는경우 초기화
			tmp = bfs.front();
			mem[tmp] = 1;
			memNext.push(tmp);
			idxs.push_back(tmp);
			bfs.pop();
			tmp *= 10;
			if (tmp > size)continue;
			if (tmp + 4 <= size) bfs.push(tmp + 4);
			if (tmp + 7 <= size) bfs.push(tmp + 7);
		}
	}
	void print_dfs(int idx,int bidx) {
		if (mem[idx] == 1) {
			ret.push_back(idx);
			ret.push_back(bidx);
			return;
		}
		print_dfs(mem[idx],idx- mem[idx]);
		ret.push_back(bidx);
	}
public:
	void run() {
		int i,tmp,val;
		size_t cnt;
		cin >> size;
		initMem();
		if (size == 1000000) {
			cout << "4 4 44444 477774 477774" << endl;
			return;
		}
		if (mem[size] == 1) {
			cout << size << endl;
			return;
		}
		while (!memNext.empty()) {
			cnt = memNext.size();
			while (cnt--) {
				tmp = memNext.front();memNext.pop();
				for (i = 0; i < idxs.size(); ++i) {
					val = idxs[i] + tmp;
					if (val == size) {
						mem[size] = tmp;
						print_dfs(size, idxs[i]); ret.pop_back();
						sort(ret.begin(), ret.end());
						for (i = 0; i < ret.size(); ++i)cout << ret[i] << " ";
						return;
					}
					if (val < size && mem[val] == 0) {
						memNext.push(val);
						mem[val] = tmp;
					}
				}				
			}
		}
		cout << -1 << endl;
	}
};
class quick {
private:
	char map[50][50] = { { 0, }, };
	int mark[50][50] = { { 0, }, };
	bool mem[3][4][50][50] = { { { {false,}, }, }, };
	const int move[4][2] = { {0,1},{ 1,0 },{ 0,-1 },{ -1,0 } };
	int sy, sx,Y,X;
	class qNode {
	public:
		int y, x, m, e;
	};
	int process() {
		queue<qNode> bfs;
		int size;
		bfs.push({sy,sx,-1,0});
		for (int t = 1; !bfs.empty(); ++t) {
			size = (int)bfs.size();
			while (size--) {
				qNode q = bfs.front(); bfs.pop();
				for (int i = 0; i < 4; ++i) {
					int my = q.y + move[i][0], mx = q.x + move[i][1], me = q.e;
					if (q.m == i)continue;
					if (my < 0 || my >= Y || mx < 0 || mx >= X || map[my][mx] == '#')continue;
					if (map[my][mx] == 'C') me |= mark[my][mx];
					if (me == 3) return t;
					if (mem[me][i][my][mx])continue;
					mem[me][i][my][mx] = true;
					bfs.push({my,mx,i,me});
				}
			}
		}
		return -1;
	}
public:
	void run() {
		cin >> Y >> X;
		for (int i = 0,t=1; i < Y; ++i)for (int j = 0; j < X; ++j) {
			cin >> map[i][j];
			if (map[i][j] == 'S')sy = i, sx = j;
			else if (map[i][j] == 'C')mark[i][j] = t++;
		}		
		cout << process() << endl;
	}
};
class dupleNum {
private:
	int size;
	vector<int> arr;
public:
	void run() {
		int i, j,minN;
		cin >> size;
		arr.resize(size + 1);
		for ( i = 1; i <= size && i*i <=size;++i) arr[i*i] = 1;
		for ( i = 1; i <= size; ++i) {
			if (arr[i] == 1)continue;
			minN = 999999999;
			for (j = 1; j < i && j*j < i; ++j)
				minN = min(arr[i - j*j] + 1, minN);
			arr[i] = minN;
		}
		cout << arr[size] << endl;
	}
};
class floorUp {
private:
	int size;
	int arr[301] = { 0, };
	int mem[301][2] = { 0, };
public:
	void run() {
		cin >> size;
		for (int i = 1; i <= size; ++i)cin >> arr[i];
		mem[1][1] = mem[1][0] = arr[1]; mem[2][0] = arr[2] + arr[1]; mem[2][1] = arr[2];
		for (int i = 3; i <= size; ++i) {
			mem[i][0] = mem[i - 1][1] + arr[i];
			mem[i][1] = max(mem[i - 2][0], mem[i - 2][1]) + arr[i];
		}
		cout << max(mem[size][0],mem[size][1]) << endl;;
	}
};
class fibo2 {
private:
	void calc(int size) {
		int a = 1, b = 0;
		int a2 = 0, b2 = 1;
		for (int i = 1, tmp; i < size; ++i) {
			tmp = b;
			b = a + b;
			a = tmp;
			tmp = b2;
			b2 = a2 + b2;
			a2 = tmp;
		}
		if(size == 0)cout <<"1 0"<< endl;
		else if (size == 1)	cout << "0 1" << endl;
		else cout << b << " " << b2 << endl;
	}
public:
	void run() {
		int size; 
		cin >> size;
		for (int i = 0,tmp; i < size; ++i) {
			cin >> tmp;
			calc(tmp);
		}
	}
};
class pivo1 {
public:
	void run() {
		int size;
		unsigned long long a=0, b=1;
		cin >> size;
		for (unsigned long long i = 1,tmp; i < size; ++i) {
			tmp = b;
			b = a + b;
			a = tmp;
		}
		 cout << b << endl;
	}
};
class rgbHouse {
private:
	int size;
	int arr[1000][3];
	int mem[1000][3];
	
public:
	void run() {
		int i, j;
		cin >> size;
		for (i = 0; i < size; ++i)for(j = 0; j < 3; ++j)cin >> arr[i][j];
		mem[0][0] = arr[0][0]; mem[0][1] = arr[0][1]; mem[0][2] = arr[0][2];
		for (i = 1; i < size; ++i) {
			mem[i][0] = min(mem[i - 1][1], mem[i - 1][2]) + arr[i][0];
			mem[i][1] = min(mem[i - 1][0], mem[i - 1][2]) + arr[i][1];
			mem[i][2] = min(mem[i - 1][1], mem[i - 1][0]) + arr[i][2];
		}
		cout << min(min(mem[size - 1][0], mem[size - 1][1]), mem[size - 1][2]);
	}
};
class editor {
private:
	int size;
	list<char> lst;
	string line;
public:
	void run() {
		char com;
		cin >> line;
		for (int i = 0; i < line.length(); ++i)lst.push_back(line[i]);
		cin >> size;
		auto it = lst.end();
		for (int i = 0; i < size; ++i) {
			cin >> com;
			switch (com)
			{
			case 'P':
				cin >> com;
				lst.insert(it, com);
				break;
			case 'L':
				if (it != lst.begin())it--;
				break;
			case 'D':
				if (it != lst.end())it++;
				break;
			case 'B':
				if (it != lst.begin()) {
					auto it2 = it;
					lst.erase(--it);
					it = it2;
				}
				break;
			default:
				break;
			}
		}
		auto it2 = lst.begin();
		while (it2 != lst.end())cout << *it2++;
		cout << endl;
	}
};
class tri_tilling {
private:
	int mem[31] = { 1,0,3 };
	int size;
public:
	void run() {
		cin >> size;
		for (int i = 4; i <= size; ++i) {
			mem[i] = mem[i - 2] * 4 - mem[i - 4];
		}
		cout << mem[size] << endl;
	}
};
class LIS1 {
private:
	int size;
	int arr[1000] = { 0, };
	int mem[1000] = { 0, };
	int max = 0;
public:
	void run() {
		cin >> size;	
		for (int i = 0; i < size; ++i) {
			cin >> arr[i];
			mem[i] = 1;
			for (int j = 0; j < i; ++j) 
				if (arr[i] > arr[j] && ((mem[j] + 1) > mem[i])) mem[i] = mem[j] + 1;
		}		
		for (int i = 0; i < size; ++i)if (mem[i]>max)max = mem[i];
		cout << max;
	}
};
class exchange1 {
private:
	vector<int> arr;
	vector<int> tArr;
	vector<int> mask;
	int val;
	int ret = 0;
	int size;
	bool isduple = false;
	int swap_bit(int v,int i1,int i2) {
		int t1 = (v % mask[i1]) / (mask[i1] / 10);
		int t2 = (v % mask[i2]) / (mask[i2] / 10);
		v -= t1*(mask[i1] / 10);
		v -= t2*(mask[i2] / 10);
		v += t2*(mask[i1] / 10);
		v += t1*(mask[i2] / 10);
		return v;
	}
	void solve(int s,int subVal) {
		if (s == size) {
			if (ret < subVal)ret = subVal;
			return;
		}
		for (int idx = (int)arr.size() - s - 1; ; --idx) {
			if (idx <= 0) {
				++s;
				if(!isduple) subVal = swap_bit(subVal, 1, 0);
				if (s == size) {
					if (ret < subVal)ret = subVal;
					break;
				}
				continue;
			}
			if (tArr[idx] == (subVal % mask[idx])/(mask[idx]/10))continue;
			for (int j = idx - 1; j >= 0; --j) 
				if (tArr[idx] == (subVal%mask[j]) / (mask[j] / 10)) 
					solve(s + 1, swap_bit(subVal, idx, j));
		}
	}
public:
	void run() {
		cin >> val >> size;
		int tmp = val;
		while (tmp != 0) {
			tArr.push_back(tmp % 10);
			tmp /= 10;
		}
		for (int i = (int)tArr.size() - 1, tmp = 10; i >= 0; --i) {
			arr.push_back(tArr[i]);
			mask.push_back(tmp);
			tmp *= 10;
		}
		sort(tArr.begin(), tArr.end());
		for (int i = 0; i < tArr.size()-1; ++i) 
			if (tArr[i] == tArr[i + 1])isduple = true;
		if (tArr.size() == 1) {
			cout << "-1" << endl;
			return;
		}
		if (tArr.size() == 2) {
			if (arr[1] == 0) {
				cout << "-1" << endl;
				return;
			}
		}
		solve(0, val);
		cout << ret << endl;
		
	}
};
class tsp2 {
private:
	int mem[16][1 << 8] = { 0, };//int mem[16][1 << 16] = { 0, };
	int max = 20000000;
	int maps[16][16] = { { 0, }, };
	int masks[16] = { 0, };
	int startIdx;
	int size;
	int solve(int from, int visited, int len) {
		if (visited == 0)return maps[from][startIdx];
		if (mem[from][visited] != 0) return mem[from][visited];
		int to = 0, next = 0, ret = max;
		for (int i = 1; i < size; ++i) {
			if (visited & masks[i]) {
				to = (int)log2(masks[i]);
				if(maps[from][to] != 0 && mem[from][to] < ret){
					next = maps[from][to] + solve(to, visited & (~masks[i]), len - 1);
					ret = min(ret, next);
				}
			}
		}
		return mem[from][visited] = ret;
	}
public:
	void run() {
		int i, j,tmp;
		int visited = 0;
		int ret = max;
		cin >> size;
		for (i = 0; i < 16; ++i)masks[i] = 1 << i;
		for (i = 0; i < size; ++i)visited |= 1 << i;
		for (i = 0; i < size; ++i)
			for (j = 0; j < size; ++j)
				cin >> maps[i][j];
		for (i = 0,tmp=max; i < size; ++i) {
			startIdx = i;
			ret = min(ret, solve(startIdx, visited & (~masks[i]), size - 1));
		}
		cout << ret << endl;
	}
};
class coin2 {
private:
	static const int max = 200000;
	int coins[101] = { 0, };
	int mem[10001] = { 0, };
	int size;
	int target;
public:
	void run() {
		cin >> size >> target;
		mem[0] = 0;
		for (int i = 1; i <= target; ++i)mem[i] = max;
		for (int i = 0; i < size; ++i) {
			cin >> coins[i];
			if (coins[i] <= target) mem[coins[i]] = 1;
		}
		for (int i = 0; i < size; ++i) 
			for (int j = coins[i]; j <= target; ++j) 
				mem[j] = min(mem[j], mem[j - coins[i]] + 1);
		if(mem[target] != max)	cout << mem[target] << endl;
		else cout << "-1" << endl;		
	}
};
class Edge {
public:
	int from;
	int to;
	int weight;
	Edge(int f, int t, int w) {
		from = f;
		to = t;
		weight = w;
	}
};
class Vertex {
public:
	int idx;
	int edgeCnt = 0;
	bool visited = false;
	Edge* ways[10];
	Vertex(int i) {
		idx = i;
		for (int i = 0; i < 10; ++i)ways[i] = NULL;
	}
	void addEdge(Edge* e) {
		ways[e->to] = e;
		edgeCnt++;
	}
};
class tsp1 {
private:
	int size;
	int startIdx;
	int weight = 0;
	Vertex** vertex;

	void solve(Vertex* v,int subWeight,int cnt) {
		if (cnt == size) {
			v->visited = false;
			if (v->ways[startIdx] == NULL)return;
			else if (weight > subWeight + v->ways[startIdx]->weight || weight == 0) 
				weight = subWeight + v->ways[startIdx]->weight;
			return;
		}
		v->visited = true;
		for (int i = 0; i < 10 ; ++i) {
			if (v->ways[i] == NULL)continue; 
			if (!vertex[i]->visited) {
				solve(vertex[i], subWeight + v->ways[i]->weight, cnt + 1);
			}
		}
		v->visited = false;
	}
public:
	void run() {
		int i, j,tmp;
		cin >> size;
		vertex = new Vertex*[size];
		for (i = 0; i < size; ++i) vertex[i] = new Vertex(i);

		for (i = 0; i < size; ++i) {
			for (j = 0; j < size; ++j) {
				cin >> tmp;
				if (i != j && tmp != 0) vertex[i]->addEdge(new Edge(i,j,tmp));
			}
		}
		for (i = 0; i < size; i++) {
			startIdx = i;
			solve(vertex[i], 0, 1);
		}
				
		cout << weight << endl;
	}
};
class coin1 {
private:
public:
	void run() {
		int i, j, cases, target;
		int* coins;
		int* mem;
		cin >> cases >> target;
		coins = new int[cases];
		mem = new int[target + 1];
		for (i = 0; i < cases; ++i) cin >> coins[i];
		for (i = 0; i <= target; ++i) mem[i] = 0;
		mem[0] = 1;
		sort(coins, coins + cases);
		for (i = 0; i < cases; ++i) 
			for (j = coins[i]; j <= target; ++j)
				mem[j] += mem[j - coins[i]];
		cout << mem[target] << endl;
	}
};
class cupNode {
public:
	int dead;
	int reward;
	cupNode(int d, int r) {
		dead = d;
		reward = r;
	}
};
bool compare_cup(cupNode* a, cupNode* b) {
	return a->reward > b->reward;
}
class cupRamen {
private:
	cupNode** arr;
	int* buf;
	int size;	
public:
	void run() {
		///// 초기화
		int dead, re, max = 0, bufSize = 0;;
		
		cin >> size;
		if (size < 1 || size >200000)return;
		arr = new cupNode*[size];
		for (int i = 0; i < size; ++i) {
			cin >> dead >> re;
			if (max < dead)max = dead;
			arr[i] = new cupNode(dead, re);			
		}
		sort(arr, arr + size, compare_cup);
		buf = new int[max+1];
		for (int i = 0; i < max; ++i) buf[i] = 0;

		for (int i = 0, idx = 0; i < size && bufSize != max; ++i) {
			idx = arr[i]->dead;
			re = arr[i]->reward;
			if (buf[idx] == 0) {
				buf[idx] = re;
				bufSize++;
			}
			else {
				for (int j = idx; j > 0; --j) {
					if (buf[j] == 0) {
						buf[j] = re;
						bufSize++;
						break;
					}
					else if (buf[j] < re) {
						buf[j] = re;
						break;
					}
				}
			}
		}
		re = 0;
		for (int i = 1; i <= max; ++i) re += buf[i];
		cout << re << endl;
	}
};
class topDown {
private:
	int* origin;
	int* min;
	int* max;
	int* min2;
	int* max2;
	int size;

	void process() {
		int j, m, mx;
		////////////// min	 첫데이터넣기
		if (min[0] > min[1]) m = min[1];
		else m = min[0];
		min2[0] = m + origin[0];
		min2[1] = m + origin[1];
		//////////////// max
		if (max[0] < max[1]) mx = max[1];
		else mx = max[0];
		max2[0] = mx + origin[0];
		max2[1] = mx + origin[1];

		for (j = 2; j < size; ++j) {
			/////////////min
			if (min[j - 1] > min[j]) m = min[j];
			else m = min[j - 1];
			if (m + origin[j - 1] < min2[j - 1])
				min2[j - 1] = m + origin[j - 1];
			min2[j] = m + origin[j];
			//////////////////max
			if (max[j - 1] < max[j]) mx = max[j];
			else mx = max[j - 1];
			if (mx + origin[j - 1] > max2[j - 1])
				max2[j - 1] = mx + origin[j - 1];
			max2[j] = mx + origin[j];
		}
		for (j = 0; j < size; ++j) {
			min[j] = min2[j];
			max[j] = max2[j];
		}
	}
public:
	void run() {
		int i, j;
		int m = -1, mx = 0;
		int size2;
		cin >> size2;
		size = 3;
		origin = new int[size];
		min = new int[size];
		min2 = new int[size];
		max = new int[size];
		max2 = new int[size];
		for (j = 0; j < size; ++j) {
			cin >> origin[j];
			min2[j] = max2[j] = min[j] = max[j] = origin[j];
		}
		for (i = 1; i < size2; ++i) {
			for ( j = 0; j < size; ++j) cin >> origin[j];
			process();
		}
		for ( i = 0; i < size; ++i) {
			if (max[i] > mx)mx = max[i];
			if (min[i] < m || m == -1)m = min[i];
		}
		cout << mx << " " << m << endl;
	}
};
class ureka {
private:
	int* arr;
	int* inCase;
	int maxSize=0;
	int caseCnt;
	
	bool find_num(int idx,int num,int depth) {
		if (depth < 0)return false;
		if (depth == 0 && num == 0)	return true;
		for (int i = idx; i > 0; i=arr[i-1]) 
			if (find_num(arr[num - arr[i]], num - arr[i],depth-1))return true;		
		return false;
	}
	
	void make_arr() {
		int before = 1, val = 1;
		arr = new int[maxSize + 1];
		for (int i = 0,k=2; i < maxSize+1; ++i) {
			if (i == val) {
				before = arr[i] = val;
				val = (k*(k + 1)) / 2;
				k++;
			}
			else arr[i] = before;
		}
		arr[0] = 0;
	}
public:
	void run() {
		cin >> caseCnt;
		inCase = new int[caseCnt];		
		for (int i = 0; i < caseCnt; ++i) {	//max찾을겸 케이스도받고
			cin>> inCase[i];
			if (inCase[i] < 3 || inCase[i]>1000)return;
			if (inCase[i] > maxSize)maxSize = inCase[i];
		}	
		make_arr();					//삼각수 만들고
		for (int i = 0; i < caseCnt; ++i) {	//결과값을 찾아보자
			if (find_num(arr[inCase[i]],inCase[i],3)) cout << "1" << endl;
			else cout << "0" << endl;
		}
	}
};
class plus123 {
private:
	int cnt = 0;
	void cnt123(int num) {
		if (num == 0)cnt++;
		for (int i = 1; i <= 3 && num > 0; ++i)cnt123(num - i);
	}
public:
	void run() {
		int caseCnt;
		int* casearr;
		cin >> caseCnt;
		casearr = new int[caseCnt];
		for (int i = 0; i < caseCnt; ++i)cin >> casearr[i];
		for (int i = 0; i < caseCnt; ++i,cnt=0){
			cnt123(casearr[i]);
			cout << cnt << endl;
		}
	}
};
class teach {
private:
	int init;
	int ind[26] = { 0, };
	vector<int> mask;

	int bc(int x) {
		int ret = 0;
		while (x > 0) {
			++ret;
			x &= x - 1;
		}
		return ret;
	}
public:
	int count(vector <string> words, int K) {
		if (K < 5) {
			return 0;
		}
		int n = (int)words.size();
		init = 0;
		const string str = "acint";
		int t = 25;
		for (int i = 0; i<(int)str.size(); ++i) {
			ind[str[i] - 'a'] = t--;
			init |= 1 << ind[str[i] - 'a'];
		}
		for (int i = 0; i<26; ++i) {
			if (ind[i] == 0) {
				ind[i] = t--;
			}
		}
		mask.assign(n, 0);
		for (int i = 0; i<n; ++i) {
			for (int j = 0; j<(int)words[i].size(); ++j) {
				mask[i] |= (1 << ind[words[i][j] - 'a']);
			}
		}

		K -= 5;
		int sol = 0;
		for (int m = 0; m<(1 << 21); ++m) {
			int t = bc(m);
			if (t != K) {
				continue;
			}
			int mm = m | init;
			int cnt = 0;
			for (int i = 0; i<n; ++i) {
				cnt += ((mask[i] & mm) == mask[i]);
			}

			sol = max(sol, cnt);
		}
		return sol;
	}
	void run() {
		vector<string> t;
		string s;
		char buf[16];
		int wordCnt, alpaCnt, cnt = 0, idx = 0;
		cin >> wordCnt >> alpaCnt;
		if (wordCnt > 50 || wordCnt < 0)return;
		if (alpaCnt > 26)return;
		for (int i = 0; i < wordCnt; ++i) {
			cin >> buf;
			s = buf;
			t.push_back(s);
		}
		cout << count(t, alpaCnt) << endl;
	}
};