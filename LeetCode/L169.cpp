/*
	Majority Element
	https://leetcode.com/problems/majority-element/

	주어진 배열에서 과반수를 찾는 문제다.

	"보이어-무어 과반수 투표" 알고리즘을 사용했다.
	'int candidate'로 과반수 후보를 지정한다.
	'size_t counts'는 'candidate'의 다른 수 대비 등장 횟수를 저장한다.

	주어진 배열의 구간 "[0, 배열 크기)"를 순차적으로 탐색한다.
	1. 'counts' == 0
		1) 현재 수를 'candidate'로 지정한다.
	2. 'counts' != 0
		1) 'candidate' == 현재 수
			'counts'를 1 증가시킨다.
		2) 'candidate' != 현재 수
			'counts'를 1 감소시킨다.
	탐색이 끝나면 'candidate'에는 과반수가 저장되어 있다.
	배열을 한 번만 탐색하기 때문에 위 과정의 시간 복잡도는 O(N)이다.
*/

class Solution
{
public:
    int majorityElement(vector<int>& nums)
    {
        int		candidate;
        size_t	counts = 0;

        for (size_t idx = 0; idx < nums.size(); ++idx)
            if (counts == 0)
            {
                candidate = nums[idx];
                counts = 1;
            }
            else
                counts += nums[idx] == candidate ? 1 : -1;
        return candidate;
    }
};