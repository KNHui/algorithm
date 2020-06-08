/*
	2×n 타일링
    https://www.acmicpc.net/problem/11726

	2×n 크기의 직사각형을 1×2, 2×1 타일로 채우는 방법의 수를 구해야 한다.

	2×n 크기의 직사각형을 채우는 방법은
	2×(n - 1) 크기의 직사각형에서 2×1 타일을 하나 놓는 방법과
	2×(n - 2) 크기의 직사각형에서 1×2 타일을 둘 놓는 방법이 있다.

	따라서, 2×(n - 1) 크기의 직사각형을 놓는 방법의 수와
	2×(n - 2) 크기의 직사각형을 놓는 방법의 수를 합치면,
	2×n 크기의 직사각형을 채우는 방법의 수를 알 수 있다.

	그래서 2×n 크기의 직사각형을 채우는 방법의 수를 dp[n]에 기록하고,
	다음과 같은 점화식을 만들어 반복문을 수행하면서 정답을 도출했다.
	dp[n] = (dp[n - 1] + dp[n - 2]) % 10007;
*/
#include <cstring>
#include <iostream>
using namespace std;

int n;
int dp[1003];

void init()
{
	cin >> n;
	memset(dp, 0, sizeof(dp));
}

void solve()
{
	dp[1] = 1;
	dp[2] = 2;

	for (int i = 3; i <= n; ++i)
    {
		dp[i] = (dp[i - 1] + dp[i - 2]) % 10007;
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	init(); 
	solve();
	cout << dp[n];

	return 0;
}