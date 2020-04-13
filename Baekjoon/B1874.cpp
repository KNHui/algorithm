/*
	스택 수열
	https://www.acmicpc.net/problem/1874
	
	1부터 'N'까지의 수를 순서대로 넣을 수 있는 스택이 있다.
	이 스택으로 입력으로 주어지는 수열을 만드는 데 필요한 연산의 순서를 구하는 문제다.

	스택에서 가져와야 하는 수를 'num'이라 하자.
	스택에 연산할 때마다 출력을 위한 큐에 '+' 또는 '-'를 넣는다.
	'num'이 'N'이 될 때까지 다음 과정을 반복한다.
	1. 'num'이 스택의 'top'보다 큰 경우
		1) 'num'을 가져오기 위해 스택의 'top'이 'num'과 같아질 때까지 'push'한다.
		2) 'push' 연산을 했으므로, 큐에 '+'를 넣는다.
	2. 'num'이 스택의 'top'과 같은 경우
		1) 스택을 'pop' 해서 'num'을 가져온다.
		2) 'pop' 연산을 했으므로, 큐에 '-'를 넣는다.
	3. 'num'이 스택의 'top'보다 작은 경우
		1) 만들 수 없는 수열이므로, 'NO'를 출력한다.
*/

#include <stack>
#include <queue>
#include <iostream>

using namespace std;

constexpr int MAX_N = 100000 + 1;

int			N;
int			sqnc[MAX_N];
stack<int>	stc;
queue<char>	ans;

void	input(void)
{
	cin >> N;
	for (int i = 0; i < N; ++i)
	{
		cin >> sqnc[i];
	}
}

void	output(void)
{
	while (!ans.empty())
	{
		cout << ans.front() << '\n';
		ans.pop();
	}
}

void	push(int num)
{
	stc.push(num);
	ans.push('+');
}

void	pop(void)
{
	stc.pop();
	ans.push('-');
}

void	solve(void)
{
	int num = 1;
	int sqnc_idx = 0;

	while (sqnc_idx != N)
	{
		if (stc.empty())
			push(num++);

		if (stc.top() < sqnc[sqnc_idx])
		{
			while (stc.top() != sqnc[sqnc_idx])
				push(num++);
		}
		else if (stc.top() == sqnc[sqnc_idx])
		{
			pop();
			++sqnc_idx;
		}
		else
		{
			cout << "NO";
			return;
		}
	}
	output();
}

int		main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	input();
	solve();
	return 0;
}