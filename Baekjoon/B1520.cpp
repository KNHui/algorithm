/*
	내리막 길
	https://www.acmicpc.net/problem/1520

	제일 왼쪽 위 지점에서 제일 오른쪽 아래 지점까지 항상 내리막길로만 이동하는 경로의 개수를 구하는 문제다.

	중복 연산을 처리하기 위해 "다이내믹 프로그래밍"을 사용했다.
	깊이 우선 탐색을 하면서 "int dp[row][col]"에 좌표 "(row, col)"에서 도착점까지 가는 경로의 수를 저장했다.
	'dp' 배열 원소들의 초깃값은 -1로 설정한다.
	깊이 우선 탐색 도중 'dp[row][col]'의 값이 -1이 아니라면 'dp[row][col]'의 값을 그대로 리턴한다.
*/
#include <iostream>

using namespace std;

constexpr int MAX = 500 + 1;
constexpr int dy[4] = { 1, 0, -1, 0 };
constexpr int dx[4] = { 0, 1, 0, -1 };

int M, N;
int map[MAX][MAX];
int dp[MAX][MAX];

void	init()
{
	cin >> M >> N;
	for (int i = 1; i <= M; ++i)
	{
		fill(dp[i] + 1, dp[i] + N + 1, -1);
		for (int j = 1; j <= N; ++j)
			cin >> map[i][j];
	}
}

bool	check_range(int row, int col)
{
	return row > 0 && row <= M && col > 0 && col <= N;
}

int		dfs(int row, int col)
{
	if (row == M && col == N)
		return 1;
	if (dp[row][col] != -1)
		return dp[row][col];

	int cnt = 0;

	for (int i = 0; i < 4; ++i)
	{
		int next_row = row + dy[i];
		int next_col = col + dx[i];

		if (check_range(next_row, next_col))
			if (map[next_row][next_col] < map[row][col])
				cnt += dfs(next_row, next_col);
	}
	return dp[row][col] = cnt;
}

int		main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	init();
	cout << dfs(1, 1) << '\n';
	return 0;
}