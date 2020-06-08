/*
	Remove K Digits
	https://leetcode.com/problems/remove-k-digits/

	양의 정수 'num'이 문자열로 주어질 때, 문자 'k'개를 제거하여 만들 수 있는 최소 숫자를 구하는 문제다.

	'deque'을 이용해서 제거할 숫자들을 선별했다.
	높은 자릿수가 낮은 자릿수보다 영향이 많기 때문에 'num'의 앞 부분부터 탐색했다.

	1. num의 원소를 앞 부분부터 순회
		1) 'num'의 원소가 'deque'의 'back'보다 큼 && k > 0
			a) 'deque'의 'back'이 현재 원소 이하가 될 때까지 제거
		2) 'deque'의 'back'에 현재 원소 삽입
	2. 'deque'의 구간 "[first not zero index, dq.size() - k)"을 반환

	이 때, 'deque'의 전체 구간을 반환하지 않는다.
	그 이유는 앞 부분에서 의미가 없는 '0'을 제거하기 위함이다.
	뒷 부분은 'deque'이 오름차순으로 정렬된 경우 'k'가 남기 때문이다.
*/

#include <deque>
#include <iostream>

using namespace std;

class Solution
{
public:
	string removeKdigits(string num, int k)
	{
		string		answer;
		deque<char> dq;

		for (int i = 0; i < num.size(); ++i)
		{
			while (k && !dq.empty() && dq.back() > num[i])
			{
				dq.pop_back();
				--k;
			}
			dq.push_back(num[i]);
		}

		int start = 0;
		while (start < dq.size() && dq[start] == '0')
			++start;
		for (int i = start; i < dq.size() - k; ++i)
			answer += dq[i];
		return answer.empty() ? "0" : answer;
	}
};
