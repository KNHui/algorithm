/*
	스택 수열
	https://www.acmicpc.net/problem/1874
	
	만들어야 하는 수열의 수가
	스택의 top 에 있는 수보다 작다면
	만들 수 없는 수열이다.
*/

#include <iostream>
#include <stack>
#include <queue>

using namespace std;

int N;
int sqnc[100001];

stack<int> stc;
queue<char> ans;

void input()
{
	cin >> N;
	for (int i = 0; i < N; ++i)
	{
		cin >> sqnc[i];
	}
}

void output()
{
	while (!ans.empty())
	{
		cout << ans.front() << '\n';
		ans.pop();
	}
}

void push(int num)
{
	stc.push(num);
	ans.push('+');
}

void pop()
{
	stc.pop();
	ans.push('-');
}

void solve()
{
	int num = 1;
	int sqncIdx = 0;

	while (sqncIdx != N)
	{
		if (stc.empty())
		{
			push(num++);
		}

		if (stc.top() < sqnc[sqncIdx])
		{
			while (stc.top() != sqnc[sqncIdx])
			{
				push(num++);
			}
		}
		else if (stc.top() == sqnc[sqncIdx])
		{
			pop();
			++sqncIdx;
		}
		else
		{
			cout << "NO";
			return;
		}
	}

	output();
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	input();
	solve();

	return 0;
}