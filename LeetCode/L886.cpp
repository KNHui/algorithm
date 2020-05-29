/*
	Possible Bipartition
	https://leetcode.com/problems/possible-bipartition/

	구간 "[1, N]"의 숫자들을 이분화할 수 있는지 구하는 문제다.

	모든 숫자를 기점으로 "깊이 우선 탐색"을 하면서 연결된 숫자를 탐색했다.
	그리고 탐색하면서 현재 숫자를 이전 숫자와 다른 그룹으로 나누었다.
	만약 서로 연결되어 있는 숫자가 같은 그룹에 있다면, 이분화할 수 없는 상태다.
*/

class Solution
{
private:
	vector<vector<int> >		_path;
	unordered_map<int, bool>	_grp;
public:
	bool isImpossible(int curr, bool grp)
	{
		if (_grp.find(curr) != _grp.end())
			return _grp[curr] != grp;
		_grp[curr] = grp;
		for (const auto& next : _path[curr])
			if (isImpossible(next, grp ^ true))
				return true;
		return false;
	}

	bool possibleBipartition(int N, vector<vector<int>>& dislikes)
	{
		_path.resize(N + 1);
		for (const auto& dislike : dislikes)
		{
			_path[dislike[0]].push_back(dislike[1]);
			_path[dislike[1]].push_back(dislike[0]);
		}
		for (size_t idx = 1; idx <= N; ++idx)
			if (_grp.find(idx) == _grp.end() && isImpossible(idx, false))
				return false;
		return true;
	}
};