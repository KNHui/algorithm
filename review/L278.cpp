/*
	First Bad Version
	https://leetcode.com/problems/first-bad-version/

	제일 처음으로 등장한 bad version을 구하는 문제다.

	한 version이 bad version일 때, 그 뒤의 version도 모두 bad version이다.
	즉, version은 bad인 것과 아닌 것으로 정렬된 상태다.
	그래서 이분 탐색을 통해 제일 처음으로 등장한 bad version을 찾았다.
*/

class Solution
{
public:
    int firstBadVersion(int n)
    {
        int				mid;
        unsigned int	front = 0;
        unsigned int	rear = n;

        while (front <= rear)
        {
            mid = (front + rear) / 2;
            if (isBadVersion(mid))
                rear = mid - 1;
            else
                front = mid + 1;
        }
        return front;
    }
};