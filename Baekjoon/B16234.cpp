/*
	�α� �̵�
	https://www.acmicpc.net/problem/16234

	[��ü ����]
	1.	��� ��ǥ�� �������� �ϴ� BFS�� ���鼭,
		-1�� �ʱ�ȭ�Ǿ� �ִ� 2���� int �迭 unionVisit��
		0���� �����ϴ� �׷��� ��ȣ�� �Ű� ���´�.
	2.	�ش� �׷� ��ȣ�� �α� ����� vector aver�� �����Ѵ�.
	3.	�׷� ��ȣ�� ��� �Ű�ٸ� �׷� ��ȣ�� -1�� �ƴ� ������
		aver[�׷� ��ȣ]�� ������ �α� �̵��� �����Ѵ�.
	4.	�α� �̵��� �����ٸ� ans�� 1 ������Ų��.
	5.	�α� �̵��� �Ͼ�� �ʾҴٸ� solve �Լ��� ����ǰ� ans�� ����Ѵ�.

	[������ ���ȴ��� �Ǻ��ϴ� ��]
	1.	BFS �Լ��� bool Ÿ���� ��ȯ�ϴµ� ������ ���ȴ��� �� ���ȴ����� Ȯ���Ѵ�.
		���տ� ���� ������ ��(cnt)�� 1 �ʰ��� �ƴ϶��, ������ ������ �ʾ����Ƿ� false�� ��ȯ�Ѵ�.
	2.	��ȯ ���� ������ �Ʒ��� ���� ������ �ϰ�,
 		(isOpen = isOpen ? isOpen : openBorder(i, j))
		�� ���̶� ������ ���ȴٸ� �α� �̵��� �����ϰ� �ٽ� ������ ���� �� �ִ��� BFS�� ����.

	[int unionVisit[50][50]�� �ִµ� bool totalVisit[50][50]�� ���� ����]
 	1.	int Ÿ�� �񱳺��� bool Ÿ�� �񱳰� �� ������ ������ ����Ͽ���,
		������ ���ϴ� �ӵ��� 4ms��ŭ ��������.
 	2.	�޸𸮸� �� ������ ���̶� ����������, �ǿܷ� 2008KB�� �Ȱ��� �����Ǿ���.
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