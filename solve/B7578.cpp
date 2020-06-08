/*
	공장
	https://www.acmicpc.net/problem/7578

	A 열의 원소가 순서가 섞여서 B 열에 있고, 같은 값의 원소를 케이블로 연결했을 때,
	서로 교차하는 케이블 쌍의 개수를 구하는 문제다.

	A 열의 번호로 B 열의 번호를 방문하고,
	B 열의 번호 오른쪽에 있는 번호 중에서 이전에 방문한 번호의 수를 ret 에 더해주고,
	누적 합 ret 를 출력하는 Inversion Counting 문제다.

	Inversion Counting을 위하여 vector A_col(A 열)에는 식별번호를 저장하고,
	int B_col[MAX_IDX](B 열)에는 식별번호를 인덱스로 하고, 몇 번째인지를 값으로 저장한다.

	방문한 번호의 수를 빠르게 구하기 위하여 SegmentTree를 사용했다.
	query 함수에선 구간 B_col[A_col[i]](번호의 B 열 번째 수) ~ N - 1(오른쪽 끝)에 있는 방문한 번호의 수를 구한다.
	update 함수에선 기계의 식별번호에 해당하는 리프 노드와 부모 노드들을 갱신한다.
*/
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

constexpr auto MAX_IDX = 1000001;

struct SegmentTree
{
    int n;
    int tree_size;
    vector<long long> range_right_visit_cnt;
    SegmentTree(const vector<int> &idxs)
    {
        n = idxs.size();
        int height = (int)ceil(log2(n));
        tree_size = (1 << (height + 1));
        range_right_visit_cnt.resize(tree_size);
        init(0, n - 1, 1);
    }

    long long init(int left, int right, int node)
    {
        if (left == right)
            return range_right_visit_cnt[left] = 0;
        int mid = (left + right) / 2;
        init(left, mid, node * 2);
        init(mid + 1, right, node * 2 + 1);
        return range_right_visit_cnt[left] = 0;
    }

    long long query(int left, int right, int node, int node_left, int node_right)
    {
        if (right < node_left || node_right < left)
            return 0;
        if (left <= node_left && node_right <= right)
            return range_right_visit_cnt[node];
        int mid = (node_left + node_right) / 2;
        long long left_cnt = query(left, right, node * 2, node_left, mid);
        long long right_cnt = query(left, right, node * 2 + 1, mid + 1, node_right);
        return left_cnt + right_cnt;
    }

    long long query(int left)
    {
        return query(left, n - 1, 1, 0, n - 1);
    }

    long long update(int left, int right, int node, int idx)
    {
        if (idx < left || right < idx)
            return range_right_visit_cnt[node];
        if (left == right)
            return range_right_visit_cnt[node] = 1;
        int mid = (left + right) / 2;
        long long left_cnt = update(left, mid, node * 2, idx);
        long long right_cnt = update(mid + 1, right, node * 2 + 1, idx);
        return range_right_visit_cnt[node] = left_cnt + right_cnt;
    }

    long long update(int idx)
    {
        return update(0, n - 1, 1, idx);
    }
};

int N;
int B_col[MAX_IDX];

void input(vector<int> &A_col)
{
    cin >> N;
    for (int i = 0; i < N; ++i)
    {
        int idx;
        cin >> idx;
        A_col.push_back(idx);
    }
    for (int i = 0; i < N; ++i)
    {
        int idx;
        cin >> idx;
        B_col[idx] = i;
    }
}

long long solve(const vector<int> &A_col)
{
    long long ret = 0;
    SegmentTree st(A_col);
    for (int i = 0; i < N; ++i)
    {
        ret += st.query(B_col[A_col[i]]);
        st.update(B_col[A_col[i]]);
    }
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<int> A_col;
    input(A_col);
    long long ans = solve(A_col);
    cout << ans;
    return 0;
}