/*
	���ٲ��� 5
	https://www.acmicpc.net/problem/17071

	�����̿� ������ ���� ���� ������ �ð��� ���ϴ� �����̴�.

	�������� ��ġ�� X���, �����̴� 1�� �ڿ� X - 1, X + 1, X * 2�� �̵��� �� �ִ�.
	��, �����̴� 2�� �ڿ� ���� �ִ� ��ġ�� �ٽ� �ǵ��ƿ� �� �ִ�.
	�̸� �̿��Ͽ�, �����̰� ¦�� �ð��� Ȧ�� �ð��� �湮�� ���� ���� ǥ���Ѵ�.
	�׸��� ������ ¦�� �ð��� �����̰� ¦�� �ð��� �湮�ߴ� ���� �����ϸ�,
	�����̿� ������ �ش� ¦�� �ð��� ���� �� �ִٴ� ���� �ȴ�.

	������ ������ ������ ������ �����̹Ƿ� ������ ǥ���� int An �� �����ϰ�,
	�ð��� �带 ������ ������ ��ġ�� An�� �����ش�.
	�����̴� �湮�ߴ� ��� ������ ����Ͽ� �湮���� �ʾҴ� ������ �̵��Ѵ�.
	�׷��ٰ� ������ �湮�� ��ġ�� �����̰� �湮�߾��� ��ġ���,
	�� ������ time�� ������ �ȴ�.
*/
#include <algorithm>
#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

constexpr auto MAX = 500000;

int N, K;
int ans;
int visitEven[MAX + 1];
int visitOdd[MAX + 1];

void setTime(int time, int idx)
{
    if (time % 2 == 0)
    {
        if (visitEven[idx] == -1)
            visitEven[idx] = time;
        else
            visitEven[idx] = visitEven[idx] > time ? time : visitEven[idx];
    }
    else
    {
        if (visitOdd[idx] == -1)
            visitOdd[idx] = time;
        else
            visitOdd[idx] = visitOdd[idx] > time ? time : visitOdd[idx];
    }
}

bool isVisit(int time, int idx)
{
    if (time % 2 == 0)
    {
        if (visitEven[idx] > time || visitEven[idx] == -1)
            return false;
        else
            return true;
    }
    else
    {
        if (visitOdd[idx] > time || visitOdd[idx] == -1)
            return false;
        else
            return true;
    }
}

void bfs()
{
    queue<int> subin;
    int bro = K;
    int An = 1; // ����
    int time = 0;
    subin.push(N);

    while (!subin.empty())
    {
        if (bro > MAX)
            return;
        if (isVisit(time, bro))
        {
            ans = time;
            return;
        }

        int size = subin.size();
        for (int i = 0; i < size; ++i)
        {
            int sx = subin.front();
            subin.pop();

            if (sx * 2 <= MAX && sx != 0 && !isVisit(time + 1, sx * 2))
            {
                subin.push(sx * 2);
                setTime(time + 1, sx * 2);
            }

            if (sx + 1 <= MAX && !isVisit(time + 1, sx + 1))
            {
                subin.push(sx + 1);
                setTime(time + 1, sx + 1);
            }

            if (sx - 1 >= 0 && !isVisit(time + 1, sx - 1))
            {
                subin.push(sx - 1);
                setTime(time + 1, sx - 1);
            }
        }
        bro += An;
        ++time;
        ++An;
    }
}

void init()
{
    cin >> N >> K;
    ans = -1;
    memset(visitOdd, -1, sizeof(visitOdd));
    memset(visitEven, -1, sizeof(visitEven));
}

void solve()
{
    if (N == K)
        ans = 0;
    else
        bfs();
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();
    cout << ans;
    return 0;
}