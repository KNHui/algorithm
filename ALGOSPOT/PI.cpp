/*
	원주율 외우기
	https://www.algospot.com/judge/problem/read/PI

	수열이 주어질 때, 규칙으로 계산된 최소의 난이도를 구하는 문제다.

	"외발 뛰기" 문제처럼 "메모이제이션"을 사용했다.
	(https://github.com/KNHui/algorithm/blob/master/ALGOSPOT/JUMPGAME.cpp)

	"cache[idx]"는 "원주율 [idx, 마지막 인덱스]"로 얻을 수 있는 최소의 난이도를 저장한다.

	규칙에 따라 원주율을 세 글자, 네 글자, 다섯 글자 조각으로 만들어보면서 모든 경우를 시도한다.
	조각으로 만들 때는 가장 난이도가 적은 방법을 선택한다.
*/
#include <iostream>
#include <algorithm>

using namespace std;

constexpr int MAX = 10000 + 1;
constexpr int INF = 987654321;

int		cache[MAX];
string	pi;

void	init(void)
{
	cin >> pi;
	fill(cache, cache + MAX, -1);
}

bool	check_same(int start, int end)
{
	for (int i = start; i < end; i++)
		if (pi[i] != pi[i + 1])
			return false;
	return true;
}

bool	check_monotonic(int start, int end)
{
	int common_diff = pi[start] - pi[start + 1];
	if (abs(common_diff) != 1)
		return false;
	for (int i = start; i < end; i++)
		if (pi[i] - pi[i + 1] != common_diff)
			return false;
	return true;
}

bool	check_alternate(int start, int end)
{
	for (int i = start; i < end - 1; ++i)
		if (pi[i] == pi[i + 1] || pi[i] != pi[i + 2])
			return false;
	return true;
}

bool	check_progressive(int start, int end)
{
	int common_diff = pi[start] - pi[start + 1];
	for (int i = start + 1; i < end; ++i)
		if (pi[i] - pi[i + 1] != common_diff)
			return false;
	return true;
}

int		dfs(int idx)
{
	int& ret = cache[idx];
	if (ret != -1)
		return ret;
	if (idx == pi.size())
		return ret = 0;
	if (idx + 2 > pi.size())
		return ret = INF;

	ret = INF;
	for (int i = 2; i <= 4; ++i)
	{
		if (idx + i >= pi.size())
			break;
		if (check_same(idx, idx + i))
			ret = min(ret, dfs(idx + i + 1) + 1);
		else if (check_monotonic(idx, idx + i))
			ret = min(ret, dfs(idx + i + 1) + 2);
		else if (check_alternate(idx, idx + i))
			ret = min(ret, dfs(idx + i + 1) + 4);
		else if (check_progressive(idx, idx + i))
			ret = min(ret, dfs(idx + i + 1) + 5);
		else
			ret = min(ret, dfs(idx + i + 1) + 10);
	}
	return ret;
}


int		main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int c;
	cin >> c;
	for (int tcn = 1; tcn <= c; ++tcn)
	{
		init();
		cout << dfs(0) << '\n';
	}
	return 0;
}