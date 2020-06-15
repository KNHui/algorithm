/*
	캔디팡
	https://codeup.kr/problem.php?id=2605
*/

#include <queue>
#include <iostream>

using namespace std;

constexpr int MAX = 7;
constexpr int dy[4] = { 1, 0, -1, 0 };
constexpr int dx[4] = { 0, 1, 0, -1 };

int		board[MAX][MAX];
bool	visit[MAX][MAX];

void	input()
{
	for (int r = 0; r < MAX; ++r)
		for (int c = 0; c < MAX; ++c)
			cin >> board[r][c];
}

bool	check_range(int y, int x)
{
	return y >= 0 && y < MAX && x >= 0 && x < MAX;
}

bool	bfs(int r, int c)
{
	int			color = board[r][c];
	int			len = 1;
	queue<int>	yq, xq;

	yq.push(r);
	xq.push(c);
	visit[r][c] = true;
	while (!yq.empty())
	{
		int y = yq.front();
		int x = xq.front();

		yq.pop();
		xq.pop();
		for (int i = 0; i < 4; ++i)
		{
			int ny = y + dy[i];
			int nx = x + dx[i];

			if (check_range(ny, nx) && !visit[ny][nx] && board[ny][nx] == color)
			{
				++len;
				yq.push(ny);
				xq.push(nx);
				visit[ny][nx] = true;
			}
		}
	}
	return len >= 3;
}

int		solve()
{
	int cnt = 0;

	for (int r = 0; r < MAX; ++r)
		for (int c = 0; c < MAX; ++c)
			if (!visit[r][c] && bfs(r, c))
				++cnt;
	return cnt;
}

int		main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	input();
	cout << solve();
	return 0;
}