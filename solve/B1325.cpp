/*
	효율적인 해킹
	https://www.acmicpc.net/problem/1325

	단방향 그래프에서 다른 컴퓨터와 가장 많이 연결된 컴퓨터의 번호를 찾는 문제다.

	"int cnt[idx]"에 'idx' 컴퓨터를 해킹하면 몇 개의 컴퓨터를 해킹할 수 있는지 저장했다.
	역순으로 탐색하면서 자신을 해킹할 수 있는 컴퓨터의 'cnt' 값을 '1' 증가시켰다.
*/
#include <queue>
#include <iostream>

using namespace std;

constexpr int MAXN = 10001;

int			N, M;
int			cnt[MAXN];
bool		visit[MAXN];
queue<int>	ans;
vector<int>	map[MAXN];

void init()
{
	cin >> N >> M;
	for (int i = 0; i < M; ++i)
	{
		int A, B;

		cin >> A >> B;
		map[A].push_back(B);
	}
}

void reverse_search(int idx)
{
	visit[idx] = true;
	for (int next : map[idx])
	{
		if (!visit[next])
		{
			++cnt[next];
			reverse_search(next);
		}
	}
}

void solve()
{
	for (int idx = 1; idx <= N; ++idx)
	{
		fill(visit, visit + N + 1, false);
		reverse_search(idx);
	}

	int max_cnt = 0;
	for (int idx = 1; idx <= N; ++idx)
		max_cnt = max_cnt < cnt[idx] ? cnt[idx] : max_cnt;
	for (int idx = 1; idx <= N; ++idx)
		if (max_cnt == cnt[idx])
			ans.push(idx);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	init();
	solve();
	while (!ans.empty())
	{
		cout << ans.front() << ' ';
		ans.pop();
	}
	return 0;
}