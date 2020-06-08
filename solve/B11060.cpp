/*
	점프 점프
	https://www.acmicpc.net/problem/11060

	첫 칸부터 시작하여 최소 몇 번 점프해야 마지막 칸으로 갈 수 있는지 구하는 문제다.

	칸에 있는 값 이하만큼 오른쪽으로 움직일 수 있다.
	그래서 1부터 칸에 있는 값까지의 점프를 모두 해보는데,
	메모이제이션을 통한 상향식 접근법으로 중복 연산을 피할 수 있다.
	그 방법은 재귀 함수 dfs를 수행하면서 처음 방문한 인덱스라면,
	memo[idx]에 마지막 칸으로 가기 위한 최소 점프 횟수를 기록한다.
*/
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

constexpr auto MAX = 1000 + 1;
constexpr auto INF = 987654321;

int N, T;
int A[MAX], memo[MAX];

void init()
{
	cin >> N;
	for (int i = 1; i <= N; ++i)
		cin >> A[i];
	memset(memo, -1, sizeof(memo));
}

int dfs(int idx)
{
	if (idx == N)
		return 0;
	if (idx > N)
		return INF;
	if (memo[idx] != -1)
		return memo[idx];
	memo[idx] = INF;
	for (int i = 1; i <= A[idx]; ++i)
		memo[idx] = min(memo[idx], dfs(idx + i) + 1);
	return memo[idx];
}

int solve()
{
	int result = dfs(1);
	return result == INF ? -1 : result;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	init();
	int ans = solve();
	cout << ans;
	return 0;
}