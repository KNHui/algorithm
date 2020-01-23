/*
	가장 큰 정사각형
	https://www.acmicpc.net/problem/1915

	arr 배열의 왼쪽 위에서 오른쪽 아래로 내려가면서 이전에 탐색한 정보들을 활용한다.
	dp 배열에는 해당 인덱스를 오른쪽 아래 꼭짓점으로 하는 정사각형의 한 변의 길이가 담긴다.

	arr[i][j]에 1이 저장되어 있다면, dp 배열에서
	인덱스 (i - 1, j), (i, j - 1), (i - 1, j - 1)에
	저장된 값들의 최솟값에 1을 더한 값을 dp[i][j]에 저장한다.
	즉, 인덱스 (i, j)에서 dp[i][j]의 값을 한 변으로 하는 정사각형을 왼쪽 위로 그릴 수 있다는 것이다.
*/

#pragma warning(disable : 4996)
#include <iostream>
#include <algorithm>

using namespace std;

int n, m;
int arr[1001][1001];

int side;
int dp[1001][1001];

void input(void)
{
    string row;
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
    {
        cin >> row;
        for (int j = 0; j < m; ++j)
        {
            arr[i][j] = row[j] - 48;
            if (arr[i][j] == 1)
            {
                dp[i][j] = 1;
                side = 1;
            }
        }
    }
}

void solve(void)
{
    for (int i = 1; i < n; ++i)
    {
        for (int j = 1; j < m; ++j)
        {
            if (arr[i][j] == 1)
            {
                dp[i][j] = min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1;
                side = side < dp[i][j] ? dp[i][j] : side;
            }
        }
    }
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    input();
    solve();

    printf("%d", side * side);

    return 0;
}