/*
	�� �μ��� �̵��ϱ�
	https://www.acmicpc.net/problem/2206

	BFS�� Ȱ���Ͽ� �ִ� �Ÿ��� ���ߴ�.
	�ִ� �Ÿ����� �������� �������� ���Եȴ�.

	���� 1�� �μ� �� �ֱ⿡ �ߺ� �湮�� ó���ϴ�
	bool visit�� 3�������� �����ؼ� ���� �ν������� �����ϵ��� �������.

	bfs �Լ����� ���� �湮 ����� (ny, nx)��
	������ (N - 1, M - 1) �̸� ��� ���� �����ϵ��� �ߴ�.
	�̷��� �ϸ� ť���� �������� ������ ���� ���� �� �� ���� ã����,
	������ (0, 0)�� �������� ��츦 ó������ ���ϹǷ�,
	�Լ��� ������ �� ����ó�� �ߴ�.
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