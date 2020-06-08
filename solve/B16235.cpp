/*
	나무 재테크
	https://www.acmicpc.net/problem/16235

	계절에 따라 발생하는 상황을 구현하는 시뮬레이션 문제다.

	'N'의 최대 크기가 10이다.
	그래서 나무를 "vector<int> tree[R][C]"에 저장하고, 모든 좌표를 탐색하면서 나무들을 처리했다.
	그리고 봄, 여름, 가을, 겨울이 순차적으로 일어나도록 구현했다.
	봄, 여름에는 다른 좌표에 영향을 주지 않으므로 한 좌표에서 봄을 처리하고 바로 여름을 처리했다.
*/
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

constexpr int MAX_N = 10 + 1;

int dr[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int dc[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

int			N, M, K;
int			map[MAX_N][MAX_N];
int			A[MAX_N][MAX_N];
vector<int> tree[MAX_N][MAX_N]; 

void	init(void)
{
	cin >> N >> M >> K;
	for (int i = 1; i <= N; ++i)
	{
		fill(map[i], map[i] + N + 1, 5);
		for (int j = 1; j <= N; ++j)
			cin >> A[i][j];
	}
	for (int i = 0; i < M; i++)
	{
		int r, c, age;
		cin >> r >> c >> age;
		tree[r][c].push_back(age);
	}
}

bool	check_ragne(int y, int x)
{
	return y >= 1 && y <= N && x >= 1 && x <= N;
}

void	spring_summer(void)
{
	for (int r = 1; r <= N; ++r)
		for (int c = 1; c <= N; ++c)
			if (!tree[r][c].empty())
			{
				int dead = 0;
				vector<int> tmp;
				sort(tree[r][c].begin(), tree[r][c].end());
				for (int i = 0; i < tree[r][c].size(); i++)
				{
					int age = tree[r][c][i];
					if (age <= map[r][c])
					{
						map[r][c] -= age;
						tmp.push_back(age + 1);
					}
					else
						dead += age / 2;
				}
				tree[r][c] = tmp;
				map[r][c] += dead;
			}
}

void	fall(void)
{
	for (int r = 1; r <= N; ++r)
		for (int c = 1; c <= N; ++c)
			if (!tree[r][c].empty())
				for (int i = 0; i < tree[r][c].size(); i++)
				{
					int age = tree[r][c][i];
					if (age % 5 == 0)
					{
						for (int i = 0; i < 8; i++)
						{
							int nr = r + dr[i];
							int nc = c + dc[i];
							if (check_ragne(nr, nc))
								tree[nr][nc].push_back(1);
						}
					}
				}
}

void	winter(void)
{
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= N; ++j)
			map[i][j] += A[i][j];
}

void	solve(void)
{
	for (int year = 1; year <= K; year++)
	{
		spring_summer();
		fall();
		winter();
	}
}

void	output(void)
{
	int total = 0;
	for (int r = 1; r <= N; ++r)
		for (int c = 1; c <= N; ++c)
			total += tree[r][c].size();
	cout << total << '\n';
}

int		main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	init();
	solve();
	output();
	return 0;
}