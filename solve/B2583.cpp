/*
	영역 구하기
	https://www.acmicpc.net/problem/2583

	너비 우선 탐색으로 직사각형이 없는 영역의 넓이를 구했다.
*/
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;

constexpr int dy[4] = { 1, 0, -1, 0 };
constexpr int dx[4] = { 0, 1, 0, -1 };

int M, N, K;
bool map[100][100];
bool visit[100][100];
vector<int> area;

void init()
{
	cin >> M >> N >> K;
	for (int i = 0; i < K; ++i)
	{
		int left_x, right_x, btm_y, top_y;
		cin >> left_x >> btm_y >> right_x >> top_y;
		for (int row = btm_y; row < top_y; ++row)
		{
			for (int col = left_x; col < right_x; ++col)
			{
				map[row][col] = true;
			}
		}
	}
}

int bfs(int row, int col)
{
	int cnt;
	queue<int> yq, xq;

	cnt = 1;
	yq.push(row);
	xq.push(col);
	visit[row][col] = true;
	while (!yq.empty())
	{
		int y = yq.front();
		int x = xq.front();
		yq.pop();
		xq.pop();
		for (int i = 0; i < 4; ++i)
		{
			int ny = y + dy[i];
			int nx = x + dx[i];

			if (ny >= 0 && ny < M && nx >= 0 && nx < N)
			{
				if (map[ny][nx] == false && visit[ny][nx] == false)
				{
					++cnt;
					visit[ny][nx] = true;
					yq.push(ny);
					xq.push(nx);
				}
			}
		}
	}
	return cnt;
}

void solve()
{
	for (int row = 0; row < M; ++row)
	{
		for (int col = 0; col < N; ++col)
		{
			if (map[row][col] == false && visit[row][col] == false)
			{
				area.push_back(bfs(row, col));
			}
		}
	}
	sort(area.begin(), area.end());
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	init();
	solve();
	cout << area.size() << '\n';
	for (size_t i = 0; i < area.size(); ++i)
	{
		cout << area[i] << ' ';
	}
	return 0;
}