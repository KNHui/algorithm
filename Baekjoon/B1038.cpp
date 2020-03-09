/*
	감소하는 수
	https://www.acmicpc.net/problem/1038

	N 번째 감소하는 수를 구해야 하는데, 모든 자릿수를 비교하면 시간이 오래 걸린다.
	그런데 감소하는 수는 이전에 나온 수에 10을 곱하고 십의 자릿수보다 작은 숫자들을 일의 자리에 넣으면 완성된다.
	그래서 0부터 9까지 큐에 집어넣고, 다음 차례의 감소하는 수들을 구했다.
	cnt가 N과 같아지면 큐에 마지막으로 들어간 수를 출력했다.
*/
#include <queue>
#include <iostream>

using namespace std;

int N;

long long solve()
{
	int cnt = 0;
	queue<long long> q;

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
	long long ans = solve();
	cout << ans;
	return 0;
}