/*
	두 동전
	https://www.acmicpc.net/problem/16197

	두 동전 중 하나만 보드에서 떨어뜨리기 위해 눌러야 하는 버튼의 최소 횟수를 구하는 문제이다.

	BFS로 탐색하면서, 답을 구해야 하는데 다음과 같은 상황들을 처리해줘야 한다.
	1. 두 동전이 모두 떨어진 상황
	2. 동전 하나만 떨어진 상황
	3. 둘 다 떨어지지 않은 상황

	1번 상황
		하나만 떨어트려야 하므로 continue 하여 해당 상황은 무시한다.
	2번 상황
		해당 상황까지 가기 위한 횟수를 리턴하는데,
		아래 풀이에선 10번 움직인 상황에서 다음 상황이 동전 하나만 떨어져서 11을 리턴하는 경우가 있다.
		이를 위하여 리턴 값이 10보다 큰 경우 -1을 반환한다.
	3번 상황
		동전의 다음 위치를 큐에 넣어 주는데, 다음 위치가 벽인 경우 현재 위치를 큐에 넣는다.
		똑같은 상황을 반복하지 않기 위하여, 두 동전의 방문을 저장하는 visit 배열을 4차원으로 선언한다.
*/
#include <queue>
#include <iostream>

using namespace std;

const int dy[4] = {1, 0, -1, 0};
const int dx[4] = {0, 1, 0, -1};

int N, M;
char map[21][21];

bool visit[21][21][21][21];
pair<int, int> coin[2];

void init()
{
    cin >> N >> M;
    coin[0] = {-1, -1};
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
        {
            cin >> map[i][j];
            if (map[i][j] == 'o')
            {
                if (coin[0].first == -1)
                    coin[0] = {i, j};
                else
                    coin[1] = {i, j};
                map[i][j] = '.';
            }
        }
}

bool square_is_wall(const pair<int, int> &square)
{
    return (map[square.first][square.second] == '#');
}

bool pos_is_out(const pair<int, int> &pos)
{
    return (pos.first < 0 || pos.first >= N || pos.second < 0 || pos.second >= M);
}

int bfs()
{
    queue<pair<int, int>> fq, sq;
    queue<int> cq;

    fq.push(coin[0]);
    sq.push(coin[1]);
    cq.push(0);

    while (!fq.empty())
    {
        pair<int, int> first = fq.front();
        pair<int, int> second = sq.front();
        int count = cq.front();
        fq.pop();
        sq.pop();
        cq.pop();
        if (count > 10)
            return -1;

        pair<int, int> nfirst;
        pair<int, int> nsecond;
        for (int i = 0; i < 4; ++i)
        {
            nfirst.first = first.first + dy[i];
            nfirst.second = first.second + dx[i];
            nsecond.first = second.first + dy[i];
            nsecond.second = second.second + dx[i];
            if (pos_is_out(nfirst) && pos_is_out(nsecond))
                continue;
            else if (pos_is_out(nfirst) || pos_is_out(nsecond))
                return count + 1;
            else
            {
                if (square_is_wall(nfirst))
                    nfirst = first;
                if (square_is_wall(nsecond))
                    nsecond = second;
                if (!visit[nfirst.first][nfirst.second][nsecond.first][nsecond.second])
                {
                    fq.push(nfirst);
                    sq.push(nsecond);
                    cq.push(count + 1);
                    visit[nfirst.first][nfirst.second][nsecond.first][nsecond.second] = true;
                }
            }
        }
    }
    return -1;
}

int solve()
{
    int result = bfs();
    if (result > 10)
        return -1;
    return result;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    int answer = solve();
    cout << answer << '\n';
    return 0;
}