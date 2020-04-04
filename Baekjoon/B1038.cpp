/*
	감소하는 수
	https://www.acmicpc.net/problem/1038

	N 번째 감소하는 수를 구하는 문제다.

	'10' 이상의 감소하는 수는 다음과 같은 규칙을 가지고 있다.
	"이전에 나온 수 * 10 + '이전에 나온 수의 일의 자리보다 작은 숫자'"
	그래서 0부터 9까지 큐에 넣고, 위의 규칙에 따라 다음 차례의 감소하는 수들을 구했다.
*/
#include <queue>
#include <iostream>

using namespace std;

int N;

long long solve()
{
	int					cnt = 0;
	queue<long long>	q;

	for (int i = 0; i < 10; ++i)
	{
		q.push((long long)i);
		if (cnt == N)
			return q.back();
		++cnt;
	}

	while (!q.empty())
	{
		long long num = q.front();
		int last = num % 10;
		q.pop();

		for (int i = 0; i < last; ++i)
		{
			q.push(num * 10 + (long long)i);
			if (cnt == N)
				return q.back();
			++cnt;
		}
	}
	return -1;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;
	cout << solve();
	return 0;
}