/*
	이분 그래프
	https://www.acmicpc.net/problem/1707

	정점과 간선이 주어질 때, 이분 그래프인지 판별하는 문제다.

	간선으로 연결된 정점을 서로 다른 집합에 넣을 수 있다면, 이분 그래프다.

	집합이 정해지지 않은 정점부터 "너비 우선 탐색"을 진행한다.
	탐색을 진행하면서 다음 정점이 집합에 포함되지 않았다면, 현재 정점과 다른 집합에 넣는다.
	만약 다음으로 탐색할 정점이 이미 현재 정점과 같은 집합에 들어가 있다면, 주어진 그래프는 이분 그래프가 아니다.
*/
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

constexpr int MAX_V = 20000 + 1;

int			K, V, E;
int			set[MAX_V];
bool		possible;
vector<int>	graph[MAX_V];

void	init(void)
{
	cin >> V >> E;
	possible = true;
	for (int i = 1; i <= V; ++i)
	{
		set[i] = 0;
		graph[i].clear();
	}
	for (int i = 1; i <= E; ++i)
	{
		int vertex1, vertex2;

		cin >> vertex1 >> vertex2;
		graph[vertex1].push_back(vertex2);
		graph[vertex2].push_back(vertex1);
	}
}

bool	bfs(int start)
{
	queue<int> q;

	q.push(start);
	set[start] = 1;
	while (!q.empty())
	{
		int vertex = q.front();

		q.pop();
		for (size_t i = 0; i < graph[vertex].size(); ++i)
		{
			int next = graph[vertex][i];

			if (set[next] == set[vertex])
				return false;
			else if (set[next] == 0)
			{
				set[next] = (set[vertex] == 1 ? 2 : 1);
				q.push(next);
			}
		}
	}
	return true;
}

void	solve(void)
{
	for (int i = 1; i <= V && possible; ++i)
		if (set[i] == 0)
			possible &= bfs(i);
}

int		main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> K;
	for (int i = 1; i <= K; ++i)
	{
		init();
		solve();
		cout << (possible ? "YES" : "NO") << '\n';
	}
	return 0;
}