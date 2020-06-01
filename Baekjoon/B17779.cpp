/*
	게리맨더링 2
	https://www.acmicpc.net/problem/17779

	재현시를 5개의 구역으로 게리맨더링을 하는데, 인구가 가장 많은 선거구와 가장 적은 선거구의 인구 차이를 최소로 만드는 문제다.

	4중 반복문을 통해서 "(x, y), d1, d2"의 모든 경우의 수를 시행했다.

	모든 구역은 적어도 하나의 지역을 포함해야 한다.
	그래서 함수 "bool is_possible(int r, int c)"을 통해 모든 구역이 적어도 하나의 지역을 포함하는지 확인했다.

	게리맨더링은 먼저 5번 구역을 만들었다.
	그 후, 5번 구역의 테두리를 기준으로 나머지 외곽 구역을 넘버링 했다.

	게리맨더링이 끝나면 각 구역의 인구수를 구했다.
	이때, 넘버링이 안된 0번 구역은 5번 구역 내부이므로, 5번 구역과 함께 계산한다.
*/

#include <queue>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

constexpr int INF = 987654321;
constexpr int MAX_N = 20 + 1;
constexpr int dr[4] = { 1, 0, -1, 0 };
constexpr int dc[4] = { 0, 1, 0, -1 };

int N;
int ans;
int A[MAX_N][MAX_N];
int number[MAX_N][MAX_N];

void	init()
{
	ans = INF;
	cin >> N;
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			cin >> A[i][j];
}

bool	 check_range(int r, int c)
{
	return r >= 0 && r < N && c >= 0 && c < N;
}

void	section_five(int standard_r, int standard_c, int d1, int d2)
{
	queue<int> rq, cq;

	rq.push(standard_r);
	cq.push(standard_c);
	while (!rq.empty())
	{
		int r = rq.front();
		int c = cq.front();
		int nr = r + 1;
		int nc = c - 1;

		rq.pop();
		cq.pop();
		number[r][c] = 5;
		if (check_range(nr, nc) && nr - standard_r <= d1)
		{
			rq.push(nr);
			cq.push(nc);
		}
	}
	rq.push(standard_r);
	cq.push(standard_c);
	while (!rq.empty())
	{
		int r = rq.front();
		int c = cq.front();
		int nr = r + 1;
		int nc = c + 1;

		rq.pop();
		cq.pop();
		number[r][c] = 5;
		if (check_range(nr, nc) && nr - standard_r <= d2)
		{
			rq.push(nr);
			cq.push(nc);
		}
	}
	rq.push(standard_r + d1);
	cq.push(standard_c - d1);
	while (!rq.empty())
	{
		int r = rq.front();
		int c = cq.front();
		int nr = r + 1;
		int nc = c + 1;

		rq.pop();
		cq.pop();
		number[r][c] = 5;
		if (check_range(nr, nc) && nr - standard_r - d1 <= d2)
		{
			rq.push(nr);
			cq.push(nc);
		}
	}
	rq.push(standard_r + d2);
	cq.push(standard_c + d2);
	while (!rq.empty())
	{
		int r = rq.front();
		int c = cq.front();
		int nr = r + 1;
		int nc = c - 1;

		rq.pop();
		cq.pop();
		number[r][c] = 5;
		if (check_range(nr, nc) && nr - standard_r - d2 <= d1)
		{
			rq.push(nr);
			cq.push(nc);
		}
	}
}

void	number_section_one(int standard_r, int standard_c, int d1, int d2)

{
	queue<int> rq, cq;

	rq.push(standard_r);
	cq.push(standard_c);
	while (!rq.empty())
	{
		int r = rq.front();
		int c = cq.front();

		rq.pop();
		cq.pop();
		for (int i = 2; i < 4; ++i)
		{
			int nr = r + dr[i];
			int nc = c + dc[i];

			if (check_range(nr, nc) && number[nr][nc] != 1)
			{
				number[nr][nc] = 1;
				rq.push(nr);
				cq.push(nc);
			}
		}
	}
	for (int len = 1; len < d1; ++len)
	{
		rq.push(standard_r + len);
		cq.push(standard_c - len);

		while (!rq.empty())
		{
			int r = rq.front();
			int c = cq.front();
			int nr = r;
			int nc = c - 1;

			rq.pop();
			cq.pop();
			if (check_range(nr, nc) && number[nr][nc] != 1)
			{
				number[nr][nc] = 1;
				rq.push(nr);
				cq.push(nc);
			}
		}
	}
}

void	number_section_two(int standard_r, int standard_c, int d1, int d2)

