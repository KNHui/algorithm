/*
    접미사 배열
    https://www.acmicpc.net/problem/11656

    0.  접미사 배열을 사용하여, 시간 복잡도가 O(NlgNlgN) 만에 풀었다.
        시간 복잡도가 O(NlogN)인 방식도 있지만, O(NlogN) 방식은 너무 복잡해서
        코드 작성에 시간이 많이 들기 때문에 알고리즘 대회에서는 대부분 코드가
        간결하고 속도도 충분히 빠른 O(NlgNlgN) 방식을 쓴다고 한다.
        그래서, O(NlgNlgN) 방식으로 문제를 해결하였다.
        그러나 O(NlogN) 방식도 공부하여 카운팅 정렬에 대해서
        더 공부하는 것도 좋을 것 같다.

    1.  vector<int>perm 
        -   시작 위치를 값으로 가지고 있는 배열
        -   사전 순으로 정렬됨
        ex. S = "banbcd"일 때, perm[0] = 1이라는 것은
            S[1...] 접미사(anbcd)가 사전 순으로 제일 빠르다는 것을 의미한다.

    2. group[i]
        -   S[i..]의 그룹 번호
        -   그룹 번호가 작을수록 사전 순으로 더 빠름
        -   사전 순으로 정렬된 perm을 가지고
            다음에 t 글자를 기준으로 사용할 next_group을 만듦
        -   group[perm[0]]은 사전 순으로 가장 빠른 접미사의
            시작 위치의 그룹 번호이므로 0을 대입
        -   S의 길이를 n이라 할 때, group[n]은 S[n...]의
            그룹 번호이고 S[n...]은 길이가 0인 접미사이므로
            항상 사전 순으로 제일 앞에 있음.
            그래서 group[n]에 -1을 대입하여 항상 그룹 번호가 가장 작도록 함.
        
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
        // a + t는 문자열 길이 n 이하
        // group[a]와 group[b]가 같을려면 두 접미사의 길이가 t 이상이어야 함
        // 그래서 group[n]을 작은 값으로 만들어야 함
        return group[a + t] < group[b + t];
    }
};

string S;

vector<int> getSuffixAry(string s)
{
    int n = s.size();
    int t = 1;

    vector<int> group(n + 1); // group[i] = S[i..]의 그룹 번호
    group[n] = -1;
    vector<int> perm(n); // 접미사의 시작 위치
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