/*
	특정한 최단 경로
	https://www.acmicpc.net/problem/1504

	다익스트라 알고리즘을 사용하여 최단 경로를 찾는 문제다.

	반드시 거쳐야 하는 정점이 두 개 주어지기 때문에, 다음과 같이 경우의 수를 처리했다.
	1) 출발점 - 첫 번째 정점 - 두 번째 정점 - 도착점
	2) 출발점 - 두 번째 정점 - 첫 번째 정점 - 도착점
	각 경로와 정답이 'INF(987654321)'보다 크거나 음수인지 확인해서 유효성을 검사했다.
	만약 유효한 값들이라면 더 작은 값을 answer에 대입하고 마지막으로 answer가 유효한지 검사 후 출력한다.
*/
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

constexpr auto INF = 987654321;
constexpr auto MAXN = 800 + 1;

int N, E;
int answer;
int mid1, mid2;
int map[MAXN][MAXN];

bool is_valid(int val)
{
	if (val >= 0 && val <= INF)
		return true;
	return false;
}

void init()
{
	for (int i = 0; i < N; ++i)
	{
		fill(map[i], map[i] + N, INF);
	}
	answer = -1;
}

void input()
{
	cin >> N >> E;
	init();
	for (int i = 0; i < E; ++i)
	{
		int a, b, c;
		cin >> a >> b >> c;
		map[--a][--b] = c;
		map[b][a] = c;
	}
	cin >> mid1 >> mid2;
	--mid1;
	--mid2;
}

int dijkstra(int start, int goal)
{
	priority_queue<pair<int, int>, vector<pair<int, int>>> pq;
	vector<int> min_dist(N, INF);

	pq.push({0, start});
	min_dist[start] = 0;
	while (!pq.empty())
	{
		int dist = pq.top().first;
		int node = pq.top().second;

		pq.pop();
		for (int i = 0; i < N; ++i)
		{
			if (map[node][i] - dist < min_dist[i])
			{
				pq.push({dist - map[node][i], i});
				min_dist[i] = map[node][i] - dist;
			}
		}
	}

	return min_dist[goal];
}

void solve()
{
	int StoM1;
	int StoM2;
	int MtoM;
	int M1toE;
	int M2toE;

	StoM1 = dijkstra(0, mid1);
	StoM2 = dijkstra(0, mid2);
	MtoM = dijkstra(mid1, mid2);
	M1toE = dijkstra(mid1, N - 1);
	M2toE = dijkstra(mid2, N - 1);

	int candi1 = INF + 1;
	int candi2 = INF + 1;

	if (is_valid(MtoM))
	{
		if (is_valid(StoM1) && is_valid(M2toE))
			candi1 = StoM1 + MtoM + M2toE;
		if (is_valid(StoM2) && is_valid(M1toE))
			candi2 = StoM2 + MtoM + M1toE;
		answer = candi1 < candi2 ? candi1 : candi2;
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	input();
	solve();
	cout << (is_valid(answer) ? answer : -1) << '\n';
	return 0;
}
