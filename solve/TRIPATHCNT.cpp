/*
	삼각형 위의 최대 경로 수 세기
	https://www.algospot.com/judge/problem/read/TRIPATHCNT

	숫자의 합이 가장 큰 경로의 개수를 구하는 문제다.

	숫자의 합이 가장 큰 경로는 'TRIANGLEPATH'에서 구했었다.
	(https://github.com/KNHui/algorithm/blob/master/ALGOSPOT/TRIANGLEPATH.cpp)
	'TRIANGLEPATH'에서는 숫자의 합만 반환했기 때문에 경로를 세진 않았다.

	이번 문제에서는 경로를 세는 함수에서 값이 더 큰 경로를 선택해서 가도록 했다.
	숫자의 합이 가장 큰 경로를 구할 때 남쪽과 남동쪽 중 값이 더 큰 경로를 선택했었다.
	이를 이용해 선택됐었던 값이 더 큰 경로만 탐색했다.
	맨 아래 줄에 도착하면 1을 반환해서 숫자의 합이 가장 큰 경로의 수를 세도록 했다.
*/
#include <iostream>
#include <algorithm>

using namespace std;

constexpr int MAX_N = 100 + 1;

int n;
int map[MAX_N][MAX_N];
int cache_sum[MAX_N][MAX_N];
int cache_cnt[MAX_N][MAX_N];

void	init(void)
{
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		fill(cache_sum[i], cache_sum[i] + i + 1, -1);
		fill(cache_cnt[i], cache_cnt[i] + i + 1, -1);
		for (int j = 0; j <= i; ++j)
			cin >> map[i][j];
	}
}

bool	check_range(int y, int x)
{
	return y >= 0 && y < n && x >= 0 && x <= y + 1;
}

int		get_path_sum(int y, int x)
{
	if (cache_sum[y][x] != -1)
		return cache_sum[y][x];
	if (y == n - 1)
		return cache_sum[y][x] = map[y][x];

	int se = get_path_sum(y + 1, x);
	int s = get_path_sum(y + 1, x + 1);
	return cache_sum[y][x] = max(se, s) + map[y][x];
}

int		get_path_cnt(int y, int x)
{
	if (cache_cnt[y][x] != - 1)
		return cache_cnt[y][x];
	if (y == n - 1)
		return cache_cnt[y][x] = 1;

	cache_cnt[y][x] = 0;
	if (get_path_sum(y + 1, x) >= get_path_sum(y + 1, x + 1))
		cache_cnt[y][x] += get_path_cnt(y + 1, x);
	if (get_path_sum(y + 1, x) <= get_path_sum(y + 1, x + 1))
		cache_cnt[y][x] += get_path_cnt(y + 1, x + 1);
	return cache_cnt[y][x];
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
		cout << get_path_cnt(0, 0) << '\n';
	}
	return 0;
}
