/*
	전력난
	https://www.acmicpc.net/problem/6497

	모든 도시를 연결하는 최소 스패닝 트리를 구하는 문제다.

	크루스칼 알고리즘을 사용하여 최소 스패닝 트리를 구했다.
	모든 경로를 오름차순으로 정렬하고, 길이가 짧은 경로부터 탐색했다.
	경로의 두 정점을 연결해도 사이클을 이루지 않는다면, 연결하고 경로의 길이를 'min_dist'에 더했다.
	최소 스패닝 트리를 완성했다면, 불을 꺼도 되는 경로들의 합인 'total_dist - min_dist'를 출력했다.
*/
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

constexpr int MAX = 200001;

int m, n;
int parent[MAX];

int find(int idx)
{
	return parent[idx] == idx ? idx : parent[idx] = find(parent[idx]);
}

void init(int &total_dist, vector<pair<int, pair<int, int> > > &road)
{
	int i;

	cin >> m >> n;
	fill(parent, parent + MAX, 0);
	for (i = 0; i < n; ++i)
	{
		int x, y, z;
		cin >> x >> y >> z;
		total_dist += z;
		parent[i] = i;
		road.push_back({ z, {x, y} });
	}
	if (n == m - 1)
		parent[n] = n;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	m = 1;
	while (true)
	{
		int total_dist = 0;
		int min_dist = 0;
		int cnt = 0;
		vector<pair<int, pair<int, int> > > road;

		init(total_dist, road);
		if (m == 0)
			break;
		sort(road.begin(), road.end());
		for (size_t i = 0; i < road.size(); ++i)
		{
			int from_parent = find(road[i].second.first);
			int to_parent = find(road[i].second.second);
			if (from_parent == to_parent)
				continue;
			parent[from_parent] = to_parent;
			min_dist += road[i].first;
			++cnt;
			if (cnt == m - 1)
				break;
		}
		cout << total_dist - min_dist << '\n';
	}
	return 0;
}