/*
	바이러스
	https://www.acmicpc.net/problem/2606

	주어지는 양방향 그래프에서 1번 컴퓨터와 연결된 컴퓨터의 수를 구하는 문제다.

	플로이드-워셜 알고리즘을 사용하여 컴퓨터 간에 연결되어 있는지를 표시했다.
	그 후, 1번 컴퓨터와 연결된 컴퓨터의 수를 세었다.
*/
#include <iostream>

using namespace std;

constexpr auto MAXN = 100 + 1;

int N, M;
int d[MAXN][MAXN];

void floyd()
{
	for (int m = 1; m <= N; m++)
		for (int s = 1; s <= N; s++)
			for (int e = 1; e <= N; e++)
				if (d[s][m] == 1 && d[m][e] == 1)
					d[s][e] = 1;
}

void input()
{
	cin >> N;
	cin >> M;
	int first_com, second_com;
	for (int i = 1; i <= M; ++i)
	{
		cin >> first_com >> second_com;
		d[first_com][second_com] = 1;
		d[second_com][first_com] = 1;
	}
}

int solve()
{
	int ret = 0;

	floyd();
	for (int j = 2; j <= N; ++j)
		if (d[1][j] == 1)
			ret++;
	return ret;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	input();
	int ans = solve();
	cout << ans;
	return 0;
}