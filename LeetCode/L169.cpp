/*
	Majority Element
	https://leetcode.com/problems/majority-element/

	주어진 배열에서 과반수를 찾는 문제다.

	"보이어-무어 과반수 투표" 알고리즘을 사용했다.
	'int major'로 과반수를 지정한다.
	'size_t counts'는 'major'의 다른 수 대비 등장 횟수를 저장한다.

	주어진 배열의 구간 "[0, 배열 크기)"를 순차적으로 탐색한다.
	1. 'counts' == 0
		1) 현재 수를 'major'로 지정한다.
	2. 'counts' != 0
		1) 'major' == 현재 수
			'counts'를 1 증가시킨다.
		2) 'major' != 현재 수
			'counts'를 1 감소시킨다.
	위와 같은 과정을 통해 O(N)의 시간 복잡도로 답을 구할 수 있다.
*/

class Solution
{
public:
    int majorityElement(vector<int>& nums)
    {
        int		major;
        size_t	counts = 0;

        for (size_t idx = 0; idx < nums.size(); ++idx)
            if (counts == 0)
            {
                major = nums[idx];
                counts = 1;
            }
            else
                counts += nums[idx] == major ? 1 : -1;
        return major;
    }
};