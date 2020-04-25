/*
	비대칭 타일링
	https://www.algospot.com/judge/problem/read/ASYMTILING

	"2 * 1" 크기의 타일로 채우는 비대칭 타일링 방법의 수를 구하는 문제다.

	"외발 뛰기" 문제처럼 "메모이제이션"을 사용했다.
	(https://github.com/KNHui/algorithm/blob/master/ALGOSPOT/JUMPGAME.cpp)
	"int cache[width]"는 "2 * width" 크기의 직사각형을 타일링하는 방법의 수를 저장한다.

	비대칭 타일링 방법의 수는 전체 경우의 수에서 대칭 타일링 방법의 수를 빼면 구할 수 있다.
	타일링이 대칭되는 경우는 3가지로 구분할 수 있다.
	1. 짝수 너비
		1) 정 가운데 부분의 너비 2만큼을 가로 타일 2개를 두고, 양쪽을 똑같이 타일링
		2) 정 가운데를 기준으로 왼쪽 부분을 타일링하고 오른쪽도 똑같이 타일링
	2. 홀수 너비
		1) 정 가운데에 세로 타일 1개를 두고, 양쪽을 똑같이 타일링

	"2 * width" 크기의 직사각형을 타일링하는 방법의 수는 다음 두 경우를 더해서 구할 수 있다.
	1. "2 * (width - 1)" 크기의 직사각형 오른쪽에 세로 타일 1개 두기
	2. "2 * (width - 2)" 크기의 직사각형 오른쪽에 가로 타일 2개 두기
	위의 두 경우로 점화식을 세우고, 깊이 우선 탐색으로 점화식을 구현했다.
	기저 영역은 'width'가 1 이하인 경우에는 1을 리턴하도록 했다.
*/
#include <iostream>

using namespace std;

constexpr int MAX_N = 100 + 1;
constexpr int MOD = 1000000007;

int	n;
int	cache[MAX_N];

void	init(void)
{
	cin >> n;
	fill(cache, cache + n + 1, -1);
}

int		tiling(int width)
{
	int& ret = cache[width];
	if (ret != -1)
		return ret;
	if (width <= 1)
		return ret = 1;

	return ret = (tiling(width - 1) + tiling(width - 2)) % MOD;
}

int		asym_tiling(int width)
{
	int ret = tiling(width);
	if (width % 2 == 1)
		return (ret - tiling((width - 1) / 2) + MOD) % MOD;
	
	ret = (ret - tiling(width / 2) + MOD) % MOD;
	ret = (ret - tiling((width - 2) / 2) + MOD) % MOD;
	return ret;
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
		cout << asym_tiling(n) << "\n";
	}
	return 0;
}