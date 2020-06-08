/*
	삼각형 위의 최대 경로
	https://www.algospot.com/judge/problem/read/TRIANGLEPATH

	모든 경로 중 포함된 숫자의 최대 합을 구해야 한다.

	"외발 뛰기" 문제처럼 "메모이제이션"을 사용했다.
	(https://github.com/KNHui/algorithm/blob/master/ALGOSPOT/JUMPGAME.cpp)
	함수 "int dfs(int y, int x)"는 좌표 "(y, x)"에서 출발하여 얻을 수 있는 숫자의 최대 합을 반환한다.
*/
#include <iostream>
#include <algorithm>

using namespace std;

constexpr int MAX_N = 100 + 1;

int n;
int map[MAX_N][MAX_N];
int cache[MAX_N][MAX_N];

void	init(void)
{
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		fill(cache[i], cache[i] + i + 1, -1);
		for (int j = 0; j <= i; ++j)
			cin >> map[i][j];
	}
}

bool	check_range(int y, int x)
{
	return y >= 0 && y < n && x >= 0 && x <= y + 1;
}

int		dfs(int y, int x)
{
	if (!check_range(y, x))
		return 0;
	if (cache[y][x] != -1)
		return cache[y][x];

	int se = dfs(y + 1, x);
	int s = dfs(y + 1, x + 1);
	return cache[y][x] = max(se, s) + map[y][x];
}

int		main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int C;

	cin >> C;
	for (int tcn = 1; tcn <= C; ++tcn)
	{
		init();
		cout << dfs(0, 0) << '\n';
	}
	return 0;
}
