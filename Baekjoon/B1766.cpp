/*
	문제집
	https://www.acmicpc.net/problem/1766

	위상 정렬을 사용하면서 난이도가 쉬운 문제부터 출력한다.

	단순히 위상 정렬을 사용하면, 어려운 문제부터 풀 수 있다.
	ex.
	input
	4 4
	3 1
	2 1
	4 3
	4 2

	wrong output
	4 3 2 1

	answer
	4 2 3 1
	그래서 위상 정렬에 우선 순위 큐를 사용하여 쉬운 문제부터 풀도록 해야한다.
*/
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

constexpr int MAXN = 32000 + 1;

int N, M;
int indegree[MAXN];
vector<int> workbook[MAXN];

void init()
{
	cin >> N >> M;
	for (int i = 0; i < M; ++i)
	{
		int A, B;

		cin >> A >> B;
		++indegree[B];
		workbook[A].push_back(B);
	}
}

void solve()
{
	priority_queue<int, vector<int>, greater<int>> pq;

	for (int i = 1; i <= N; i++)
		if (indegree[i] == 0)
			pq.push(i);
	while (!pq.empty())
	{
		int problem = pq.top();

		pq.pop();
		cout << problem << ' ';
		for (int i = 0; i < workbook[problem].size(); ++i)
		{
			int next = workbook[problem][i];

			if (--indegree[next] == 0)
				pq.push(next);
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	init();
	solve();
	return 0;
}