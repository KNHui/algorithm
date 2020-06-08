/*
	외발 뛰기
	https://www.algospot.com/judge/problem/read/JUMPGAME

	시작점에서 끝 점에 도달할 수 있는지 확인하는 문제다.

	"메모이제이션"을 사용해서 중복 연산을 피한다.
	"cache[y][x]"는 좌표 "(y, x)"에서 끝 점으로 갈 수 있는지 나타낸다.
	갈 수 있다면 1, 없다면 0, 아직 연산을 하지 않았다면 -1을 저장한다.

	"깊이 우선 탐색"을 하면서 'cache' 배열을 갱신한다.
	기저 사례는 범위를 벗어난 경우, 끝 점에 도착한 경우, 이미 탐색한 좌표인 경우로 처리했다.
	50 라인에서는 OR 연산을 사용해서 아랫쪽을 탐색했을 때 끝 점에 도달한 경우 오른쪽을 탐색하지 않는다.
*/
#include <iostream>

using namespace std;

constexpr int MAX_N = 100 + 1;

int n;
int map[MAX_N][MAX_N];
int cache[MAX_N][MAX_N];

void	init(void)
{
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cin >> map[i][j];
		fill(cache[i], cache[i] + n, -1);
	}
}

bool	check_range(int y, int x)
{
	return y >= 0 && y < n && x >= 0 && x < n;
}

int		dfs(int y, int x)
{
	if (!check_range(y, x))
		return cache[y][x] = 0;
	if (y == n - 1 && x == n - 1)
		return cache[y][x] = 1;
	if (cache[y][x] != -1)
		return cache[y][x];

	return cache[y][x] = dfs(y + map[y][x], x) || dfs(y, x + map[y][x]);
}

int		main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int c;

	cin >> c;
	for (int tcn = 1; tcn <= c; ++tcn)
	{
		init();
		cout << (dfs(0, 0) > 0 ? "YES" : "NO") << '\n';
	}
	return 0;
}