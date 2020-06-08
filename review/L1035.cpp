/*
	Uncrossed Lines
	https://leetcode.com/problems/uncrossed-lines/

	같은 숫자를 선으로 연결하면서 선이 교차되지 않도록 할 때, 최대 연결 횟수를 구하는 문제다.

	이 문제는 "최장 공통 부분 수열(LCS)" 문제다.
	선이 교차되지 않도록 하면서 연결하는 것은 숫자간의 상대적 위치를 지키는 것이다.
	그래서 이미 지나간 원소는 비교하지 않고, 현재의 원소와 이전의 길이를 가지고 'LCS'를 만들었다.
*/

class Solution
{
public:
    int maxUncrossedLines(vector<int>& A, vector<int>& B)
    {
        int cache[A.size() + 1][B.size() + 1];

        memset(cache, 0, sizeof(cache));
        for (size_t i = 1; i <= A.size(); ++i)
            for (size_t j = 1; j <= B.size(); ++j)
                if (A[i - 1] == B[j - 1])
                    cache[i][j] = cache[i - 1][j - 1] + 1;
                else
                    cache[i][j] = max(cache[i - 1][j], cache[i][j - 1]);
        return cache[A.size()][B.size()];
    }
};