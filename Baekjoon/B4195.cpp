/*
	https://www.acmicpc.net/problem/4195

	string 형인 사람 이름을 int 형으로 바꾸어서 index로 활용한다.
	유니온 파인드 알고리즘을 활용하여 그룹을 만드는데,
	union을 해야 하는 경우 각 부모의 친구 네트워크 크기를 더해준다.
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