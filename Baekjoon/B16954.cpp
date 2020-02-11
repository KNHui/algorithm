/*
	움직이는 미로 탈출
	https://www.acmicpc.net/problem/16954

	BFS를 사용하여 7행 0열에서 시작하여, 0행 7열로 갈 수 있는지 없는지를 출력하는 문제이다.
	
	캐릭터는 빈 칸으로만 이동할 수 있는데,
	인접한 한 칸 또는 대각선 방향으로 인접한 한 칸으로 이동하거나, 현재 위치에 서 있을 수 있다.
	그래서 방향을 담고 있는 int dy[9] 와 int dx[9] 에 제자리를 포함하여 9 가지 방향을 담아야 한다.

	int visit[행 좌표][열 좌표] 는 해당 좌표의 방문 시간을 담고 있다.
	동일한 시간에 같은 장소에 방문하는 불필요한 연산을 피하고,
	다른 시간에는 방문했던 장소에 갈 수 있도록 하기 위하여 visit 배열을 int 형으로 선언 하였다.

	캐릭터가 이동한 후에 벽이 움직이기 때문에 queue<int> tq 에 시간을 저장하고
	preTime에 이전 시간을 저장하여 시간이 경과하면, 벽을 움직인다.
	그리고 캐릭터가 현재 벽 위치에 있다면, continue를 하여 큐의 다음 원소로 넘어간다.

    크기가 8x8인 작은 체스판에서 탈출하기 때문에 시간은 오래 걸리지 않으나,
    조금이라도 빨리 답을 구하기 위하여, noWallTime에 가장 높이 있는 벽이 사라지는 시간을 저장한다.
    그리고 0행 7열에 도착했을 때 뿐만 아니라,
    현재 time이 noWallTime 이상이라면 탈출할 수 있다고 표시하고 bfs 함수를 종료한다.
*/
#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

constexpr int MAP_SIZE = 8;
constexpr int dy[9] = {1, 0, 1, 0, -1, 1, -1, 0, -1};
constexpr int dx[9] = {1, 1, 0, 0, 1, -1, 0, -1, -1};

bool isPossible;
int noWallTime; // 벽이 다 사라지는데 걸리는 시간
int map[MAP_SIZE][MAP_SIZE];
int visit[MAP_SIZE][MAP_SIZE];

void init()
{
    isPossible = false;
    noWallTime = 0;

    char ip;
    for (int i = 0; i < MAP_SIZE; ++i)
    {
        for (int j = 0; j < MAP_SIZE; ++j)
        {
            visit[i][j] = -1;
            cin >> ip;
            if (ip == '.')
                map[i][j] = 0;
            else
            {
                map[i][j] = 1;
                noWallTime = noWallTime < MAP_SIZE - i ? MAP_SIZE - i : noWallTime;
            }
        }
    }
}
void moveWall()
{
    int nextMap[MAP_SIZE][MAP_SIZE];
    for (int j = 0; j < MAP_SIZE; ++j)
        nextMap[0][j] = 0;

    for (int i = 0; i < MAP_SIZE - 1; ++i)
        for (int j = 0; j < MAP_SIZE; ++j)
            if (map[i][j] == 0)
                nextMap[i + 1][j] = 0;
            else
                nextMap[i + 1][j] = 1;

    memcpy(map, nextMap, sizeof(nextMap));
}

void bfs()
{
    queue<pair<int, int>> q;
    queue<int> tq;
    q.push(make_pair(7, 0));
    tq.push(0);
    visit[7][0] = 0;

    int preTime = 0;
    while (!q.empty())
    {
        int y = q.front().first;
        int x = q.front().second;
        int time = tq.front();
        q.pop();
        tq.pop();

        if (preTime + 1 == time)
        {
            moveWall();
            ++preTime;
        }

        if (map[y][x] == 1)
            continue;

        if ((y == 0 && x == 7) || noWallTime <= time)
        {
            isPossible = true;
            return;
        }

        for (int i = 0; i < 9; ++i)
        {
            int ny = y + dy[i];
            int nx = x + dx[i];

            if (ny >= 0 && ny < MAP_SIZE && nx >= 0 && nx < MAP_SIZE)
            {
                if (visit[ny][nx] != time + 1 && map[ny][nx] == 0)
                {
                    q.push(make_pair(ny, nx));
                    tq.push(time + 1);
                    visit[ny][nx] = time + 1;
                }
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    bfs();
    cout << (isPossible ? 1 : 0) << '\n';

    return 0;
}