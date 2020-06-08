/*
	벽 부수고 이동하기 3
	https://www.acmicpc.net/problem/16933

	백준 14442번 벽 부수고 이동하기 2(http://bitly.kr/LOZYL3lo)와 유사한 문제다.
	
	다른 점은 움직일 때마다 밤과 낮이 바뀌는데, 낮에만 벽을 부술 수 있다.
	움직이지 않고 가만히 있는 것도 가능한데, 낮에는 벽을 부술 수 있기에 가만히 있는 움직임이 쓸모없다.
	그래서 밤에만 가만히 있도록 했고, visit의 차원을 늘려서 밤과 낮 중 언제 방문했는지도 표현했다.
*/
#include <queue>
#include <iostream>

using namespace std;

const int dy[5] = { 1, 0, -1, 0, 0 };
const int dx[5] = { 0, 1, 0, -1, 0 };

int N, M, K;
char map[1001][1001];
bool visit[2][11][1001][1001];

void input()
{
	cin >> N >> M >> K;
	for (int i = 0; i < N; ++i)
		cin >> map[i];
}

int bfs()
{
	if (0 == N - 1 && 0 == M - 1)
		return 1;
	queue<int> yq, xq, tq, cq;
	queue<bool> dq;
	yq.push(0);
	xq.push(0);
	tq.push(1);
	cq.push(0);
	dq.push(true);
	visit[1][0][0][0] = true;

	while (!yq.empty())
	{
		int y = yq.front();
		int x = xq.front();
		int time = tq.front();
		int cnt = cq.front();
		bool is_day = dq.front();
		yq.pop();
		xq.pop();
		tq.pop();
		cq.pop();
		dq.pop();
		for (int i = 0; i < 5; ++i)
		{
			int ny = y + dy[i];
			int nx = x + dx[i];
			if (i == 4 && is_day)
				continue;
			if (ny >= 0 && ny < N && nx >= 0 && nx < M)
			{
				if (ny == N - 1 && nx == M - 1)
					return time + 1;
				if (!visit[!is_day][cnt][ny][nx])
				{
					if (map[ny][nx] == '0' || i == 4)
					{
						yq.push(ny);
						xq.push(nx);
						tq.push(time + 1);
						cq.push(cnt);
						dq.push(!is_day);
						visit[!is_day][cnt][ny][nx] = true;
					}
					else if (cnt < K && is_day)
					{
						yq.push(ny);
						xq.push(nx);
						tq.push(time + 1);
						cq.push(cnt + 1);
						dq.push(!is_day);
						visit[!is_day][cnt + 1][ny][nx] = true;
					}
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