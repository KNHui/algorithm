/*
	네트워크
	https://programmers.co.kr/learn/courses/30/lessons/43162
	
	BFS의 반환값을 answer에 더하는데,
	BFS로 탐색하면서 방문하지 않았던 컴퓨터가 나타난다면 1을 리턴하고,
	그렇지 않다면 새로운 네트워크가 아니므로 0을 리턴한다.
*/
#include <queue>
#include <string>
#include <vector>

using namespace std;

int bfs(int index, vector<vector<int>> &computers, vector<vector<bool>> &visits)
{
	bool isNew;
	queue<int> iq;

	isNew = false;
	iq.push(index);
	while (!iq.empty())
	{
		int i = iq.front();
		iq.pop();

		for (size_t j = 0; j < computers[i].size(); ++j)
		{
			if (!visits[i][j] && computers[i][j])
			{
				isNew = true;
				iq.push(j);
				visits[i][j] = true;
			}
		}
	}
	return isNew ? 1 : 0;
}

int solution(int n, vector<vector<int>> computers)
{
	int answer = 0;

	vector<bool> visit(n, false);
	vector<vector<bool>> visits(n, visit);
	for (int i = 0; i < n; ++i)
	{
		answer += bfs(i, computers, visits);
	}
	return answer;
}