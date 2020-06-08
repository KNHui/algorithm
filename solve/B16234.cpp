/*
	인구 이동
	https://www.acmicpc.net/problem/16234

	[전체 로직]
	1.	모든 좌표를 기점으로 하는 BFS를 돌면서,
		-1로 초기화되어 있는 2차원 int 배열 unionVisit에
		0부터 시작하는 그룹의 번호를 매겨 놓는다.
	2.	해당 그룹 번호의 인구 평균을 vector aver에 저장한다.
	3.	그룹 번호를 모두 매겼다면 그룹 번호가 -1이 아닌 지점에
		aver[그룹 번호]의 값으로 인구 이동을 진행한다.
	4.	인구 이동이 끝났다면 ans를 1 증가시킨다.
	5.	인구 이동이 일어나지 않았다면 solve 함수가 종료되고 ans를 출력한다.

	[국경이 열렸는지 판별하는 법]
	1.	BFS 함수는 bool 타입을 반환하는데 국경이 열렸는지 안 열렸는지를 확인한다.
		연합에 속한 나라의 수(cnt)가 1 초과가 아니라면, 국경이 열리지 않았으므로 false를 반환한다.
	2.	반환 값을 가지고 아래와 같은 연산을 하고,
 		(isOpen = isOpen ? isOpen : openBorder(i, j))
		한 번이라도 국경이 열렸다면 인구 이동을 진행하고 다시 국경이 열릴 수 있는지 BFS를 돈다.
		
	[int unionVisit[50][50]이 있는데 bool totalVisit[50][50]을 쓰는 이유]
 	1.	int 타입 비교보다 bool 타입 비교가 더 빠르기 때문에 사용하였고,
		정답을 구하는 속도가 4ms만큼 빨라졌다.
 	2.	메모리를 더 차지할 것이라 예상했으나, 의외로 2008KB로 똑같이 측정되었다.
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <queue>
using namespace std;

int dy[4] = {1, 0, -1, 0};
int dx[4] = {0, 1, 0, -1};

int N, L, R;
int map[50][50];

int ans, unionNum;
int unionVisit[50][50];
bool totalVisit[50][50];
vector<int> aver;

void input()
{
	cin >> N >> L >> R;
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			cin >> map[i][j];
		}
	}
}

bool openBorder(int ry, int rx)
{
	queue<int> pos;
	pos.push(ry * N + rx);
	int total = 0, cnt = 0;

	int y, x, ny, nx, i, diff;
	while (!pos.empty())
	{
		y = pos.front() / N;
		x = pos.front() % N;
		pos.pop();

		for (i = 0; i < 4; ++i)
		{
			ny = y + dy[i];
			nx = x + dx[i];

			if (ny >= 0 && ny < N && nx >= 0 && nx < N)
			{
				if (unionVisit[ny][nx] == -1)
				{
					diff = abs(map[y][x] - map[ny][nx]);
					if (diff >= L && diff <= R)
					{
						pos.push(ny * N + nx);
						unionVisit[ny][nx] = unionNum;
						totalVisit[ny][nx] = true;
						total += map[ny][nx];
						++cnt;
					}
				}
			}
		}
	}

	if (cnt > 1)
	{
		aver.push_back(total / cnt);
		++unionNum;
	}

	return cnt > 1;
}

void solve()
{
	int cnt = 0;
	bool isOpen;
	do
	{
		aver.clear();
		unionNum = 0;
		isOpen = false;

		for (int i = 0; i < N; ++i)
		{
			fill(totalVisit[i], totalVisit[i] + N, false);
			fill(unionVisit[i], unionVisit[i] + N, -1);
		}

		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				if (!totalVisit[i][j])
				{
					isOpen = isOpen ? isOpen : openBorder(i, j);
				}
			}
		}

		if (isOpen)
		{
			++cnt;
			for (int i = 0; i < N; ++i)
			{
				for (int j = 0; j < N; ++j)
				{
					if (unionVisit[i][j] != -1)
					{
						map[i][j] = aver[unionVisit[i][j]];
					}
				}
			}
		}

	} while (isOpen);

	ans = cnt;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	input();
	solve();

	cout << ans << '\n';

	//while (1) {}
	return 0;
}