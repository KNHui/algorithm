/*
	Flood Fill
	https://leetcode.com/problems/flood-fill/

	좌표 "(sr, sc)"와 같은 색으로 연결되어 있는 픽셀들을 'newColor'로 'flood fill'하는 문제다.

	좌표 "(sr, sc)"를 시작으로 '너비 우선 탐색'으로 'flood fill'을 수행했다.
	만약 좌표 "(sr, sc)"의 색이 'newColor'와 같다면, 'flood fill'을 수행해도 변화가 없어서 바로 함수를 종료했다.
*/

class Solution
{
private:
	size_t _r, _c;
public:
	inline bool				checkRange(int r, int c)
	{
		return r >= 0 && r < _r && c >= 0 && c < _c;
	}

	vector<vector<int> >	floodFill(vector<vector<int> >& image, int sr, int sc, int newColor)
	{
		if (image[sr][sc] == newColor)
			return image;
		queue<int> rq, cq;

		_r = image.size();
		_c = image[0].size();
		rq.push(sr);
		cq.push(sc);
		while (!rq.empty())
		{
			int r = rq.front();
			int c = cq.front();

			rq.pop();
			cq.pop();
			for (int i = 0; i < 4; ++i)
			{
				int nr = r + dr[i];
				int nc = c + dc[i];

				if (checkRange(nr, nc) && image[nr][nc] == image[sr][sc] && (nr != sr || nc != sc))
				{
					image[nr][nc] = newColor;
					rq.push(nr);
					cq.push(nc);
				}
			}
		}
		image[sr][sc] = newColor;
		return image;
	}
};