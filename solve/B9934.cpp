/*
	완전 이진 트리
	https://www.acmicpc.net/problem/9934

	중위 순회 탐색 결과를 보고 전체 트리를 출력하는 문제다.

	중위 순회를 하면서 노드를 방문할 때, "vector<int> op[깊이]"에 빌딩 번호를 저장했다.
*/
#include <vector>
#include <iostream>

using namespace std;

int K;
vector<int> op[10 + 1];

void inorder(int idx, int depth)
{
	int ip;

	if (depth < K)
		inorder(idx * 2, depth + 1);
	cin >> ip;
	op[depth].push_back(ip);
	if (depth < K)
		inorder(idx * 2 + 1, depth + 1);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> K;
	inorder(1, 1);
	for (int i = 1; i <= K; ++i)
	{
		for (size_t j = 0; j < op[i].size(); ++j)
			cout << op[i][j] << ' ';
		cout << '\n';
	}
	return 0;
}