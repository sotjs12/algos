#pragma once
#include <iostream>
#include <cstring>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
using namespace std;

double B[500];
double M[500][500];
double T[500][500];

string w[500];
string s[100][500];
class OCR
{
private:
	int m, q;
public:
	void run()
	{
		int i, j,k;
		char buf[100];
		cin >> m >> q;
		for ( i = 0; i < m; ++i)cin >> buf, w[i] = buf;
		for ( i = 0; i < m; ++i)cin >> B[i];
		for (i = 0; i < m; ++i)for (j = 0; j < m; ++j)cin >> T[i][j];
		for (i = 0; i < m; ++i)for (j = 0; j < m; ++j)cin >> M[i][j];
		for (i = 0; i < q; ++i)
		{
			cin >> k;
			for (j = 0; j < k; ++j)cin >> buf, s[i][j] = buf;
		}
	}
};
class PACKING
{
private:
	int n, c;
	int volume[100];
	int need[100];
	int mem[1001][100];
	string name[100];
	vector<int> idx;

	int pack(int capacity, int item)
	{
		if (item == n)return 0;
		int& ret = mem[capacity][item];
		if (ret != -1)return ret;
		ret = pack(capacity, item + 1);
		if (capacity >= volume[item])
			ret = max(ret, pack(capacity - volume[item], item + 1) + need[item]);
		return ret;
	}

