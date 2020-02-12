/*
	숨바꼭질 5
	https://www.acmicpc.net/problem/17071

	수빈이와 동생이 가장 빨리 만나는 시간을 구하는 문제이다.

	수빈이의 위치가 X라면, 수빈이는 1초 뒤에 X - 1, X + 1, X * 2로 이동할 수 있다.
	즉, 수빈이는 2초 뒤에 현재 있는 위치로 다시 되돌아올 수 있다.
	이를 이용하여, 수빈이가 짝수 시간과 홀수 시간에 방문한 것을 따로 표시한다.
	그리고 동생이 짝수 시간에 수빈이가 짝수 시간에 방문했던 곳에 도착하면,
	수빈이와 동생은 해당 짝수 시간에 만날 수 있다는 것이 된다.

	동생은 계차가 등차인 수열로 움직이므로 계차를 표현할 int An 을 선언하고,
	시간이 흐를 때마다 동생의 위치에 An을 더해준다.
	수빈이는 방문했던 모든 곳에서 출발하여 방문하지 않았던 곳으로 이동한다.
	그러다가 동생이 방문한 위치가 수빈이가 방문했었던 위치라면,
	그 순간의 time이 정답이 된다.
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
    int An = 1; // 계차
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