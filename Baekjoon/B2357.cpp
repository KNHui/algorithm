/*
    최솟값과 최댓값
    https://www.acmicpc.net/problem/2357

    최솟값과 최댓값을 둘 다 구해야 하기 때문에 구간 최소 트리를 사용하여 최솟값을 구하고
    구간 최소 트리를 수정하여 구간 최대 트리를 만들어서 최댓값을 구하면 된다.
*/
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct SegmentTree_Min
{
    int n;
    vector<int> range_min;
    SegmentTree_Min(const vector<int> &arr)
    {
        n = arr.size();
        range_min.resize(n * 4);
        init_min(arr, 0, n - 1, 1);
    }
    
    int init_min(const vector<int> &arr, int left, int right, int node)
    {
        if (left == right)
            return range_min[node] = arr[left];
        int mid = (left + right) / 2;
        int left_min = init_min(arr, left, mid, node * 2);
        int right_min = init_min(arr, mid + 1, right, node * 2 + 1);
        
        return range_min[node] = min(left_min, right_min);
    }
	
    int query_min(int left, int right, int node, int node_left, int node_right)
    {
        if (right < node_left || node_right < left)
            return 1000000001;
        if (left <= node_left && node_right <= right)
            return range_min[node];
        int mid = (left + right) / 2;
        int left_min = query_min(left, right, node * 2, node_left, mid);
        int right_min = query_min(left, right, node * 2 + 1, mid + 1, node_right);
        return min(left_min, right_min);
    }
    
    int query_min(int left, int right)
	{
		return query_min(left, right, 1, 0, n - 1);
	}
};

struct SegmentTree_Max
{
    int n;
    vector<int> range_max;
    SegmentTree_Max(const vector<int> &arr)
    {
        n = arr.size();
        range_max.resize(n * 4);
        init_max(arr, 0, n - 1, 1);
    }
    
    int init_max(const vector<int> &arr, int left, int right, int node)
    {
        if (left == right)
            return range_max[node] = arr[left];
        int mid = (left + right) / 2;
        int left_max = init_max(arr, left, mid, node * 2);
        int right_max = init_max(arr, mid + 1, right, node * 2 + 1);
        return range_max[node] = max(left_max, right_max);
    }
    
    int query_max(int left, int right, int node, int node_left, int node_right)
    {
        if (right < node_left || node_right < left)
            return -1;
        if (left <= node_left && node_right <= right)
            return range_max[node];
        int mid = (left + right) / 2;
        int left_max = query_max(left, right, node * 2, node_left, mid);
        int right_max = query_max(left, right, node * 2 + 1, mid + 1, node_right);
        return max(left_max, right_max);
    }
    
    int query_max(int left, int right)
	{
		return query_max(left, right, 1, 0, n - 1);
	}
};


int N, M;
vector<int> nums;

void init()
{
    cin >> N >> M;
    for (int i = 0; i < N; ++i)
    {
        int num;
        cin >> num;
        nums.push_back(num);
    }
}

void solve()
{
    SegmentTree_Min st_min(nums);
    SegmentTree_Max st_max(nums);
    for (int i = 0; i < M; ++i)
    {
        int left, right;
        cin >> left >> right;
        cout << st_min.query_min(left - 1, right - 1) << ' ' << st_max.query_max(left - 1, right - 1) << '\n';
    }
}

int main()
{
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);
   
   init();
   solve();
   return 0;
}