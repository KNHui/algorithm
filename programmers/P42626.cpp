/*
	더 맵게
	https://programmers.co.kr/learn/courses/30/lessons/42626

	우선순위 큐를 사용해서 모든 음식의 스코빌 지수가 K 이상이 될 때까지
	스코빌 지수가 가장 낮은 음식과 두 번째로 낮은 음식을 섞었다.
*/
#include <queue>
#include <vector>

using namespace std;

int mix(int first, int second)
{
	return first + second * 2;
}

int solution(vector<int> scoville, int K)
{
	int answer = 0;
	priority_queue<int, vector<int>, greater<int>> pq;
	for (size_t index = 0; index < scoville.size(); ++index)
		pq.push(scoville[index]);

	while (pq.size() >= 2 && pq.top() < K)
	{
		int first = pq.top();
		pq.pop();
		int second = pq.top();
		pq.pop();
		pq.push(mix(first, second));
		++answer;
	}

	if (pq.top() < K)
		return -1;
	return answer;
}