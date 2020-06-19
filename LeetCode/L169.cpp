/*
	Majority Element
	https://leetcode.com/problems/majority-element/

	주어진 배열에서 과반수를 찾는 문제다.

	'Boyer–Moore majority vote' 알고리즘을 사용했다.
	'int candidate'로 과반수 후보를 지정한다.
	'size_t counts'는 'candidate'의 다른 수 대비 등장 횟수를 저장한다.

	'candidate'와 'counts'를 갱신하면서 배열을 한 번만 순회한다.
	순회가 끝나게 된다면 'candidate'는 과반수를 담고 있다.
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