/*
	[2020카카오공채] 블록 이동하기
	https://programmers.co.kr/learn/courses/30/lessons/60063

	"2 x 1" 크기의 로봇을 좌표 (1, 1)에서부터 (N, N)까지 이동하는데 필요한 최소 시간을 구하는 문제다.

	로봇의 크기가 2칸을 차지한다.
	이를 처리하기 위해 'bool visit[MAX][MAX][2]' 배열을 3차원으로 선언했다.
	로봇이 가로로 있을 때는 로봇의 오른쪽이 'pair<int, int> front', 왼쪽이 'pair<int, int> back'이다.
	로봇이 세로로 있을 때는 로봇의 아랫쪽이 'pair<int, int> front', 윗쪽이 'pair<int, int> back'이다.
	위와 같이 하면 'front'를 기준으로 왼쪽이나 윗쪽에 'back'이 있는 2가지의 경우만 생긴다.
	그래서 가로인지 세로인지에 따라 'front'의 좌표만으로 방문 여부를 확인할 수 있다.

	로봇이 회전 하는 것을 처리하기 위해 회전할 때 사용하는 Direction array를 추가했다.
	회전할 때는 회전하면서 지나는 곳도 비어있는지 확인해야 한다.
	XOR 연산으로 1번만 등장하는 y좌표와 x좌표를 구해서 지나는 곳이 비어있는지 확인했다.
*/
#include <queue>
#include <string>
#include <vector>

using namespace std;

constexpr int MAX = 100 + 1;
constexpr int dy[4] = { 1, 0, -1, 0 };
constexpr int dx[4] = { 0, 1, 0, -1 };
constexpr int left_dy[4] = { 1, -1, 0, 0 };
constexpr int left_dx[4] = { 1, 1, 0, 0 };
constexpr int right_dy[4] = { 0, 0, 1, -1 };
constexpr int right_dx[4] = { 0, 0, -1, -1 };
constexpr int top_dy[4] = { 1, 1, 0, 0 };
constexpr int top_dx[4] = { 1, -1, 0, 0 };
constexpr int bottom_dy[4] = { 0, 0, -1, -1 };
constexpr int bottom_dx[4] = { 0, 0, 1, -1 };

int		N;
bool	visit[MAX][MAX][2];

bool check_goal(pair<int, int> yx)
{
	return yx.first == N - 1 && yx.second == N - 1;
}

bool check_range(pair<int, int> yx)
{
	return yx.first >= 0 && yx.first < N && yx.second >= 0 && yx.second < N;
}

bool check_empty(vector<vector<int>>& board, vector<pair<int, int> > yx, vector<pair<int, int> > nyx)
{
	pair<int, int> vertex = { 0, 0 };

	for (int i = 0; i < 2; i++)
	{
		if (board[nyx[i].first][nyx[i].second])
			return false;
		vertex.first ^= yx[i].first ^ nyx[i].first;
		vertex.second ^= yx[i].second ^ nyx[i].second;
	}
	if (vertex.first || vertex.second)
		if (check_range(vertex))
			if (board[vertex.first][vertex.second])
				return false;
	return true;
}

bool check_possible(vector<vector<int>>& board, vector<pair<int, int> > yx, vector<pair<int, int> > nyx)
{	
	if (check_range(nyx[0]) && check_range(nyx[1]))
		if (nyx[0].second == nyx[1].second)
		{
			if (!visit[nyx[0].first][nyx[0].second][0])
				if (check_empty(board, yx, nyx))
				{
					visit[nyx[0].first][nyx[0].second][0] = true;
					return true;
				}
		}
		else
		{
			if (!visit[nyx[0].first][nyx[0].second][1])
				if (check_empty(board, yx, nyx))
				{
					visit[nyx[0].first][nyx[0].second][1] = true;
					return true;
				}
		}
	return false;
}

int solution(vector<vector<int>> board)
{
	int						answer = 0;
	queue<int>				tq;
	queue<pair<int, int> >	fq, bq;

	N = board.size();
	tq.push(0);
	fq.push({ 0, 1 });
	bq.push({ 0, 0 });
	visit[0][1][1] = true;
	while (!fq.empty())
	{
		int				time = tq.front();
		pair<int, int>	f = fq.front();
		pair<int, int>	b = bq.front();

		if (check_goal(f))
			return time;
		tq.pop();
		fq.pop();
		bq.pop();
		for (int i = 0; i < 4; i++)
		{
			pair<int, int> nf = { f.first + dy[i], f.second + dx[i] };
			pair<int, int> nb = { b.first + dy[i], b.second + dx[i] };

			if (check_possible(board, { f, b }, { nf, nb }))
			{
				tq.push(time + 1);
				fq.push(nf);
				bq.push(nb);
			}

			if (f.first == b.first)
			{
				nf = { f.first + right_dy[i], f.second + right_dx[i] };
				nb = { b.first + left_dy[i], b.second + left_dx[i] };

				if (nf.first < nb.first || nf.second < nb.second)
					swap(nf, nb);
				if (check_possible(board, { f, b }, { nf, nb }))
				{
					tq.push(time + 1);
					fq.push(nf);
					bq.push(nb);
				}
			}
			if (f.second == b.second)
			{
				nf = { f.first + bottom_dy[i], f.second + bottom_dx[i] };
				nb = { b.first + top_dy[i], b.second + top_dx[i] };

				if (nf.first < nb.first || nf.second < nb.second)
					swap(nf, nb);
				if (check_possible(board, { f, b }, { nf, nb }))
				{
					tq.push(time + 1);
					fq.push(nf);
					bq.push(nb);
				}
			}
		}
	}
	return answer;
}