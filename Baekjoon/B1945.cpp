/*
	���� ū ���簢��
	https://www.acmicpc.net/problem/1915

	arr �迭�� ���� ������ ������ �Ʒ��� �������鼭 ������ Ž���� �������� Ȱ���Ѵ�.
	dp �迭���� �ش� �ε����� ������ �Ʒ� ���������� �ϴ� ���簢���� �� ���� ���̰� ����.

	arr[i][j]�� 1�� ����Ǿ� �ִٸ�, dp �迭����
	�ε��� (i - 1, j), (i, j - 1), (i - 1, j - 1)��
	����� ������ �ּڰ��� 1�� ���� ���� dp[i][j]�� �����Ѵ�.
	��, �ε��� (i, j)���� dp[i][j]�� ���� �� ������ �ϴ� ���簢���� ���� ���� �׸� �� �ִٴ� ���̴�.
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