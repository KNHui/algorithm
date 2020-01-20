/*
	다리를 지나는 트럭
	https://programmers.co.kr/learn/courses/30/lessons/42583

	다 건넌 트럭의 인덱스를 벡터 end에 저장하고,
	end의 사이즈가 truck_weights의 사이즈와 같아질 때까지 다음 과정을 반복한다.

	먼저, 다리를 건너고 있는 트럭들의 거리를 1 증가시키고,
	다리를 건넌 트럭의 중량을 ing_weight에서 뺀다.
	이때, 다리를 가장 앞에서 건너는 트럭의 인덱스는 벡터 end의 사이즈와 같다.
	대기하고 있는 다음 트럭의 무게를 다리가 견딜 수 있다면,
	벡터 ing_dist와 ing_idx에 트럭의 무게와 인덱스를 추가한다.
	그리고 answer를 1 증가시킨다.
*/
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int solution(int bridge_length, int weight, vector<int> truck_weights)
{
    int answer = 0;
    int next = 0;
    int ing_weight = 0;
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
            ing_weight += truck_weights[next];

            ++next;
        }

        ++answer;
    }
    return answer;
}