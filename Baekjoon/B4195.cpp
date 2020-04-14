/*
	https://www.acmicpc.net/problem/4195

	string ���� ��� �̸��� int ������ �ٲپ index�� Ȱ���Ѵ�.
	���Ͽ� ���ε� �˰����� Ȱ���Ͽ� �׷��� ����µ�,
	union�� �ؾ� �ϴ� ��� �� �θ��� ģ�� ��Ʈ��ũ ũ�⸦ �����ش�.
*/
#include <iostream>
#include <unordered_map>
using namespace std;

constexpr auto MAX_SIZE = 200001;

int parent[MAX_SIZE];
int net_size[MAX_SIZE];

void init(int F) {
	for (int i = 1; i <= F * 2; ++i) {
		parent[i] = i;
		net_size[i] = 1;
	}
}

int find(int index) {
	if (parent[index] == index) {
		return index;
	}

	return parent[index] = find(parent[index]);
}

void uni(int left_index, int right_index) {
	int left_parent = find(left_index);
	int right_parent = find(right_index);

	if (left_parent == right_parent) {
		return;
	}

	parent[right_parent] = left_parent;
	net_size[left_parent] += net_size[right_parent];
}

void solve() {
	int index = 1;
	unordered_map<string, int> people_index;

	int F;
	cin >> F;
	init(F);

	for (int i = 0; i < F; ++i) {
		string left, right;
		cin >> left >> right;

		if (people_index[left] == 0) {
			people_index[left] = index++;
		}

		if (people_index[right] == 0) {
			people_index[right] = index++;
		}

		uni(people_index[left], people_index[right]);
		cout << net_size[parent[people_index[left]]] << '\n';
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int tc;
	cin >> tc;
	for (int i = 0; i < tc; ++i) {
		solve();
	}

	return 0;
}