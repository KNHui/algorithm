/*
	찾기
	https://www.acmicpc.net/problem/1786

	KMP 알고리즘을 사용하여 문자열 T에서 문자열 P가
	어느 위치에서 나타나는지 벡터 result에 저장하고,
	벡터 result의 사이즈와 요소들을 출력한다.

	이 때, 문제에서 인덱스는 1부터 시작하므로 result에 담기는 인덱스 값에 1을 더하여 저장한다.
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

string T, P;

void input()
{
	getline(cin, T);
	getline(cin, P);
}

void output(vector<int> &result)
{
	cout << result.size() << '\n';
	for (size_t i = 0; i < result.size(); ++i)
	{
		cout << result[i] << '\n';
	}
}

vector<int> getPartialMatch()
{
	size_t m = P.size();
	vector<int> pi(m, 0);

	int begin = 1, matched = 0;

	while (begin + matched < m)
	{
		if (P[begin + matched] == P[matched])
		{
			++matched;
			pi[begin + matched - 1] = matched;
		}
		else
		{
			if (matched == 0)
			{
				++begin;
			}
			else
			{
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}

	return pi;
}

vector<int> kmp()
{
	size_t n = T.size();
	size_t m = P.size();

	vector<int> result;
	vector<int> pi = getPartialMatch();

	int matched = 0;

	for (int i = 0; i < n; ++i)
	{
		while (matched > 0 && T[i] != P[matched])
		{
			matched = pi[matched - 1];
		}

		if (T[i] == P[matched])
		{
			++matched;
			if (matched == m)
			{
				result.push_back(i - m + 2);
				matched = pi[matched - 1];
			}
		}
	}

	return result;
}

void solve()
{
	vector<int> result = kmp();
	output(result);
}
int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	input();
	solve();

	return 0;
}