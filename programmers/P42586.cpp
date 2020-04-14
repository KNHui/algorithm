/*
    ��ɰ���
	https://programmers.co.kr/learn/courses/30/lessons/42586

	�����ִ� �۾� �߿��� �켱������ ���� ���� �۾���
	������ ��� �ð��� ������� ������ ������ ����Ͽ� ���Ѵ�.
	�ش� �ð��� ������ ��, ���� �켱������ �۾����� �Ϸ�Ǿ����� Ž���ϸ鼭
	������ �� �ִ� �۾��� ���� answer ������ ���� �����Ѵ�.
*/
#include <string>
#include <vector>
using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds)
{
    vector<int> answer;
    int day = 0;

    for (size_t i = 0; i < progresses.size();)
    {
        int workload = 100 - (progresses[i] + day * speeds[i]);
        int work_time = workload / speeds[i];
        int remainder = workload % speeds[i];

        if (remainder > 0)
        {
            ++work_time;
        }
        day += work_time;

        int count = 0;
        while (i < progresses.size() && progresses[i] + day * speeds[i] >= 100)
        {
            ++count;
            ++i;
        }

        answer.push_back(count);
    }

    return answer;
}