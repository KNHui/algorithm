/*
	Online Stock Span
	https://leetcode.com/problems/online-stock-span/

	주식 가격이 내려가지 않은 기간을 구하는 문제다.

	비슷한 유형의 "주식가격" 문제에서는 시간 복잡도 O(N^2)으로 풀었었다.
	(https://github.com/KNHui/algorithm/blob/master/programmers/P42584.cpp)
	스택을 사용하여 시간 복잡도 O(N)으로 풀이 방식을 개선했다.

	'int _day'는 오늘의 날짜, 'stack<int> _idx'는 인덱스로 쓰이는 날짜가 담긴다.

	인자로 넘겨받은 'int price'보다 낮거나 같은 가격을 가진 인덱스는 '_idx'에서 모두 빼낸다.
	그리고 '_day'에 '_idx.top()'을 빼서 가격이 내려가지 않은 기간을 구한다.
	만약 '_idx'가 비어있다면, 가격이 내려가지 않은 기간은 '_day + 1' 이다.
	'_day'는 인덱스로 사용돼서 0부터 시작하기 때문에 1을 더해주어야 올바른 기간이 나온다.
*/

class StockSpanner
{
private:
	int			_day;
	stack<int>	_idx;
	vector<int>	_prices;

public:
	StockSpanner()
	{
		_day = -1;
		_idx = stack<int>();
		_prices.clear();
	}
	
	int	next(int price)
	{
		int span;

		++_day;
		while(!_idx.empty() && price >= _prices[_idx.top()])
			_idx.pop();
		span = _idx.empty() ? _day + 1 : _day - _idx.top();
		_prices.push_back(price);
		_idx.push(_day);
		return span;
	}
};