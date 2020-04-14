/*
	��Ƽ
	https://www.acmicpc.net/problem/1238

	�� �л����� X �������� ���� �ִ� �ð� �߿��� ���� ���� �ɸ��� �ð��� ����ؾ� �Ѵ�.
	�׷��� ��� ����� �ִ� �ð��� ���ϴ� �÷��̵�-���� �˰����� ����Ͽ�,
	����� �ҿ� �ð��� ����ִ� int dist[�����][������] �� �����ϰ�
	dist[X][���� ��ȣ] + dist[���� ��ȣ][X] �� ���� ū ���� ����Ѵ�.
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