/*
	Sort Characters By Frequency
	https://leetcode.com/problems/sort-characters-by-frequency/

	출현 빈도순으로 글자를 정렬하는 문제다.

	배열 'cnt'에 글자의 등장 횟수를 헤아리고, 내림차순으로 정렬했다.
	그리고 많이 등장한 글자부터 등장 횟수만큼 'string ret'에 붙여서 답을 구했다.
*/

class Solution
{
public:
	string	frequencySort(string s)
	{
		string					ret = "";
		vector<pair<int, int> > cnt(128);
		
		for (size_t i = 0; i < s.size(); ++i)
		{
			++cnt[s[i]].first;
			cnt[s[i]].second = s[i];
		}
		sort(cnt.rbegin(), cnt.rend());
		for (size_t i = 0; i < s.size() && cnt[i].first > 0; ++i)
		{
			for (size_t j = 0; j < cnt[i].first; ++j)
				ret += cnt[i].second;
		}
		return ret;
	}
};