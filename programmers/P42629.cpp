/*
	라면공장
	https://programmers.co.kr/learn/courses/30/lessons/42629

	공급 일정이 남은 밀가루 수량 이하인 것 중에서 밀가루 수량이 가장 큰 것을 찾았다.
*/
#include <queue>
#include <vector>

using namespace std;

int solution(int stock, vector<int> dates, vector<int> supplies, int k)
{
	int answer = 0;
	int next = 0;
	priority_queue<int, vector<int>, less<int>> pq;

	while (stock < k)
	{
		for (int i = next; i < dates.size() && stock >= dates[i]; ++i)
		{
			pq.push(supplies[i]);
			next = i + 1;
		}
		stock += pq.top();
		pq.pop();
		++answer;
	}
	return answer;
}