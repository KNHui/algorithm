/*
    기능개발
	https://programmers.co.kr/learn/courses/30/lessons/42586

	남아있는 작업 중에서 우선순위가 가장 높은 작업이
	배포에 드는 시간을 나누기와 나머지 연산을 사용하여 구한다.
	해당 시간이 지났을 때, 다음 우선순위의 작업들이 완료되었는지 탐색하면서
	배포될 수 있는 작업의 수를 answer 벡터의 끝에 저장한다.
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