/*
	여행 짐 싸기
	https://www.algospot.com/judge/problem/read/PACKING

	가져갈 수 있는 물건들의 최대 절박도 합과 가져갈 물건들을 구하는 문제다.

	'배낭 알고리즘'을 이용해서 최대 절박도 합을 구했다.
	"int cache[idx][capacity]"는 용량이 'capacity'만큼 남았을 때, 구간 "[idx, N)"의 물건들로 얻을 수 있는 최대 절박도를 저장한다.

	최대 절박도 합뿐만 아니라 선택된 물건들의 개수와 이름도 출력해야 한다.
	'idx'번째 물건이 선택되었는지 확인하는 것은 다음과 같이 알 수 있다.
	1. "cache[idx][capacity] == cache[idx + 1][capacity]"
		'idx'가 없어도 최대 절박도는 변함이 없다.
		따라서, 'idx'는 선택되지 않았다.
	2. "cache[idx][capacity] != cache[idx + 1][capacity]"
		'idx'가 없으면 최대 절박도가 달라진다.
		따라서, 'idx'는 선택되었다.
*/
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

constexpr int MAX_N = 100 + 1;
constexpr int MAX_W = 1000 + 1;

int		N, W;
int		volume[MAX_N];
int		value[MAX_N];
int		cache[MAX_N][MAX_W];
string	name[MAX_N];

void	init(void)
{
   cin >> N >> W;
   for (int i = 0; i < N; ++i)
   {
	   cin >> name[i] >> volume[i] >> value[i];
	   fill(cache[i], cache[i] + W + 1, -1);
   }
}

int		pack(int idx, int capacity)
{
	if (idx == N)
		return 0;
	int& ret = cache[idx][capacity];
	if (ret != -1)
		return ret;
	
	ret = pack(idx + 1, capacity);
	int choose;
	if (capacity >= volume[idx])
		choose = pack(idx + 1, capacity - volume[idx]) + value[idx];
	return ret = max(ret, choose);
}

void	reconstruct(int idx, int capacity, vector<int>& picked)
{
	if (idx == N)
		return;

	if (pack(idx, capacity) == pack(idx + 1, capacity))
		reconstruct(idx + 1, capacity, picked);
	else
	{
		picked.push_back(idx);
		reconstruct(idx + 1, capacity - volume[idx], picked);
	}
}

void	output(vector<int>& picked)
{
	cout << pack(0, W) << ' ' << picked.size() << '\n';
	for (int i = 0; i < picked.size(); ++i)
		cout << name[picked[i]] << '\n';
}

int		main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int C;
	cin >> C;
	for (int tcn = 1; tcn <= C; tcn++)
	{
		vector<int> picked;
		init();
		reconstruct(0, W, picked);
		output(picked);
	}
	return 0;
}