/*
	Longest Increasing Sequence
	https://www.algospot.com/judge/problem/read/LIS

	주어진 수열의 가장 긴 증가 부분 수열의 길이(LIS)를 구하는 문제다.

	"외발 뛰기" 문제처럼 "메모이제이션"을 사용했다.
	(https://github.com/KNHui/algorithm/blob/master/ALGOSPOT/JUMPGAME.cpp)

	수열 'nums'에 'N'개의 수가 있을 때, "cache[idx]"는 "nums [idx, N)의 LIS 길이"다.
	'깊이 우선 탐색'을 하면서 'cache'를 갱신했다.
	LIS의 시작 위치는 '0'이 될 수도 있고, 'N - 1'이 될 수도 있기 때문에 모든 위치를 기점으로 호출 했다.
*/
#include <iostream>
#include <algorithm>

using namespace std;

constexpr int MAX_N = 500 + 1;

int N;
int	ip[MAX_N];
int cache[MAX_N];

void	init(void)
{
	cin >> N;
	for (int i = 0; i < N; ++i)
		cin >> ip[i];
}

int		lis(int idx)
{
	if (cache[idx])
		return cache[idx];

	int max_result = 1;

	for (int i = idx + 1; i < N; ++i)
		if (ip[idx] < ip[i])
			max_result = max(max_result, lis(i) + 1);
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