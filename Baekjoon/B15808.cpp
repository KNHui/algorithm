/*
	주말 여행 계획
	https://www.acmicpc.net/problem/15808

	[입력]
	int map[행][열]에 지도의 정보를 입력받고,
	다익스트라 알고리즘을 위해 모든 원소가 -987654321로 초기화된
	int dijkstra[번호]에 여행지의 기대치를 저장한다.
	그 다음 다익스트라 알고리즘을 사용한 후에 정답을 찾기 위해 숙소의 번호와 기대치를
	vector<pair<번호, 기대치>> rooms에 저장한다.

	장소의 번호들은 1부터 시작하기 때문에 for문에 사용하는 인덱스도 1 부터 n 까지 증가하도록 한다.

	[풀이]
	다익스트라 알고리즘을 사용하여, 출발점으로 사용되지 않았고,
	기대치가 가장 높은 장소의 번호를 출발점으로 사용하여,
	연결되어 있는 다른 장소의 기대치가 "출발점의 기대치 - 출발점과 다른 장소의 거리" 보다 작다면
	( dijkstra[다른 장소의 번호] < dijkstra[출발점의 번호] - map[다른 장소의 번호][출발점의 번호] )
	다른 장소의 기대치를 갱신해준다.

	더 이상 출발점으로 사용될 장소가 없을 경우,
	숙소의 번호에 갱신되어 있는 기대치와 입력받은 해당 숙소의 원래 기대치의 합이
	( dijkstra[rooms[i].first] + rooms[i].second )
	가장 큰 것을 ans에 저장하여 출력한다.
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