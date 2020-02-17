
/*
	키로거
	https://www.acmicpc.net/problem/5397

	주어진 입력에 따라 비밀번호를 유추하는 문제다.

	First In, Last Out 구조를 가진 스택을 사용하면, 나중에 입력된 문자를 연산자로 처리하여 문제를 풀 수 있다.
	커서의 위치를 이동하는 <, > 연산 때문에 두 개의 스택을 사용해야한다.
	커서가 이동할 때, 한 쪽 스택의 top을 다른 쪽 스택으로 넣어주면 된다.

	글자들을 읽는 순서대로 stack<char> inverse에 push한다.
	< 가 나오면 inverse의 top을 stack<char> direct에 push한다.
	> 가 나오면 direct의 top을 stack<char> inverse에 push한다.
	- 가 나오면 inverse의 top을 pop 한다.

	답을 출력할 때, inverse에 있는 값들을 스택의 순서에 맞게 순차적으로 direct에 넣어주고,
	direct의 값들을 순차적으로 출력할 스트링에 더해주면 된다.
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;

int tc;
vector<string> ip;
stack<char> inverse, direct;

void input()
{
	cin >> tc;

	for (int i = 1; i <= tc; ++i)
	{
		string tmp;
		cin >> tmp;
		ip.push_back(tmp);
	}
}

void solve()
{
	for (int i = 0; i < ip.size(); ++i)
	{
		for (int j = 0; j < ip[i].length(); ++j)
		{
			if (ip[i][j] == '<')
			{
				if (!inverse.empty())
				{
					direct.push(inverse.top());
					inverse.pop();
				}
			}
			else if (ip[i][j] == '>')
			{
				if (!direct.empty())
				{
					inverse.push(direct.top());
					direct.pop();
				}
			}
			else if (ip[i][j] == '-')
			{
				if (!inverse.empty())
				{
					inverse.pop();
				}
			}
			else
			{
				inverse.push(ip[i][j]);
			}
		}

		while (!direct.empty())
		{
			inverse.push(direct.top());
			direct.pop();
		}

		while (!inverse.empty())
		{
			direct.push(inverse.top());
			inverse.pop();
		}

		string op = "";
		while (!direct.empty())
		{
			op += direct.top();
			direct.pop();
		}

		cout << op << endl;
	}
}

int main()
{
	ios_base::sync_with_stdio(0);
	input();
	solve();
	return 0;
}