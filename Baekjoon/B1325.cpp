/*
	효율적인 해킹
	https://www.acmicpc.net/problem/1325

	단방향 그래프에서 다른 컴퓨터와 가장 많이 연결된 컴퓨터의 번호를 찾는 문제다.

	깊이 우선 탐색을 사용하여 어떤 컴퓨터를 해킹하면
	현재 'idx'의 컴퓨터를 해킹할 수 있는지 역순으로 탐색했다.
	중복 연산을 하지 않도록 'visit' 배열로 확인하고,
	깊이 우선 탐색을 할 때마다 'visit' 배열을 초기화했다.

	가장 많은 컴퓨터를 해킹할 수 있는 컴퓨터의 번호를 오름차순으로 출력해야 한다.
	그래서 가장 많은 컴퓨터의 수 'max_cnt'를 구하고,
	'max_cnt'와 같은 수를 가진 컴퓨터를 작은 번호부터 'queue'에 삽입했다.
	그리고 'queue'에 있는 데이터를 차례대로 출력했다.
*/
#include <queue>
#include <iostream>

using namespace std;

constexpr auto MAX = 10001;

int N, M;
int cnt[MAX];
bool visit[MAX];
queue<int> ans;
vector<int> map[MAX];

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

void dfs(int idx)
{
	visit[idx] = true;

	for (int next : map[idx])
	{
		if (!visit[next])
		{
			++cnt[next];
			dfs(next);
		}
	}
}

void solve()
{
	for (int idx = 1; idx <= N; ++idx)
	{
		fill(visit, visit + N + 1, false);
		dfs(idx);
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