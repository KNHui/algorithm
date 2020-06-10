#include <cstring>
#include <iostream>

using namespace std;

constexpr int MAX_N = 20 + 1;
constexpr int MAX_M = MAX_N * MAX_N;
constexpr int MAX_k = 1000 + 1;
constexpr int dy[4] = { -1, 1, 0, 0 };
constexpr int dx[4] = { 0, 0, -1, 1 };

int				N, M, k;
int				dead_cnt;
int				shark_d[MAX_M];
int				shark_priority[MAX_M][4][4];
pair<int, int>	shark_pos[MAX_M];
pair<int, int>	smell[MAX_N][MAX_N];

void	init(void)
{
	cin >> N >> M >> k;
	for (int row = 0; row < N; ++row)
		for (int col = 0; col < N; ++col)
		{
			cin >> smell[row][col].first;
			if (smell[row][col].first)
			{
				shark_pos[smell[row][col].first] = { row, col };
				smell[row][col].second = k;
			}
		}
	for (int idx = 1; idx <= M; ++idx)
	{
		cin >> shark_d[idx];
		--shark_d[idx];
	}
	for (int idx = 1; idx <= M; ++idx)
		for (int row = 0; row < 4; ++row)
			for (int col = 0; col < 4; ++col)
			{
				cin >> shark_priority[idx][row][col];
				--shark_priority[idx][row][col];
			}
}

void	decrease(void)
{
	for (int row = 0; row < N; ++row)
		for (int col = 0; col < N; ++col)
			if (smell[row][col].second > 0)
			{
				--smell[row][col].second;
				if (smell[row][col].second == 0)
					smell[row][col].first = 0;
			}
}

bool	check_range(int y, int x)
{
	return y >= 0 && y < N && x >= 0 && x < N;
}

void	move(void)
{
	for (int idx = 1; idx <= M; ++idx)
	{
		int		y = shark_pos[idx].first;
		int		x = shark_pos[idx].second;
		int&	d = shark_d[idx];
		bool	is_move = false;

		if (y == -1)
			continue;
		for (size_t col = 0; col < 4; col++)
		{
			int nd = shark_priority[idx][d][col];
			int ny = y + dy[nd];
			int nx = x + dx[nd];

			if (check_range(ny, nx) && smell[ny][nx].first == 0)
			{
				shark_pos[idx] = { ny, nx };
				d = nd;
				is_move = true;
				break;
			}
		}
		if (is_move)
			continue;
		for (size_t col = 0; col < 4; col++)
		{
			int nd = shark_priority[idx][d][col];
			int ny = y + dy[nd];
			int nx = x + dx[nd];

			if (check_range(ny, nx) && smell[ny][nx].first == idx)
			{
				shark_pos[idx] = { ny, nx };
				d = nd;
				break;
			}
		}
	}
}

void	dead(void)
{
	bool is_there[MAX_N][MAX_N];

	memset(is_there, false, sizeof(is_there));
	for (int idx = 1; idx <= M; ++idx)
	{
		int&	y = shark_pos[idx].first;
		int		x = shark_pos[idx].second;

		if (y == -1)
			continue;
		if (is_there[y][x])
		{
			y = -1;
			++dead_cnt;
		}
		else
		{
			is_there[y][x] = true;
			smell[y][x] = { idx, k };
		}
	}
}

int		solve(void)
{
	int time = 1;

	for (; time <= 1000 && dead_cnt < M - 1; ++time)
	{
		move();
		decrease();
		dead();
	}
	return dead_cnt == M - 1 ? time - 1 : -1;
}

int		main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	init();
	cout << solve() << '\n';
	return 0;
}