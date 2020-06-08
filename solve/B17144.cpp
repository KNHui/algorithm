/*
	미세먼지 안녕!
	https://www.acmicpc.net/problem/17144

	미세먼지가 확산되고 공기 청정기가 작동할 때, 'T'초 후에 방에 남아있는 미세먼지 양을 구하는 문제다.

	공기청정기의 바람이 시계방향, 반 시계방향으로 순환한다.
	공기청정기에 들어오는 바람부터 나가는 바람까지 역순으로 처리했다.
	바람을 역순으로 처리하면, 다음 차례의 바람과 겹치는 구간을 신경쓰지 않아도 된다.
*/
#include <vector>
#include <cstring>
#include <iostream>

using namespace std;

constexpr int MAX = 50 + 1;
constexpr int dy[4] = { 1, 0, -1, 0 };
constexpr int dx[4] = { 0, 1, 0, -1 };

int R, C, T;
int map[MAX][MAX];
vector<pair<int, int> > cleaner;

void init()
{
	cin >> R >> C >> T;
	for (int i = 1; i <= R; ++i)
	{
		for (int j = 1; j <= C; ++j)
		{
			cin >> map[i][j];
			if (map[i][j] == -1)
				cleaner.push_back({ i, j });
		}
	}
}

bool check_bound(int y, int x)
{
	return (y >= 1 && y <= R && x >= 1 && x <= C);
}

void west_wind(pair<int, int> start, pair<int, int> end)
{
	int pre = map[start.first][start.second];

	for (int i = start.second; i + 1 <= end.second && map[start.first][i + 1] >= 0; ++i)
	{
		int tmp = map[start.first][i + 1];
		map[start.first][i + 1] = pre;
		pre = tmp;
	}
}

void east_wind(pair<int, int> start, pair<int, int> end)
{
	int pre = map[start.first][start.second];

	for (int i = start.second; i - 1 >= end.second && map[start.first][i - 1] >= 0; --i)
	{
		int tmp = map[start.first][i - 1];
		map[start.first][i - 1] = pre;
		pre = tmp;
	}
}

void north_wind(pair<int, int> start, pair<int, int> end)
{
	int pre = map[start.first][start.second];

	for (int i = start.first; i <= end.first && map[i + 1][start.second] >= 0; ++i)
	{
		int tmp = map[i + 1][start.second];
		map[i + 1][start.second] = pre;
		pre = tmp;
	}
}

void south_wind(pair<int, int> start, pair<int, int> end)
{
	int pre = map[start.first][start.second];

	for (int i = start.first; i >= end.first && map[i - 1][start.second] >= 0; --i)
	{
		int tmp = map[i - 1][start.second];
		map[i - 1][start.second] = pre;
		pre = tmp;
	}
}

void run_cleaner()
{
	north_wind({ 1, cleaner[0].second }, { cleaner[0].first - 1, cleaner[0].second });
	east_wind({ 1, C }, { 1, cleaner[0].second });
	south_wind({ cleaner[0].first, C }, { 1, C });
	west_wind({ cleaner[0].first, cleaner[0].second + 1 }, { cleaner[0].first, C });
	if (check_bound(cleaner[0].first, cleaner[0].second + 1))
		map[cleaner[0].first][cleaner[0].second + 1] = 0;

	south_wind({ R, cleaner[1].second }, { cleaner[1].first + 1, cleaner[1].second });
	east_wind({ R, C }, { R, cleaner[1].second });
	north_wind({ cleaner[1].first, C }, { R, C });
	west_wind({ cleaner[1].first, cleaner[1].second + 1 }, { cleaner[1].first, C });
	if (check_bound(cleaner[1].first, cleaner[1].second + 1))
		map[cleaner[1].first][cleaner[1].second + 1] = 0;
}

void spread_dust()
{
	int next_map[MAX][MAX] = { 0, };

	for (int r = 1; r <= R; ++r)
		for (int c = 1; c <= C; ++c)
			if (map[r][c] >= 5)
			{
				int cnt = 0;

				for (int i = 0; i < 4; i++)
				{
					int nr = r + dy[i];
					int nc = c + dx[i];

					if (check_bound(nr, nc) && map[nr][nc] >= 0)
					{
						next_map[nr][nc] += map[r][c] / 5;
						++cnt;
					}
				}
				next_map[r][c] += map[r][c] - cnt * (map[r][c] / 5);

			}
			else if (map[r][c] > 0)
				next_map[r][c] += map[r][c];
	memcpy(map, next_map, sizeof(next_map));
	map[cleaner[0].first][cleaner[0].second] = -1;
	map[cleaner[1].first][cleaner[1].second] = -1;
}

int solve()
{
	int total = 0;

	for (int i = 1; i <= T; ++i)
	{
		spread_dust();
		run_cleaner();
	}
	for (int i = 1; i <= R; ++i)
		for (int j = 1; j <= C; ++j)
			if (map[i][j] > 0)
				total += map[i][j];
	return total;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	init();
	cout << solve();
	return 0;
}