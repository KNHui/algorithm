  
/*
	주식가격
	https://programmers.co.kr/learn/courses/30/lessons/42584

	주식가격이 내려가지 않은 기간을 구하는 문제다.

	1. 'size_t i'의 주식가격이 내려가지 않는 경우
		1) 'size_t j'는 구하려는 값보다 '1' 큰 상태이므로, 'vector<int> answer'에 'j - i - 1'을 'push_back'
	2. 'size_t i'의 주식가격이 내려간 경우
		1) 'answer'에 'j - i'를 'push_back'
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