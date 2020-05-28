/*
	Counting Bits
	https://leetcode.com/problems/counting-bits/

	구간 "[0, num]"의 모든 숫자에 대해 2진수에서 1의 수를 계산하는 문제다.

	진수는 이전에 사용했던 진수를 가져와서 똑같은 패턴으로 표현한다.
	단 한가지 달라지는 것은 가장 큰 비트에 1이 추가되는 것이다.
	그래서 자릿수가 증가할 때마다 '이전에 계산한 1의 수 + 1'을 배열에 새로 넣어주었다.
*/

class Solution
{
public:
    vector<int> countBits(int num)
    {
        vector<int> ret(1);
        
        for (size_t power = 1; ret.size() < num + 1; power <<= 1)
            for (size_t pre = 0; pre < power && ret.size() < num + 1; ++pre)
                ret.push_back(ret[pre] + 1);
        return ret;
    }
};