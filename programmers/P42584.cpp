/*
	�ֽİ���
	https://programmers.co.kr/learn/courses/30/lessons/42584

	�ֽİ����� �������� �ʴ� �ð��� answer�� �����Ͽ� �����Ѵ�.

    �ε��� j�� �迭�� ��� ������ �ֽİ����� �������� �ʴ´ٸ�,
    j�� ���� ������ 1 ū �����̹Ƿ�, answer�� (j - i - 1)�� ��ƾ� �Ѵ�.
    �׷��� ���� ���� �ϰ� �Ǹ� �ֽİ����� �������� ��,
    answer�� 1 ���� ���� ���� ������ j�� 1 �������Ѿ� �Ѵ�.
*/

#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> prices)
{
    vector<int> answer;

    for (size_t i = 0; i < prices.size(); ++i)
    {
        size_t j;
        for (j = i + 1; j < prices.size(); ++j)
        {
            if (prices[i] > prices[j])
            {
                ++j;
                break;
            }
        }
        answer.push_back(j - i - 1);
    }
    return answer;
}