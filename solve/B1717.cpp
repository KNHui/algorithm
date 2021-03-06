/*
	집합의 표현
	https://www.acmicpc.net/problem/1717

	"서로소 집합" 자료 구조를 사용하여 집합을 표현하는 문제다.

	모든 원소의 부모를 자기 자신으로 설정하고 연산을 수행했다.
	
	연산 '0'은 'Union' 연산으로 처리했다.
	'Union' 연산은 한 인덱스의 부모를 다른 인덱스의 부모로 바꾸었다.

	연산 '1'은 'Find' 연산으로 두 인덱스의 부모를 찾아서 같은 집합인지 확인했다.
	'Find' 연산은 재귀를 통하여 자기 자신이 부모인 인덱스를 찾아서 반환했다.
*/
#include <iostream>

using namespace std;

constexpr int MAX_M = 100000 + 1;

int n, m;
int parent[MAX_M];

void	init(void)
{
	cin >> n >> m;
	for (int i = 0; i <= n; ++i)
		parent[i] = i;
}

int		find(int index)
{
	if (parent[index] == index)
		return index;
	return parent[index] = find(parent[index]);
}

void	merge(int left_index, int right_index)
{
	int left_parent = find(left_index);
	int right_parent = find(right_index);

	if (left_parent == right_parent)
		return;
	parent[left_parent] = right_parent;
}

void	solve(void)
{
	for (int i = 0; i < m; ++i)
	{
		int command, a, b;

		cin >> command >> a >> b;
		switch (command)
		{
		case 0:
			merge(a, b);
			break;
		case 1:
			string result = find(a) == find(b) ? "YES" : "NO";

			cout << result << '\n';
			break;
		}
	}
}

int		main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	init();
	solve();
	return 0;
}