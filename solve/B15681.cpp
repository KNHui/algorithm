/*
	트리와 쿼리
	https://www.acmicpc.net/problem/15681
*/

#include <vector>
#include <iostream>

using namespace std;

constexpr int MAX_N = 100000 + 1;

int			N, R, Q;
int			cache[MAX_N];
bool		visit[MAX_N];
vector<int>	path[MAX_N];
vector<int>	query;

void	input(void)
{
	int U, V;

	cin >> N >> R >> Q;
	query.resize(Q);
	for (int i = 0; i < N - 1; ++i)
	{
		cin >> U >> V;
		path[U].push_back(V);
		path[V].push_back(U);
	}
	for (int i = 0; i < Q; ++i)
		cin >> query[i];
}

int		get_sub_size(int node)
{
	int& ret = cache[node];
	if (ret != 0)
		return ret;

	ret = 1;
	for (const int& next : path[node])
		if (!visit[next])
		{
			visit[next] = true;
			ret += get_sub_size(next);
		}
	return ret;
}

void	solve(void)
{
	visit[R] = true;
	get_sub_size(R);
	for (const int& sub_root : query)
		cout << get_sub_size(sub_root) << '\n';
}

int		main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	input();
	solve();
	return 0;
}