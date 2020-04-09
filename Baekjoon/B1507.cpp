/*
	궁금한 민호
	https://www.acmicpc.net/problem/1507

	최소 이동 시간을 유지하면서 도로 개수가 최소일 때, 모든 도로의 시간의 합을 구하는 문제다.

	"플로이드-워셜 알고리즘"을 사용해서 불필요한 경로를 확인했다.
	사용하지 않아도 최소 이동 시간이 유지되는 경로가 있다면, 해당 경로를 사용하지 않는다.
	1. 경로 "s - e"의 시간이 경로 "s - m - e"의 시간과 같은 경우
		경로 "s - e"를 사용하지 않는다.
	2. 경로 "s - e"의 시간이 경로 "s - m - e"의 시간보다 큰 경우
		강호의 표가 잘못되었으므로 '-1' 출력
*/
#include <cstring>
#include <iostream>

using namespace std;

const int MAXN = 20;

int		N;
int		answer;
int		map[MAXN][MAXN];
bool	road[MAXN][MAXN];

void	init(void)
{
	cin >> N;
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			cin >> map[i][j];
	memset(road, true, sizeof(road));
}

void	floyd(void)
{
	for (int m = 0; m < N; ++m)
		for (int s = 0; s < N; ++s)
			for (int e = 0; e < N; ++e)
				if (s == e || e == m || s == m)
					continue;
				else if (map[s][e] == map[s][m] + map[m][e])
					road[s][e] = false;
				else if (map[s][e] > map[s][m] + map[m][e])
				{
					answer = -1;
					return;
				}
}

int		get_total_time()
{
	int ret = 0;

	for (int i = 0; i < N; ++i)
		for (int j = i + 1; j < N; ++j)
			if (road[i][j])
				ret += map[i][j];
	return ret;
}

void	solve(void)
{
	floyd();
	if (answer != -1)
		answer = get_total_time();
}

int		main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	init();
	solve();
	cout << answer << '\n';
	return 0;

}