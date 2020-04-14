/*
	H-Index
	https://programmers.co.kr/learn/courses/30/lessons/42747

	citations�� ������������ �����ϰ�, 	citations�� �տ������� ��ȸ�ϸ鼭
	citations[i]�� answer���� ������ H ���� �̴��̹Ƿ� answer�� ���̰� Ž���� ����ϰ�,
	citations[i]�� answer���� ũ�� H ���� �����̹Ƿ� answer�� �����Ѵ�.
*/
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> citations)
{
    int answer = citations.size();
    sort(citations.begin(), citations.end());

    for (size_t i = 0; i < citations.size(); ++i)
    {
        if (citations[i] >= answer)
            break;
        else
            --answer;
    }
    return answer;
}