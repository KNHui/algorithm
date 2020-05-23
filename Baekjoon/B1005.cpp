/*
	ACM Craft
	https://www.acmicpc.net/problem/1005

	목표 건물 'W'를 건설 완료하는데 드는 최소 시간을 구하는 문제다.

	"진입 차수 위상 정렬"을 사용하여 풀었다.
	진입 차수가 '0'인 건물은 건설을 시작할 수 있다는 의미다.
	정답은 'W'까지 가는 경로 중에서 가장 긴 누적 합을 가지고 있는 경로의 시간이다.
	그 이유는 'W'로 향하는 모든 경로가 완료되어야 'W' 건설을 시작할 수 있기 때문이다.
*/
#include <queue>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

constexpr int MAXN = 1000 + 1;

int			N, K;
int			W;
int			time[MAXN];
int			indegree[MAXN];
vector<int>	order[MAXN];

void init()
{
	cin >> N >> K;
	for (int i = 1; i <= N; ++i)
		order[i].clear();
	for (int i = 1; i <= N; ++i)
		cin >> time[i];
	memset(indegree, 0, sizeof(indegree));
	for (int i = 1; i <= K; ++i)
	{
		int X, Y;

		cin >> X >> Y;
		order[X].push_back(Y);
		++indegree[Y];
	}
	cin >> W;
}

int solve()
{
	queue<int>	q;
	vector<int>	total_time(N + 1, 0);

	for (int i = 1; i <= N; ++i)
	{
		if (indegree[i] == 0)
		{
			q.push(i);
			total_time[i] = time[i];
		}
	}
	
	while (!q.empty())
	{
		int building = q.front();

		q.pop();
		for (size_t i = 0; i < order[building].size(); ++i)
		{
			int next = order[building][i];

			total_time[next] = max(total_time[next], total_time[building] + time[next]);
			if (--indegree[next] == 0)
				q.push(next);
		}
	}
	return total_time[W];
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int tc;

	cin >> tc;
	for (int tcn = 1; tcn <= tc; ++tcn)
	{
		init();
		cout << solve() << '\n';
	}
	return 0;
}