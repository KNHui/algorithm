/*
	폴리오미노
	https://www.algospot.com/judge/problem/read/POLY

	'n'개의 사각형으로 세로로 단조인 폴리오미노의 수를 몇 개 만들 수 있는지 구하는 문제다.

	"외발 뛰기" 문제처럼 "메모이제이션"을 사용했다.
	(https://github.com/KNHui/algorithm/blob/master/ALGOSPOT/JUMPGAME.cpp)
	"int cache[rest][pre]"는 'rest'개의 정사각형이 남았고, 이전 층에 'pre'개의 정사각형을 썼을 때 만들 수 있는 세로 단조 폴리오미노 개수를 저장한다.

	세로로 단조인 폴리오미노는 각 높이에 가로로 연속된 직사각형이 1개씩 있고, 모든 직사각형이 연결된 상태다.  
	따라서, 각 높이에 "[1, rest]" 개의 정사각형을 사용해보고, 다음 높이로 넘어간다.  
	
	이전 층에 'pre'개의 정사각형을 쓰고, 이번 층에 'now'개의 정사각형을 썼다고 하자.
	이전 층의 직사각형과 이번 층의 직사각형을 조합해서 세로 단조 폴리오미노를 만드는 경우의 수는 다음과 같다.
	1. 이전 층의 맨 오른쪽 정사각형이 이번 층의 직사각형 위에 있는 경우의 수 = 'now'
	2. 이전 층의 맨 오른쪽 정사각형이 이번 층의 직사각형 오른쪽으로 삐져나간 경우의 수 = 'pre - 1'
	그래서 다음 층이 반환하는 경우의 수에 "now + pre - 1"를 곱한다.
*/
#include <iostream>
#include <algorithm>

using namespace std;

constexpr int MAX_N = 100 + 1;
constexpr int MOD = 10000000;

int	n;
int	cache[MAX_N][MAX_N];

void	init(void)
{
	cin >> n;
	for (int i = 0; i <= n; ++i)
		fill(cache[i], cache[i] + n + 1, -1);
}

int		poly(int rest, int pre)
{
	int& ret = cache[rest][pre];
	if (ret != -1)
		return ret;
	if (rest == 0)
		return ret = 1;
	
	ret = 0;
	for (int now = 1; now <= rest; ++now)
	{
		int cnt = (rest == 0) ? 1 : now + pre - 1;
		ret += (poly(rest - now, now) * cnt) % MOD;
	}
	return ret %= MOD;
}

int		main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int C;
	cin >> C;
	for (int tcn = 1; tcn <= C; ++tcn)
	{
		init();
		cout << poly(n, 0) << "\n";
	}
	return 0;
}