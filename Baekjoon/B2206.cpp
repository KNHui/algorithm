/*
	벽 부수고 이동하기
	https://www.acmicpc.net/problem/2206

	BFS를 활용하여 최단 거리를 구했다.
	최단 거리에는 시작점과 도착점도 포함된다.

	벽을 1번 부술 수 있기에 중복 방문을 처리하는
	bool visit을 3차원으로 선언해서 벽을 부쉈는지도 저장하도록 만들었다.

	bfs 함수에서 다음 방문 장소인 (ny, nx)가
	도착점 (N - 1, M - 1) 이면 즉시 답을 리턴하도록 했다.
	이렇게 하면 큐에서 도착점을 꺼내기 전에 답을 좀 더 빨리 찾지만,
	시작점 (0, 0)이 도착점인 경우를 처리하지 못하므로,
	함수를 시작할 때 예외처리 했다.
*/
#include <queue>
#include <iostream>

using namespace std;

const int dy[4] = {1, 0, -1, 0};
const int dx[4] = {0, 1, 0, -1};

int N, M;
char map[1001][1001];
bool visit[2][1001][1001];

void input()
{
	cin >> N >> M;
	for (int i = 0; i < N; ++i)
		cin >> map[i];
}

int bfs()
{
	if (N - 1 == 0 && M - 1 == 0)
		return 1;
	queue<int> yq, xq, cq;
	queue<bool> wq;
	yq.push(0);
	xq.push(0);
	wq.push(0);
	cq.push(1);

	while (!yq.empty())
	{
		int y = yq.front();
		int x = xq.front();
		int cnt = cq.front();
		bool wall = wq.front();
		yq.pop();
		xq.pop();
		wq.pop();
		cq.pop();

		for (int i = 0; i < 4; ++i)
		{
			int ny = y + dy[i];
			int nx = x + dx[i];

			if (ny >= 0 && ny < N && nx >= 0 && nx < M)
				if (!visit[wall][ny][nx])
					if (map[ny][nx] == '0')
					{
						if (ny == N - 1 && nx == M - 1)
							return cnt + 1;
						yq.push(ny);
						xq.push(nx);
						cq.push(cnt + 1);
						wq.push(wall);
						visit[wall][ny][nx] = true;
					}
					else if (!wall)
					{
						if (ny == N - 1 && nx == M - 1)
							return cnt + 1;
						yq.push(ny);
						xq.push(nx);
						cq.push(cnt + 1);
						wq.push(!wall);
						visit[!wall][ny][nx] = true;
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