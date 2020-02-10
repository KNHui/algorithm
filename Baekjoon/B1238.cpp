/*
	파티
	https://www.acmicpc.net/problem/1238

	각 학생들이 X 마을까지 가는 최단 시간 중에서 가장 오래 걸리는 시간을 출력해야 한다.
	그래서 모든 경로의 최단 시간을 구하는 플로이드-워셜 알고리즘을 사용하여,
	경로의 소요 시간이 담겨있는 int dist[출발점][도착점] 을 갱신하고
	dist[X][마을 번호] + dist[마을 번호][X] 가 가장 큰 값을 출력한다.
*/
#include <iostream>

using namespace std;

constexpr auto N_MAX = 1001;
constexpr auto INF = 987654321;

int N, M, X;
int dist[N_MAX][N_MAX];

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

    int start, end, length;
    for (int i = 0; i < M; ++i)
    {
        cin >> start >> end >> length;
        dist[start][end] = length;
    }
}

void fw()
{
    for (int m = 1; m <= N; ++m)
        for (int s = 1; s <= N; ++s)
            for (int e = 1; e <= N; ++e)
                dist[s][e] = dist[s][e] < dist[s][m] + dist[m][e] ? dist[s][e] : dist[s][m] + dist[m][e];
}

int solve()
{
    int ans = -INF;

    fw();
    for (int i = 1; i <= N; ++i)
        if (dist[X][i] != INF)
            ans = ans < dist[X][i] + dist[i][X] ? dist[X][i] + dist[i][X] : ans;

    return (ans);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    int ans = solve();
    cout << ans << '\n';

    return 0;
}