/*
	거의 최단 경로
	https://www.acmicpc.net/problem/5719

	최단 경로에 포함되지 않는 도로를 사용한 거의 최단 경로의 길이를 구하는 문제다.

	"데익스트라 알고리즘"을 사용하여 최단 경로를 구하고, "너비 우선 탐색"을 사용하여 최단 경로를 지웠다.
	그러고 나서 거의 최단 경로를 구할 때 최단 경로에 포함된 도로를 지나가지 못하도록 했다.

	최단 경로는 하나가 아닐 수 있다.
	그래서 백준 11779번처럼 최단 경로를 기록하는 자료구조로 스택을 쓰면 안 된다.
	(https://github.com/KNHui/algorithm/blob/master/Baekjoon/B11779.cpp)
	최단 경로는 "vector trace[500 + 1]"를 사용하여 기록했다.
	'trace[next]'에는 'next'를 최단 경로를 사용하여 갔던 장소를 저장한다.

	최단 경로를 지우는 작업은 "너비 우선 탐색"을 사용했다.
	도착점에서부터 출발점까지 'trace'를 활용하여 역순으로 최단 경로를 탐색했다.
	이때, 방문하는 도로는 최단 경로에 포함된 도로라서 해당 도로의 길이를 '-1'로 초기화했다.
	그리고 거의 최단 경로를 찾을 때, 길이가 '-1'인 도로는 지나가지 못하도록 했다.
*/
#include <queue>
#include <cstring>
#include <iostream>

using namespace std;

constexpr int INF = 987654321;
constexpr int MAX = 500 + 1;
typedef pair<int, int> pii;

int N, M;
int S, D;
bool visit[MAX][MAX];
vector<pii> map[MAX];
vector<int> trace[MAX];

int init()
{
	cin >> N >> M;
	if (N + M == 0)
		return 0;
	cin >> S >> D;
	memset(visit, false, sizeof(visit));
	for (int i = 0; i < N; ++i)
	{
		map[i].clear();
		trace[i].clear();
	}

	for (int i = 0; i < M; ++i)
	{
		int U, V, P;
		cin >> U >> V >> P;
		map[U].push_back({ P, V });
	}
	return N + M;
}

int dijk()
{
	vector<int> dist;
	priority_queue<pii, vector<pii>, greater<pii> > pq;

	pq.push({ 0, S });
	dist.resize(N + 1, INF);
	dist[S] = 0;
	while (!pq.empty())
	{
		int cumulative = pq.top().first;
		int place = pq.top().second;
		pq.pop();

		if (cumulative > dist[place])
			continue;

		for (size_t i = 0; i < map[place].size(); ++i)
		{
			int cost = map[place][i].first;
			int next = map[place][i].second;

			if (cost == -1)
				continue;

			if (cost + cumulative < dist[next])
			{
				pq.push({ cost + cumulative, next });
				dist[next] = cost + cumulative;

				trace[next].clear();
				trace[next].push_back(place);
			}
			else if (cost + cumulative == dist[next])
				trace[next].push_back(place);
		}
	}
	return dist[D];
}

void bfs()
{
	queue<int> q;

	q.push(D);
	while (!q.empty())
	{
		int place = q.front();
		q.pop();

		for (size_t i = 0; i < trace[place].size(); ++i)
		{
			int next = trace[place][i];

			if (visit[place][next])
				continue;

			for (size_t j = 0; j < map[next].size(); j++)
				if (map[next][j].second == place)
					map[next][j].first = -1;
			visit[place][next] = true;
			q.push(next);
		}
	}
}

int solve()
{
	int ret;

	dijk();
	bfs();
	ret = dijk();
	return ret;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	while (init())
	{
		int answer = solve();
		cout << (answer == INF ? -1 : answer) << '\n';
	}
	return 0;
}