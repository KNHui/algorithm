/*
	달팽이
	https://algospot.com/judge/problem/read/SNAIL

	달팽이가 우물을 탈출할 수 있을 확률을 구하는 문제다.

	"외발 뛰기" 문제처럼 "메모이제이션"을 사용했다.
	(https://github.com/KNHui/algorithm/blob/master/ALGOSPOT/JUMPGAME.cpp)

	"cache[day][hgt]"는 'day'일 후에 'hgt'미터만큼 올라왔을 때, 탈출 확률이다.
	비가 올 때는 '0.75'를 곱하고, 맑은 날일 때는 '0.25'를 곱해서 확률을 계산했다.
*/
#include <iostream>

using namespace std;

constexpr int MAX_N = 1000 + 1;
constexpr int MAX_M = 1000 + 1;
constexpr int INF = 987654321;

int		n, m;
double	cache[MAX_M][MAX_N + 1];

void	init(void)
{
	cin >> n >> m;
	for (size_t i = 0; i <= m; i++)
		fill(cache[i], cache[i] + n + 2, -1);
}

double	climb(int day, int hgt)
{
	double& ret = cache[day][hgt];
	if (ret != -1)
		return ret;
	if (day == m)
		return ret = hgt >= n ? 1 : 0;

	double rain = climb(day + 1, hgt + 2) * 0.75;
	double sunny = climb(day + 1, hgt + 1) * 0.25;
	return ret = rain + sunny;
}

int		main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.precision(10);

	int C;
	cin >> C;
	for (int tcn = 1; tcn <= C; ++tcn)
	{
		init();
		cout << fixed << climb(0, 0) << "\n";
	}
	return 0;
}