/*
	Interval List Intersections
	https://leetcode.com/problems/interval-list-intersections/

	닫힌 구간을 원소로 가지는 두 배열이 주어질 때, 교차 구간을 반환하는 문제다.

	두 닫힌 구간이 있을 때, 한 구간의 끝나는 곳이 다른 구간에 포함되어 있다면 교차 구간이 존재한다.
	두 배열은 오름차순으로 정렬되어 있기 때문에 배열을 앞에서부터 탐색하면서 교차 구간이 있는지 확인한다.
	이 때, 더 일찍 끝나는 구간을 버리고, 다음 구간으로 넘어가면서 탐색한다.
*/

class Solution
{
public:
	bool isCross(vector<int>& A, vector<int>& B)
	{
		if (B[0] <= A[1] && A[1] <= B[1])
			return true;
		if (A[0] <= B[1] && B[1] <= A[1])
			return true;
		return false;
	}

	vector<vector<int> > intervalIntersection(vector<vector<int> >& A, vector<vector<int> >& B)
	{
		vector<vector<int> > ret;

		for (int i = 0, j = 0; i < A.size() && j < B.size(); A[i][1] < B[j][1] ? ++i : ++j)
		{
			if (isCross(A[i], B[j]))
			{
				int			start = max(A[i][0], B[j][0]);
				int			end = min(A[i][1], B[j][1]);
				vector<int>	tmp = { start, end };

				ret.push_back(tmp);
			}
		}
		return ret;
	}
};