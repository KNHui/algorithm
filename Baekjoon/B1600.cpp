/*
    ���� �ǰ��� ������
    https://www.acmicpc.net/problem/1600

    �Ϲ����� �׷��� Ž�� �����̱⿡ BFS �˰������� ����ϸ� �ȴ�.
    
    �׷��� �����¿�� �̵��ϴ� �����̴� K����ŭ ü���� ����Ʈó�� ������ �� �ִ�.
    �׷��� �湮�� ǥ���ϴ� visit �迭�� ������ ���� �����Ͽ�
    (y, x) ��ǥ�� ���� ��, ����Ʈó�� �� �� ���������� ����Ѵ�.
    bool visit[ y��ǥ ][ x��ǥ ][ K ];

    �׷� ���� ����Ʈ�� �������� ���� �迭 kdy, kdx�� �����ϰ�,
    ����Ʈó�� �� �� ������������ ť kq�� �����Ͽ� ������ �ذ��Ͽ���.
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