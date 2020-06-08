/*
	다리를 지나는 트럭
	https://programmers.co.kr/learn/courses/30/lessons/42583

	다리를 건넌 트럭의 인덱스를 'vector<int> end'에 저장한다.
	'end'의 'size'가 'vector<int> truck_weights'의 'size'와 같아질 때까지 다음 과정을 반복한다.
	* 다리를 가장 앞에서 지나고 있는 트럭의 인덱스는 'end'의 'size'와 같다.
	1. 다리를 지나고 있는 트럭 처리
		1) 다리를 지나고 있는 트럭의 거리를 '1' 증가
		2) 트럭이 다리를 건넌 경우
			a. 다리를 건넌 트럭의 중량을 'int ing_weight'에서 뺀다.
			b. 'end'에 다리를 건넌 트럭의 인덱스를 'push_back'
	2. 맨 앞에서 대기하는 트럭 처리
		1) '맨 앞에서 대기하는 트럭의 무게 + ing_weight'가 'weight' 이하인 경우
			a. 맨 앞에서 대기하는 트럭 '1'만큼 전진
	3. answer 1 증가
*/

#include <string>
#include <vector>
#include <iostream>

using namespace std;

int solution(int bridge_length, int weight, vector<int> truck_weights)
{
	int			answer = 0;
	int			next = 0;
	int			ing_weight = 0;
	vector<int> ing_dist;
	vector<int> ing_idx;
	vector<int> end;

	while (end.size() < truck_weights.size())
	{
		for (size_t i = end.size(); i < ing_dist.size(); ++i)
		{
			++ing_dist[i];
			if (ing_dist[i] > bridge_length)
			{
				ing_weight -= truck_weights[ing_idx[i]];
				end.push_back(ing_idx[i]);
			}
		}
		if (ing_weight + truck_weights[next] <= weight)
		{
			ing_dist.push_back(1);
			ing_idx.push_back(next);
			ing_weight += truck_weights[next++];
		}
		++answer;
	}
	return answer;
}