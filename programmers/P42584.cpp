/*
	주식가격
	https://programmers.co.kr/learn/courses/30/lessons/42584

	주식가격이 내려가지 않는 시간을 answer에 저장하여 리턴한다.

    인덱스 j가 배열을 벗어날 때까지 주식가격이 내려가지 않는다면,
    j는 원래 값보다 1 큰 상태이므로, answer에 (j - i - 1)을 담아야 한다.
    그러나 위와 같이 하게 되면 주식가격이 내려갔을 때,
    answer에 1 작은 값이 담기기 때문에 j를 1 증가시켜야 한다.
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