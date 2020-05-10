/*
	Valid Perfect Square
	https://leetcode.com/problems/valid-perfect-square

	주어진 양의 정수 'int num'이 제곱수인지 확인하는 문제다.

	'num'의 64진수 1의 자리를 가지고 가지를 쳤다.
	두 수를 곱한 결과의 1의 자리 수는 원래 숫자의 1의 자리 수와 같다.
	10진수의 경우 제곱 수의 1의 자리는 "0, 1, 4, 5, 6, 9"로 6가지다.
	즉, 'num'의 1의 자리가 "2, 3, 7, 8"인 경우에는 제곱수가 아니라는 것이다.
	10진수의 경우 배제 비율이 '40%'인데, 64진수는 '81.25%'다.
	진수가 커질 수록 배제 비율은 늘어나는데, 128진수의 배제비율은 '82.03%'다.
	128진수는 64진수에 비해서 배제 비율 상승폭이 작어서 64진수로 가지치기를 했다.

	'num'의 64진수 1의 자리가 제곱수가 될 수 있는 경우에는 제곱 값이 'num' 이상인 정수를 찾았다.
	그 후 해당 정수의 제곱 값이 'num'과 같은지 비교했다.
*/

constexpr int BASENUM = 64;

class Solution
{
private:
    bool bBase[BASENUM];
public:
    void prepareToCheckSquare()
    {
        for (int i = 0; i < BASENUM; i++)
            bBase[i * i % BASENUM] = true;
    }
    
    bool isPerfectSquare(int num)
    {
        prepareToCheckSquare();
        if (bBase[(int)(num & (BASENUM - 1))])
        {
            long long sqrt;

            sqrt = 1;
            while (sqrt * sqrt < num)
                ++sqrt;
            return sqrt * sqrt == num;
        }
        else return false;
    }
};