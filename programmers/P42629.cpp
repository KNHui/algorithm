/*
	라면공장
	https://programmers.co.kr/learn/courses/30/lessons/42629

	dates[index]가 stock 이하인 것 중에서 가장 큰 supplies[index]를 찾아서 공급의 최소 횟수를 구하는 문제다.

	가장 큰 supplies[index]를 찾는 방법으로 우선순위 큐를 사용했다.
	for 문을 수행하면서 dates[index]가 stock 이하면, supplies[index]를 우선순위 큐에 넣었다.
	이때, 다음 for 문의 시작 인덱스는 "index + 1"이 된다.
	왜냐하면, dates는 오름차순으로 정렬되어 있어서,
	이 전에 방문했던 인덱스들은 이미 우선순위 큐에 담겨있기 때문이다.
*/
#include <vector>
#include <queue>

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