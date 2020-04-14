/*
	�� ����
	https://www.acmicpc.net/problem/16197

	�� ���� �� �ϳ��� ���忡�� ����߸��� ���� ������ �ϴ� ��ư�� �ּ� Ƚ���� ���ϴ� �����̴�.

	BFS�� Ž���ϸ鼭, ���� ���ؾ� �ϴµ� ������ ���� ��Ȳ���� ó������� �Ѵ�.
	1. �� ������ ��� ������ ��Ȳ
	2. ���� �ϳ��� ������ ��Ȳ
	3. �� �� �������� ���� ��Ȳ

	1�� ��Ȳ
		�ϳ��� ����Ʈ���� �ϹǷ� continue �Ͽ� �ش� ��Ȳ�� �����Ѵ�.
	2�� ��Ȳ
		�ش� ��Ȳ���� ���� ���� Ƚ���� �����ϴµ�,
		�Ʒ� Ǯ�̿��� 10�� ������ ��Ȳ���� ���� ��Ȳ�� ���� �ϳ��� �������� 11�� �����ϴ� ��찡 �ִ�.
		�̸� ���Ͽ� ���� ���� 10���� ū ��� -1�� ��ȯ�Ѵ�.
	3�� ��Ȳ
		������ ���� ��ġ�� ť�� �־� �ִµ�, ���� ��ġ�� ���� ��� ���� ��ġ�� ť�� �ִ´�.
		�Ȱ��� ��Ȳ�� �ݺ����� �ʱ� ���Ͽ�, �� ������ �湮�� �����ϴ� visit �迭�� 4�������� �����Ѵ�.
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