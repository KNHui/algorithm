/*
	Jewels and Stones
	https://leetcode.com/problems/jewels-and-stones/

	문자열 'J'에 포함된 문자열 'S'의 글자 수를 구하는 문제다.

	문자열 'J'와 'S'는 알파벳 소문자와 대문자로 이루어져 있다.
	그래서 소문자는 [0, 26), 대문자는 [26, 52)로 변환해서 문자열 'J'에 있는 글자들을 표시했다.
	그 후, 문자열 'S'의 글자들을 하나씩 확인하면서 'J'에 포함되어 있는 글자 수를 구했다.
*/

class Solution
{
private:
	bool	isJewel[52];
public:
	int		toNum(char c)
	{
		if (c >= 'a')
			return c - 'a';
		return c - 'A' + ('z' - 'a' + 1);
	}

	int		numJewelsInStones(string J, string S)
	{
		int ret = 0;

		for (int idx = 0; idx < J.size(); ++idx)
			isJewel[toNum(J[idx])] = true;
		for (int idx = 0; idx < S.size(); ++idx)
			if (isJewel[toNum(S[idx])])
				++ret;
		return ret;
	}
};