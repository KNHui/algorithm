/*
    말이 되고픈 원숭이
    https://www.acmicpc.net/problem/1600

    BFS 알고리즘을 사용하는 그래프 탐색 문제다.
    
    상하좌우로 이동하는 원숭이는 'K'번만큼 체스의 나이트처럼 움직일 수 있다.
    그래서 나이트의 움직임을 담은 방향 배열을 선언하고, 원숭이의 방문을 기록하는 배열을 다음과 같이 선언했다.
    "bool visit[ y좌표 ][ x좌표 ][ n ]"
    이는 (y, x) 좌표에 갔을 때, 나이트처럼 'n' 번 움직였다는 것이다.
*/
#include <iostream>
#include <queue>

using namespace std;

const int dy[4] = {0, 0, 1, -1};
const int dx[4] = {1, -1, 0, 0};
const int kdy[8] = {2, 1, 2, -1, 1, -2, -1, -2};
const int kdx[8] = {1, 2, -1, 2, -2, 1, -2, -1};

int K, W, H;
int map[201][201];

int ans = -1;
bool visit[201][201][31];

void input()
{
    cin >> K >> W >> H;
    for (int i = 0; i < H; ++i)
    {
        for (int j = 0; j < W; ++j)
        {
            cin >> map[i][j];
        }
    }
}

void bfs()
{
    queue<int> yq, xq, cq, kq;
    yq.push(0);
    xq.push(0);
    cq.push(0);
    kq.push(0);

    int y, x, cnt, kCnt, ny, nx;
    while (!yq.empty())
    {
        y = yq.front();
        x = xq.front();
        cnt = cq.front();
        kCnt = kq.front();
        yq.pop(), xq.pop(), cq.pop(), kq.pop();

        if (y == H - 1 && x == W - 1)
        {
            ans = cnt;
            return;
        }

        // ��������
        for (int i = 0; i < 4; ++i)
        {
            ny = y + dy[i];
            nx = x + dx[i];
            if (ny >= 0 && nx >= 0 && ny < H && nx < W)
            {
                if (map[ny][nx] == 0)
                {
                    if (!visit[ny][nx][kCnt])
                    {
                        yq.push(ny);
                        xq.push(nx);
                        cq.push(cnt + 1);
                        kq.push(kCnt);
                        visit[ny][nx][kCnt] = true;
                    }
                }
            }
        }

        // �� ����
        if (kCnt < K)
        {
            for (int i = 0; i < 8; ++i)
            {
                ny = y + kdy[i];
                nx = x + kdx[i];
                if (ny >= 0 && nx >= 0 && ny < H && nx < W)
                {
                    if (map[ny][nx] == 0)
                    {
                        if (!visit[ny][nx][kCnt + 1])
                        {
                            yq.push(ny);
                            xq.push(nx);
                            cq.push(cnt + 1);
                            kq.push(kCnt + 1);
                            visit[ny][nx][kCnt + 1] = true;
                        }
                    }
                }
            }
        }
    }
}

void solve()
{
    bfs();
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    input();
    solve();

    cout << ans << '\n';
    return 0;
}