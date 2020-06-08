/*
	타겟 넘버
	https://programmers.co.kr/learn/courses/30/lessons/43165
	
	DFS로 최종 인덱스까지 도달했을 때,
	값이 타겟 넘버와 같다면 1을 리턴하고,
	다르면 0을 리턴하면서 경우의 수를 쌓아나간다.
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