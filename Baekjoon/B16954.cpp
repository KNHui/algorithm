/*
	�����̴� �̷� Ż��
	https://www.acmicpc.net/problem/16954

	BFS�� ����Ͽ� 7�� 0������ �����Ͽ�, 0�� 7���� �� �� �ִ��� �������� ����ϴ� �����̴�.
	
	ĳ���ʹ� �� ĭ���θ� �̵��� �� �ִµ�,
	������ �� ĭ �Ǵ� �밢�� �������� ������ �� ĭ���� �̵��ϰų�, ���� ��ġ�� �� ���� �� �ִ�.
	�׷��� ������ ��� �ִ� int dy[9] �� int dx[9] �� ���ڸ��� �����Ͽ� 9 ���� ������ ��ƾ� �Ѵ�.

	int visit[�� ��ǥ][�� ��ǥ] �� �ش� ��ǥ�� �湮 �ð��� ��� �ִ�.
	������ �ð��� ���� ��ҿ� �湮�ϴ� ���ʿ��� ������ ���ϰ�,
	�ٸ� �ð����� �湮�ߴ� ��ҿ� �� �� �ֵ��� �ϱ� ���Ͽ� visit �迭�� int ������ ���� �Ͽ���.

	ĳ���Ͱ� �̵��� �Ŀ� ���� �����̱� ������ queue<int> tq �� �ð��� �����ϰ�
	preTime�� ���� �ð��� �����Ͽ� �ð��� ����ϸ�, ���� �����δ�.
	�׸��� ĳ���Ͱ� ���� �� ��ġ�� �ִٸ�, continue�� �Ͽ� ť�� ���� ���ҷ� �Ѿ��.

    ũ�Ⱑ 8x8�� ���� ü���ǿ��� Ż���ϱ� ������ �ð��� ���� �ɸ��� ������,
    �����̶� ���� ���� ���ϱ� ���Ͽ�, noWallTime�� ���� ���� �ִ� ���� ������� �ð��� �����Ѵ�.
    �׸��� 0�� 7���� �������� �� �Ӹ� �ƴ϶�,
    ���� time�� noWallTime �̻��̶�� Ż���� �� �ִٰ� ǥ���ϰ� bfs �Լ��� �����Ѵ�.
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
int noWallTime; // ���� �� ������µ� �ɸ��� �ð�
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