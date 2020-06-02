/*
	Course Schedule
	https://leetcode.com/problems/course-schedule/

	선행 조건이 주어질 때, 구간 "[0, numCourses)"의 과목을 모두 수강할 수 있는지 구하는 문제다.

	"진입 차수 위상 정렬"을 사용하여 선행 과목이 남아있지 않아서 수강 가능한 과목을 탐색했다.
	탐색이 끝나면, 수강할 수 있는 과목의 수가 'numCourses'만큼 돼서 모두 수강할 수 있는지 확인했다.
*/

class Solution
{
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites)
    {
        queue<int> 				q;
        vector<int>				degree(numCourses , 0);
        vector<vector<int> >	path(numCourses, vector<int>());
        
        for (const auto& ele : prerequisites)
        {
            path[ele[1]].push_back(ele[0]);
            ++degree[ele[0]];
        }
        for (int i = 0; i < numCourses; ++i)
            if (degree[i] == 0)
                q.push(i);
        while (!q.empty())
        {
            int course = q.front();
            
            q.pop();
            --numCourses;
            for (const auto& next : path[course])
            {
                --degree[next];
                if (degree[next] == 0)
                    q.push(next);
            }
        }
        return numCourses == 0;
    }
};