{
	queue<int> rq, cq;

	rq.push(standard_r + d2);
	cq.push(standard_c + d2);
	while (!rq.empty())
	{
		int r = rq.front();
		int c = cq.front();

		rq.pop();
		cq.pop();
		for (int i = 1; i <= 2; ++i)
		{
			int nr = r + dr[i];
			int nc = c + dc[i];

			if (check_range(nr, nc) && number[nr][nc] != 2)
			{
				number[nr][nc] = 2;
				rq.push(nr);
				cq.push(nc);
			}
		}
	}
	for (int len = 1; len < d2; ++len)
	{
		rq.push(standard_r + d2 - len);
		cq.push(standard_c + d2 - len);

		while (!rq.empty())
		{
			int r = rq.front();
			int c = cq.front();
			int nr = r - 1;
			int nc = c;

			rq.pop();
			cq.pop();
			if (check_range(nr, nc) && number[nr][nc] != 2)
			{
				number[nr][nc] = 2;
				rq.push(nr);
				cq.push(nc);
			}
		}
	}
}

void	number_section_three(int standard_r, int standard_c, int d1, int d2)

{
	queue<int> rq, cq;

	rq.push(standard_r + d1);
	cq.push(standard_c - d1);
	while (!rq.empty())
	{
		int r = rq.front();
		int c = cq.front();

		rq.pop();
		cq.pop();
		for (int i = 0; i < 4; i += 3)
		{
			int nr = r + dr[i];
			int nc = c + dc[i];

			if (check_range(nr, nc) && number[nr][nc] != 3)
			{
				number[nr][nc] = 3;
				rq.push(nr);
				cq.push(nc);
			}
		}
	}
	for (int len = 1; len < d2; ++len)
	{
		rq.push(standard_r + d1 + len);
		cq.push(standard_c - d1 + len);

		while (!rq.empty())
		{
			int r = rq.front();
			int c = cq.front();
			int nr = r + 1;
			int nc = c;

			rq.pop();
			cq.pop();
			if (check_range(nr, nc) && number[nr][nc] != 3)
			{
				number[nr][nc] = 3;
				rq.push(nr);
				cq.push(nc);
			}
		}
	}
}

void	number_section_four(int standard_r, int standard_c, int d1, int d2)
{
	queue<int> rq, cq;

	rq.push(standard_r + d1 + d2);
	cq.push(standard_c - d1 + d2);
	while (!rq.empty())
	{
		int r = rq.front();
		int c = cq.front();

		rq.pop();
		cq.pop();
		for (int i = 0; i < 2; ++i)
		{
			int nr = r + dr[i];
			int nc = c + dc[i];

			if (check_range(nr, nc) && number[nr][nc] != 4)
			{
				number[nr][nc] = 4;
				rq.push(nr);
				cq.push(nc);
			}
		}
	}
	for (int len = 1; len < d1; ++len)
	{
		rq.push(standard_r + d1 + d2 - len);
		cq.push(standard_c - d1 + d2 + len);

		while (!rq.empty())
		{
			int r = rq.front();
			int c = cq.front();
			int nr = r;
			int nc = c + 1;

			rq.pop();
			cq.pop();
			if (check_range(nr, nc) && number[nr][nc] != 4)
			{
				number[nr][nc] = 4;
				rq.push(nr);
				cq.push(nc);
			}
		}
	}
}

int		get_diff()
{
	int 		min_section;
	int 		max_section;
	vector<int> cnt(6);

	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			cnt[number[i][j]] += A[i][j];
	min_section = cnt[0] + cnt[5];
	max_section = cnt[0] + cnt[5];
	for (int i = 1; i < 5; i++)
	{
		min_section = min(min_section, cnt[i]);
		max_section = max(max_section, cnt[i]);
	}
	return max_section - min_section;
}

bool	is_possible(int r, int c)
{
	if ((r | c) == 0)
		return false;
	if (r == N - 1 && c == 0)
		return false;
	if (r == 0 && c == N - 1)
		return false;
	if (r == N - 1 && c == N - 1)
		return false;
	return true;
}

void	solve()
{
	for (int r = 0; r < N; ++r)
		for (int c = 0; c < N; ++c)
			if (is_possible(r, c))
				for (int d1 = 1; c - d1 >= 0; ++d1)
					for (int d2 = 1; r + d1 + d2 < N && c + d2 < N; ++d2)
					{
						int diff;

						section_five(r, c, d1, d2);
						number_section_one(r, c, d1, d2);
						number_section_two(r, c, d1, d2);
						number_section_three(r, c, d1, d2);
						number_section_four(r, c, d1, d2);
						diff = get_diff();
						ans = min(diff, ans);
						memset(number, 0, sizeof(number));
					}
}

int		main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	init();
	solve();
	cout << ans << '\n';
	return 0;
}