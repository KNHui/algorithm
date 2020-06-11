/*
	Longest Increasing Sequence
	https://www.algospot.com/judge/problem/read/LIS

	주어진 수열의 가장 긴 증가 부분 수열의 길이(LIS)를 구하는 문제다.

	'메모이제이션'을 사용하여 문제를 풀었다.
	수열 'nums'에 'N'개의 수가 있을 때, 'cache[idx]'는 'nums'의 구간 '[idx, N)'의 LIS다.

	LIS의 시작 위치는 어디든 될 수 있기 때문에 모든 위치를 기점으로 탐색했다.
	탐색할 때는 현재 인덱스 'idx' 의 숫자보다 크고, 가장 긴 LIS를 가진 인덱스 'next'를 찾아낸다.
	그 후, 'cache[idx]'를 'cache[next] + 1'로 갱신하면서 LIS를 구해나갔다.
*/

#include <iostream>
#include <algorithm>

using namespace std;

constexpr int MAX_N = 500 + 1;

int N;
int	nums[MAX_N];
int cache[MAX_N];

void	init(void)
{
	cin >> N;
	for (int i = 0; i < N; ++i)
		cin >> nums[i];
}

int		lis(int idx)
{
	if (cache[idx])
		return cache[idx];
	int max_result = 1;

	for (int next = idx + 1; next < N; ++next)
		if (nums[idx] < nums[next])
			max_result = max(max_result, lis(next) + 1);
	return cache[idx] = max_result;
}

int		solve(void)
{
	int answer = 0;

	for (int i = 0; i < N; ++i)
		answer = max(answer, lis(i));
	return answer;
}

int		main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int C;

	cin >> C;
	for (int i = 1; i <= C; ++i)
	{
		init();
		cout << solve() << '\n';
	}
	return 0;
}