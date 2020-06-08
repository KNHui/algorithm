/*
	찾기
	https://www.acmicpc.net/problem/1786

	"KMP" 알고리즘으로 문자열 'T'에서 문자열 'P'가 어느 위치에서 나타나는지 구했다.
*/

#include <vector>
#include <string>
#include <iostream>

using namespace std;

string T, P;

void		input(void)
{
	getline(cin, T);
	getline(cin, P);
}

void		output(vector<int> &result)
{
	cout << result.size() << '\n';
	for (size_t i = 0; i < result.size(); ++i)
		cout << result[i] << '\n';
}

vector<int>	getPartialMatch(void)
{
	int			begin = 1;
	int			matched = 0;
	size_t		m = P.size();
	vector<int>	pi(m, 0);

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

void		kmp(vector<int> &result)
{
	int			matched = 0;
	size_t		n = T.size();
	size_t		m = P.size();
	vector<int>	pi = getPartialMatch();

	for (int i = 0; i < n; ++i)
	{
		while (matched > 0 && T[i] != P[matched])
			matched = pi[matched - 1];
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
}

void		solve(void)
{
	vector<int> result;

	kmp(result);
	output(result);
}

int			main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	input();
	solve();
	return 0;
}