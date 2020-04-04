/*
	파티
	https://www.acmicpc.net/problem/1238

	각 학생이 'X' 마을을 오가는 최단 시간 중에서 가장 오래 걸리는 시간을 구하는 문제다.

	모든 학생의 경로를 비교해야하기 때문에 "플로이드-워셜 알고리즘"을 사용해서 모든 경로의 최단 시간을 구했다.
	그 후, 'X' 마을을 왕복하는데 시간이 가장 오래 걸리는 학생을 찾았다.
*/
#include <iostream>

using namespace std;

constexpr auto MAXN = 1001;
constexpr auto INF = 987654321;

int N, M, X;
int dist[MAXN][MAXN];

void init()
{
    cin >> N >> M >> X;
    for (int i = 1; i <= N; ++i)
    {
        for (int j = 1; j <= N; ++j)
        {
            if (i == j)
                dist[i][j] = 0;
            else
                dist[i][j] = INF;
        }
    }
    for (int i = 0; i < M; ++i)
    {
    	int start, end, length;

        cin >> start >> end >> length;
        dist[start][end] = length;
    }
}

void floid()
{
    for (int m = 1; m <= N; ++m)
        for (int s = 1; s <= N; ++s)
            for (int e = 1; e <= N; ++e)
                dist[s][e] = dist[s][e] < dist[s][m] + dist[m][e] ? dist[s][e] : dist[s][m] + dist[m][e];
}

int solve()
{
    int ans = -INF;

    floid();
    for (int i = 1; i <= N; ++i)
        ans = ans < dist[X][i] + dist[i][X] ? dist[X][i] + dist[i][X] : ans;
    return (ans);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    cout << solve() << '\n';
    return 0;
}