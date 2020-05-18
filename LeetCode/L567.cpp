/*
	Permutation in String
	https://leetcode.com/problems/permutation-in-string/

	'string s2'가 'string s1'의 순열을 포함하는지 확인하는 문제다.

	'map<char, int>	cnt'에 문자열 's1'의 글자들의 개수를 기록한다.

	 's1'의 글자가 's2'에 있고, 's2'의 순열을 만들기 위해 아직 필요한 글자라면, 'size_t prmtt_len'을 1 증가시킨다.
	 그렇게 's1'을 순회하면서 'prmtt_len'가 's2'의 길이와 같아질 때 'true'를 반환한다.

	 목표하는 순열의 길이는 's1'의 길이와 같아야 한다.
	 그래서 더는 순열에 담을 수 없는 글자들은 빼주면서 'prmtt_len'를 증가시켰다면, 'prmtt_len'을 1 감소시킨다.

	 만약 's1'을 모두 순회했다면 순열을 찾지 못했다는 것이므로 'false'를 반환한다.
*/

class Solution
{
public:
	bool checkInclusion(string s1, string s2)
	{
		if (s1.empty() && s2.empty())
			return true;
		if (s1.empty() || s2.empty())
			return false;
		int				left_idx = -1;
		size_t			prmtt_len = 0;
		map<char, int>	cnt;

		for (size_t i = 0; i < s1.size(); ++i)
			++cnt[s1[i]];
		for (size_t i = 0; i < s2.size(); ++i)
		{
			char curr = s2[i];
			if (cnt.find(curr) != cnt.end())
			{
				if (cnt[curr])
					++prmtt_len;
				--cnt[curr];
			}
			if (prmtt_len == s1.size())
				return true;
			if (i >= s1.size() - 1)
			{
				char left_char = s2[++left_idx];
				if (cnt.find(left_char) != cnt.end())
				{
					++cnt[left_char];
					if (cnt[left_char])
						--prmtt_len;
				}
			}
		}
		return false;
	}
};