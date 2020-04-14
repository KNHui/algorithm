/*
	LCS
	https://www.acmicpc.net/problem/9251

	두 문자열이 주어질 때, "최장 공통 부분 수열(LCS)"의 길이를 구하는 문제다.

	문자열 'A', 'B'가 있을 때, "dp[a][b]"는 "A [0, a)와 B [0, b)의 LCS 길이"다.
	이중 반복문을 수행하면서 'A'의 문자와 'B'의 문자를 한 번씩 비교한다.
	1. "A[a - 1] == B[b - 1]"인 경우
		1) 두 글자가 같기 때문에 "이전 글자까지의 LCS + 1"을 "dp[a][b]"에 저장한다.
	1. "A[a - 1] != B[b - 1]"인 경우
		1) 두 글자가 다르기 때문에 "이전 글자까지의 LCS"를 "dp[a][b]"에 저장한다.
*/
#include <iostream>
#include <algorithm>

using namespace std;

constexpr int MAX_LEN = 1000 + 1;

int 	dp[MAX_LEN][MAX_LEN];
string	a, b;

int solve(void)
{
	for (size_t i = 1; i <= a.length(); ++i)
		for (size_t j = 1; j <= b.length(); ++j)
			if (a[i - 1] == b[j - 1])
				dp[i][j] = dp[i - 1][j - 1] + 1;
			else
				dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
	return dp[a.length()][b.length()];
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> a >> b;
	cout << solve();
	return 0;
}