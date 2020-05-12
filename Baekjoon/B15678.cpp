/*
	연세워터파크
	https://www.acmicpc.net/problem/15678

	주어진 배열의 원소들을 조건에 맞게 선택했을 때의 최대 합을 구하는 문제다.

	'deque'을 이용하여 동적 프로그래밍을 구현했다.
	"long long cache[idx]"에는 구간 "[0, idx]"의 최대 합이 저장된다.
	'deque'에는 인덱스가 저장되는데, 앞부분부터 배열을 순회하면서 인덱스가 단조 증가로 들어간다.

	구간 "[0, N)"의 모든 인덱스에 대해서 다음 과정을 수행한다.
	먼저 현재 인덱스와 "deque.front()"의 거리가 'D' 초과라면, 'D' 이하가 될 때까지 "deque.pop_front()"를 수행한다.
	위 과정을 수행하면 "deque.front()"는 다음 두 가지 의미가 있다.

	1. 구간 "[0, 현재 인덱스)"에서 최대 합에 가장 마지막으로 영향을 준 원소의 인덱스
	2. "cache[deque.front()]"는 구간 "[0, 현재 인덱스)"의 최대 합을 나타냄

	그러므로, "cache[deque.front()]"와 현재 원소를 더해서 "cache[현재 인덱스]"를 갱신한다.
	만약 "cache[deque.back()]"이 "cache[현재 인덱스]" 이하라면, 초과가 될 때까지 "deque.back()"를 빼낸다.
	"deque.back()"은 현재 인덱스보다 작고, 현재 인덱스가 대체할 수 있는 원소이기 때문이다.
*/

#include <deque>
#include <iostream>
#include <algorithm>

using namespace std;

constexpr int		MAX_N = 100000 + 1;
constexpr long long	INF = 4587654321987654321;

int			N, D;
int			bridge[MAX_N];
long long	cache[MAX_N];

void		init(void)
{
	cin >> N >> D;
	for (int i = 0; i < N; ++i)
		cin >> bridge[i];
	fill(cache, cache + N, -INF);
}

long long	solve(void)
{
	deque<int>	dq;
	long long	ret = -INF;

	for (int i = 0; i < N; ++i)
	{
		while (!dq.empty())
		{
			if (dq.front() < i - D)
				dq.pop_front();
			else
				break;
		}

		cache[i] = (dq.empty() || cache[dq.front()] < 0 ? 0 : cache[dq.front()]) + bridge[i];
		ret = max(cache[i], ret);

		while (!dq.empty())
		{
			if (cache[dq.back()] <= cache[i])
				dq.pop_back();
			else
				break;
		}
		dq.push_back(i);
	}
	return ret;
}

int			main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	init();
	cout << solve();
	return 0;
}
