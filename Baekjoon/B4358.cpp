/*
	생태학
	https://www.acmicpc.net/problem/4358

	나무들이 주어졌을 때, 각 종의 비중을 구하는 문제다.

	각 종의 이름을 사전 순으로 출력해야 하므로 'map'을 사용했다.
*/
#include <map>
#include <string>
#include <iostream>

using namespace std;

int					total;
map<string, int>	dict;

void input()
{
	string ip;

	while (getline(cin, ip))
	{
		++total;
		++dict[ip];
	}
}

void solve()
{
	cout << fixed;
	cout.precision(4);
	for (auto tree : dict)
		cout << tree.first << ' ' << ((double)tree.second / (double)total * 100) << '\n';
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	input();
	solve();
	return 0;
}