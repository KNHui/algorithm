/*
	원판 돌리기
	https://www.acmicpc.net/problem/17822

	문제에서 제시하는 대로 원판을 돌린 후에 남은 수의 총합을 구하는 문제다.

	덱을 이용해서 원판의 회전을 구현했다.
	시계 방향 회전은 'back'을 'front'로, 반시계방향 회전은 'front'를 'back'으로 옮겼다.

	인접한 수를 찾을 때는 '너비 우선 탐색' 알고리즘으로 찾았다.
	"deque	board[y][x]"에서 좌표 "(y, x)"는 문제의 "(i, j)"와 같다.
	탐색 도중에 'x'가 '-1'이 된다면 'M - 1'로, 'M'이 된다면 '0'으로 수정하여 덱을 원형 큐처럼 탐색했다.

	인접한 수를 찾고 난 뒤에 남아있는 수가 1 이하라면, 더는 회전을 해도 변화가 없음으로 회전을 종료하고 답을 출력한다.
*/

#include <queue>
#include <vector>
#include <cstring>
#include <iostream>

using namespace std;

constexpr int MAX_NM = 50 + 1;
constexpr int dy[4] = { 1, 0, -1, 0 };
constexpr int dx[4] = { 0, 1, 0, -1 };

int			N, M, T;
int			total_sum;
int			total_cnt;
bool		visit[MAX_NM][MAX_NM];
deque<int>	board[MAX_NM];
vector<int> x, d, k;

void init()
{
	cin >> N >> M >> T;
	x.resize(T);
	d.resize(T);
	k.resize(T);
	for (int row = 0; row < N; ++row)
	{
		board[row].resize(M);
		for (int col = 0; col < M; ++col)
		{
			cin >> board[row][col];
			total_sum += board[row][col];
		}
	}
	total_cnt = N * M;
	for (int i = 0; i < T; ++i)
		cin >> x[i] >> d[i] >> k[i];
}

void rotate(int idx)
{
	if (d[idx])
	{
		for (int row = x[idx] - 1; row < N; row += x[idx])
		{
			for (int cnt = 0; cnt < k[idx]; ++cnt)
			{
				board[row].push_back(board[row].front());
				board[row].pop_front();
			}
		}
	}
	else
	{
		for (int row = x[idx] - 1; row < N; row += x[idx])
		{
			for (int cnt = 0; cnt < k[idx]; ++cnt)
			{
				board[row].push_front(board[row].back());
				board[row].pop_back();
			}
		}
	}

}

bool chech_range(int y)
{
	return y >= 0 && y < N;
}

void modify_x(int& x)
{
	if (x == M)
		x = 0;
	else if (x == -1)
		x = M - 1;
}

bool find_neighbor(int r, int c)
{
	if (visit[r][c])
		return false;
	bool		is_there = false;
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

			modify_x(nx);
			if (chech_range(ny) && !visit[ny][nx])
			{
				if (board[r][c] == board[ny][nx])
				{
					yq.push(ny);
					xq.push(nx);
					--total_cnt;
					total_sum -= board[r][c];
					visit[ny][nx] = true;
					board[ny][nx] = 0;
					is_there = true;
				}
			}
		}
	}
	if (is_there)
	{
		--total_cnt;
		total_sum -= board[r][c];
		board[r][c] = 0;
	}
	return is_there;
}

void solve()
{
	for (int idx = 0; idx < T; ++idx)
	{
		bool is_there = false;

		rotate(idx);
		memset(visit, false, sizeof(visit));
		for (int row = 0; row < N; ++row)
			for (int col = 0; col < M; ++col)
				if (board[row][col])
					is_there |= find_neighbor(row, col);
		if (total_cnt <= 1)
			return;
		if (!is_there)
		{
			int average = total_sum / total_cnt;
			int mod = total_sum % total_cnt;

			for (int row = 0; row < N; ++row)
				for (int col = 0; col < M; ++col)
				{
					if (!board[row][col])
						continue;
					if (board[row][col] > average)
					{
						--board[row][col];
						--total_sum;
					}
					else if (board[row][col] < average)
					{
						++board[row][col];
						++total_sum;
					}
					else if (mod > 0)
					{
						++board[row][col];
						++total_sum;
					}
				}
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	init();
	solve();
	cout << total_sum << '\n';
	return 0;
}