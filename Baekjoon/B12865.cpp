/*
	평범한 배낭
	https://www.acmicpc.net/problem/12865

	대표적인 knapsack 알고리즘 문제다.

	dp[i][j]는 i 번째 물건까지 무게 j만큼 넣었을 때의 최대 가치이다.
	집어넣으려는 현재 물건의 무게를 w, 가치를 v라고 하자.
	그때, 현재 물건을 넣지 않았을 때의 최댓값 "dp[i - 1][j]"와
	현재 물건을 넣었을 때의 최댓값 "dp[i - 1][j - w] + v" 중
	더 큰 값을 선택하여 dp[i][j]에 기록하면,
	dp[N][K]에는 배낭에 넣을 수 있는 물건들의 가치 합의 최댓값이 담긴다.
*/
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int N, K;
vector<int> W, V;

void input()
{
	cin >> N >> K;
	W.push_back(0);
	V.push_back(0);
	for (int i = 0; i < N; ++i)
	{
		int weight, value;
		cin >> weight >> value;
		W.push_back(weight);
		V.push_back(value);
	}
}

void solve()
{
	vector<vector<int>> dp(N + 1, vector<int>(K + 1, 0));

	for (int i = 1; i <= N; ++i)
	{
		for (int j = 0; j <= K; ++j)
		{
			if (W[i] <= j)
				dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - W[i]] + V[i]);
			else
				dp[i][j] = dp[i - 1][j];
		}
	}
	cout << dp[N][K];
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	input();
	solve();
	return 0;
}