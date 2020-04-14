/*
	공통 부분 문자열
	https://www.acmicpc.net/problem/5582

	두 문자열이 주어질 때, '최장 공통 부분 문자열'의 길이를 구하는 문제다.

	'최장 공통 부분 수열(LCS)'과 달리 "최장 공통 부분 문자열"은 연속된 문자들이다.
	(https://github.com/KNHui/algorithm/blob/master/Baekjoon/B9251.cpp)
	그래서 문자가 다를 경우 '공통 부분 문자열'의 길이는 0이 된다.
*/
#include <iostream>
#include <algorithm>

using namespace std;

constexpr int MAX_LEN = 4000 + 1;

int		dp[MAX_LEN][MAX_LEN];
string	a, b;

int solve(void)
{
	int lcs = 0;

	for (size_t i = 1; i <= a.length(); ++i)
		for (size_t j = 1; j <= b.length(); ++j)
			if (a[i - 1] == b[j - 1])
			{
				dp[i][j] = dp[i - 1][j - 1] + 1;
				lcs = max(dp[i][j], lcs);
			}
	return lcs;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> a >> b;
	cout << solve();
	return 0;
}