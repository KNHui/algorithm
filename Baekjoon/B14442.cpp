/*
	벽 부수고 이동하기 2
	https://www.acmicpc.net/problem/14442

	백준 2206번 벽 부수고 이동하기(http://bitly.kr/UAvGSFqP)와 유사한 문제다.

	벽을 부술 수 있는 횟수가 1 번에서 K 번으로 달라졌다.
	그래서 bool 타입으로 벽을 부쉈는지 판단하던 것을 int 타입으로 수정했다.
*/
#include <queue>
#include <iostream>

using namespace std;

const int dy[4] = { 1, 0, -1, 0 };
const int dx[4] = { 0, 1, 0, -1 };

int N, M, K;
char map[1001][1001];
bool visit[11][1001][1001];

void input()
{
	cin >> N >> M >> K;
	for (int i = 0; i < N; ++i)
		cin >> map[i];
}

int bfs()
{
	if (0 == N - 1&& 0 == M - 1)
		return 1;
	queue<int> yq, xq, tq, cq;
	yq.push(0);
	xq.push(0);
	tq.push(1);
	cq.push(0);
	visit[0][0][0] = true;

	while (!yq.empty())
	{
		int y = yq.front();
		int x = xq.front();
		int time = tq.front();
		int cnt = cq.front();
		yq.pop();
		xq.pop();
		tq.pop();
		cq.pop();

		for (int i = 0; i < 4; ++i)
		{
			int ny = y + dy[i];
			int nx = x + dx[i];
			if (ny >= 0 && ny < N && nx >= 0 && nx < M)
			{
				if (ny == N - 1 && nx == M - 1)
					return time + 1;
				if (!visit[cnt][ny][nx])
					if (map[ny][nx] == '0')
					{
						yq.push(ny);
						xq.push(nx);
						tq.push(time + 1);
						cq.push(cnt);
						visit[cnt][ny][nx] = true;
					}
					else if (cnt < K)
					{
						yq.push(ny);
						xq.push(nx);
						tq.push(time + 1);
						cq.push(cnt + 1);
						visit[cnt + 1][ny][nx] = true;
					}
			}
		}
	}
	return -1;
}

int solve()
{
	int ret = bfs();
	return ret;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	input();
	int ans = solve();
	cout << ans;
	return 0;
}