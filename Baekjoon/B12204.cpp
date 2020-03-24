/*
	Parentheses Order (Small)
	https://www.acmicpc.net/problem/12204

	괄호의 쌍 수와 사전상의 번호가 주어지면, 해당하는 괄호를 출력한다.

	동적 계획법을 사용하여 풀었다.
	'dp[o][c]'는 'o'개의 여는 괄호와 'c'개의 닫는 괄호가 있을 때, 만들 수 있는 경우의 수다.
	'dp[0][i]', 'dp[i][0]' (i = from 0 to 10) 는 섞을 수가 없으므로 '1'이다.

	같은 것이 있는 순열을 응용하면 dp[o][c]의 값을 구할 수 있을 줄 알았다.
	예를 들어 'dp[2][3]'일 때, 모든 경우의 수는 '5! / (3! * 2!)'가 나온다.
	모든 경우의 수에서 부분 수열을 빼면 될 줄 알았는데 예외 상황이 너무 많았다.
	그래서 'dp' 배열의 값을 표로 그려보니 다음과 같은 공식이 나왔다.
	1. o < c인 경우
		1) dp[o][c] = dp[o - 1][c] + dp[o][c - 1]
	2. o >= c인 경우
		1) dp[o][c] = dp[o - 1][c] 
	이를 활용하여, dp 배열을 완성했다.

	사전 상의 순서는 여는 괄호가 먼저 나오면 빨라진다.
	1. k > 0인 경우 다음 사항을 반복한다.
		1) dp[o][c] >= k인 경우, 자기보다 작은 조합으로 완성하기 위해 dp[o - 1][c]로 비교한다.
			a. dp[o - 1][c] >= k인 경우
				a) 현재 남은 괄호들을 사전 상으로 앞으로 당겨주기 위해 여는 괄호를 더한다.
				b) 여는 괄호를 하나 썼으므로 o = o - 1
			b. dp[o - 1][c] < k인 경우
				a) 괄호 한 쌍을 만들었기 때문에 사전 상의 번호 k에 작은 조합 dp[o - 1][c]의 수만큼 뺀다.
				   k = k - dp[o - 1][c]
				b) 현재 남은 괄호들을 사전 상으로 뒤로 밀어주기 위해 닫는 괄호를 더한다.
				c) 닫는 괄호를 하나 썼으므로 c = c - 1
		2) dp[o][c] < k인 경우
			a. k가 모든 경우의 수를 초과해서 불가능한 순번이다.
	2. k <= 0일 때
		1) 완성되었으므로 종료한다.
*/
#include <iostream>

using namespace std;

constexpr int MAX = 10 + 1;

int n, k;
int dp[MAX][MAX];

void init()
{
	for (size_t i = 0; i < MAX; i++)
	{
		dp[0][i] = 1;
		dp[i][0] = 1;
	}

	for (int i = 1; i < MAX; i++)
		for (int j = 1; j < MAX; j++)
			dp[i][j] = dp[i - 1][j] + (i < j ? dp[i][j - 1] : 0);
}

string solve(int pair, int order)
{
	string ret = "";
	int open = pair;
	int close = pair;

	while (k > 0)
	{
		if (dp[open][close] >= k)
		{
			if (open > 0 && dp[open - 1][close] >= k)
			{
				ret += '(';
				--open;
			}
			else
			{
				if (open > 0)
					k -= dp[open - 1][close];
				ret += ')';
				--close;
			}
		}
		else
		{
			return "Doesn't Exist!";
		}

		if (open <= 0 && close <= 0)
			return ret;
	}
	return ret;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int tc;
	cin >> tc;
	init();
	for (int tcn = 1; tcn <= tc; tcn++)
	{
		cin >> n >> k;
		cout << "Case #" << tcn << ": " << solve(n, k) << '\n';
	}
	return 0;
}