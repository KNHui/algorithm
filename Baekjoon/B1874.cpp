/*
	���� ����
	https://www.acmicpc.net/problem/1874
	
	������ �ϴ� ������ ����
	������ top �� �ִ� ������ �۴ٸ�
	���� �� ���� �����̴�.
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