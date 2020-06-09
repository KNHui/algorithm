#include <queue>
#include <vector>
#include <cstring>
#include <iostream>

using namespace std;

constexpr int MAX_N = 13 + 1;
constexpr int MAX_K = 10 + 1;
constexpr int MAX_D = 10 + 1;
constexpr int dy[4] = { 0, 0, -1, 1 };
constexpr int dx[4] = { 1, -1, 0, 0 };

int						N, K;
int						ans;
int						board[MAX_N][MAX_N];
bool					visit[MAX_K][MAX_N][MAX_N][MAX_D];
deque<pair<int, int> >	knight_idx_d[MAX_N][MAX_N];
vector<pair<int, int> >	knight_pos;

void 	print_board(void)
{
	string arrow[4] = { "→", "←", "↑", "↓" };

	cout << endl;
	cout << endl;
	cout << "Direction " << endl;
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
			cout << board[i][j] << ' ' << (knight_idx_d[i][j].empty() ? " " : arrow[knight_idx_d[i][j].front().second]) << '	';
		cout << endl;
	}
	cout << endl;
}

void 	print_board(int time)
{
	string arrow[4] = { "→", "←", "↑", "↓" };

	cout << endl;
	cout << "Time : " << time << endl;
	cout << "Direction " << endl;
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
			cout << board[i][j] << ' ' << (knight_idx_d[i][j].empty() ? " " : arrow[knight_idx_d[i][j].front().second]) << '	';
		cout << endl;
	}
	cout << endl;
}

// 0은 흰색, 1은 빨간색, 2는 파란색
// 1부터 순서대로 →, ←, ↑, ↓
void 	init(void)
{
	cin >> N >> K;
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			cin >> board[i][j];
	for (int i = 0; i < K; i++)
	{
		int y, x, d;

		cin >> y >> x >> d;
		knight_pos.push_back({ --y, --x });
		knight_idx_d[y][x].push_front({ i, --d });
	}
}

bool 	check_range(int y, int x)
{
	return y >= 0 && y < N && x >= 0 && x < N;
}

void 	set_tower(deque<pair<int, int> >& tower, int y, int x, int idx)
{
	for (int i = knight_idx_d[y][x].size() - 1; i >= 0; --i)
	{
		int back_idx = knight_idx_d[y][x].back().first;
		int back_d = knight_idx_d[y][x].back().second;

		tower.push_front({ back_idx, back_d });
		knight_idx_d[y][x].pop_back();
		if (back_idx == idx)
			return;
	}
}

bool 	is_end(void)
{
	int cnt[MAX_N][MAX_N];

	memset(cnt, 0, sizeof(cnt));
	for (size_t i = 0; i < knight_pos.size(); i++)
	{
		int y = knight_pos[i].first;
		int x = knight_pos[i].second;

		if (++cnt[y][x] >= 4)
			return true;
	}
	return false;
}

bool 	move(void)
{
	for (int i = 0; i < K; ++i)
	{
		int						y = knight_pos[i].first;
		int						x = knight_pos[i].second;
		deque<pair<int, int> >	tower;

		set_tower(tower, y, x, i);
		if (tower.empty())
			continue;
		int btm_d = tower.front().second;
		int ny = y + dy[btm_d];
		int nx = x + dx[btm_d];

		if (check_range(ny, nx) && board[ny][nx] != 2)
		{
			if (board[ny][nx] == 0)
			{
				while (!tower.empty())
				{
					int idx = tower.front().first;
					int d = tower.front().second;

					tower.pop_front();
					knight_pos[idx] = { ny, nx };
					knight_idx_d[ny][nx].push_back({ idx, d });
				}
			}
			else if (board[ny][nx] == 1)
			{
				while (!tower.empty())
				{
					int idx = tower.back().first;
					int d = tower.back().second;

					tower.pop_back();
					knight_pos[idx] = { ny, nx };
					knight_idx_d[ny][nx].push_back({ idx, d });
				}
			}
		}
		else
		{
			ny = y + dy[btm_d ^ 1];
			nx = x + dx[btm_d ^ 1];
			tower.front().second ^= 1;
			if (check_range(ny, nx) && board[ny][nx] != 2)
			{
				if (board[ny][nx] == 0)
				{
					while (!tower.empty())
					{
						int idx = tower.front().first;
						int d = tower.front().second;

						tower.pop_front();
						knight_pos[idx] = { ny, nx };
						knight_idx_d[ny][nx].push_back({ idx, d });
					}
				}
				else if (board[ny][nx] == 1)
				{
					while (!tower.empty())
					{
						int idx = tower.back().first;
						int d = tower.back().second;

						tower.pop_back();
						knight_pos[idx] = { ny, nx };
						knight_idx_d[ny][nx].push_back({ idx, d });
					}
				}
			}
			else
			{
				while (!tower.empty())
				{
					int idx = tower.front().first;
					int d = tower.front().second;

					tower.pop_front();
					knight_pos[idx] = { y, x };
					knight_idx_d[y][x].push_back({ idx, d });
				}
			}
		}
		if (is_end())
			return true;
	}
	return false;
}

bool 	is_done(void)
{
	bool ret = true;

	for (size_t i = 0; i < knight_pos.size() && ret; ++i)
	{
		int y = knight_pos[i].first;
		int x = knight_pos[i].second;
		int d = 0;

		for (size_t j = 0; j < knight_idx_d[y][x].size(); j++)
			if (i == knight_idx_d[y][x][j].first)
			{
				d = knight_idx_d[y][x][j].second;
				break;
			}
		ret &= visit[i][y][x][d];
		visit[i][y][x][d] = true;
	}
	return ret;
}

int 	solve(void)
{
	for (size_t time = 1; !is_done(); ++time)
	{
		if (move())
			return time;
	}
	return -1;
}

int 	main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	init();
	cout << solve();
	return 0;
}