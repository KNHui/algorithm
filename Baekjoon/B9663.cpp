/*
	N-Queen
	https://www.acmicpc.net/problem/9663

	N이 입력으로 주어질 때, N-Queen을 만족하는 경우의 수를 구하는 문제다.

	현재 열의 모든 행에 퀸을 놓아보면서 N-Queen을 만족한다면,
	다음 열로 넘어가는 깊이 우선 탐색을 했다.

	N-Queen을 만족하는지 검사하는 것은 지나온 열에 있는 모든 퀸이
	같은 행 또는 기울기가 1 또는 -1인 대각선에 없다면 N-Queen을 만족한다.
*/
#include <iostream>

using namespace std;

int N;
int ans;
int board[15];

bool is_valid(int col)
{
	for (int i = 0; i < col; ++i)
		if (board[i] == board[col] || abs(board[i] - board[col]) == abs(i - col))
			return false;
	return true;
}

void dfs(int col)
{
	if (col == N)
	{
		++ans;
		return;
	}
    
	for (int row = 0; row < N; ++row)
	{
		board[col] = row;
		if (is_valid(col))
			dfs(col + 1);
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;
	dfs(0);
	cout << ans;
	return 0;
}