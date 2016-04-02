#pragma once
#include <list>
#include <string>
#include <queue>
#include <vector>
#include <set>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

int dp[87654322];
class BOJ_1521
{
private:
	int arr[8];
	int mask[8] = { 1,10,100,1000,10000,100000,1000000,10000000 };
	int n,dest=0,cnt=0;

	void solve(int num)
	{
		if (num == dest)return;
		for (int i = 0; i < n; ++i)
		{
			
		}
	}
public:
	void run()
	{
		memset(dp, -1, sizeof(dp));
		cin >> n;
		int start = 0;
		for (int i = 0; i < n; ++i)cin >> arr[i], start += mask[n - i - 1] * arr[i];
		sort(arr, arr + n);
		for (int i = 0; i < n; ++i)dest += mask[n - i - 1] * arr[i];
		solve(start);
	}
};
class BOJ_1463
{
private:
	int n,ret=99999999;
	void solve(int n,int cnt)
	{
		if (n == 1) ret = min(ret, cnt);
		else
		{
			(n % 3) != 0 ? solve(n - 1, cnt + 1) : solve(n / 3, cnt + 1);
			if((n % 2) == 0) solve(n / 2, cnt + 1);
		}
	}
public:
	void run()
	{
		cin >> n;
		solve(n, 0);
		cout << ret << endl;
	}
};
class BOJ_1562
{
private:
	long long dp[1][1][1 << 1];// dp[i][n][��] = ���� n��°���� i �̰� ����� ���ڵ��� ���°� s�϶� ��� ��ܼ��� ����
//	long long dp[10][101][1 << 11];
	long long mod = 1000000000;
	int n,state = (1 << 10) - 1;
	long long solve(int idx, int len,int s)
	{
		if (idx > 9 || idx < 0)return 0;
		if (len == 1)return state == s;
		long long& ret = dp[idx][len][s];
		if (ret != -1)return ret;
		ret = solve(idx - 1, len - 1, s | (1 << (idx - 1))) + solve(idx + 1, len - 1, s | (1 << (idx + 1)));
		return ret% mod;
	}
public:
	void run()
	{
		memset(dp, -1, sizeof(dp));
		cin >> n;
		long long ret = 0;
		for (int i = 1; i < 10; ++i)ret += solve(i, n, 1 << i), ret %= mod;
		cout << ret << endl;

	}
};
/*
�̳༮�� �����ε� DP �� ��� �����ߴ��� �� �����ϰ� �־�� Ǯ���ִ�.
DP �� dp[i][n] �� ���� i �� 3�̰� n �� 3�̶��  333 ~ 999 ������ ����Ǽ��̴�
�׷���  000~999 - 333-999 �� �ϸ� 000~299 ������ ���� �˾Ƴ����ִ�.
�̷������� �ڵ带 �ۼ��ϸ� Ǯ�̿ϼ�
*/
class BOJ_10573
{
private:
	string s;
	long long dp[10][82];	// dp[i][n] = ���� n�ڸ����� i�϶�  �����ϴ� ���� ����
	long long  solve(int idx,int n)
	{
		if (n == 0)return 1;
		long long & ret = dp[idx][n];
		if (ret != -1)return ret;
		ret = 0;
		for (int i = 0; i <= idx; ++i)
			ret += solve(i, n - 1);
		return ret;
	}
public:
	void run()
	{
		memset(dp, -1, sizeof(dp));
		int t,n;
		solve(9, 81);
		cin >> t;
		while (t--)
		{
			cin >> s, n = (int)s.size();
			long long ret = dp[9][n ] - dp['9' - s[0]][n];
			for (int i = 1; i < n; ++i)
			{				
				if (s[i - 1] > s[i])
				{
					ret = -1;
					break;
				}
				ret += dp[9][n - i] - dp['9' - s[i] ][n - i] - (dp[9][n - i] - dp['9' - s[i-1]][n - i]);
			}
			cout << ret<< endl;
		}
	}
};
class BOJ_11057
{
private:
	int mod = 10007;
	int dp[10][1001];	// dp[i][n] = ���� n�ڸ����� i�϶�  �پ�����ʴ� ���� ����
	int solve(int idx, int n)
	{
		if (n == 0)return 1;
		int& ret = dp[idx][n];
		if (ret != -1)return ret;
		ret = 0;
		for (int i = 0; i <= idx; ++i)
			ret += solve(i, n - 1)%mod;
		return ret;
	}
public:
	void run()
	{
		memset(dp, -1, sizeof(dp));
		int n;
		cin >> n;
		cout << solve(9, n)%mod << endl;
	}
};
class BOJ_2688
{
private:
	unsigned long long dp[10][65];	// dp[i][n] = ���� n�ڸ����� i�϶�  �پ�����ʴ� ���� ����
	unsigned long long solve(int idx,int n)
	{
		if (n == 0)return 1;
		unsigned long long& ret = dp[idx][n];
		if (ret != -1)return ret;
		ret = 0;
		for (int i = 0; i <= idx; ++i)
			ret += solve(i, n - 1);
		return ret;
	}
public:
	void run()
	{
		memset(dp, -1, sizeof(dp));
		int t,n;
		cin >> t;
		while (t--)		
			cin >> n,cout<<solve(9,n)<<endl;
	}
};
class BOJ_1633
{
private:
	int dp[100][16][16];	// dp[i][a][b]  =  i��° ��� �������� �����ϰų� �������� ������ a ���� ������ b�������� �������ִ� �ְ���
	//int dp[1001][16][16];	// dp[i][a][b]  =  i��° ��� �������� �����ϰų� �������� ������ a ���� ������ b�������� �������ִ� �ְ���
	int n = 0;
	int arr[1001][2];
	int solve(int idx,int wcnt,int bcnt)
	{
		if ((wcnt == 0 && bcnt == 0) || idx >=n)return 0;
		int& ret = dp[idx][wcnt][bcnt];
		if (ret != -1)return ret;
		ret = solve(idx + 1, wcnt, bcnt);
		if (wcnt - 1 >= 0)	ret = max(ret,solve(idx + 1, wcnt - 1, bcnt) + arr[idx][0]);
		if (bcnt - 1 >= 0)	ret = max(ret,solve(idx + 1, wcnt, bcnt-1) + arr[idx][1]);
		return ret;
	}
public:
	void run()
	{
		memset(dp, -1, sizeof(dp));
		while (scanf_s("%d%d", &arr[n][0], &arr[n][1]) > 0)++n;
		cout << solve(0,15,15) << endl; 
	}
};
/*
����� 3������ ����������.
 dp[0][a] = ��������� �ȹ��� , dp[1][a] = ��������������
 �ᱹ ��������� �ȹ�� ���ݰ�ܿ� �ö�Դٸ� �׶��� 1���� 2���� �������ִ�
 ������ ��������� ��Ҵٸ� 2ĭ�� �����ؼ� �����ڸ��� �;��Ѵ�.  
 ��
*/
class BOJ_2579
{
private:
	int n;
	int arr[301];
	int dp[2][301];	// dp[0][a] = ��������� �ȹ��� , dp[1][a] = ��������������
	int solve(bool be,int idx)
	{
		if (idx < 0)return 0;
		int& ret = dp[be][idx];
		if (ret != -1)return ret;
		if (!be) ret = max(solve(1, idx - 1), solve(0, idx - 2)) + arr[idx];
		else ret = solve(0, idx - 2) + arr[idx];
		return ret;
	}
public:
	void run()
	{
		memset(dp, -1, sizeof(dp));
		cin >> n;
		for (int i = 1; i <= n; ++i)cin >> arr[i];
		cout << solve(0,n) << endl;
	}
};
/*
�������� ��ǥ�� �־��� ü�³����� �ִ����� ����� ������ ���̴�. �������� ü���� 100�̰�, ����� 0�̴�.
���� �������� ü���� 0�� �ǰų�, ������ �Ǹ�, �װԵǼ� �ƹ��� ����� �� ���� ���� �ȴ�. �����̰� ���� �� �ִ� �ִ� ����� ����ϴ� ���α׷��� �ۼ��Ͻÿ�.

dp[a][b] = a���� ���ų� �Ȱ������ ü���� b ��� �������ִ� �ִ� �ູ��
�ҳ� �߿��� ������ ���´� �����ϰų� �������� �ʰ� �����Ѱ��� �ƴѰ���� �������Ͽ� ū���� DP�� �����ϴ¹���̴�
�̷� �񽺹����� ������ ������ �����ص־߰ڴ�.
*/
class BOJ_1535
{
private:
	int n;
	int joys[21];
	int lifes[21];
	int dp[21][101];	//dp[i]= i �϶� �������ִ� �ִ븸��
	int solve(int life,int i)
	{
		if (i == n)return 0;
		int& ret = dp[i][life];
		if (ret != -1)return ret;
		if (life - lifes[i] > 0)ret = solve(life - lifes[i], i + 1) + joys[i];
		int tmp = solve(life, i + 1);
		if (tmp > ret) ret = tmp;
		return ret;
	}
public:
	void run()
	{
		memset(dp, -1, sizeof(dp));
		cin >> n;
		for (int i = 0; i < n; ++i)cin >> lifes[i];
		for (int i = 0; i < n; ++i)cin >> joys[i];
		cout << solve(100,0) << endl;
	}
};
/*
������ �ճ࿡�� �� ������ ���� ������ W��, �� ������ ���� ������ H ������. �ճ�� �Ҿƹ������� ���� ���ڸ� ���̿� ����� ���´�.
�� 2N���� ������ ���̰� 2N�� ���ڿ��� ��������� �ȴ�. �� ��, ������ ���� �ٸ� ���ڿ��� ������ �� �� ���ϱ�?

īŻ�������̶�µ� ������ ���Ҹ������� �׳� DP �� Ǯ��Ҵ� �ӵ��� Ȯ���� ����.
�����ϰ� 30 �̶� �������־ Ÿ�Ӿƿ��� ���ߴ�.
�Ѱ�¥���� �ɰ������ �ݰ�¥���� �ϳ�����Ƿ� ret = solve(a - 1, b + 1) + solve(a, b - 1) ��� ��ȭ���� ���Դ�.
�̶� dp[a][b] = �Ѱ�¥���� a ���̰� �ݰ�¥���� b ���϶� ������ִ� ���ڿ��� �� ���� ����
*/
class BOJ_4811
{
	long long dp[31][31];
private:
	long long solve(int a,int b)
	{
		if (a < 0 || b < 0)return 0;
		if (a == 0 && b == 0)return  1;
		long long& ret = dp[a][b];
		if (ret != -1)return ret;		
		return ret = solve(a - 1, b + 1) + solve(a, b - 1);
	}
public:
	void run()
	{
		int i, j, a;
		for ( i = 0; i < 31; ++i)for( j = 0; j < 31; ++j)dp[i][j] = -1;
		cin >> a;
		while (a != 0)
		{
			cout << solve(a,0) << endl;
			cin >> a;
		}
	}
};
// ���ʶ� ������� �׳� -1,-2,-3 ������ �ٴ��ϸ�ǰ� �����뿪�� ���� �򰥸�
class BOJ_9095
{
private:
	int dp[11];
	int solve(int a)
	{
		if (a < 0)return 0;
		if (a == 0)return 1;
		int& ret = dp[a];
		if (ret != -1)return ret;
		return ret = solve(a - 1) + solve(a - 2) + solve(a - 3);
	}
public:
	void run()
	{
		memset(dp, -1, sizeof(dp));
		int t,a;
		cin >> t;
		while (t--)
		{
			cin >> a;
			cout << solve(a) << endl;
		}
	}
};
class BOJ_1793
{
private:
	string arr[251] = { "1","1" , };
	string add_big(string a, string b)
	{
		int al = (int)a.length(), bl = (int)b.length(),cl,i,j;
		string c;
		al > bl ? c.resize(al + 1) : c.resize(bl + 1), cl = (int)c.length() - 1;
		for ( i = al - 1, j = bl - 1; i >= 0 && j >= 0 ; --i,--j,--cl)
		{
			if(c[cl] != 1) c[cl] = 0;
			c[cl] += a[i] + b[i] - '0';
			if (c[cl] > '9')c[cl - 1] = 1, c[cl] = c[cl] - 58 + '0';
		}
		while (i > 0)
		{
			c[cl] += a[i];
			if (c[cl] > '9')c[cl - 1] = 1, c[cl] = c[cl] - 58 + '0';
			--cl, --i;
		}
		while (j > 0)
		{
			c[cl] += b[j];
			if (c[cl] > '9')c[cl - 1] = 1, c[cl] = c[cl] - 58 + '0';
			--cl, --j;
		}
		if (c[0] == 1)c[0] = '1';
		else c.erase(0,1);
		return c;
	}
	string solve(int a)
	{
		if (a < 0)return "0";
		if (arr[a].length() != 0)return arr[a];
		return arr[a] = add_big(solve(a - 1), add_big(solve(a - 2), solve(a - 2)));
	}
public:
	void run()
	{
		int a;
		while (scanf_s("%d", &a)>0)
		{
			cout << solve(a) << endl;
		}
	}
};
class BOJ_2133
{
private:
	int arr[1001];
	int solve(int w)
	{
		if (w < 0 || w%2 == 1)return 0;
		int& ret = arr[w];
		if (ret != -1)return ret;
		ret = solve(w - 2) * 3;
		w -= 2;
		while (w > 0)w -= 2, ret += arr[w] * 2;
		return ret;
	}
public:
	void run()
	{
		int a;
		memset(arr, -1, sizeof(arr));
		arr[0] = 1; arr[1] = 0, arr[2] = 3;
		cin >> a;
		cout << solve(a) << endl;
	}
};
class BOJ_11727
{
private:
	int arr[1001];
	int mod = 10007;
	int solve(int w)
	{
		if (w < 0)return 0;
		int& ret = arr[w];
		if (ret != -1)return ret;
		return ret = (solve(w - 1) % mod + (2 * solve(w - 2)) % mod) % mod;
	}
public:
	void run()
	{
		int a;
		memset(arr, -1, sizeof(arr));
		arr[0] = arr[1] = 1;
		cin >> a;
		cout << solve(a) << endl;
	}
};
class BOJ_11726
{
private:
	int arr[1001];
	int mod = 10007;
	int solve(int w)
	{
		if (w < 0)return 0;
		int& ret = arr[w];
		if (ret != -1)return ret;
		return ret = (solve(w - 1)%mod + solve(w - 2)%mod)%mod;
	}
public:
	void run()
	{
		int a;
		memset(arr, -1, sizeof(arr));
		arr[0] = arr[1] = 1;
		cin >> a;
		cout << solve(a) << endl;
	}
};
class BOJ_9507
{
private:
	long long arr[68] = {1,1,2,4,8, };
public:
	void run()
	{
		int t;
		long long a;
		cin >> t;
		while (t--)
		{
			cin >> a;
			for (int i = 0; i <= a; ++i)
			{
				if (arr[i] != 0)continue;
				arr[i] = arr[i - 1] * 2 - arr[i - 5];
			}
			cout << arr[a] << endl;
		}
	}
};
class BOJ_1309
{
private:
public:
	void run()
	{
		int (*dp)[3];
		int n,mod = 9901;
		cin >> n;
		dp = new int[n][3];
		dp[0][0] = dp[0][1] = dp[0][2] = 1;
		for (int i = 1; i < n; ++i)
		{
			dp[i][0] = (dp[i - 1][1] + dp[i - 1][2] + dp[i - 1][0]) % mod;
			dp[i][1] = (dp[i - 1][0] + dp[i - 1][2]) % mod;
			dp[i][2] = (dp[i - 1][0] + dp[i - 1][1]) % mod;
		}
		cout << (dp[n - 1][0] + dp[n - 1][1] + dp[n - 1][2]) % mod << endl;
	}
};
/*
	���������̶� ���̶���.
	���� abc �������� abc ���� ��ġ�� �������� �ʰ� �迭�ϴ� ����̴�.
	��ȭ���� �� n+2 ���� �л��� �ִٰ� ������.
	a_(n+2) = (n+1)*a_(n+1) + (n+1)*a_n �̴�
	��ȭ���� �˸齱���� �𸥴ٸ� �����ǹ��� 
	������ �˻��ؼ� �˾Ƴ� ������
*/
class BOJ_1947
{
private:
	long long* dp;
public:
	void run()
	{
		long long n,mod = 1000000000;
		cin >> n;
		dp = new long long[n];
		dp[1] = 0, dp[2] = 1;
		for (int i = 3; i <= n; ++i)
			dp[i] = ( ((i - 1)*dp[i - 1])%mod + ((i - 1)*dp[i - 2])%mod)%mod;
		cout << dp[n] << endl;
	}
};
/*
class BOJ_1146
{
private:
	int dp[101][101] = { {0,}, };
	int n;
	int MOD = 1000000;
public:
	void run()
	{
		dp[1][1] = 1;
		cin >> n;
		int ret = 0,i,j,k;
		for (i = 2; i <= n; ++i)
			for (j = 1; j < i; ++j)
				for (k = j; k < i; ++k)
					dp[i][i - j + 1] = (dp[i][i - j + 1] + dp[i-1][k]) % MOD;
		cout << ret << endl;
	}
};
*/
class BOJ_9461
{
private:
	long long dp[101] = { 0,1,1,1,2, };
public:
	void run()
	{
		int t,n;
		cin >> t;
		while (t--)
		{
			cin >> n;
			for (int i = 4; i <= n; ++i)
			{
				if (dp[i] != 0)continue;
				else dp[i] = dp[i - 3] + dp[i - 2];
			}
			cout << dp[n] << endl;
		}
	}
};
/*
������ �־��� �� �̿� ���� ���� ���� �� �������� ����Ͽ� ���� ������ �Ʒ� �������� �׻� ��������θ� �̵��ϴ� ����� ������ ���ϴ� ���α׷��� �ۼ��Ͻÿ�.

���� ���� DP ������
dp[i][j] = 0,0 ���� i,j �� �����ִ� ����Ǽ�
��ͷ� Ǯ���µ� base_case �� y,x �� 0,0 �϶� 1����ȯ�ؼ� ��θ� 1��������
*/
class BOJ_1520
{
private:
	//int dp[500][500] = { { 0, }, };
	//int arr[500][500] = { { 0, }, }; 
	int dp[100][100] = { { 0, }, };
	int arr[100][100] = { { 0, }, };
	int move[4][2] = { {0,1},{1,0},{-1,0},{0,-1} };
	int n, m;
	int solve(int y, int x)
	{
		int ny, nx;
		if (x == 0 && y == 0)return 1;
		int& ret = dp[y][x];
		if (ret != -1)return ret;
		ret = 0;
		for (int i = 0; i < 4; ++i)
		{
			ny = y + move[i][0], nx = x + move[i][1];
			if (ny < 0 || nx < 0 || ny == n || nx == m)continue;
			if (arr[y][x] >= arr[ny][nx])continue;
			ret += solve(ny, nx);
		}
		return ret;
	}
public:
	void run()
	{
		memset(dp, -1, sizeof(dp));
		cin >> n >> m;
		for (int i = 0; i < n; ++i)for (int j = 0; j < m; ++j)cin >> arr[i][j];
		cout << solve(n - 1, m - 1) << endl;
	}
};
/*

45656�̶� ���� ����.
�� ���� ������ ��� �ڸ����� ���̰� 1�� ����. �̷� ���� ��� ����� �Ѵ�.
�����̴� ���� ���̰� N�� ��� ���� �� �� �ִ��� �ñ�������.
N�� �־��� ��, ���̰� N�� ��� ���� �� �� �� �ִ��� ���ϴ� ���α׷��� �ۼ��Ͻÿ�. (0���� �����ϴ� ���� ����.)

DP[i][j] : j �� ������ i ��° ��� ����
DP[i][j] = DP[i-1][j-1] + DP[i-1][j+1]; 
�� j �� 0,9 �϶��� 1�������ǹǷ�
DP[i][j] = DP[i-1][j-1] OR DP[i-1][j+1]; �̴�.
*/
class BOJ_10844
{
private:	
public:
	void run()
	{
		int dp[101][10] = { {0,},{0,1,1,1,1,1,1,1,1,1}, };
		int num,ret=0;
		long MOD = 1000000000;
		cin >> num;
		for (int i = 2; i <= num; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				if (j == 0)dp[i][j] = dp[i - 1][j + 1];
				else if (j == 9)dp[i][j] = dp[i - 1][j - 1];
				else dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j + 1])%MOD;
			}
		}
		for (int j = 0; j < 10; ++j)ret += dp[num][j],ret %= MOD;
		cout << ret << endl;

	}
};