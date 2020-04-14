/*
	�ָ� ���� ��ȹ
	https://www.acmicpc.net/problem/15808

	[�Է�]
	int map[��][��]�� ������ ������ �Է¹ް�,
	���ͽ�Ʈ�� �˰����� ���� ��� ���Ұ� -987654321�� �ʱ�ȭ��
	int dijkstra[��ȣ]�� �������� ���ġ�� �����Ѵ�.
	�� ���� ���ͽ�Ʈ�� �˰����� ����� �Ŀ� ������ ã�� ���� ������ ��ȣ�� ���ġ��
	vector<pair<��ȣ, ���ġ>> rooms�� �����Ѵ�.

	����� ��ȣ���� 1���� �����ϱ� ������ for���� ����ϴ� �ε����� 1 ���� n ���� �����ϵ��� �Ѵ�.

	[Ǯ��]
	���ͽ�Ʈ�� �˰����� ����Ͽ�, ��������� ������ �ʾҰ�,
	���ġ�� ���� ���� ����� ��ȣ�� ��������� ����Ͽ�,
	����Ǿ� �ִ� �ٸ� ����� ���ġ�� "������� ���ġ - ������� �ٸ� ����� �Ÿ�" ���� �۴ٸ�
	( dijkstra[�ٸ� ����� ��ȣ] < dijkstra[������� ��ȣ] - map[�ٸ� ����� ��ȣ][������� ��ȣ] )
	�ٸ� ����� ���ġ�� �������ش�.

	�� �̻� ��������� ���� ��Ұ� ���� ���,
	������ ��ȣ�� ���ŵǾ� �ִ� ���ġ�� �Է¹��� �ش� ������ ���� ���ġ�� ����
	( dijkstra[rooms[i].first] + rooms[i].second )
	���� ū ���� ans�� �����Ͽ� ����Ѵ�.
*/
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define MAX 1005
#define INF 987654321

int n;
int p, q, l, w;
int map[MAX][MAX];
int dijkstra[MAX];
bool visit[MAX];
vector<pair<int, int>> rooms;

void init()
{
    fill_n(&dijkstra[0], MAX, -INF);
    cin >> n;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> map[i][j];

    cin >> p >> q;
    for (int i = 0; i < p; i++)
    {
        cin >> l >> w;
        dijkstra[l] = w;
    }

    for (int i = 0; i < q; i++)
    {
        cin >> l >> w;
        rooms.push_back(make_pair(l, w));
    }
}

int find_next()
{
    int next = -1;
    int val = -INF;

    for (int i = 1; i <= n; i++)
        if (visit[i] == false && dijkstra[i] > val)
        {
            val = dijkstra[i];
            next = i;
        }
    return next;
}

int solve()
{
    int next = find_next();
    while (next != -1)
    {
        visit[next] = true;
        for (int i = 1; i <= n; i++)
            if (map[next][i] != 0 && dijkstra[i] < dijkstra[next] - map[next][i])
            {
                dijkstra[i] = dijkstra[next] - map[next][i];
            }
        next = find_next();
    }

    int ans = -INF;
    for (int i = 0; i < rooms.size(); i++)
        if (ans < dijkstra[rooms[i].first] + rooms[i].second)
            ans = dijkstra[rooms[i].first] + rooms[i].second;
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    int ans = solve();
    cout << ans << '\n';

    return 0;
}