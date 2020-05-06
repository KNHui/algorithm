/*
	Number Complement
	https://leetcode.com/problems/number-complement/

	'int num'의 1의 보수를 구하는 문제다.

	비트 연산을 위해 "int getLen(int num)" 함수에서 비트 길이를 구한다.
	그리고 'bitset'의 'flip' 함수를 이용하여 비트 길이만큼 비트를 반전시켰다.
*/
class Solution
{
public:
    int getLen(int num)
	{
        if (num == 0)
            return 1;
        int len = 0;

        while (num > 0)
        {
            num /= 2;
            ++len;
        }
        return len;
    }

    int findComplement(int num)
	{
        int			len = getLen(num);
        bitset<32>	bs(num);

        for (int i = 0; i < len; i++)
		{
            bs.flip(i);
        }
        return (int)(bs.to_ulong());
    }
};