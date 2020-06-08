/*
	최소비용 구하기 2
	https://www.acmicpc.net/problem/11779

	다익스트라 알고리즘을 이용하여 출발점에서 도착점까지의 최소 비용과 경로를 출력하는 문제다.

	최소 비용은 다익스트라 알고리즘을 이용하여 dist 배열에 해당 도시까지의 최소 비용을 기록하여 구한다.

	경로는 스택처럼 기록하는데, pre 배열에 index 도시까지 최소 비용으로 도착한 이전 도시의 번호를 기록한다.
	다익스트라 알고리즘이 종료되면, pre[도착점]부터 시작하여 이전 도시들을 출발점 도시까지 진짜 스택에 저장한다.
	이는 도시 번호를 이용한 반복문으로 수행하는데, 도시 번호는 1부터 시작하고, pre[출발점]은 0이기 때문에 가능하다.
	왜냐하면, 출발점 도시는 dist[출발점]를 0으로 초기화해서 어떤 도시도 방문할 수 없기 때문이다.
	그래서 pre[출발점]는 0을 유지하기 때문에 이전 도시들을 방문하는 반복문이 출발점에 도착하면 종료된다.
*/
#include <stack>
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

constexpr auto INF = 987654321;

int n, m;
int start, goal;
int pre[1001];
vector<pair<int, int> > map[1001];

void input()
{
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		int start, end, cost;
		cin >> start >> end >> cost;
		map[start].push_back({ end, cost });
	}
	cin >> start >> goal;
}

int dijk()
{
	vector<int> dist(n + 1, INF);
	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;

	pq.push({ 0, start });
	dist[start] = 0;
	while (!pq.empty())
	{
		int city = pq.top().second;
		int cumulative = pq.top().first;

		pq.pop();
		for (size_t i = 0; i < map[city].size(); ++i)
		{
			int end = map[city][i].first;
			int cost = map[city][i].second;

			if (cost + cumulative < dist[end])
			{
				pq.push({ cost + cumulative, end });
				dist[end] = cost + cumulative;
				pre[end] = city;
			}
		}
	}
	return dist[goal];
}

void solve()
{
	int num = 0;
	int city = goal;
	int cumulative = dijk();
    stack<int> route;

	while (city)
	{
		++num;
		route.push(city);
		city = pre[city];
	}
	cout << cumulative << '\n';
	cout << num << '\n';
	while (!route.empty())
	{
		cout << route.top() << ' ';
		route.pop();
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	input();
	solve();
	return 0;
}