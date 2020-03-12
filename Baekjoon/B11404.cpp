/*
	플로이드
	https://www.acmicpc.net/problem/11404

	플로이드 와샬을 사용하여 모든 정점간의 최소 비용을 구하는 문제다.
*/
#include <iostream>

using namespace std;

constexpr int INF = 987654321;

int n, m;
int dist[101][101];

void init()
{
	cin >> n >> m;
	for (int row = 1; row <= n; ++row)
		for (int col = 1; col <= n; ++col)
			if (row == col)
				dist[row][col] = 0;
			else
				dist[row][col] = INF;
	for (int i = 0; i < m; ++i)
	{
		int a, b, c;

		cin >> a >> b >> c;
		dist[a][b] = dist[a][b] < c ? dist[a][b] : c;
	}
}

void floid()
{
	for (int m = 1; m <= n; ++m)
		for (int s = 1; s <= n; ++s)
			for (int e = 1; e <= n; ++e)
				dist[s][e] = dist[s][e] < dist[s][m] + dist[m][e] ? dist[s][e] : dist[s][m] + dist[m][e];
}

void output()
{
	for (int row = 1; row <= n; ++row)
	{
		for (int col = 1; col <= n; ++col)
			cout << (dist[row][col] == INF ? 0 : dist[row][col]) << ' ';
		cout << '\n';
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	init();
	floid();
	output();
	return 0;
}