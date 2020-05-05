/*
	Ransom Note
	https://leetcode.com/problems/ransom-note/

	문자열 'magazine'에 있는 글자로 문자열 'ransomNote'를 만들 수 있는지 확인하는 문제다.

	처음에는 'magazine'의 모든 글자별 개수를 'int cnt[26]'에 세고, 'ransomNote'에 있는 글자로 'cnt'의 값을 1 줄였다.
	그리고 'cnt'의 값이 음수가 되면 'false'를 반환하고, 'ransomNote' 탐색이 끝난 경우에는 'true'를 반환했다.
	속도는 '38ms'가 나왔다.

	그런데, 'magazine'의 글자를 다 확인하는 것을 개선할 수 있을 것 같았다.
	'ransomNote'의 글자는 무조건 모두 확인해야 하므로, 먼저 'ransomNote'의 모든 글자별 개수를 세었다.
	그리고 'magazine'을 탐색하면서 'ransomNote'에 남아있는 글자라면 'size_t total'의 값을 1 증가시켰다.
	만약 탐색 도중 'total'의 값이 'ransomNote'의 길이와 같아진다면 'true'를 반환했다.
	'magazine'을 모두 탐색하지 않게 되니 속도는 '24ms'가 나왔다.
*/

class Solution {
private:
	int     cnt[26];
    size_t	total;
public:
    int toNum(char c) {
        return c - 'a';
    }

    bool	canConstruct(string ransomNote, string magazine) {
        for (size_t idx = 0; idx < ransomNote.length(); ++idx) {
            int num = toNum(ransomNote[idx]);

            ++cnt[num];
        }

        for (size_t idx = 0; idx < magazine.length(); ++idx) {
            int num = toNum(magazine[idx]);

            --cnt[num];
            if (cnt[num] >= 0) {
                ++total;
                if (total == ransomNote.size())
                    return true;
            }
        }

        return total == ransomNote.size() ? true : false;
    }
};