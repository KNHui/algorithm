/*
    Ÿ�� �ѹ�
    https://programmers.co.kr/learn/courses/30/lessons/43165

    DFS�� ���� �ε������� �������� ��,
    ���� Ÿ�� �ѹ��� ���ٸ� 1�� �����ϰ�,
    �ٸ��� 0�� �����ϸ鼭 ����� ���� �׾Ƴ�����.
*/
#include <string>
#include <vector>

using namespace std;

int dfs(int total, size_t index, vector<int> &numbers, int target)
{
    int plusCase;
    int minusCase;
    if (index == numbers.size())
    {
        if (total == target)
            return 1;
        else
            return 0;
    }
    plusCase = dfs(total + numbers[index], index + 1, numbers, target);
    minusCase = dfs(total - numbers[index], index + 1, numbers, target);
    return (plusCase + minusCase);
}

int solution(vector<int> numbers, int target)
{
    int answer = 0;
    answer = dfs(0, 0, numbers, target);
    return answer;
}