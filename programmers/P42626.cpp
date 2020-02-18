/*
    더 맵게
    https://programmers.co.kr/learn/courses/30/lessons/42626

    모든 음식들의 스코빌 지수를 K 이상으로 만들기 위해서
    스코빌 지수가 가장 낮은 음식과 두 번째로 낮은 음식을 섞어야 한다.

    그렇기에 우선순위 큐를 오름차순으로 설정한 뒤, 음식들을 우선순위 큐에 담는다.
    그 후에 가장 덜 매운 음식의 스코빌 지수가 K 이상이 될 때까지 섞는 것을 반복한다.
    
    만약 우선 순위 큐의 top에 있는 음식의 스코빌 지수가 K 미만이라면,
    음식이 하나만 남아서 섞지 못해 반복문이 종료되었으므로 -1을 리턴한다.
*/
#include <vector>
#include <queue>

using namespace std;

int mix(int first, int second)
{
    return first + second * 2;    
}

int solution(vector<int> scoville, int K)
{
    int answer = 0;
    priority_queue<int, vector<int>, greater<int>> pq;
    for (size_t index = 0; index < scoville.size(); ++index)
        pq.push(scoville[index]);

    while (pq.size() >= 2 && pq.top() < K)
    {
        int first = pq.top();
        pq.pop();
        int second = pq.top();
        pq.pop();
        pq.push(mix(first, second));
        ++answer;
    }

    if (pq.top() < K)
        return -1;
    return answer;
}