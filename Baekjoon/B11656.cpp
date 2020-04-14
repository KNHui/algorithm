/*
    ���̻� �迭
    https://www.acmicpc.net/problem/11656

    0.  ���̻� �迭�� ����Ͽ�, �ð� ���⵵�� O(NlgNlgN) ���� Ǯ����.
        �ð� ���⵵�� O(NlogN)�� ��ĵ� ������, O(NlogN) ����� �ʹ� �����ؼ�
        �ڵ� �ۼ��� �ð��� ���� ��� ������ �˰��� ��ȸ������ ��κ� �ڵ尡
        �����ϰ� �ӵ��� ����� ���� O(NlgNlgN) ����� ���ٰ� �Ѵ�.
        �׷���, O(NlgNlgN) ������� ������ �ذ��Ͽ���.
        �׷��� O(NlogN) ��ĵ� �����Ͽ� ī���� ���Ŀ� ���ؼ�
        �� �����ϴ� �͵� ���� �� ����.

    1.  vector<int>perm 
        -   ���� ��ġ�� ������ ������ �ִ� �迭
        -   ���� ������ ���ĵ�
        ex. S = "banbcd"�� ��, perm[0] = 1�̶�� ����
            S[1...] ���̻�(anbcd)�� ���� ������ ���� �����ٴ� ���� �ǹ��Ѵ�.

    2. group[i]
        -   S[i..]�� �׷� ��ȣ
        -   �׷� ��ȣ�� �������� ���� ������ �� ����
        -   ���� ������ ���ĵ� perm�� ������
            ������ t ���ڸ� �������� ����� next_group�� ����
        -   group[perm[0]]�� ���� ������ ���� ���� ���̻���
            ���� ��ġ�� �׷� ��ȣ�̹Ƿ� 0�� ����
        -   S�� ���̸� n�̶� �� ��, group[n]�� S[n...]��
            �׷� ��ȣ�̰� S[n...]�� ���̰� 0�� ���̻��̹Ƿ�
            �׻� ���� ������ ���� �տ� ����.
            �׷��� group[n]�� -1�� �����Ͽ� �׻� �׷� ��ȣ�� ���� �۵��� ��.
        
*/
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

struct Comparator
{
    vector<int> group;
    int t;
    Comparator(vector<int> _group, int _t) : group(_group), t(_t)
    {
        group = _group;
        t = _t;
    }

    bool operator()(int a, int b)
    {
        if (group[a] != group[b])
            return group[a] < group[b];
        // a + t�� ���ڿ� ���� n ����
        // group[a]�� group[b]�� �������� �� ���̻��� ���̰� t �̻��̾�� ��
        // �׷��� group[n]�� ���� ������ ������ ��
        return group[a + t] < group[b + t];
    }
};

string S;

vector<int> getSuffixAry(string s)
{
    int n = s.size();
    int t = 1;

    vector<int> group(n + 1); // group[i] = S[i..]�� �׷� ��ȣ
    group[n] = -1;
    vector<int> perm(n); // ���̻��� ���� ��ġ
    for (int i = 0; i < n; ++i)
    {
        group[i] = s[i];
        perm[i] = i;
    }

    while (t < n)
    {
        Comparator compareUsing2T(group, t);
        sort(perm.begin(), perm.end(), compareUsing2T);

        t *= 2;
        if (t >= n)
            break;

        vector<int> newGroup(n + 1);
        newGroup[n] = -1;
        newGroup[perm[0]] = 0;
        for (int i = 1; i < n; ++i)
        {
            if (compareUsing2T(perm[i - 1], perm[i]))
                newGroup[perm[i]] = newGroup[perm[i - 1]] + 1;
            else
                newGroup[perm[i]] = newGroup[perm[i - 1]];
        }

        group = newGroup;
    }

    return perm;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> S;
    vector<int> suffixAry = getSuffixAry(S);

    for (size_t i = 0; i < suffixAry.size(); ++i)
    {
        cout << S.c_str() + suffixAry[i] << '\n';
    }

    //while (1) {}
    return 0;
}