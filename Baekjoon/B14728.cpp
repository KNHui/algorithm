/*
	벼락치기
	https://www.acmicpc.net/problem/14728

	백준 12865번 평범한 배낭과 같은 0-1 배낭 문제다.
	(https://github.com/KNHui/algorithm/blob/master/Baekjoon/B12865.cpp)
*/
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


int N, T;
int knap[101][10001];
vector<pair<int, int> > book;

void input()
{
	cin >> N >> T;
	book.resize(T + 1, { 0, 0 });
	for (int i = 1; i <= N; ++i)
	{
		int K, S;
		cin >> K >> S;
		book[i] = { K, S };
	}
}

void solve()
{
	for (int i = 1; i <= N; ++i)
		for (int j = 0; j <= T; ++j)
			if (book[i].first <= j)
				knap[i][j] = max(knap[i - 1][j], knap[i - 1][j - book[i].first] + book[i].second);
			else
				knap[i][j] = knap[i - 1][j];
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	input();
	solve();
	cout << knap[N][T];
	return 0;
}