/*
	등산로
	https://algospot.com/judge/problem/read/MORDOR

	주어진 구간의 최소 해발 고도와 최대 해발 고도를 구하는 문제다.
	구간 최소 트리를 사용하여 각 구간의 최소 해발 고도를 저장했다.
	해발 고도에 '-1'을 곱하면, 구간 최소 트리로 각 구간의 최대 해발 고도를 구할 수 있다.
*/
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAX = numeric_limits<int>::max();

struct RMQ
{
    int			n;
    vector<int>	rangeMin;

    RMQ(const vector<int> &array)
    {
        n = array.size();
        rangeMin.resize(n * 4);
        init(array, 0, n - 1, 1);
    }

    int init(const vector<int> &array, int left, int right, int node)
    {
        if (left == right)
            return rangeMin[node] = array[left];

        int mid = (left + right) / 2;
        int leftMin = init(array, left, mid, node * 2);
        int rightMin = init(array, mid + 1, right, node * 2 + 1);
        return rangeMin[node] = min(leftMin, rightMin);
    }

    int query(int left, int right, int node, int nodeLeft, int nodeRight)
    {
        if (right < nodeLeft || nodeRight < left)
            return MAX;
        if (left <= nodeLeft && nodeRight <= right)
            return rangeMin[node];

        int mid = (nodeLeft + nodeRight) / 2;
        return min(query(left, right, node * 2, nodeLeft, mid), query(left, right, node * 2 + 1, mid + 1, nodeRight));
    }

    int query(int left, int right)
    {
        return query(left, right, 1, 0, n - 1);
    }

    int update(int index, int newValue, int node, int nodeLeft, int nodeRight)
    {
        if (index < nodeLeft || nodeRight < index)
            return rangeMin[node];
        if (nodeLeft == nodeRight)
            return rangeMin[node] = newValue;

        int mid = (nodeLeft + nodeRight) / 2;
        return rangeMin[node] = min(update(index, newValue, node * 2, nodeLeft, mid), update(index, newValue, node * 2 + 1, mid + 1, nodeRight));
    }

    int update(int index, int newValue)
    {
        return update(index, newValue, 1, 0, n - 1);
    }
};

void solve(int N, int Q)
{
    vector<int>	height;
    vector<int>	minusHeight;
    for (int j = 0; j < N; ++j)
    {
        int h;
        cin >> h;
        height.push_back(h);
        minusHeight.push_back(h * -1);
    }
    RMQ rmq(height);
    RMQ minusRmq(minusHeight);
    for (int i = 0; i < Q; ++i)
    {
        int start, finish;
        cin >> start >> finish;
        int low = rmq.query(start, finish);
        int high = abs(minusRmq.query(start, finish));
        cout << high - low << '\n';
    }
}

int main(void)
{
    int tc;
    cin >> tc;
    for (int i = 0; i < tc; ++i)
    {
        int N, Q;
        cin >> N >> Q;
        solve(N, Q);
    }
    return 0;
}