	void reconstruct(int capacity, int item)
	{
		if (item == n)return;
		if (pack(capacity, item) == pack(capacity, item + 1)) 
			reconstruct(capacity, item + 1);
		else {
			idx.push_back(item);
			reconstruct(capacity - volume[item], item + 1);
		}
		
	}
public:
	void run()
	{
		int t;
		char buf[21];
		cin >> t;
		while (t--)
		{
			idx.clear();
			memset(mem, -1, sizeof(mem));
			cin >> n >> c;
			for (int i = 0; i < n; ++i)
			{
				cin >> buf;
				name[i] = buf;
				cin >> volume[i] >> need[i];
			}
			cout << pack(c, 0) << " ";
			reconstruct(c, 0);
			cout << idx.size() << endl;
			for (int i = 0; i < idx.size(); ++i)cout << name[idx[i]] << endl;
		}
	}
};
class NUMB3RS
{
private:
	double mem[51][101];
	int map[51][51];
	int adj[51] = { 0, };
	int n, d, p, q;
	double solve(int here,int days)
	{
		if (days == 0)return (here == p ? 1.0 : 0.0);
		double& ret = mem[here][days];
		if (ret > -0.5)return ret;
		ret = 0.0;
		for (int there = 0; there < n; ++there)
			if (map[here][there] == 1)
				ret += (solve(there, days - 1) / adj[there]);
		return ret;
	}
public:
	void run()
	{
		int t,t2;
		cin >> t;
		while (t--)
		{
			memset(adj, 0, sizeof(adj));
			cin >> n >> d >> p;
			for (int i = 0; i < n; ++i)for (int j = 0; j < n; ++j)
			{
				cin >> map[i][j];
				if (map[i][j] == 1)adj[i]++;
			}
			for (int i = 0; i < n; ++i)for (int j = 0; j <= d; ++j)mem[i][j] = -1;
			cin >> t2;
			for (int i = 0; i < t2; ++i)
			{
				cin >> q;
				cout.precision(8);
				cout << solve(q, d) << " ";
			}
			cout << endl;
		}
	}
};
class POLY
{
private:
	int mem[101][101], mod = 10000000;
	int poly(int n,int f)
	{
		int a;
		if (n == f)return 1;
		int& ret = mem[n][f];
		if (ret != -1)return ret;
		ret = 0;
		for (int s = 1; s <= n - f; ++s)
		{
			a = (s + f - 1);
			a *= poly(n - f, s);
			a %= mod;
			ret += a;
			ret %= mod;
		}
		return ret;
	}
public:
	void run()
	{
		int t,n;
		cin >> t;
		while (t--)
		{
			memset(mem, -1, sizeof(mem));
			cin >> n;
			int ret = 0;
			for (int i = 1; i <= n; ++i)
			{
				ret += poly(n, i);
				ret %= mod;
			}
			cout<< ret <<endl;
		}
	}
};
class SNAIL
{
private:
	double mem[101][201];
	int d,c;
	double climb(int day,int climed)
	{
		if (day == d)return climed >= c;
		double& ret = mem[day][climed];
		if (ret != -1)return ret;
		return ret = 0.25*climb(day + 1, climed + 1) + 0.75*climb(day + 1, climed + 2);
	}
public:
	void run()
	{
		int t;
		cin >> t;
		while (t--)
		{
			cin >> c >> d;
			for (int i = 0; i < d; ++i)for (int j = 0; j < c * 2 + 1; ++j)mem[i][j] = -1;
			cout.precision(8);
			cout << climb(0,0)<<endl;
		}
	}
};
class TILING2
{
private:
	int n;
	int mem[101];
	int solve(int w)
	{
		if (w <= 0)return 0;
		int& ret = mem[w];
		if (ret != -1)return ret;
		return ret = solve(w - 2)*mem[w-1] + solve(w-1);
	}
public:
	void run()
	{
		int t;
		cin >> t;
		while (t--)
		{
			memset(mem, -1, sizeof(mem));
			cin >> n;
			mem[1] = 1, mem[2] = 5;
			cout << solve(n) << endl;
		}
	}
};
class QUANTIZE
{
private:
	const int INF = 987654;
	int arr[101];
	int subSum[101];
	int mem[1001][11];
	int n, s;
	int calc_avr(int a,int b)
	{
		if (a == b)return 0;
		if (a == 0)
		{
			int m = (subSum[b]) / (b - a + 1);
			int ret = 0;
			for (int i = 0; i <= b; ++i)ret += (arr[i] - m)*(arr[i] - m);
			return ret;
		}
		int m = (subSum[a + b] - subSum[a - 1]) / (b - a + 1);
		int ret = 0;
		for (int i = a; i < a + b; ++i)ret += (arr[i] - m)*(arr[i] - m);
		return ret;
	}
	int solve(int start,int part)
	{
		if (start == n)return 0;
		if (part == 0)return INF;
		int& ret = mem[start][part];
		if (ret != -1)return ret;
		ret = INF;
		for (int i = 1; i + start <= n; ++i)
			ret = min(ret, calc_avr(start, start + i - 1) + solve(start + i, part - 1));//start 에서 i개까지 최소값 미분임
		return ret;
	}
public:
	void run()
	{
		int t,i;
		cin >> t;
		while (t--)
		{
			memset(subSum, 0, sizeof(subSum));
			memset(mem, -1, sizeof(mem));
			cin >> n >> s;
			for (i = 0; i < n; ++i)cin>>arr[i];
			sort(arr, arr + n);
			for (i = 1, subSum[0] = arr[0]; i < n; ++i)subSum[i] += subSum[i - 1];
			cout << solve(0, s) << endl;
		}
	}
};
class PI
{
private:
	int mem[10001];
	string arr;
	int get_level(int a,int b)
	{
		int ret = 0,size = b - a + 1,i,tmp;
		for ( i = 1; i < size; ++i)
			if (arr[a + i - 1] == arr[a + i])ret++;
		if (ret == size - 1)return 1;

		tmp = arr[a] - arr[a + 1];
		if(tmp == 1 || tmp == -1)
		for (ret=0,i = 1; i < size; ++i)
			if (arr[a + i - 1] - arr[a + i] == tmp)ret++;
		if (ret == size - 1)return 2;

		for (ret = 0, i = 0; i < size - 2; ++i)
			if (arr[a + i] == arr[a + i + 2])ret++;
		if (ret == size - 2)return 4;

		ret = arr[a] - arr[a + 1];
		for (i = 2; i < size; ++i)
			if (arr[a + i - 1] - arr[a + i] != ret)return 10;
		return 5;
	}
	int solve()
	{
		mem[3] = get_level(1, 3);
		mem[4] = get_level(1, 4);
		mem[5] = get_level(1, 5);
		for (int i = 6; i < arr.size(); ++i)
			for (int j = 3; j <= 5 && i - j >= 3; ++j)
				mem[i] = min(mem[i], mem[i - j] + get_level(i - j + 1, i));
		return mem[arr.size() - 1];
	}
public:
	void run()
	{
		vector<int> ret;
		int t;
		cin >> t;
		while (t--)
		{
			cin >> arr;
			arr = " " + arr;
			for (int i = 0; i < arr.size(); ++i)mem[i] = 400000;
			ret.push_back(solve());
		}
		for (int i = 0; i < ret.size(); ++i)
			cout << ret[i] << endl;
	}
};
class JLIS
{
private: 
	const long long NEGINF = numeric_limits<long long>::min();
	int mem[101][101];
	int arr1[101];
	int arr2[101];
	int n,m;
	int solve(int a,int b)
	{
		int& ret = mem[a + 1][b + 1];
		if (ret != -1)return ret;
		ret = 2;
		long long a1 = (a == -1 ? NEGINF : arr1[a]);
		long long b1 = (b == -1 ? NEGINF : arr2[b]);
		long long maxE = max(a1, b1);
		for (int i = a + 1; i < n; ++i)
			if ( maxE < arr1[i])ret = max(ret, solve(i, b) + 1);
		for (int i = b + 1; i < m; ++i)
			if ( maxE < arr2[i])ret = max(ret, solve(a, i) + 1);
		return ret;
	}
public:
	void run()
	{
		int t;
		cin >> t;
		while (t--)
		{
			memset(mem, -1, sizeof(mem));
			cin >> n >> m;
			for (int i = 0; i < n; ++i)cin >> arr1[i];
			for (int i = 0; i < m; ++i)cin >> arr2[i];
			cout << solve(-1, -1) - 2 << endl;
		}
	}
};
class LIS
{
private:
	int mem[501],n;
	vector<int> arr;
	int solve2(int idx)
	{
		int& ret = mem[idx+1];
		if (ret != -1) return ret;
		ret = 1;
		for (int i = idx + 1; i < n; ++i)
			if (idx == -1 || arr[idx] < arr[i])ret = max(ret, solve2(i) + 1);
		return ret;
	}
	int solve(const vector<int>& arr)
	{
		if (arr.empty())return 0;
		int ret = 0;
		for (int i = 0; i < arr.size(); ++i)
		{
			vector<int> tarr;
			for (int j = i + 1; j < arr.size(); ++j)
				if (arr[i] < arr[j])tarr.push_back(arr[j]);
			ret = max(ret, solve(tarr) + 1);
		}
		return ret;
	}
public:
	void run()
	{
		int t;
		cin >> t;
		while (t--)
		{
			memset(mem, -1, sizeof(mem));
			cin >> n;
			for (int i = 0, tmp; i < n; ++i)cin >> tmp, arr.push_back(tmp);
			cout<<solve2(-1)-1<<endl;
			arr.clear();
		}
	}
};
class TRIANGLEPATH
{
private:
	int n;
	int mem[101][101];
	int cnts[101][101];
	int map[101][101];
	int solve(int y,int x)
	{
		if (y == n - 1) {
			mem[y][x] = map[y][x];
			return map[y][x];
		}
		int& ret = mem[y][x];
		if (ret != -1)return ret;
		return ret = max( solve(y + 1, x), solve(y + 1, x + 1)) + map[y][x];
	}
	int cnt(int y, int x)
	{
		if (y == n - 1)return 1;
		int& ret = cnts[y][x];
		if (ret != -1)return ret;
		ret = 0;
		if (mem[y + 1][x] > mem[y + 1][x + 1])return ret += cnt(y + 1, x);
		else if (mem[y + 1][x] < mem[y + 1][x + 1])return ret += cnt(y + 1, x + 1);
		else return ret += cnt(y + 1, x + 1) + cnt(y + 1, x);
	}
public:
	void run()
	{
		int t;
		cin >> t;
		while (t--)
		{
			memset(mem, -1, sizeof(mem));
			memset(cnts, -1, sizeof(cnts));
			cin >> n;
			for (int i = 0; i < n; ++i)for (int j = 0; j <= i; ++j)cin >> map[i][j];
			solve(0, 0);
			cout << cnt(0,0) << endl;
		}
	}
};
class WILDCARD
{
private:
	vector<string> ret;
	int mem[101][101];
	int n;
	string p, w;
	int solve(const string& pt, const string& wd)
	{
		int pos = 0;
		while (pos < pt.size() && pos < wd.size() && (pt[pos] == '?' || wd[pos] == pt[pos]))++pos;
		if (pos == pt.size())return pos == wd.size();
		if (pt[pos] == '*')
			for (int i = 0; pos + i <= wd.size(); ++i)
				if (solve(pt.substr(pos + 1), wd.substr(pos + i)))return true;
		return false;
	}
	int solve2(int pt,int wd)
	{
		int& ret = mem[pt][wd];
		if (ret != -1)return ret;
		while (pt < p.size() && wd < w.size() && (p[pt] == '?' || w[wd] == p[pt]))++pt, ++wd;
		if (pt == p.size())return ret = (wd == w.size());
		if (p[pt] == '*')for (int i = 0; i + wd < w.size(); ++i)if (solve2(pt + 1, wd + i))return ret = 1;
		return ret = 0;
	}
	int solve3(int pt, int wd)
	{
		int& ret = mem[pt][wd];
		if (ret != -1)return ret;
		while (pt < p.size() && wd < w.size() && (p[pt] == '?' || w[wd] == p[pt]))return ret = solve3(pt + 1, wd + 1);
		if (pt == p.size())return ret = (wd == w.size());
		if (p[pt] == '*')if (solve3(pt + 1, wd) || (wd < w.size() && solve3(pt, wd + 1)))return ret = 1;
		return ret = 0;
	}
public:
	void run()
	{
		int t;
		cin >> t;
		while (t--)
		{
			cin >> p;
			cin >> n;
			for (int i = 0; i < n; ++i)
			{
				memset(mem, -1, sizeof(mem));
				cin >> w;
				if (solve3(0,0))ret.push_back(w);
			}
			sort(ret.begin(), ret.end());
			for (int i = 0; i < ret.size(); ++i)cout << ret[i] << endl;
			ret.clear();
		}
	}
};
class JUMPGAME
{
private:
	int n, map[100][100] = { {0,}, }, mem[100][100] = { { 0, }, };
	int solve(int y, int x)
	{
		if (y >= n || x >= n)return 0;
		if (y == n - 1 && x == n - 1)return 1;
		int& ret = mem[y][x];
		if (ret != -1)return ret;
		int jump = map[y][x];
		return ret = solve(y + jump, x) || solve(y, x + jump);
	}
public:
	void run()
	{
		int t;
		cin >> t;
		while (t--)
		{
			memset(mem, -1, sizeof(mem));
			cin >> n;
			for (int i = 0; i < n; ++i)for (int j = 0; j < n; ++j)cin >> map[i][j];
			if (solve(0, 0))cout << "YES" << endl;
			else cout << "NO" << endl;
		}
	}
};
class FENCE
{
private:
	vector<int> arr;
	int solve(int left, int right)
	{
		if (left == right)return arr[left];
		int mid = (left + right) / 2;
		int ret = max(solve(left, mid), solve(mid + 1, right));
		int lo = mid, hi = mid + 1;
		int height = min(arr[lo], arr[hi]);
		ret = max(ret, height * 2);
		while (lo > left || hi < right)
		{
			if (hi < right && (lo == left || arr[lo - 1] < arr[hi + 1]))++hi, height = min(arr[hi], height);
			else --lo, height = min(height, arr[lo]);
			ret = max(height*(hi - lo + 1), ret);
		}
		return ret;
	}
public:
	void run()
	{
		int t,n,tmp;
		cin >> t;
		while (t--)
		{
			cin >> n;
			for (int i = 0; i < n; ++i)cin >> tmp, arr.push_back(tmp);
			cout << solve(0,(int)arr.size()-1) << endl;
			arr.clear();
		}
	}
};
class QUADTREE
{
private:
	string solve(string::iterator &sin)
	{
		char h = *(sin++);
		if (h == 'w' || h == 'b')return string(1,h);
		string uleft = solve(sin);
		string uright = solve(sin);
		string lleft = solve(sin);
		string lright = solve(sin);
		return 'x' + lleft + lright + uleft + uright;
	}
public:
	void run()
	{
		int t;
		string sIn;
		cin >> t;
		while (t--)
		{
			cin >> sIn;
			auto it = sIn.begin();
			cout << solve(it).c_str()<<endl;
		}
	}
};
class CLOCKSYNC
{
private:
	vector<int> map[10];
	int arr[16] = { 0, };
	int tmpMap[100] = { 3,0,1,2,4,3,7,9,11,4,4,10,14,15,5,0,4,5,6,7,5,6,7,8,10,12,4,0,2,14,15,3,3,14,15,5,4,5,7,14,15,5,1,2,3,4,5,5,3,4,5,9,13 };
	
