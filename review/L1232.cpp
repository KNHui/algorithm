/*
	Check If It Is a Straight Line
	https://leetcode.com/problems/check-if-it-is-a-straight-line/

	주어지는 점들을 이은 선이 직선인지 확인하는 문제다.

	첫 번째 점을 기준으로 잡고 모든 점과 기울기를 확인했다.
	기울기가 다른 점이 있다면 'false'를 반환하고, 모든 점과 기울기가 같다면 'true'를 반환했다.
*/

constexpr int INF = 987654321;

class Solution
{
public:
	bool checkStraightLine(vector<vector<int>>& coordinates)
	{
		const auto& criteria = coordinates[0];
		double		dx = criteria[0] - coordinates[1][0];
		double		dy = criteria[1] - coordinates[1][1];
		double		d = dy == 0 ? INF : dx / dy;
	
		for (int idx = 2; idx < coordinates.size(); ++idx)
		{
			const auto&	point = coordinates[idx];
			double		ndx = criteria[0] - point[0];
			double		ndy = criteria[1] - point[1];
			double		nd = ndy == 0 ? INF : ndx / ndy;

			if (d != nd)
				return false;
		}
		return true;
	}
};