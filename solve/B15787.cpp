/*
	기차가 어둠을 헤치고 은하수를
	https://www.acmicpc.net/problem/15787

	은하를 건널 수 있는 기차의 수를 구하는 문제다.

	은하를 건너려면 승객의 앉은 상태가 앞서 은하를 건넌 기차와 달라야한다.
	빠르게 승객의 앉은 상태를 비교하기 위해 비트 연산으로 명령을 수행했다.
	좌석은 20번째까지 있는데, 모든 좌석에 승객이 앉은 상태(2^20 - 1)에 2를 곱해도(2^21 - 2) int 형 범위를 벗어나지 않는다.
	그래서 승객이 앉은 상태를 배열의 인덱스로 사용할 수 있다.

	1 번 명령 :
		x 번째 비트만 1인 수와 OR 연산을 해서 x 번째 비트를 1로 만들었다.
	2 번 명령 :
		x 번째 비트만 0인 수와 AND 연산을 해서 x 번째 비트를 0으로 만들었다.
	3 번 명령 :
		쉬프트 연산으로 앉은 상태를 2배로 만들었다.
		그리고 '(1 << 20) - 1'과 AND 연산을 해서 범위가 벗어난 부분을 지웠다.
	4 번 명령 :
		쉬프트 연산으로 앉은 상태를 0.5배로 만들었다.
*/
#include <iostream>

using namespace std;

int N, M;
int train[100001];
bool visit[(1 << 20)];

int solve()
{
	for (int command_idx = 0; command_idx < M; ++command_idx)
	{
		int command, i, x;
		cin >> command >> i;
		switch (command)
		{
		case 1:
			cin >> x;
			train[i - 1] |= (1 << (x - 1));
			break;
		case 2:
			cin >> x;
			train[i - 1] &= ((1 << 20) - 1) - (1 << (x - 1));
			break;
		case 3:
			train[i - 1] <<= 1;
			train[i - 1] &= (1 << 20) - 1;
			break;
		case 4:
			train[i - 1] >>= 1;
			break;
		}
	}

	int cnt = 0;
	for (int idx = 0; idx < N; ++idx)
	{
		if (!visit[train[idx]])
		{
			++cnt;
			visit[train[idx]] = true;
		}
	}
	return cnt;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;
	cout << solve();
	return 0;
}