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
	long long dp[1][1][1 << 1];// dp[i][n][ㄴ] = 현재 n번째수가 i 이고 사용한 숫자들의 상태가 s일때 모든 계단수의 개수
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
이녀석은 변형인데 DP 를 어떻게 정의했는지 잘 이해하고 있어야 풀수있다.
DP 의 dp[i][n] 은 만약 i 가 3이고 n 이 3이라면  333 ~ 999 까지의 경우의수이다
그래서  000~999 - 333-999 를 하면 000~299 까지의 답을 알아낼수있다.
이런식으로 코드를 작성하면 풀이완성
*/
class BOJ_10573
{
private:
	string s;
	long long dp[10][82];	// dp[i][n] = 현재 n자리수가 i일때  증가하는 수의 개수
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
	int dp[10][1001];	// dp[i][n] = 현재 n자리수가 i일때  줄어들지않는 수의 개수
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
	unsigned long long dp[10][65];	// dp[i][n] = 현재 n자리수가 i일때  줄어들지않는 수의 개수
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
	int dp[100][16][16];	// dp[i][a][b]  =  i번째 사람 이전까지 선택하거나 안했을때 백팀이 a 명남고 흑팀이 b명남았을때 얻을수있는 최고점
	//int dp[1001][16][16];	// dp[i][a][b]  =  i번째 사람 이전까지 선택하거나 안했을때 백팀이 a 명남고 흑팀이 b명남았을때 얻을수있는 최고점
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
계단을 3번연속 밟을수없다.
 dp[0][a] = 이전계단을 안밟음 , dp[1][a] = 이전계단을밟았음
 결국 이전계단을 안밟고 지금계단에 올라왔다면 그때는 1개든 2개든 밟을수있다
 하지만 이전계단을 밟았다면 2칸을 점프해서 현재자리로 와야한다.  
 끝
*/
class BOJ_2579
{
private:
	int n;
	int arr[301];
	int dp[2][301];	// dp[0][a] = 이전계단을 안밟음 , dp[1][a] = 이전계단을밟았음
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
세준이의 목표는 주어진 체력내에서 최대한의 기쁨을 느끼는 것이다. 세준이의 체력은 100이고, 기쁨은 0이다.
만약 세준이의 체력이 0이 되거나, 음수가 되면, 죽게되서 아무런 기쁨을 못 느낀 것이 된다. 세준이가 얻을 수 있는 최대 기쁨을 출력하는 프로그램을 작성하시오.

dp[a][b] = a까지 고르거나 안골랐을때 체력이 b 라면 얻을수있는 최대 행복도
꾀나 중요한 개념이 나온다 선택하거나 선택하지 않고 선택한경우와 아닌경우의 값을비교하여 큰값을 DP에 저장하는방식이다
이런 비스무리한 문제가 많으니 숙지해둬야겠다.
*/
class BOJ_1535
{
private:
	int n;
	int joys[21];
	int lifes[21];
	int dp[21][101];	//dp[i]= i 일때 얻을수있는 최대만족
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
종수는 손녀에게 한 조각을 꺼낸 날에는 W를, 반 조각을 꺼낸 날에는 H 보낸다. 손녀는 할아버지에게 받은 문자를 종이에 기록해 놓는다.
총 2N일이 지나면 길이가 2N인 문자열이 만들어지게 된다. 이 때, 가능한 서로 다른 문자열의 개수는 총 몇 개일까?

카탈랑수열이라는데 솔직히 뭔소린지몰라서 그냥 DP 로 풀어보았다 속도는 확실히 느림.
감사하게 30 이란 제약을주어서 타임아웃을 면했다.
한개짜리가 쪼개질경우 반개짜리가 하나생기므로 ret = solve(a - 1, b + 1) + solve(a, b - 1) 라는 점화식이 나왔다.
이때 dp[a][b] = 한개짜리가 a 개이고 반개짜리가 b 개일때 만들수있는 문자열의 총 수로 했음
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
// 기초라 설명없음 그냥 -1,-2,-3 했을때 다더하면되고 기저대역이 조금 헷갈림
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
	완전순열이란 놈이란다.
	순열 abc 가있을때 abc 같은 위치에 존재하지 않게 배열하는 방법이다.
	점화식은 총 n+2 명의 학생이 있다고 했을때.
	a_(n+2) = (n+1)*a_(n+1) + (n+1)*a_n 이다
	점화식을 알면쉽지만 모른다면 지옥의문제 
	운좋게 검색해서 알아냄 ㄱㅇㄷ
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
지도가 주어질 때 이와 같이 제일 왼쪽 위 지점에서 출발하여 제일 오른쪽 아래 지점까지 항상 내리막길로만 이동하는 경로의 개수를 구하는 프로그램을 작성하시오.

비교적 쉬운 DP 문제임
dp[i][j] = 0,0 에서 i,j 로 갈수있는 경로의수
재귀로 풀었는데 base_case 는 y,x 가 0,0 일때 1을반환해서 경로를 1씩축적함
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

45656이란 수를 보자.
이 수는 인접한 모든 자리수의 차이가 1이 난다. 이런 수를 계단 수라고 한다.
세준이는 수의 길이가 N인 계단 수가 몇 개 있는지 궁금해졌다.
N이 주어질 때, 길이가 N인 계단 수가 총 몇 개 있는지 구하는 프로그램을 작성하시오. (0으로 시작하는 수는 없다.)

DP[i][j] : j 로 끝나는 i 번째 계단 갯수
DP[i][j] = DP[i-1][j-1] + DP[i-1][j+1]; 
단 j 가 0,9 일때는 1개씩만되므로
DP[i][j] = DP[i-1][j-1] OR DP[i-1][j+1]; 이다.
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