/*
    ��Ʈ��ũ
    https://programmers.co.kr/learn/courses/30/lessons/43162

    BFS�� ��ȯ���� answer�� ���ϴµ�,
    BFS�� Ž���ϸ鼭 �湮���� �ʾҴ� ��ǻ�Ͱ� ��Ÿ���ٸ� 1�� �����ϰ�,
    �׷��� �ʴٸ� ���ο� ��Ʈ��ũ�� �ƴϹǷ� 0�� �����Ѵ�.
*/
#include <string>
#include <vector>
#include <queue>

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