	bool check_align()
	{
		for (int i = 0; i < 16; ++i)
			if (arr[i] != 12)return false;
		return true;
	}
	int solve(int cnt)
	{
		if (cnt == 10)
		{
			if (check_align())return 0;
			return 100;
		}
		int ret = 100, i, j;
		for (i = 0; i < 4 ; ++i)
		{
			ret = min(ret, i + solve(cnt + 1));
			for (j = 0; j < map[cnt].size(); ++j)
			{
				arr[map[cnt][j]] += 3;
				if (arr[map[cnt][j]] == 15)arr[map[cnt][j]] = 3;
			}
		}
		return ret;
	}
public:
	void run()
	{
		int i = 0, j=0, cnt;
		for (i = 0,j=0; i < 10;++i)
		{
			cnt = tmpMap[j] + j;
			for (j=j+1; j <= cnt; ++j)map[i].push_back( tmpMap[j] );
		}
		cin >> cnt;
		while (cnt--)
		{
			for (i = 0; i < 16; ++i)cin >> arr[i];
			int ret = solve(0);
			if (ret == 100)cout << "-1" << endl;
			else cout << ret << endl;
		}

	}
};
class BOARDCOVER
{
private:
	int move[4][2][2] = { {{0,1},{1,0}},{ { 0,1 },{ 1,1 } },{ { 1,0 },{ 1,1 } },{ { 1,0 },{ 1,-1 } } };
	char map[20][20];
	int h, w;
	int solve()
	{
		int i, j, y = -1, x = -1, ret = 0;
		for (i = 0; i < h && y == -1; ++i)for (j = 0; j < w && y == -1; ++j)if (map[i][j] == '.') y = i, x = j;
		if (y == -1 && x == -1)return 1;
		for (i = 0; i < 4; ++i)
		{
			if (map[y + move[i][0][0]][x + move[i][0][1]] == '.' && map[y + move[i][1][0]][x + move[i][1][1]] == '.')
			{
				map[y][x] = map[y + move[i][0][0]][x + move[i][0][1]] = map[y + move[i][1][0]][x + move[i][1][1]] = '#';
				ret += solve();
				map[y][x] = map[y + move[i][0][0]][x + move[i][0][1]] = map[y + move[i][1][0]][x + move[i][1][1]] = '.';
			}
		}
		return ret;
	}
public:
	void run()
	{
		int t, cnt = 0,i,j;
		cin >> t;
		while (t--)
		{
			memset(map, ' ', sizeof(char)*20*20);
			cin >> h >> w;
			for (i = 0, cnt = 0; i < h; ++i)for (j = 0; j < w;++j)
			{
				cin >> map[i][j];
				if (map[i][j] == '.') cnt++;
			}
			if (cnt % 3 != 0)cout << 0 << endl;
			else cout << solve() << endl;
		}
	}
};
class PICNIC {
private:
	int n, m;
	bool map[10][10] = { {false,}, };
	bool check[10] = { false, };
	int solve()
	{
		int ret = 0, i = -1;	
		for (int j = 0; j < n; ++j)	if (!check[j])
		{
			i = j;
			break;
		}
		if (i == -1)return 1;
		for (int j = i + 1; j < n; ++j)
		{
			if (map[i][j] && !check[j])
			{
				check[i] = check[j] = true;
				ret += solve();
				check[i] = check[j] = false;
			}
		}
		return ret;
	}
public:
	void run()
	{
		int t,a,b;
		cin >> t;
		while (t--)
		{
			cin >> n >> m;
			for (int i = 0; i < m; ++i)	cin >> a >> b,	a > b ? map[b][a] = true:map[a][b] = true;
			cout << solve() <<endl;
			memset(map, 0, sizeof(bool) * 10 * 10);
			memset(check, 0, sizeof(bool) * 10);
		}
	}
};