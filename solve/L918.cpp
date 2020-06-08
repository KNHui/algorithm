/*
	Maximum Sum Circular Subarray
	https://leetcode.com/problems/maximum-sum-circular-subarray/

	원형으로 된 배열에서 최대 부분합을 구하는 문제다.

	'카데인 알고리즘'을 활용하여 문제를 풀었다.
	선형일 때는 카데인 알고리즘을 그래도 적용하면 답을 구할 수 있다.
	그러나 원형이기 때문에 'front'와 'rear'가 맞닿은 형태도 부분합에 포함된다.

	이를 처리하기 위해 배열의 최소 부분합을 구했다.
	'front'와 'rear'가 맞닿은 부분합의 최댓값은 배열의 누적 합에 최소 부분합을 뺀 값이기 때문이다.
	선형으로 된 배열의 최대 부분합과 'front'와 'rear'가 맞닿은 부분합 중 큰 값을 반환했다.
*/

class Solution
{
public:
	int getKadane(vector<int>& A)
	{
		int curr = A[0];
		int ret = A[0];

		for (size_t i = 1; i < A.size(); ++i)
		{
			curr = max(curr, 0) + A[i];
			ret = max(ret, curr);
		}
		return ret;
	}

	int maxSubarraySumCircular(vector<int>& A)
	{
		int negative_cnt = 0;
		for (size_t i = 0; i < A.size(); ++i)
			if (A[i] < 0)
				++negative_cnt;

		int kadane = getKadane(A);
		int sum = 0;
		for (size_t i = 0; i < A.size(); ++i)
		{
			sum += A[i];
			A[i] = -A[i];
		}
		int negative_kadane = getKadane(A);

		if (negative_cnt == A.size())
			return kadane;
		return max(kadane, sum + negative_kadane);
	}
};