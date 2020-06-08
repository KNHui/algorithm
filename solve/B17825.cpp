#include <deque>
#include <stack>
#include <vector>
#include <iostream>

using namespace std;

constexpr int BOARD_SIZE = 33;

int				ans;
vector<int>		dice(10);
vector<int>		board(BOARD_SIZE);

void init(void)
{
	for (int i = 0; i < 10; ++i)
		cin >> dice[i];
	for (int i = 1; i < BOARD_SIZE - 1; i++)
	{
		if (i < 20)
			board[i] = i * 2;
		else if (i >= 20 && i <= 22)
			board[i] = board[5] + (i - 20 + 1) * 3;
		else if (i >= 23 && i <= 24)
			board[i] = board[10] + (i - 23 + 1) * 2;

		else if (i >= 25 && i <= 28)
			board[i] = board[15] - 2 - (i - 25);
		else
			board[i] = board[28] + (i - 28) * 5;
	}
}

void modify_pos(int& pos, int move)
{
	int next = pos + move;

	switch (pos)
	{
	case 5:
		pos = (20 - 1) + move;
		if (pos > 22)
			pos = (28 - 1) + pos - 22;
		break;
	case 10:
		pos = (23 - 1) + move;
		if (pos > 24)
			pos = (28 - 1) + pos - 24;
		break;
	case 15:
		pos = (25 - 1) + move;
		break;
	default:
		int next = pos + move;

		if (pos <= 19 && next > 19)
			next = (31 - 1) + next - 19;
		else if (pos <= 22 && next > 22)
			next = (28 - 1) + next - 22;
		else if (pos <= 24 && next > 24)
			next = (28 - 1) + next - 24;
		else if (pos <= 27 && next > 27)
			next = (28 - 1) + next - 27;
		pos = next > 32 ? 32 : next;
		break;
	}
}

int simul(deque<pair<int, int> >& comb)
{
	int			score = 0;
	stack<int>	st[BOARD_SIZE];
	vector<int> knight(4);

	for (int i = 0; i < 4; ++i)
		st[0].push(i);
	for (size_t i = 0; i < comb.size(); ++i)
	{
		int		knight_idx = comb[i].first;
		int		dice_idx = comb[i].second;
		int&	knight_pos = knight[knight_idx];
		int		pre = knight_pos;

		modify_pos(knight_pos, dice[dice_idx]);
		if (knight_pos == 32 || st[knight_pos].empty())
		{
			st[pre].pop();
			score += board[knight_pos];
			st[knight_pos].push(knight_idx);
		}
		else
			return -1;
	}
	return score;
}

void dfs(deque<pair<int, int> >& comb, vector<int>& cnt, int dice_idx)
{
	if (dice_idx == 10)
	{
		for (size_t i = 1; i < cnt.size(); i++)
			if (cnt[i - 1] < cnt[i])
				return;
		int result = simul(comb);

		ans = ans < result ? result : ans;
		return;
	}

	for(size_t knight_idx = 0; knight_idx < 4; ++knight_idx)
	{ 
		++cnt[knight_idx];
		if (knight_idx == 0 || cnt[knight_idx - 1] + 9 - dice_idx >= cnt[knight_idx])
		{
			comb.push_back({ knight_idx, dice_idx });
			dfs(comb, cnt, dice_idx + 1);
			comb.pop_back();
		}
		--cnt[knight_idx];
	}
}

void solve(void)
{
	vector<int>				cnt(4);
	deque<pair<int, int> >	comb;

	dfs(comb, cnt, 0);
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	init();
	solve();
	cout << ans;
	return 0;
}