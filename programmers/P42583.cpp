/*
	�ٸ��� ������ Ʈ��
	https://programmers.co.kr/learn/courses/30/lessons/42583

	�� �ǳ� Ʈ���� �ε����� ���� end�� �����ϰ�,
	end�� ����� truck_weights�� ������� ������ ������ ���� ������ �ݺ��Ѵ�.

	����, �ٸ��� �ǳʰ� �ִ� Ʈ������ �Ÿ��� 1 ������Ű��,
	�ٸ��� �ǳ� Ʈ���� �߷��� ing_weight���� ����.
	�̶�, �ٸ��� ���� �տ��� �ǳʴ� Ʈ���� �ε����� ���� end�� ������� ����.
	����ϰ� �ִ� ���� Ʈ���� ���Ը� �ٸ��� �ߵ� �� �ִٸ�,
	���� ing_dist�� ing_idx�� Ʈ���� ���Կ� �ε����� �߰��Ѵ�.
	�׸��� answer�� 1 ������Ų��.
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