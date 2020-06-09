#include <iostream>

using namespace std;

constexpr int MAX_N = 20 + 1;
constexpr int MAX_M = MAX_N * MAX_N;
constexpr int MAX_k = 1000 + 1;
constexpr int dy[4] = { -1, 1, 0, 0 };
constexpr int dx[4] = { 0, 0, -1, 1 };

int				N, M, k;
int				dead_cnt;
int				shark_d[MAX_M];											// 현재 방향
int				shark_priority[MAX_M][4][4];
pair<int, int>	shark_pos[MAX_M];
pair<int, int>	smell[MAX_N][MAX_N];									// 상어 인덱스, 남은 냄새

// 계속 같은 패턴 반복하는 경우 걸러줘야 하는데 아래와 같이 사용하면 제출할 때 메모리 초과
bool			visit1[MAX_M][MAX_N][MAX_N][4][MAX_N][MAX_N][MAX_k];	// 약 10억 개 배열
//					  상어idx	y	  x	    d  냄새y   냄새x 냄새

bool			visit2[MAX_M][MAX_N][MAX_N][4][MAX_k];					// 약 2천500만 개 배열
//						idx		y		x	 d	냄새

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
		cin >> shark_d[idx];
	for (int idx = 1; idx <= M; ++idx)
		for (int row = 0; row < 4; ++row)
			for (int col = 0; col < 4; ++col)
				cin >> shark_priority[idx][row][col];
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

// 1, 2, 3, 4는 각각 위, 아래, 왼쪽, 오른쪽
// 상어가 움직이지 못 하는 경우는 없음
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

// 원래는 idx 구간 [1, M]을 순회했다.
// 그리고 상어의 y, x, d에 따라 모든 맵의 냄새을 확인 했다. M * N * N
bool	is_done1(void)
{
	bool ret = true;

	for (int idx = 1; idx <= M; ++idx)
	{
		int		y = shark_pos[idx].first;
		int		x = shark_pos[idx].second;
		int		d = shark_d[idx];

		if (y == -1)
			continue;
		for (int row = 0; row < N; ++row)
			for (int col = 0; col < N; ++col)
			{
				int	remain = smell[row][col].second;

				if (!visit1[idx][y][x][d][row][col][remain])
				{
					ret = false;
					visit1[idx][row][col][d][remain] = true;
				}
			}
	}
	for (int row = 0; row < N; ++row)
		for (int col = 0; col < N; ++col)
		{
			int idx = smell[row][col].first;
			int	d = smell[row][col].second;
			int	remain = smell[row][col].second;

			if (row == -1)
				continue;
			if (!visit2[idx][row][col][d][remain])
			{
				ret = false;
				visit2[idx][row][col][d][remain] = true;
			}
		}
	return ret;
}

bool	is_done2(void)
{
	bool ret = true;

	for (int row = 0; row < N; ++row)
		for (int col = 0; col < N; ++col)
		{
			int idx = smell[row][col].first;
			int	d = smell[row][col].second;
			int	remain = smell[row][col].second;

			if (!visit2[idx][row][col][d][remain])
			{
				ret = false;
				visit2[idx][row][col][d][remain] = true;
			}
		}
	return ret;
}

int		solve(void)
{
	int time = 1;

	for (; time <= 1000 && dead_cnt < M - 1; ++time)
	{
		decrease();
		move();
		dead();
		// 어떻게 중복처리를 해야할까?
		//if (is_done())
		//	return -1;
	}
	return dead_cnt == M - 1 ? time : -1;
}

int		main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	init();
	cout << solve() << '\n';
	return 0;
}